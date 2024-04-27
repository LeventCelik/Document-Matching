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
 * into integers. The string ends with three 0s, and contains
 * no other 0s. The elements of the string are bounded by n.
 *
 * @param str String represented as int array
 * @param n Size of the string, not including 0s.
 * @return int* Suffix array of the string of size n.
 */
int *build_suffix_array(int *str, int n);

/**
 * @brief Kasai's algorithm to compute LCP array from
 * the suffix array in O(n) time.
 * @param str String represented as int array
 * @param suffix_array Suffix array of the string
 * @param n Size of the string
 * @return int* LCP array of the string
 */
int *kasai(int *str, int *suffix_array, int n);

/**
 * @brief Builds a suffix tree from a suffix array
 * and an LCP array.
 * @param str String represented as int array
 * @param n Size of the string
 * @param suffix_array Suffix array of the string
 * @param LCP LCP array of the string
 * @return node*
 */
node *build_suffix_tree(int *str, int n, int *suffix_array, int *LCP);

/**
 * @brief Traverses the suffix tree and fills the suffix array
 * @param root Root of the suffix tree
 * @param suffix_array Empty array to be filled with suffixes
 */
void traverse_suffix_tree(node *root, int *suffix_array, int *index);

#endif /* DOCUMENT_MATCHING_H */