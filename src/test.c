#include "document_matching.h"
#include <assert.h>
#include <time.h>

#define TEST_SIZE 1000000
#define TEST_COUNT 100

int test_suffix_array(int sz, double *sa_time, double *kasai_time) {
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
	free(suffix_array);
	free(LCP);
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

int main() {
	// srand(time(NULL));
	printf("Running tests...\n");
	char spinner[] = "|/-\\";
	printf("Testing %d suffix arrays of size %d.\n", TEST_COUNT, TEST_SIZE);
	double total_sa_time = 0;
	double total_kasai_time = 0;
	for (int i = 0; i < TEST_COUNT; i++) {
		printf("\r[%c] Running test %d/%d...", spinner[i % 4], i + 1,
			   TEST_COUNT);
		fflush(stdout); // Make sure the output is immediately shown
		double sa_time, kasai_time;
		int test = test_suffix_array(TEST_SIZE, &sa_time, &kasai_time);
		if (test != 0) {
			printf("\n%s failed.\n",
				   test == -1 ? "Suffix array check" : "LCP array check");
			exit(0);
		}
		total_sa_time += sa_time;
		total_kasai_time += kasai_time;
	}
	printf("\nAll suffix array tests passed.\n");
	printf("Average suffix array building time: %.3Lf ms.\n",
		   total_sa_time / TEST_COUNT * 1000);
	printf("Average LCP array building time: %.3Lf ms.\n",
		   total_kasai_time / TEST_COUNT * 1000);
}