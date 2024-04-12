#include "utils.h"

void counting_sort(void **arr, size_t sz, int max, int numeric_value(void*)) {
	list_node* counts[max+1];
	// TODO: Virtual initialization
	// TODO: Safety cleanup using global array
	memset(counts, 0, (max+1)*sizeof(list_node*));
	for (int i = 0; i < sz; i++) {
		int num = numeric_value(arr[i]);
		list_node* node = (list_node*)malloc(sizeof(list_node));
		node->val = arr[i];
		node->next = counts[num];
		counts[num] = node;
	}
	int j = 0;
	int k = 0;
	while (j < max+1) {
		if (counts[j] == NULL) {
			j++;
			continue;
		}
		list_node* node = counts[j];
		counts[j] = counts[j]->next;
		arr[k++] = node->val;
		free(node);
	}
}



// Creates a random array where elements are in the range 0...max
unsigned int *random_array(int size, int max) {
    unsigned int *array = (unsigned int*)malloc(size*sizeof(unsigned int));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % (max + 1);
    }
    return array;
}

bool is_sorted(unsigned int *arr, size_t sz) {
	for (int i = 1; i < sz; i++) {
		if (arr[i-1] > arr[i]) {
			return false;
		}
	}
	return true;
}


// Older version of the functions:

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