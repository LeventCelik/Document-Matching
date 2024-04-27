#include "utils.h"

node *new_node(int size) {
	node *n = (node *)malloc(sizeof(node));
	n->size = size;
	n->data = (int *)malloc(size * sizeof(int));
	n->children = (node **)malloc((size + 1) * sizeof(node *));
	for (int i = 0; i < size; i++) {
		n->data[i] = 0;
		n->children[i] = NULL;
	}
	n->children[size] = NULL;
	return n;
}

void free_node(node *n) {
	free(n->data);
	free(n->children);
	free(n);
}

bool lcp_array_check(int *str, int *suffix_array, int *lcp, int n) {
	for (int i = 1; i < n; i++) {
		int len = 0;
		while (suffix_array[i] + len < n && suffix_array[i - 1] + len < n &&
			   str[suffix_array[i] + len] == str[suffix_array[i - 1] + len]) {
			len++;
		}
		if (len != lcp[i-1]) {
			printf("Error at %d: %d != %d\n", i, len, lcp[i]);
			return false;
		}
	}
	return true;
}

bool suffix_array_check(int *str, int n, int *suffix_array) {
	for (int i = 1; i < n; i++) {
		if (!compare_suffixes(str, n, suffix_array[i - 1], suffix_array[i])) {
			return false;
		}
	}
	return true;
}

bool compare_suffixes(int *str, int n, int i, int j) {
	while (i < n && j < n) {
		if (str[i] != str[j]) {
			return str[i] < str[j];
		}
		i++;
		j++;
	}
	return i == n;
}

int *radix_sort(int *indices, int sz, int *str, int n, int alphabet_sz,
				int digits) {
	for (int i = digits - 1; i >= 0; i--) {
		counting_sort(indices, sz, str, n, alphabet_sz, i);
	}
	return indices;
}

/**
 * @brief Stable counting sort, using the keys str[indices[i]+index].
 * Sorts the indices array. Used as reference the answer at
 * https://stackoverflow.com/questions/2572195/how-is-counting-sort-a-stable-sort.
 *
 * @param indices
 * @param sz
 * @param str
 * @param n
 * @param alphabet_sz
 * @param index
 */
void counting_sort(int *indices, int sz, int *str, int n, int alphabet_sz,
				   int index) {
	int *counts = (int *)calloc(alphabet_sz + 1, sizeof(int));
	// Count the elements
	for (int i = 0; i < sz; i++) {
		int num = str[indices[i] + index];
		counts[num]++;
	}
	// Make the counts cumulative for stability
	for (int i = 1; i < alphabet_sz + 1; i++) {
		counts[i] += counts[i - 1];
	}
	int *sorted = (int *)malloc((sz + 3) * sizeof(int));
	// Iterate backwards, also for stability
	for (int i = sz - 1; i >= 0; i--) {
		int num = str[indices[i] + index];
		counts[num]--;
		sorted[counts[num]] = indices[i];
	}
	// Transfer data to the input array
	for (int i = 0; i < sz; i++) {
		indices[i] = sorted[i];
	}
	free(counts);
	free(sorted);
}

bool equal_blocks(int b1, int b2, int *str) {
	return str[b1] == str[b2] && str[b1 + 1] == str[b2 + 1] &&
		   str[b1 + 2] == str[b2 + 2];
}

int *random_string(int size, int max) {
	int *array = (int *)malloc((size + 3) * sizeof(int));
	for (int i = 0; i < size; i++) {
		array[i] = rand() % (max) + 1;
	}
	array[size] = array[size + 1] = array[size + 2] = 0;
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

void print_blocks(int *indices, int sz, int *str, int n) {
	printf("%d blocks: [\n", sz);
	for (int i = 0; i < sz; i++) {
		printf("\t%d: [%d, %d, %d]\n", i, str[indices[i]], str[indices[i] + 1],
			   str[indices[i] + 2]);
	}
	printf("]\n");
}
