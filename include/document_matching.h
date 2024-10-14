/**
 * @file document_matching.h
 * @author Levent Çelik (celiklevent@protonmail.com)
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
 * @brief Builds the suffix array of a string (represented
 * as an unsigned integer array).
 *
 * Requires str to end with 3 0s, and contain no other 0s.
 * Requires the elements of str to be bounded by n. Actual
 * size of str is n + 3, including the three 0s at the end.
 *
 * @param str Integer array ending with 3 0s. Other elements are
 * positive and bounded by n. Actual str size is n + 3, including
 * the three 0s.
 * @param n String size (not including the 0s).
 * @return unsigned int* Suffix array of str.
 */
int *build_suffix_array(int *str, int n);

/**
 * @brief Builds the LCP (Longest Common Prefix) array of a string
 * using its suffix array in linear time using Kasai's algorithm.
 *
 * @param str Integer array ending with 3 0s. Other elements are
 * positive and bounded by n. Actual str size is n + 3, including
 * the three 0s.
 * @param suffix_array Suffix array of str.
 * @param n String size (not including the 0s).
 * @return unsigned int* LCP array of str.
 */
int *kasai(int *str, int *suffix_array, int n);

/**
 * @brief Recursively builds the suffix tree from the suffix array and LCP
 * array, i.e., transforms a suffix array into a suffix tree.
 *
 * @param str Integer array ending with 3 0s. Other elements are
 * positive and bounded by n. Actual str size is n + 3, including
 * the three 0s.
 * @param n Size of str (not including the 3 0s).
 * @param suffix_array Suffix array of str.
 * @param LCP LCP array of str.
 * @return node* Pointer to the root of the suffix tree.
 */
node *build_suffix_tree(int *str, int n, int *suffix_array, int *LCP);

/**
 * @brief Traverses a suffix tree to create a suffix array, i.e., transforms
 * a suffix tree into a suffix array.
 * @param root Pointer to the root of the suffix tree.
 * @param suffix_array Empty array to be filled with suffixes - the suffix
 * array.
 * @param index Recursion helper, pass the address of a 0 valued size_t.
 */
void traverse_suffix_tree(node *root, int *suffix_array, int *index);

#endif /* DOCUMENT_MATCHING_H */