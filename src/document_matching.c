#include "document_matching.h"

suffix *build_suffix_array(int *str, int sz) {
	/**
	 * Recursively builds the suffix array by building an array
	 * of suffixes with starting indices 0 and 1 mod 3, and an
	 * array of suffixes with starting indices 2 mod 3; and
	 * combining the two.
	 */

	// Base case:

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
	block *binary_blocks = (block *)malloc(block_count * sizeof(block));
	int j = 0;
	for (int i = 0; i < sz; i++) {
		if (i % 3 != 2) {
			block b = create_block();
			for (int k = 0; k < BLOCK_SIZE; k++) {
				if (i + k < sz)
					b.nums[k] = str[i + k];
			}
			binary_blocks[j++] = b;
		}
	}

	if (DEBUG) {
		print_int_array(str, sz);
		print_block_array(binary_blocks, block_count);
	}

	int *sorted_blocks = radix_sort(binary_blocks, block_count, sz);
	if (DEBUG) {
		print_int_array(sorted_blocks, block_count);
		print_indexed_block_array(binary_blocks, block_count, sorted_blocks);
	}

	int *indices = (int *)malloc(block_count * sizeof(int));
	for (int i = 0; i < block_count; i++) {
		indices[sorted_blocks[i]] = i; // ! Will not handle non-unique blocks
	}
	if (DEBUG) {
		print_int_array(indices, block_count);
	}

	//* suffix *binary_array = build_suffix_array(indices, block_count);

	// Build suffix array from index 2:

	int mod_2_size = result.quot;
	suffix *indices_2_mod_3 = (suffix *)malloc(mod_2_size * sizeof(suffix *));
	

	// Combine suffix arrays:

	// Free memory:
	free(binary_blocks);
}
