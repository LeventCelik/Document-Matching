#include "document_matching.h"
#include <assert.h>
#include <time.h>

#define TEST_SIZE 10000
#define STR_LEN 50

bool test_document_matching() {
	int arr[14] = {7, 1, 3, 3, 3, 1, 3, 3, 1, 3, 3, 0, 0, 0};
	int *suffix_array = build_suffix_array(arr, 11);
	printf("Expected suffix array: [8, 5, 1, 10, 7, 4, 9, 6, 3, 2, 0]\n");
	printf("Actual suffix array: ");
	print_int_array(suffix_array, 11);
	return suffix_array_check(arr, 11, suffix_array);
}

int main() {
	printf("Running tests...\n");
	bool doc_mac = test_document_matching();
	printf("\nTest %s\n", (doc_mac ? "success." : "failure."));
	return 0;
}
