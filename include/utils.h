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
struct node {
	int val;
	node *next;
	node *prev;
};
typedef struct {
	int nums[BLOCK_SIZE];
	int og_index;
} block;

block create_block(int index);
bool equal_blocks(block b1, block b2);

typedef struct {
	int first;
	int second;
	int og_index;
} tuple;

tuple create_tuple(int first, int second, int index);

int *tuple_radix_sort(tuple *tuples, int tuple_count, int alphabet_sz);

void tuple_counting_sort(int *indices, tuple *tuples, int tuple_count,
						 int alphabet_sz, int index);

int *radix_sort(block *blocks, int block_count, int alphabet_sz, int *ranks,
				bool *unique);

void counting_sort(int *indices, block *blocks, int block_count,
				   int alphabet_sz, int index);

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

void print_block(block b);

void print_block_array(block *blocks, int sz);

void print_indexed_block_array(block *blocks, int sz, int *indices);

void print_tuple(tuple t);

void print_tuple_array(tuple *tuples, int sz);

void print_indexed_tuple_array(tuple *tuples, int sz, int *indices);

#endif /* UTILS_H */