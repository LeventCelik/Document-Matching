#include "document_matching.h"
#include <assert.h>
#include <stdio.h>
#include <time.h>

#define BASE 10
#define MAX_FACTOR 6
#define TEST_SIZE 1000000
#define TEST_COUNT 100

int test_suffix_array(int sz, double *sa_time) {
	int *str = random_string(sz, sz);
	clock_t start = clock();
	int *suffix_array = build_suffix_array(str, sz);
	clock_t end = clock();
	*sa_time = (double)(end - start) / CLOCKS_PER_SEC;
	if (!suffix_array_check(str, sz, suffix_array)) {
		return -1;
	}
	free(str);
	free(suffix_array);
	return 0;
}

int test_suffix_tree(int sz, double *sa_time, double *kasai_time,
					 double *tree_time) {
	int *str = random_string(sz, sz);
	clock_t start = clock();
	int *suffix_array = build_suffix_array(str, sz);
	clock_t end = clock();
	*sa_time = (double)(end - start) / CLOCKS_PER_SEC;
	if (!suffix_array_check(str, sz, suffix_array)) {
		return -1;
	}
	start = clock();
	int *LCP = kasai(str, suffix_array, sz);
	end = clock();
	*kasai_time = (double)(end - start) / CLOCKS_PER_SEC;
	if (!lcp_array_check(str, suffix_array, LCP, sz)) {
		return -2;
	}
	start = clock();
	node *root = build_suffix_tree(str, sz, suffix_array, LCP);
	end = clock();
	*tree_time = (double)(end - start) / CLOCKS_PER_SEC;
	int *recons_suffix_array = (int *)malloc(sz * sizeof(int));
	if (recons_suffix_array == NULL) {
		fprintf(stderr, "recons_suffix_array memory allocation failed.\n");
		exit(1);
	}
	int index = 0;
	traverse_suffix_tree(root, recons_suffix_array, &index);
	if (!equal_arrays(suffix_array, recons_suffix_array, sz)) {
		return -3;
	}
	free(str);
	free(suffix_array);
	free(LCP);
	free(recons_suffix_array);
	free_node(root);
	return 0;
}

void banana_test() {
	int str[] = {3, 2, 4, 2, 4, 2, 1, 0, 0, 0};
	int sz = 7;
	int *suffix_array = build_suffix_array(str, sz);
	int *LCP = kasai(str, suffix_array, sz);
	suffix_array_check(str, sz, suffix_array);
	lcp_array_check(str, suffix_array, LCP, sz);
	for (int i = 0; i < sz; i++) {
		printf("\t%d | %d: ", LCP[i], suffix_array[i]);
		print_int_array(&str[suffix_array[i]], sz - suffix_array[i]);
	}
}

void append_to_csv(int test_size, float sa_time, float kasai_time,
				   float tree_time) {
	FILE *file;
	file = fopen("output.csv", "a");

	if (file == NULL) {
		printf("Error opening file!\n");
		return;
	}

	// Check if the file is empty
	fseek(file, 0, SEEK_END);
	if (ftell(file) == 0) {
		// If the file is empty, write the column headers
		fprintf(file, "Test Size,SA Time,Kasai Time,Tree Time\n");
	}

	// Write the data
	fprintf(file, "%d,%f,%f,%f\n", test_size, sa_time, kasai_time, tree_time);

	fclose(file);
}

int main() {
	srand(time(NULL));
	printf("Running tests...\n");
	char spinner[] = "|/-\\";
	for (int j = 3; j <= MAX_FACTOR; j++) {
		int test_size = (int)pow(BASE, j);
		printf("Testing %d strings of size %d.\n", TEST_COUNT, test_size);
		double total_sa_time = 0;
		double total_kasai_time = 0;
		double total_tree_time = 0;
		for (int i = 0; i < TEST_COUNT; i++) {
			printf("\r[%c] Running test %d/%d...", spinner[i % 4], i + 1,
				   TEST_COUNT);
			fflush(stdout); // Make sure the output is immediately shown
			double sa_time, kasai_time, tree_time;
			int test =
				test_suffix_tree(test_size, &sa_time, &kasai_time, &tree_time);
			if (test != 0) {
				printf("\n%s failed.\n", test == -1	  ? "Suffix array check"
										 : test == -2 ? "LCP array check"
													  : "Suffix tree check");
				exit(0);
			}
			total_sa_time += sa_time;
			total_kasai_time += kasai_time;
			total_tree_time += tree_time;
		}
		printf("\rAverage suffix array building time: %.3f ms.\n",
			   total_sa_time / TEST_COUNT * 1000);
		printf("Average LCP array building time: %.3f ms.\n",
			   total_kasai_time / TEST_COUNT * 1000);
		printf("Average suffix tree building time: %.3f ms.\n",
			   total_tree_time / TEST_COUNT * 1000);
		append_to_csv(test_size, total_sa_time / TEST_COUNT * 1000,
					  total_kasai_time / TEST_COUNT * 1000,
					  total_tree_time / TEST_COUNT * 1000);
	}
	printf("\nAll tests passed.\n");
	return 0;
}