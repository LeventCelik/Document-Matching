#include "string.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define DEBUG false

/**
 * @brief Simple list node holding
 * a char value and a pointer
 * to the next node.
 */
typedef struct list_node list_node;
struct list_node {
	// TODO: Fix references and casting
	void *val;
	list_node *next;
};

void str_external_counting_sort(int *indices, char **actual_arr, size_t sz,
								int str_len);

/**
 * @brief Sorts an array of strings in linear time.
 *
 * @param arr array of strings (char*)
 * @param sz array size
 * @param str_len index of sorting key
 */

void str_radix_sort(char **arr, size_t sz, int str_len);

/**
 * @brief Sorts an array of strings by the char at a given
 * index in linear time, in a stable fashion.
 *
 * @param arr array of strings (char*)
 * @param sz array size
 * @param index index of sorting key
 */
void str_counting_sort_by_char(char **arr, size_t sz, int index);

/**
 * @brief Returns a numeric value of the given
 * char where '$'=0 'A'=1 and 'z'=max.
 *
 * @return int
 */
int char_numeric_value(char);

/**
 * @brief Creates a random array where elements
 * are in the range 0...max
 *
 * @param size Size of the array
 * @param max Upper bound of the random numbers
 * @return unsigned int*
 */
unsigned int *random_int_array(int size, int max);

/**
 * @brief Creates a random array where elements
 * are equal length strings with characters in
 * the range a...zA...Z.
 *
 * @param size Size of array
 * @param len String length
 * @return char**
 */
char **random_str_array(int size, int len);

/**
 * @brief Creates a random array where elements
 * are in the range a...zA...Z.
 *
 * @param size Size of the array
 * @return char*
 */
char *random_char_array(int size);

/**
 * @brief Checks if an int array is sorted
 *
 * @param arr
 * @param sz
 * @return true if the array is sorted
 */
bool is_int_arr_sorted(unsigned int *arr, size_t sz);

/**
 * @brief Checks if a string array is sorted
 *
 * @param arr
 * @param sz
 * @param str_len
 * @return true if the array is sorted
 */
bool is_str_array_sorted(char **arr, size_t sz, int str_len);

void print_string_array(char **arr, size_t sz, int str_len);
void print_string_subarray(char **arr, size_t sz, int str_len, int begin,
						   int end);