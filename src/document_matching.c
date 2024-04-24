#include "document_matching.h"

suffix *build_suffix_array(int *str, int sz) {
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
		printf("Original string: ");
		print_int_array(str, sz);
		print_block_array(blocks, block_count);
	}

	int *sorted_blocks = radix_sort(blocks, block_count, sz);
	if (DEBUG) {
		printf("Sorted block indices: ");
		print_int_array(sorted_blocks, block_count);
		print_indexed_block_array(blocks, block_count, sorted_blocks);
	}

	int *recursion_str = (int *)malloc(block_count * sizeof(int));
	for (int i = 0; i < block_count; i++) {
		recursion_str[sorted_blocks[i]] = i;
		// ! Will not handle non-unique blocks
	}
	if (DEBUG) {
		printf("Recursion String before rank equalization: ");
		print_int_array(recursion_str, block_count);
	}

	/**
	 * The 'ranks' after the sort are unique, because they are indices of the
	 * internal array used during counting. We iterate over them and reduce
	 * ranks in O(n) time.
	 */

	int *block_ranks = calculate_ranks(blocks, block_count, sorted_blocks);

		suffix
			*block_suffixes /**  = build_suffix_array(indices, block_count) */;

	// Build suffix array from index 2:

	int tuple_count = result.quot;
	tuple *tuples = (tuple *)malloc(tuple_count * sizeof(tuple));
	j = 0;
	int k = 2;
	for (int i = 2; i < sz; i += 3) {
		int first = str[i];
		int second = 0;
		if (i + 1 < sz) {
			second = block_suffixes[k].index;
			k += 2;
		}
		tuples[j++] = create_tuple(first, second, i);
	}

	//? I think these are the even suffixes
	int *sorted_tuples = tuple_radix_sort(tuples, tuple_count, sz);
	suffix *tuple_array /** = (suffix *)malloc(tuple_count * sizeof(suffix)) */;

	// Combine suffix arrays:

	// Free memory:
	free(blocks);
	blocks = NULL;
	free(sorted_blocks);
	sorted_blocks = NULL;
	free(recursion_str);
	recursion_str = NULL;
	free(tuple_array);
	tuple_array = NULL;

	return NULL;
}
