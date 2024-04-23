#include "string.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG false

#define BLOCK_SIZE 3

/**
 * @brief Simple list node holding
 * a char value and a pointer
 * to the next node.
 */
typedef struct list_node list_node;
typedef struct suffix_array suffix_array;
typedef struct block block;
struct list_node {
	int *val;
	list_node *next;
	list_node *prev;
};
struct suffix_array {
	int index;
	int lcp;
};

struct block {
	int nums[BLOCK_SIZE];
};

block create_block() {
	block b;
	for (int i = 0; i < BLOCK_SIZE; i++) {
		b.nums[i] = -1;
	}
	return b;
}

int *radix_sort(block *blocks, size_t sz);

int *counting_sort(block *blocks, size_t sz, int index);

/**
 * @brief Creates a random array where elements
 * are in the range 0...max
 *
 * @param size Size of the array
 * @param max Upper bound of the random numbers
 * @return unsigned int* // TODO: unsigned refactoring
 */
unsigned int *random_int_array(int size, int max);

/**
 * @brief Checks if an int array is sorted
 *
 * @param arr
 * @param sz
 * @return true if the array is sorted
 */
bool is_arr_sorted(int *arr, size_t sz);

inline void print_int_array(int *arr, size_t sz) {
	printf("[");
	for (int i = 0; i < sz - 1; i++) {
		printf("%d, ", arr[i]);
	}
	printf("%d]\n", arr[sz - 1]);
}

inline void print_block(block b) {
	printf("Block: [");
	for (int i = 0; i < BLOCK_SIZE - 1; i++) {
		printf("%d, ", b.nums[i]);
	}
	printf("%d]\n", b.nums[BLOCK_SIZE - 1]);
}

inline void print_block_array(block *blocks, size_t sz) {
	printf("%lu blocks: [\n", sz);
	for (int i = 0; i < sz; i++) {
		printf("\t%d: ", i);
		print_block(blocks[i]);
	}
	printf("]\n");
}