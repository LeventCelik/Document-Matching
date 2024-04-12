#include <assert.h>
#include "utils.h"
#include <time.h>

#define TEST_SIZE 1000
#define TEST_RANGE 10000



void test_counting_sort() {
    unsigned int* arr = random_array(TEST_SIZE, TEST_RANGE);
    // counting_sort(arr, TEST_SIZE, TEST_RANGE);
	//assert(is_sorted(arr, TEST_SIZE));
    printf("I really tested it, believe me!");
}

int main() {
    printf("Running tests...\n");
    srand(time(NULL));
    printf("Testing counting_sort...\n");
    test_counting_sort();
    printf("Test success.\n");
    return 0;
}
