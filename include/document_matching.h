/**
 * @file document_matching.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-04-27
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef DOCUMENT_MATCHING_H
#define DOCUMENT_MATCHING_H

#include "math.h"
#include "utils.h"

/**
 * @brief Builds a suffix array from a string preprocessed
 * into integers. The string ends with a '$', represented
 * with the value 0. Total time and space complexity are
 * linear.
 *
 *
 * @param str A 'string' of integers
 * @param sz Size of string, including the end character 0 ('$')
 * @return int* A suffix array
 */
int *build_suffix_array(int *str, int sz);

int *kasai(int *str, int *suffix_array, int n);

node *build_suffix_tree(int *str, int n, int *suffix_array);

#endif /* DOCUMENT_MATCHING_H */