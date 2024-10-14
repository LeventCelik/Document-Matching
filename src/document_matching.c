#include "document_matching.h"

int *build_suffix_array(int *str, int n) {
	// For debug purposes
	static int recursion_depth = -1;
	recursion_depth++;

	debug_print(LOG_INFO, "\n\n\n------------------------\n");
	debug_print(LOG_INFO, "Recursion depth: %d\n", recursion_depth);
	debug_print(LOG_INFO, "------------------------\n");

	if (n == 1) {
		int *suffix_array = (int *)malloc(sizeof(int));
		suffix_array[0] = 0;
		return suffix_array;
	}

	// STEP 1: Construct A12 from indices 1 and 2 mod 3
	int c0 = (n + 2) / 3; // 0 mod 3 index element count
	int c1 = (n + 1) / 3; // 1 mod 3 index element count
	int c2 = n / 3;		  // 2 mod 3 index element count
	// If n == 1 mod 3 <=> c0-c1 > 0, include the '000' in the blocks
	int c12 = c1 + c2 + (c0 - c1);

	// Size c12+3 for the three 0s at the end
	int *A12 = malloc((c12 + 3) * sizeof(int));
	if (A12 == NULL) {
		fprintf(stderr, "A12 memory allocation failed.\n");
		exit(1);
	}

	int j = 0;
	for (int i = 0; i < n + (c0 - c1); i++) {
		if (i % 3 != 0)
			A12[j++] = i;
	}
	A12[c12] = A12[c12 + 1] = A12[c12 + 2] = 0;

	radix_sort(A12, c12, str, n, n, 3);

	int *recursion_string = (int *)malloc((c12 + 3) * sizeof(int));
	if (recursion_string == NULL) {
		fprintf(stderr, "recursion_string memory allocation failed.\n");
		exit(1);
	}
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

	debug_print(LOG_INFO, "Recursion string built\n");
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

	// STEP 2: Construct A0 from indices 0 mod 3 using the result of STEP 1
	// +3 not needed, we do not use "blocks".
	int *A0 = malloc(c0 * sizeof(int));
	if (A0 == NULL) {
		fprintf(stderr, "A0 memory allocation failed.\n");
		exit(1);
	}
	j = 0;
	// Build A0, already sorted through A12.
	for (int i = 0; i < c12; i++) {
		if (A12[i] < c0) {
			A0[j++] = 3 * A12[i];
		}
	}
	radix_sort(A0, c0, str, n, n, 1);

	// STEP 3: Merge A12 and A0
	int *suffix_array = (int *)malloc(n * sizeof(int));
	if (suffix_array == NULL) {
		fprintf(stderr, "suffix_array memory allocation failed.\n");
		exit(1);
	}
	// Name change for clarity
	int *R12 = recursion_string;
	recursion_string = NULL;

	int i0 = 0;
	// Skip first if n == 1 mod 3
	int i12 = n % 3 == 1 ? 1 : 0;
	// Actual merge sort
	for (int i = 0; i < n; i++) {
		int e12 = A12[i12] < c0 ? 3 * A12[i12] + 1 : 3 * (A12[i12] - c0) + 2;
		int e0 = A0[i0];
		if (A12[i12] < c0) {
			// 1 mod 3 index of A12
			if (str[e0] < str[e12] ||
				(str[e0] == str[e12] && R12[e0 / 3] < R12[A12[i12] + c0])) {
				// 0 index is smaller, merge from A0
				suffix_array[i] = e0;
				i0++;
				if (i0 == c0) {
					// A0 completed, copy remaining A12
					while (i12 < c12) {
						if (i > n - 2)
							debug_print(LOG_ERROR,
										"\n\n[%d] (i, n): (%d, %d)\n\n",
										__LINE__, i + 1, n);
						e12 = A12[i12] < c0 ? 3 * A12[i12] + 1
											: 3 * (A12[i12] - c0) + 2;
						i12++;
						suffix_array[++i] = e12;
					}
					break;
				}
			} else {
				// 0 index is larger, merge from A12
				suffix_array[i] = e12;
				i12++;
				if (i12 == c12) {
					// A12 completed, copy remaining A0
					while (i0 < c0) {
						if (i > n - 2)
							debug_print(LOG_ERROR,
										"\n\n[%d] (i, n): (%d, %d)\n\n",
										__LINE__, i + 1, n);
						e0 = A0[i0++];
						suffix_array[++i] = e0;
					}
					break;
				}
			}
		} else {
			// 2 mod 3 index of A12
			if (str[e0] < str[e12] ||
				(str[e0] == str[e12] && str[e0 + 1] < str[e12 + 1]) ||
				(str[e0] == str[e12] && str[e0 + 1] == str[e12 + 1] &&
				 R12[e0 / 3 + c0] < R12[A12[i12] + 1 - c0])) {
				// 0 index is smaller, merge from A0
				suffix_array[i] = e0;
				i0++;
				if (i0 == c0) {
					// A0 completed, copy remaining A12
					while (i12 < c12) {
						if (i > n - 2)
							debug_print(LOG_ERROR,
										"\n\n[%d] (i, n): (%d, %d)\n\n",
										__LINE__, i + 1, n);
						e12 = A12[i12] < c0 ? 3 * A12[i12] + 1
											: 3 * (A12[i12] - c0) + 2;
						i12++;
						suffix_array[++i] = e12;
					}
					break;
				}
			} else {
				// 0 index is larger, merge from A12
				suffix_array[i] = e12;
				i12++;
				if (i12 == c12) {
					// A12 completed, copy remaining A0
					while (i0 < c0) {
						if (i > n - 2)
							debug_print(LOG_ERROR,
										"\n\n[%d] (i, n): (%d, %d)\n\n",
										__LINE__, i + 1, n);
						e0 = A0[i0++];
						suffix_array[++i] = e0;
					}
					break;
				}
			}
		}
	}

	debug_print(LOG_INFO, "Suffix array calculated: ");
	print_int_array(suffix_array, n);
	debug_print(LOG_INFO, "Suffixes:\n");
#ifdef DEBUG
	for (int i = 0; i < n; i++) {
		printf("\t%d: ", suffix_array[i]);
		print_int_array(&str[suffix_array[i]], n - suffix_array[i]);
	}
#endif

	free(A0);
	free(A12);
	free(R12);
	if (--recursion_depth >= 0) {
		debug_print(LOG_INFO, "\n\n\n------------------------\n");
		debug_print(LOG_INFO, "Recursion depth: %d\n", recursion_depth);
		debug_print(LOG_INFO, "------------------------\n");
	}
	return suffix_array;
}

int *kasai(int *str, int *suffix_array, int n) {
	int *LCP = (int *)malloc(n * sizeof(int));
	if (LCP == NULL) {
		fprintf(stderr, "LCP memory allocation failed.\n");
		exit(1);
	}
	int *ranks = (int *)malloc(n * sizeof(int));
	if (ranks == NULL) {
		fprintf(stderr, "ranks memory allocation failed.\n");
		exit(1);
	}
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

node *build_suffix_tree(int *str, int n, int *suffix_array, int *LCP) {
	// Recursively build the suffix tree from the suffix array and LCP array
	node *root = new_node(0, NULL);
	node *current = root;
	int lcp_prev = 0;
	for (int i = 0; i < n; i++) {
		while (current->data > LCP[i]) {
			current = current->parent;
		}
		if (current->data < LCP[i]) {
			// Create a new node
			node *new = new_node(LCP[i], current);
			add_child(current, new);
			current = new;
		}
		// Create a leaf node
		node *leaf = new_node(suffix_array[i], current);
		add_child(current, leaf);
	}
	return root;
}

void traverse_suffix_tree(node *root, int *suffix_array, int *index) {
	// Traverse the suffix tree to find the suffixes
	if (is_leaf(root)) {
		suffix_array[(*index)++] = root->data;
	}
	node *child = root->first_child;
	while (child != NULL) {
		traverse_suffix_tree(child, suffix_array, index);
		child = child->next_sibling;
	}
}