#include "document_matching.h"
#include <assert.h>
#include <time.h>

#define TEST_SIZE 10000
#define STR_LEN 50

void test_document_matching() {
	int test_count = 10;
	int* arr = random_int_array(test_count, test_count);
	arr[test_count - 1] = 0;
	build_suffix_array(arr, test_count);
}

int main() {
	printf("Running tests...\n");
	test_document_matching();
	printf("\nTest success.\n");
	return 0;
}
