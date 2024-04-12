#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

/**
 * @brief Simple list node holding
 * a generic value and a pointer
 * to the next node.
 */
typedef struct list_node list_node;

struct list_node {
    void* val;
    list_node* next;
};

/**
 * @brief Sorts an array in linear time.
 * @param arr 
 * @param max Integer magnitude upper bound
 */
void counting_sort(void **arr, size_t sz, int max, int numeric_value(void*));

/**
 * @brief Creates a random array where elements
 * are in the range 0...max
 * 
 * @param size Size of the array
 * @param max Upper bound of the random numbers
 * @return unsigned int* 
 */
unsigned int *random_array(int size, int max);

/**
 * @brief Checks if an array is sorted
 * 
 * @param arr 
 * @param sz 
 * @return true if the array is sorted
 */
bool is_sorted(unsigned int *arr, size_t sz);