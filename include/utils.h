#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

/**
 * @brief Sorts an array in linear time.
 * TODO: Make it stable
 * @param arr 
 * @param max Integer magnitude upper bound
 */
void counting_sort(unsigned int *arr, size_t sz, int max);

/**
 * @brief Creates a random array where elements are in the range 0...max
 * 
 * @param size 
 * @param max 
 * @return unsigned int* 
 */
unsigned int *random_array(int size, int max);

/**
 * @brief Checks if an array is sorted
 * 
 * @param arr 
 * @param sz 
 * @return true 
 * @return false 
 */
bool is_sorted(unsigned int *arr, size_t sz);