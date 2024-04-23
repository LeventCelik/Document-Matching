#include "document_matching.h"

suffix_array *build_suffix_array(int *str, size_t sz) {
	/**
	 * Recursively builds the suffix array by building an array
	 * of suffixes with starting indices 0 and 1 mod 3, and an
	 * array of suffixes with starting indices 2 mod 3; and
	 * combining the two.
	 */

	// Base case:

	// Build suffix array from indices 0 and 1 mod 3:

	// Find the total number of blocks necessary
	ldiv_t result = ldiv(sz, 3);
	size_t block_count = 2 * result.quot;
	if (result.rem == 2) {
		block_count += 2;
	} else if (result.rem == 1) {
		block_count += 1;
	}

	// Blocks with indices 0 and 1 mod 3
	block binary_blocks[block_count];
	int j = 0;
	for (int i = 0; i < sz; i++) {
		if (i % 3 != 2) {
			block b = create_block();
			for (int j = 0; j < BLOCK_SIZE; j++) {
				if (i + j < sz)
					b.nums[j] = str[i + j];
			}
			binary_blocks[j++] = b;
		}
	}

	print_int_array(str, sz);
	print_block_array(binary_blocks, block_count);
	// int *sorted = block_radix_sort(binary_blocks, block_count, str, sz);
	//  suffix_array *indices_0_1_mod_3 = build_suffix_array():

	// Build suffix array from index 2:

	// Combine suffix arrays:
}
