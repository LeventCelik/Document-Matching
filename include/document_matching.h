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
 * @return suffix_array
 */
suffix_array *build_suffix_array(int *str, size_t sz);
