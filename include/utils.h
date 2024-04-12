#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "string.h"

/**
 * @brief Simple list node holding
 * a generic value and a pointer
 * to the next node.
 */
typedef struct list_node list_node;

struct list_node {
    char val;
    list_node *next;
};

/**
 * @brief Sorts an array in linear time.
 * @param arr 
 * @param max Integer magnitude upper bound
 */
void char_counting_sort(char *arr, size_t sz);

/**
 * @brief Returns a numeric value of the given
 * char where 'A' is 0 and 'z' is max.
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
 * are in the range a...zA...Z.
 * 
 * @param size Size of the array
 * @return char* 
 */
char *random_char_array(int size);
/**
 * @brief Checks if an array is sorted
 * 
 * @param arr 
 * @param sz 
 * @return true if the array is sorted
 */
bool is_sorted(unsigned int *arr, size_t sz);