#include "document_matching.h"
#include <assert.h>
#include <time.h>

#define TEST_SIZE 10000
#define STR_LEN 50

void test_document_matching() {
	int arr[14] = {7, 1, 3, 3, 3, 1, 3, 3, 1, 3, 3, 0, 0, 0};
	build_suffix_array(arr, 11);
}

int main() {
	printf("Running tests...\n");
	test_document_matching();
	printf("\nTest success.\n");
	return 0;
}
