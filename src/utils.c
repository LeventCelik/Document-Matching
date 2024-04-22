#include "utils.h"

int *radix_sort(block *blocks, size_t sz) {}

int *counting_sort(block *blocks, size_t sz, int index) {
	// int *sorted = (int *)malloc(block_size * sizeof(int));
	// list_node **counts = (list_node **)malloc(block_size * sizeof(list_node
	// *));
	// // TODO: Virtual initialization
	// for (int i = 0; i < block_size; i++) {
	// 	counts[i] = NULL;
	// }
	// for (int i = 0; i < block_size; i++) {
	// 	int num = char_numeric_value(actual_arr[indices[i]][index]);
	// 	list_node *node = (list_node *)malloc(sizeof(list_node));
	// 	node->val = i;
	// 	node->next = NULL;
	// 	// TODO: Make this O(1) by keeping doubly linked list and an end pointed
	// 	list_node *head = counts[num];
	// 	while (head != NULL && head->next != NULL) {
	// 		head = head->next;
	// 	}
	// 	if (head != NULL) {
	// 		head->next = node;
	// 	} else {
	// 		counts[num] = node;
	// 	}
	// }
	// int j = 0;
	// int k = 0;
	// while (j < max + 1) {
	// 	if (counts[j] == NULL) {
	// 		j++;
	// 		continue;
	// 	}
	// 	list_node *node = counts[j];
	// 	counts[j] = counts[j]->next;
	// 	indices[k++] = node->val;
	// 	// TODO: Safety cleanup using global array
	// 	free(node);
	// 	node = NULL;
	// }
	// free(counts);
}

unsigned int *random_int_array(int size, int max) {
	unsigned int *array = (unsigned int *)malloc(size * sizeof(unsigned int));
	for (int i = 0; i < size; i++) {
		array[i] = rand() % (max + 1);
	}
	return array;
}

bool is_arr_sorted(unsigned int *arr, size_t sz) {
	for (int i = 1; i < sz; i++) {
		if (arr[i - 1] > arr[i]) {
			return false;
		}
	}
	return true;
}

void print_int_array(int *arr, size_t sz) {
	printf("[");
	for (int i = 0; i < sz - 1; i++) {
		printf("%d, ", arr[i]);
	}
	printf("%d]\n", arr[sz - 1]);
}