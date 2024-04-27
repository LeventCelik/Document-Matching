/**
 * @file utils.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-04-22
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef UTILS_H
#define UTILS_H

#include "string.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG false

bool suffix_array_check(int *str, int n, int *suffix_array);

bool compare_suffixes(int *str, int n, int i, int j);

int *radix_sort(int *indices, int sz, int *str, int n, int alphabet_sz,
				int digits);

void counting_sort(int *indices, int sz, int *str, int n, int alphabet_sz,
				   int index);

bool equal_blocks(int b1, int b2, int *str);
/**
 * @brief Creates a random array where elements
 * are in the range 1...max
 *
 * @param size Size of the array
 * @param max Upper bound of the random numbers
 * @return unsigned int* // TODO: unsigned refactoring
 */
int *random_int_array(int size, int max);

/**
 * @brief Checks if an int array is sorted
 *
 * @param arr
 * @param sz
 * @return true if the array is sorted
 */
bool is_arr_sorted(int *arr, int sz);

void print_int_array(int *arr, int sz);

void print_blocks(int *indices, int sz, int *str, int n);
#endif /* UTILS_H */