#include "utils.h"

void counting_sort(unsigned int* arr, size_t sz, int max) {
	int counts[max+1];
	// TODO: Virtual initialization 
	memset(counts, 0, max*sizeof(int));
	for (int i = 0; i < sz; i++) {
		counts[arr[i]] += 1;
	}
	int j = 0;
	int k = 0;
	while (j < max+1) {
		if (counts[j] == 0) {
			j++;
			continue;
		}
		counts[j] -= 1;
		arr[k++] = j;
	}
}