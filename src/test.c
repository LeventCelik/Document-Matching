#include <assert.h>
#include <stdbool.h>
#include "utils.h"
#include <time.h>

#define TEST_SIZE 1000
#define TEST_RANGE 10000

// Creates a random array where elements are in the range 0...max
unsigned int *random_array(int size, int max) {
    unsigned int *array = (unsigned int*)malloc(size*sizeof(unsigned int));
    for (int i = 0; i < size; i++) {
        array[i] = rand() % (max + 1);
    }
    return array;
}

bool is_sorted(unsigned int *arr, size_t sz) {
	for (int i = 1; i < sz; i++) {
		if (arr[i-1] > arr[i]) {
			return false;
		}
	}
	return true;
}

void test_counting_sort() {
    unsigned int* arr = random_array(TEST_SIZE, TEST_RANGE);
    counting_sort(arr, TEST_SIZE, TEST_RANGE);
	assert(is_sorted(arr, TEST_SIZE));
}

int main() {
    printf("Running tests...\n");
    srand(time(NULL));
    printf("Testing counting_sort...\n");
    test_counting_sort();
    printf("Test success.\n");
    return 0;
}
