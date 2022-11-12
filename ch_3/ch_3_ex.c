/*
Combined compile and run command
gcc -o ch_3_ex ch_3_ex.c && ./ch_3_ex
*/

//////////////// 11/12/22 ////////////////

/**************************************** 
3-1 Our binary search makes two tests inside the loop, when one would suffice
(at the price of more tests outside). Write a version with only one test inside
the loop and measure the difference in run-time.

Two-check runtimes
	0.000056
	0.000041
	0.000040
	0.000040

One-check runtimes
	0.000044
	0.000043
	0.000048
	0.000044
*/

#include <stdio.h>
#include <time.h>

int binsearch_orig(int x, int v[], int n);
int binsearch_new(int x, int v[], int n);

int main() {
	int v[] = {1, 5, 6, 9, 10, 12, 15, 16, 18, 20, 21, 22, 25, 27, 28, 30, 35, 38, 41};
	int n = sizeof(v) / sizeof(v[0]);
	int x = 9;

	double runtime = 0.0;
	clock_t begin = clock();

	int r = binsearch_new(x, v, n);
	printf("position of %d in array: %d\n", x, r);

	clock_t end = clock();
	runtime += (double) (end - begin) / CLOCKS_PER_SEC;
	printf("Elapsed time %f seconds", runtime);
}

int binsearch_new(int x, int v[], int n) {
	int low, high, mid;

	low = 0;
	high = n - 1;

	printf("start max is %d\n", high);
	while (low <= high) {
		mid = (low + high) / 2;
		//printf("index checked: %d\n", mid);
		if (x < v[mid]) {
			high = mid - 1;
			//printf("search lower, new max is %d\n", high);
		} else {
			low = mid + 1;
			//printf("search higher, new min is %d\n", low);
		}
	}
	if (v[low] == x)
		return low;
	else if (v[high] == x)
		return high;
	else 
		return -1;    // no match
}

int binsearch_orig(int x, int v[], int n) {
	int low, high, mid;

	low = 0;
	high = n - 1;
	while (low <= high) {
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else
			return mid;
	}
	return -1;    // no match
}