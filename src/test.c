#include <assert.h>
#include "utils.h"
#include <time.h>

#define TEST_SIZE 1000
#define TEST_RANGE 10000



void test_counting_sort() {
    char* arr = random_char_array(TEST_SIZE);
    char_counting_sort(arr, TEST_SIZE);
	//assert(is_sorted(arr, TEST_SIZE));
    free(arr);
}

int main() {
    printf("Running tests...\n");
    srand(time(NULL));
    printf("Testing counting_sort...\n");
    for (int i = 0; i < TEST_RANGE; i++) {
        test_counting_sort();
    }
    printf("Test success.\n");
    return 0;
}
