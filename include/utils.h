/**
 * @file utils.h
 * @author Levent Çelik (celiklevent@protonmail.com)
 * @version 0.1
 * @date 2024-04-22
 *
 * @copyright Copyright (c) 2024
 *
 */
#ifndef UTILS_H
#define UTILS_H

#include "string.h"
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum LogLevel {
	LOG_DEBUG,
	LOG_ERROR,
	LOG_INFO,
} LogLevel;

#ifdef DEBUG

typedef struct LogConfig {
	const char *log_text;
	const char *log_color;
} LogConfig;

#define COLOR_RESET "\x1b[0m"
#define COLOR_RED "\x1b[31m"
#define COLOR_YELLOW "\x1b[33m"

static const char *parse_log_text(LogLevel log_level) {
	switch (log_level) {
	case LOG_DEBUG:
		return "DEBUG";
	case LOG_ERROR:
		return "ERROR";
	default:
		return "UNKNOWN";
	}
}

static const char *parse_log_color(LogLevel log_level) {
	switch (log_level) {
	case LOG_DEBUG:
		return COLOR_YELLOW;
	case LOG_ERROR:
		return COLOR_RED;
	default:
		return COLOR_RESET;
	}
}

static LogConfig parse_log_level(LogLevel log_level) {
	LogConfig config;
	config.log_text = parse_log_text(log_level);
	config.log_color = parse_log_color(log_level);
	return config;
}

#define debug_print(log_level, fmt, ...)                                       \
	do {                                                                       \
		if (log_level == LOG_INFO) {                                           \
			printf(fmt, ##__VA_ARGS__);                                        \
		} else {                                                               \
			LogConfig config = parse_log_level(log_level);                     \
			printf("%s[%s][%s:%s:%d] " fmt "%s", config.log_color,             \
				   config.log_text, __FILE__, __func__, __LINE__,              \
				   ##__VA_ARGS__, COLOR_RESET);                                \
		}                                                                      \
	} while (0)
#else
#define debug_print
#endif

typedef struct node {
	int data;
	struct node *parent;
	struct node *first_child;
	struct node *last_child;
	struct node *next_sibling;
	struct node *prev_sibling;
} node;

node *new_node(int data, node *parent);

node *get_child(node *n, int i);

void add_child(node *parent, node *child);

bool is_leaf(node *n);

void print_tree(node *root, int depth);

void free_node(node *n);

bool lcp_array_check(int *str, int *suffix_array, int *lcp, int n);

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
int *random_string(int size, int max);

/**
 * @brief Checks if an int array is sorted
 *
 * @param arr
 * @param sz
 * @return true if the array is sorted
 */
bool is_arr_sorted(int *arr, int sz);

bool equal_arrays(int *arr1, int *arr2, int sz);

void print_int_array(int *arr, int sz);

void print_blocks(int *indices, int sz, int *str, int n);

#endif /* UTILS_H */