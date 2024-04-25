#include "document_matching.h"

int *build_suffix_array(int *str, int sz) {
	/**
	 * Recursively builds the suffix array by building an array
	 * of suffixes with starting indices 0 and 1 mod 3, and an
	 * array of suffixes with starting indices 2 mod 3; and
	 * combining the two.
	 */

	// Base cases:
	if (sz <= 0)
		return NULL;

	// Build suffix array from indices 0 and 1 mod 3:

	// Find the total number of blocks necessary
	div_t result = div(sz, 3);
	int block_count = 2 * result.quot;
	if (result.rem == 2) {
		block_count += 2;
	} else if (result.rem == 1) {
		block_count += 1;
	}

	// Blocks with indices 0 and 1 mod 3
	block *blocks = (block *)malloc(block_count * sizeof(block));
	int j = 0;
	for (int i = 0; i < sz; i++) {
		if (i % 3 != 2) {
			block b = create_block(i);
			for (int k = 0; k < BLOCK_SIZE; k++) {
				if (i + k < sz)
					b.nums[k] = str[i + k];
			}
			blocks[j++] = b;
		}
	}

	if (DEBUG) {
		printf("Constructed blocks.\n");
		printf("Original string: ");
		print_int_array(str, sz);
		print_block_array(blocks, block_count);
	}
	int *ranks = (int *)malloc(block_count * sizeof(int));
	bool unique = true;
	int *sorted_indices = radix_sort(blocks, block_count, sz, ranks, &unique);
	if (DEBUG) {
		printf("Sorted block indices: ");
		print_int_array(sorted_indices, block_count);
		print_indexed_block_array(blocks, block_count, sorted_indices);
		print_int_array(ranks, block_count);
	}

	int *block_suffixes = (int *)malloc(block_count * sizeof(int));
	if (!unique) {
		if (DEBUG)
			printf("Non-unique blocks, entering recursion.\n");
		free(sorted_indices);
		sorted_indices = build_suffix_array(ranks, block_count);
	}
	for (int i = 0; i < block_count; i++) {
		block_suffixes[i] = blocks[sorted_indices[i]].og_index;
	}

	if (DEBUG) {
		printf("Block suffixes: ");
		print_int_array(block_suffixes, block_count);
	}

	// Build suffix array from index 2:

	int tuple_count = result.quot;
	tuple *tuples = (tuple *)malloc(tuple_count * sizeof(tuple));
	j = 0;
	int k = 2;
	for (int i = 2; i < sz; i += 3) {
		int first = str[i];
		int second = 0;
		if (i + 1 < sz) {
			second = 1; // TODO
		}
		tuples[j++] = create_tuple(first, second, i);
	}

	if (DEBUG) {
		printf("Constructed tuples.\n");
		printf("Original string: ");
		print_int_array(str, sz);
		print_tuple_array(tuples, tuple_count);
	}

	int *sorted_tuples = tuple_radix_sort(tuples, tuple_count, sz);

	if (DEBUG) {
		printf("Sorted tuple indices: ");
		print_int_array(sorted_tuples, tuple_count);
	}

	int *tuple_suffixes = (int *)malloc(tuple_count * sizeof(int));
	for (int i = 0; i < tuple_count; i++) {
		tuple_suffixes[i] = tuples[sorted_tuples[i]].og_index;
	}

	if (DEBUG) {
		printf("Tuple suffixes: ");
		print_int_array(tuple_suffixes, tuple_count);
	}

	// Combine suffix arrays:

	// Free memory:
	free(blocks);
	blocks = NULL;
	free(sorted_indices);
	sorted_indices = NULL;
	free(ranks);
	ranks = NULL;

	return NULL;
}
