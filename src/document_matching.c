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
	static int recursion_depth = -1;
	recursion_depth++;
	if (DEBUG) {
		printf("\n\n\n------------------------\n");
		printf("Recursion depth: %d\n", recursion_depth);
		printf("------------------------\n");
	}

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
	A12[c12] = A12[c12 + 1] = A12[c12 + 2] = 0;

	if (DEBUG) {
		printf("Original string: ");
		print_int_array(str, n + 3);
		printf("A12 indices: ");
		print_int_array(A12, c12 + 3);
		printf("Blocks:\n");
		print_blocks(A12, c12, str, n);
	}

	radix_sort(A12, c12, str, n, n, 3);

	if (DEBUG) {
		printf("A12 sorted.\n");
		printf("Sorted A12: ");
		print_int_array(A12, c12 + 3);
		printf("Sorted blocks:\n");
		print_blocks(A12, c12, str, n);
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
		} else {
			recursion_string[c0 + (block_index - 2) / 3] = rank;
		}
	}

	if (DEBUG) {
		printf("Recursion string built\n");
		print_int_array(recursion_string, c12 + 3);
	}
	if (rank != c12) {
		// Recursively calculate the suffix array of T'
		free(A12);
		A12 = NULL;
		A12 = build_suffix_array(recursion_string, c12);
		// Save unique ranks for future use
		for (int i = 0; i < c12; i++) {
			recursion_string[A12[i]] = i + 1; // Switch to 1 indexing
		}
	} else {
		// Elements are unique, no recursion needed.
		for (int i = 0; i < c12; i++) {
			A12[recursion_string[i] - 1] = i; // Fix 1 indexing
		}
	}

	if (DEBUG) {
		printf("A12 suffix array calculated: ");
		print_int_array(A12, c12);
	}

	// STEP 2: Construct A0 from indices 0 mod 3 using the result of STEP 1
	// +3 not needed, no blocks = no monkey bussiness
	int *A0 = malloc(c0 * sizeof(int));
	j = 0;
	// Build A0, already sorted according to A12.
	for (int i = 0; i < c12; i++) {
		if (A12[i] < c0) {
			A0[j++] = 3 * A12[i];
		}
	}
	radix_sort(A0, c0, str, n, n, 1);
	if (DEBUG) {
		printf("A0 sorted.\n");
		printf("Sorted A0: ");
		print_int_array(A0, c0);
		printf("Original string: ");
		print_int_array(str, n + 3);
	}
	// STEP 3: Merge A12 and A0
	int *suffix_array = (int *)malloc(n * sizeof(int));
	// Name change for clarity
	int *R12 = recursion_string;
	recursion_string = NULL;

	// // Transform suffix array for T' to suffix array for T
	// for (int i = 0; i < c12; i++) {
	// 	A12[i] = (A12[i] < c0) ? 3 * A12[i] + 1 : 3 * (A12[i] - c0) + 2;
	// 	// ? This may not be necessary, as the calculations can be done on the
	// 	// go.
	// }

	if (DEBUG) {
		printf("Before merge:\n");
		printf("A0: ");
		print_int_array(A0, c0);
		printf("A12': ");
		print_int_array(A12, c12 + 3);
		printf("R12: ");
		print_int_array(R12, c12 + 3);
	}

	int i0 = 0;
	// Skip first if n == 1 mod 3
	int i12 = n % 3 == 1 ? 1 : 0;
	// Actual merge sort
	for (int i = 0; i < n; i++) {
		int e12 = A12[i12] < c0 ? 3 * A12[i12] + 1 : 3 * (A12[i12] - c0) + 2;
		int e0 = A0[i0];
		if (A12[i12] < c0) {
			// 1 mod 3 index
			if (str[e0] < str[e12] ||
				(str[e0] == str[e12] && R12[e0 / 3] < R12[A12[i12] + c0])) {
				// 0 index is smaller
				suffix_array[i] = e0;
				i0++;
				if (i0 == c0) {
					// A0 completed, copy remaining A12
					while (i12 < c12) {
						suffix_array[++i] = e12;
						i12++;
						e12 = A12[i12] < c0 ? 3 * A12[i12] + 1
											: 3 * (A12[i12] - c0) + 2;
					}
					break;
				}
			} else {
				suffix_array[i] = e12;
				i12++;
				if (i12 == c12) {
					// A12 completed, copy remaining A0
					while (i0 <= c0) {
						suffix_array[++i] = e0;
						e0 = A0[++i0];
					}
					break;
				}
			}
		} else {
			// 2 mod 3 index
			if (str[e0] < str[e12] ||
				(str[e0] == str[e12]) && str[e0 + 1] < str[e12 + 1] ||
				(str[e0] == str[e12] && str[e0 + 1] == str[e12 + 1] &&
				 R12[e0 / 3 + c0] < R12[A12[i12] + 1 - c0])) {
				// 0 index is smaller
				suffix_array[i] = e0;
				i0++;
				if (i0 == c0) {
					// A0 completed, copy remaining A12
					while (i12 <= c12) {
						suffix_array[++i] = e12;
						i12++;
						e12 = A12[i12] < c0 ? 3 * A12[i12] + 1
											: 3 * (A12[i12] - c0) + 2;
					}
					break;
				}
			} else {
				suffix_array[i] = e12;
				i12++;
				if (i12 == c12) {
					// A12 completed, copy remaining A0
					while (i0 < c0) {
						suffix_array[++i] = e0;
						e0 = A0[++i0];
					}
					break;
				}
			}
		}
	}

	if (DEBUG) {
		printf("Suffix array calculated: ");
		print_int_array(suffix_array, n);
		printf("Suffixes:\n");
		for (int i = 0; i < n; i++) {
			printf("\t%d: ", suffix_array[i]);
			print_int_array(&str[suffix_array[i]], n - suffix_array[i]);
		}
	}

	free(A0);
	free(A12);
	free(R12);
	recursion_depth--;
	if (DEBUG && recursion_depth >= 0) {
		printf("\n\n\n------------------------\n");
		printf("Recursion depth: %d\n", recursion_depth);
		printf("------------------------\n");
	}
	return suffix_array;
}

int *kasai(int *str, int *suffix_array, int n) {
	/**
	 * Kasai's algorithm to compute LCP array from
	 * the suffix array in O(n) time.
	 */
	int *LCP = (int *)malloc(n * sizeof(int));
	int *ranks = (int *)malloc(n * sizeof(int));
	// Step 1: Compute the rank array
	for (int i = 0; i < n; i++) {
		ranks[suffix_array[i]] = i;
	}

	// Step 2: Compute the LCP array using rank array
	int k = 0;
	for (int i = 0; i < n; i++) {
		if (ranks[i] == n - 1) {
			k = 0;
			continue;
		}
		int j = suffix_array[ranks[i] + 1];
		while (i + k < n && j + k < n && str[i + k] == str[j + k])
			k++;
		LCP[ranks[i]] = k;
		if (k > 0)
			k--;
	}
	LCP[n - 1] = 0;
	free(ranks);
	return LCP;
}