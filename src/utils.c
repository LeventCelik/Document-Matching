#include "utils.h"

void str_counting_sort_by_char(char **arr, size_t sz, int index) {
	int max = char_numeric_value('z');
	list_node **counts = (list_node **)malloc((max + 1) * sizeof(list_node *));
	// TODO: Virtual initialization
	for (int i = 0; i < max + 1; i++) {
		counts[i] = NULL;
	}
	for (int i = 0; i < sz; i++) {
		int num = char_numeric_value(arr[i][index]);
		list_node *node = (list_node *)malloc(sizeof(list_node));
		node->val = arr[i];
		node->next = NULL;
		// TODO: Make this O(1) by keeping doubly linked list and an end pointed
		list_node *head = counts[num];
		while (head != NULL && head->next != NULL) {
			head = head->next;
		}
		if (head != NULL) {
			head->next = node;
		} else {
			counts[num] = node;
		}
	}
	int j = 0;
	int k = 0;
	while (j < max + 1) {
		if (counts[j] == NULL) {
			j++;
			continue;
		}
		list_node *node = counts[j];
		counts[j] = counts[j]->next;
		arr[k++] = node->val;
		// TODO: Safety cleanup using global array
		free(node);
		node = NULL;
	}
	free(counts);
}

int char_numeric_value(char c) {
	if (c - 'a' >= 0) {
		return 'Z' - 'A' + 1 + c - 'a';
	}
	return c - 'A';
}

unsigned int *random_int_array(int size, int max) {
	unsigned int *array = (unsigned int *)malloc(size * sizeof(unsigned int));
	for (int i = 0; i < size; i++) {
		array[i] = rand() % (max + 1);
	}
	return array;
}

char **random_str_array(int size, int len) {
	char **arr = (char **)malloc(size * sizeof(char *));
	for (int i = 0; i < size; i++) {
		arr[i] = random_char_array(len);
	}
	return arr;
}

char *random_char_array(int size) {
	char *array = (char *)malloc(size * sizeof(char));
	int range = ('z' - 'a' + 1);
	for (int i = 0; i < size; i++) {
		int num = rand() % (2 * range);
		if (num < range) {
			array[i] = 'a' + num;
		} else {
			array[i] = 'A' + num - range;
		}
	}
	return array;
}

bool is_int_arr_sorted(unsigned int *arr, size_t sz) {
	for (int i = 1; i < sz; i++) {
		if (arr[i - 1] > arr[i]) {
			return false;
		}
	}
	return true;
}

bool is_str_array_sorted(char **arr, size_t sz, int str_len) {
	for (int i = 0; i < sz - 1; i++) {
		if (strncmp(arr[i], arr[i + 1], str_len) > 0) {
			printf("Strings #%d and #%d are out of order.\n", i + 1, i + 2);
			// print_string_subarray(arr, sz, strlen(arr[i]), i, i+5);
			print_string_array(arr, sz, str_len);
			return false;
		}
	}
	return true;
}

void print_string_array(char **arr, size_t sz, int str_len) {
	print_string_subarray(arr, sz, str_len, 0, sz);
}

void print_string_subarray(char **arr, size_t sz, int str_len, int begin,
						   int end) {
	for (int i = begin; i < end && i < sz; i++) {
		printf("%d:", i + 1);
		for (int j = 0; j < str_len; j++) {
			printf("%c", arr[i][j]);
		}
		printf("\n");
	}
}

// Older version of the functions:

// REASON FOR CHANGE: Not stable, only works on integers.

// void counting_sort(unsigned int* arr, size_t sz, int max) {
// 	int counts[max+1];
// 	// TODO: Virtual initialization
// 	memset(counts, 0, (max+1)*sizeof(int));
// 	for (int i = 0; i < sz; i++) {
// 		counts[arr[i]] += 1;
// 	}
// 	int j = 0;
// 	int k = 0;
// 	while (j < max+1) {
// 		if (counts[j] == 0) {
// 			j++;
// 			continue;
// 		}
// 		counts[j] -= 1;
// 		arr[k++] = j;
// 	}
// }

//--------------------------------------------------------

// REASON FOR CHANGE: Requires explicit conversion between char* to void* twice,
// unnecessarily generic.

// void counting_sort(void **arr, size_t sz, int max, int numeric_value(void*))
// { 	list_node *counts[max+1];
// 	// TODO: Virtual initialization
// 	// TODO: Safety cleanup using global array
// 	memset(counts, 0, (max+1)*sizeof(list_node*));
// 	for (int i = 0; i < sz; i++) {
// 		int num = numeric_value(arr[i]);
// 		list_node *node = (list_node*) malloc(sizeof(list_node));
// 		node->val = arr[i];
// 		node->next = counts[num];
// 		counts[num] = node;
// 	}
// 	int j = 0;
// 	int k = 0;
// 	while (j < max+1) {
// 		if (counts[j] == NULL) {
// 			j++;
// 			continue;
// 		}
// 		list_node *node = counts[j];
// 		counts[j] = counts[j]->next;
// 		arr[k++] = node->val;
// 		free(node);
// 	}
// }