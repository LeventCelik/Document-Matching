#include "utils.h"

block create_block() {
	block b;
	for (int i = 0; i < BLOCK_SIZE; i++) {
		b.nums[i] = 0;
	}
	return b;
}

int *radix_sort(block *blocks, int block_sz, int alphabet_sz) {
	// TODO: Handle non-unique blocks
	int *indices = (int *)malloc(block_sz * sizeof(int));
	if (indices == NULL) {
		// TODO: Do the same in other malloc calls well.
		fprintf(stderr, "Radix sort: Failed to allocate memory for indices.\n");
		return NULL;
	}

	// TODO: Virtual init
	for (int i = 0; i < block_sz; i++) {
		indices[i] = i;
	}
	for (int i = BLOCK_SIZE - 1; i >= 0; i--) {
		counting_sort(indices, blocks, block_sz, alphabet_sz, i);
	}
	return indices;
}

void counting_sort(int *indices, block *blocks, int block_sz, int alphabet_sz,
				   int index) {
	node **buckets = (node **)malloc((alphabet_sz + 1) * sizeof(node *));

	// TODO: Virtual initialization
	for (int i = 0; i < alphabet_sz + 1; i++) {
		buckets[i] = NULL;
	}

	for (int i = 0; i < block_sz; i++) {
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

unsigned int *random_int_array(int size, int max) {
	unsigned int *array = (unsigned int *)malloc(size * sizeof(unsigned int));
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
	printf("Block: [");
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