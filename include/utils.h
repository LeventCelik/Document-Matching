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

#define DEBUG true

#define BLOCK_SIZE 3

/**
 * @brief Simple list node holding
 * a char value and a pointer
 * to the next node.
 */
typedef struct node node;
typedef struct suffix suffix;
typedef struct block block;
struct node {
	int val;
	node *next;
	node *prev;
};
struct suffix {
	int index;
	int lcp;
};

struct block {
	int nums[BLOCK_SIZE];
};

block create_block();

int *radix_sort(block *blocks, int block_sz, int alphabet_sz);

void counting_sort(int *indices, block *blocks, int block_sz, int alphabet_sz,
				   int index);

/**
 * @brief Creates a random array where elements
 * are in the range 1...max
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
bool is_arr_sorted(int *arr, int sz);

void print_int_array(int *arr, int sz);

void print_block(block b);

void print_block_array(block *blocks, int sz);

void print_indexed_block_array(block *blocks, int sz, int *indices);

#endif /* UTILS_H */