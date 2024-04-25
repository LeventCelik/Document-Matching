#include "utils.h"

block create_block(int index) {
	block b;
	b.og_index = index;
	for (int i = 0; i < BLOCK_SIZE; i++) {
		b.nums[i] = 0;
	}
	return b;
}

bool equal_blocks(block b1, block b2) {
	for (int i = 0; i < BLOCK_SIZE; i++) {
		if (b1.nums[i] != b2.nums[i])
			return false;
	}
	return true;
}

tuple create_tuple(int first, int second, int index) {
	tuple t;
	t.first = first;
	t.second = second;
	t.og_index = index;
	return t;
}

int *tuple_radix_sort(tuple *tuples, int tuple_count, int alphabet_sz) {
	int *indices = (int *)malloc(tuple_count * sizeof(int));
	if (indices == NULL) {
		fprintf(stderr,
				"Tuple radix sort: Failed to allocate memory for indices.\n");
		return NULL;
	}

	for (int i = 0; i < tuple_count; i++) {
		indices[i] = i;
	}
	tuple_counting_sort(indices, tuples, tuple_count, alphabet_sz, 2);
	tuple_counting_sort(indices, tuples, tuple_count, alphabet_sz, 1);
	return indices;
}

void tuple_counting_sort(int *indices, tuple *tuples, int tuple_count,
						 int alphabet_sz, int index) {
	node **buckets = (node **)malloc((alphabet_sz + 1) * sizeof(node *));

	// TODO: Virtual initialization
	for (int i = 0; i < alphabet_sz + 1; i++) {
		buckets[i] = NULL;
	}

	for (int i = 0; i < tuple_count; i++) {
		int num =
			index == 2 ? tuples[indices[i]].second : tuples[indices[i]].first;
		node *n = (node *)malloc(sizeof(node));
		n->val = indices[i];
		n->next = NULL;
		// TODO: Make this O(1) by keeping doubly linked list and an end pointed
		node *head = buckets[num];
		while (head != NULL && head->next != NULL) {
			head = head->next;
		}
		if (head != NULL) {
			head->next = n;
		} else {
			buckets[num] = n;
		}
	}
	int j = 0;
	int k = 0;

	while (j < alphabet_sz + 1) {
		if (buckets[j] == NULL) {
			j++;
			continue;
		}
		node *n = buckets[j];
		buckets[j] = buckets[j]->next;
		indices[k++] = n->val;
		// TODO: Safety cleanup using global array
		free(n);
		n = NULL;
	}
	free(buckets);
	buckets = NULL;
}

int *radix_sort(block *blocks, int block_count, int alphabet_sz, int *ranks,
				bool *unique) {
	int *indices = (int *)malloc(block_count * sizeof(int));
	if (indices == NULL) {
		// TODO: Do the same in other malloc calls well.
		fprintf(stderr, "Radix sort: Failed to allocate memory for indices.\n");
		return NULL;
	}

	// TODO: Virtual init
	for (int i = 0; i < block_count; i++) {
		indices[i] = i;
	}
	for (int i = BLOCK_SIZE - 1; i >= 0; i--) {
		counting_sort(indices, blocks, block_count, alphabet_sz, i);
	}
	int rank = 0;
	for (int i = 1; i < block_count; i++) {
		if (!equal_blocks(blocks[indices[i - 1]], blocks[indices[i]]))
			rank++;
		else
			*unique = false;
		ranks[indices[i]] = rank;
	}
	return indices;
}

void counting_sort(int *indices, block *blocks, int block_count,
				   int alphabet_sz, int index) {
	node **buckets = (node **)malloc((alphabet_sz + 1) * sizeof(node *));

	// TODO: Virtual initialization
	for (int i = 0; i < alphabet_sz + 1; i++) {
		buckets[i] = NULL;
	}

	for (int i = 0; i < block_count; i++) {
		int num = blocks[indices[i]].nums[index];
		node *n = (node *)malloc(sizeof(node));
		n->val = indices[i];
		n->next = NULL;
		// TODO: Make this O(1) by keeping doubly linked list and an end pointed
		node *head = buckets[num];
		while (head != NULL && head->next != NULL) {
			head = head->next;
		}
		if (head != NULL) {
			head->next = n;
		} else {
			buckets[num] = n;
		}
	}
	int j = 0;
	int k = 0;

	while (j < alphabet_sz + 1) {
		if (buckets[j] == NULL) {
			j++;
			continue;
		}
		node *n = buckets[j];
		buckets[j] = buckets[j]->next;
		indices[k++] = n->val;
		// TODO: Safety cleanup using global array
		free(n);
		n = NULL;
	}
	free(buckets);
	buckets = NULL;
}

int *random_int_array(int size, int max) {
	int *array = (int *)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++) {
		array[i] = rand() % (max) + 1;
	}
	return array;
}

bool is_arr_sorted(int *arr, int sz) {
	for (int i = 1; i < sz; i++) {
		if (arr[i - 1] > arr[i]) {
			return false;
		}
	}
	return true;
}

void print_int_array(int *arr, int sz) {
	printf("[");
	for (int i = 0; i < sz - 1; i++) {
		printf("%d, ", arr[i]);
	}
	printf("%d]\n", arr[sz - 1]);
}

void print_block(block b) {
	printf("Block (%d): [", b.og_index);
	for (int i = 0; i < BLOCK_SIZE - 1; i++) {
		printf("%d, ", b.nums[i]);
	}
	printf("%d]\n", b.nums[BLOCK_SIZE - 1]);
}

void print_block_array(block *blocks, int sz) {
	printf("%d blocks: [\n", sz);
	for (int i = 0; i < sz; i++) {
		printf("\t%d. ", i);
		print_block(blocks[i]);
	}
	printf("]\n");
}

void print_indexed_block_array(block *blocks, int sz, int *indices) {
	printf("%d blocks: [\n", sz);
	for (int i = 0; i < sz; i++) {
		printf("\t%d. ", i);
		print_block(blocks[indices[i]]);
	}
	printf("]\n");
}

void print_tuple(tuple t) {
	printf("Tuple (%d): (%d, %d)\n", t.og_index, t.first, t.second);
}

void print_tuple_array(tuple *tuples, int sz) {
	printf("%d tuples: [\n", sz);
	for (int i = 0; i < sz; i++) {
		printf("\t%d. ", i);
		print_tuple(tuples[i]);
	}
	printf("]\n");
}

void print_indexed_tuple_array(tuple *tuples, int sz, int *indices) {
	printf("%d tuples: [\n", sz);
	for (int i = 0; i < sz; i++) {
		printf("\t%d. ", i);
		print_tuple(tuples[indices[i]]);
	}
	printf("]\n");
}