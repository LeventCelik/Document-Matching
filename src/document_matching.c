#include "document_matching.h"

int *build_suffix_array(int *str, int n) {
	/**
	 * Recursively builds the suffix array by building an array
	 * of suffixes with starting indices 1 and 2 mod 3, and an
	 * array of suffixes with starting indices 0 mod 3; and
	 * combining the two.
	 *
	 * Requires str to end with 3 0s, and contain no other 0s.
	 * Requires the elements of str to be bounded by sz. Actual
	 * size of str is n + 3, including the three 0s at the end.
	 */

	// For debug purposes
	static int recursion_depth = 0;
	recursion_depth++;

	// STEP 1: Construct A12 from indices 1 and 2 mod 3
	int c0 = (n + 2) / 3; // 0 mod 3 index element count
	int c1 = (n + 1) / 3; // 1 mod 3 index element count
	int c2 = n / 3;		  // 2 mod 3 index element count
	// If n == 1 mod 3 <=> c0-c1 > 0, include the '000' in the blocks
	int c12 = c1 + c2 + c0 - c1;

	// +3 for the three 0s at the end
	int *A12 = malloc((c12 + 3) * sizeof(int));
	int j = 0;

	for (int i = 0; i < n + (c0 - c1); i++) {
		if (i % 3 != 0)
			A12[j++] = i;
	}
	A12[n] = A12[n + 1] = A12[n + 2] = 0;

	if (DEBUG) {
		printf("\n\n\nRecursion depth: %d\n", recursion_depth);
		printf("Original string: ");
		print_int_array(str, n + 3);
		printf("A12 indices: ");
		print_int_array(A12, c1 + c2 + 3);
		printf("Blocks:\n");
		print_blocks(A12, c1 + c2, str, n);
	}

	radix_sort(A12, c1 + c2, str, n, n, 3);

	if (DEBUG) {
		printf("A12 sorted.\n");
		printf("Sorted A12: ");
		print_int_array(A12, c1 + c2 + 3);
		printf("Sorted blocks:\n");
		print_blocks(A12, c1 + c2, str, n);
	}

	int *recursion_string = (int *)malloc((c12 + 3) * sizeof(int));
	recursion_string[c12] = recursion_string[c12 + 1] =
		recursion_string[c12 + 2] = 0;
	// Find ranks
	int rank = 1;
	for (int i = 0; i < c12; i++) {
		if (i != 0 && !equal_blocks(A12[i - 1], A12[i], str))
			rank++;
		int block_index = A12[i];
		if (block_index % 3 == 1) {
			recursion_string[(block_index - 1) / 3] = rank;
			continue;
		}
		recursion_string[c0 + (block_index - 2) / 3] = rank;
	}

	if (DEBUG) {
		printf("Recursion string built\n");
		print_int_array(recursion_string, c12 + 3);
	}
	if (rank != c12) {
		// Recursively calculate the suffix array of T'
		free(A12);
		A12 = build_suffix_array(recursion_string, c12);
	} else {
		// Elements are unique, no recursion needed.
		for (int i = 0; i < c12; i++) {
			A12[recursion_string[i] - 1] = i; // Fix 1 indexing
		}
	}
	free(recursion_string);
	recursion_string = NULL;

	// Transform suffix array for T' to suffix array for T
	for (int i = 0; i < c12; i++) {
		A12[i] = (A12[i] < c0) ? 3 * A12[i] + 1 : 3 * (A12[i] - c0) + 2;
		// ? This may not be necessary, as the calculations can be done on the
		// go.
	}

	// STEP 2: Construct A0 from indices 0 mod 3 using the result of STEP 1
	// +3 not needed, no blocks = no monkey bussiness
	int *A0 = malloc(c0 * sizeof(int));
	j = 0;
	// Build A0, already sorted according to A12.
	for (int i = 0; i < c12; i++) {
		if (A12[i] % 3 == 1) {
			A0[j++] = A12[i] - 1;
		}
	}
	radix_sort(A0, c0, str, n, n, 1);

	// STEP 3: Merge A12 and A0
	int *suffix_array = malloc(n * sizeof(int));
	// Calculate A12 ranks
	int *R12 = (int *)malloc(c12 * sizeof(int));
	for (int i = 0; i < c12; i++) {
		R12[A12[i]] = i + 1; // Switch to 1 indexing
	}

	recursion_depth--;
	return NULL;
}
