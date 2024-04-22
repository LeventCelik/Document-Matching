#include "string.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG false

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
	int *indices;
	int *lcps;
};

struct block {
	int nums[3];
};

int *block_radix_sort(int *blocks, size_t block_size, int *arr,
					  size_t arr_size);

int *counting_sort(int **arr, size_t sz, int index);

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

void print_int_array(int *arr, size_t sz);