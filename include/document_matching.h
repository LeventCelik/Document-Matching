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
