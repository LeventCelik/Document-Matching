#include "utils.h"
#include <assert.h>
#include <time.h>

#define TEST_SIZE 10000
#define STR_LEN 50

void test_random_str() {
	char **arr = random_str_array(TEST_SIZE, STR_LEN);
	if (DEBUG) {
		print_string_array(arr, TEST_SIZE, STR_LEN);
	}
	free(arr);
}

void test_counting_sort() {
	// TODO: Test int-counting sort
	// TODO: Test char-counting sort
	char **arr = random_str_array(TEST_SIZE, STR_LEN);
	for (int i = STR_LEN - 1; i >= 0; i--) {
		str_counting_sort_by_char(arr, TEST_SIZE, i);
		if (DEBUG) {
			printf("Sorted by character #%d\n", i + 1);
		}
		if (DEBUG) {
			print_string_array(arr, TEST_SIZE, STR_LEN);
			getchar();
		}
	}
	assert(is_str_array_sorted(arr, TEST_SIZE, STR_LEN));
	free(arr);
}

int main() {
	printf("Running tests...\n");
	srand(time(NULL));
	printf("\nTesting random string generation...\n");
	test_random_str();
	printf("\nTesting counting_sort...\n");
	test_counting_sort();
	printf("\nTest success.\n");
	return 0;
}
