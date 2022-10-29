/*
Combined compile and run command
gcc -o ch_2_ex ch_2_ex.c && ./ch_2_ex
*/

//////////////// 10/29/22 ////////////////
/**************************************** 
2-1 write a program to determine the ranges of char, short, int, and long variables,
	both signed and unsigned, by printing appropriate values from standard headers 
	and by direct computation. Harder if you compute them: determine the ranges of 
	the various floating-point types.
*/

#include <stdio.h>

int main() {

	signed char i, j;  		// max: 127 		min: 128
	// unsigned char v;

	int max, min, max_done, min_done;

	max = min = max_done = min_done = 0;

	for (i = j = 0; (max_done + min_done) < 2; i++, j--) {
		printf("i: %d, j: %d\n", i, j);
		if (i < 0) {    // value of i has looped, become negative
			max_done = 1;
		}
		if (max < i) {
			max = i;
		}
		if (j > 0) {    // value of j has looped, become positive
			min_done = 1;
		}
		if (min > j) {
			min = j;
		}

	}
	printf("maximum: %d\n", max);
	printf("minimum: %d\n", min);
}