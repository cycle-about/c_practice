/*
Combined compile and run command
gcc -o ch_2_ex ch_2_ex.c && ./ch_2_ex
*/

//////////////// 10/29/22 ////////////////

/**************************************** 
2-1 Write a program to determine the ranges of char, short, int, and long variables,
	both signed and unsigned, by printing appropriate values from standard headers 
	and by direct computation. Harder if you compute them: determine the ranges of 
	the various floating-point types.

	Version A. compute the values

#include <stdio.h>

int main() {

	// signed char i, j;  		// max: 127 		min: -128
	// unsigned char i, j; 		// max: 255 		min:  0
	
	// signed short i, j; 		// max: 32,767		min: -32,768
	// unsigned short i, j;		// max: 65,535 		min: 0
	
	//// must change print statement to use '%ld' for 'unsigned int'
	//// oddly it prints '-1' with %d, even with 'max' still declared as int only
	// signed int i, j; 		// max: 2,147,483,647 		min: -2,147,483,648
	// unsigned int i, j;		// max: 4,294,967,295 		min: 0

	//// use print statements with '%ld'
	//// change max and min to long
	// left this running for over 10 min without it finishing
	// signed long i, j;			// max:  		min: 

	long max, min;
	int max_done, min_done;

	max = min = max_done = min_done = 0;

	for (i = j = 0; (max_done + min_done) < 2; i++, j--) {
		// printf("i: %d, j: %d\n", i, j);
		// printf("max: %d, min: %d\n", max, min);
		if (max > i) {    // value of i has looped
			max_done = 1;
		}
		if (max < i) {
			max = i;
		}
		if (min > j) {    // value of j has looped
			min_done = 1;
		}
		if (max_done && min == j) { // unsigned case, j has looped but never goes negative
			min_done = 1;
		}
		if (min > j) {
			min = j;
		}

	}
	printf("maximum: %ld\n", max);
	printf("minimum: %ld\n", min);
}
*/

//////////////// 10/30/22 ////////////////

/**************************************** 
2-1 Version B. Print appropriate values from standard headers
	See Appendix B11, page 257 for headers info
	Values returned are *minimums* only, actual system could use larger

	Note: there is no min defined for UCHAR, UINT, ULONG (they're 0)
	Bits needed for decimal x = log2(x)


#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
	// char: 8 bits = 1 byte
	printf("CHAR_BIT: %d\n", CHAR_BIT); // 8
	printf("SCHAR_MAX: %d\n", SCHAR_MAX); // 127
	printf("SCHAR_MIN: %d\n", SCHAR_MIN); // -128
	printf("UCHAR_MAX: %d\n", UCHAR_MAX); // 255

	// short: log2(65,536) = 16 bits = 2 bytes
	printf("SHRT_MAX: %d\n", SHRT_MAX); // 32,767
	printf("SHRT_MIN: %d\n", SHRT_MIN); // -32,768
	printf("USHRT_MAX: %d\n", USHRT_MAX); // 65,535

	// int: 32 bits = 4 bytes
	printf("INT_MAX: %d\n", INT_MAX); // 2,147,483,648
	printf("INT_MIN: %d\n", INT_MIN); // -2,147,483,648
	printf("UINT_MAX: %ud\n", UINT_MAX); // 4,294,967,295

	// long: 64 bits = 8 bytes
	printf("LONG_MAX: %ld\n", LONG_MAX); // 9,223,372,036,854,775,807
	printf("LONG_MIN: %ld\n", LONG_MIN); // -9,223,372,036,854,775,808
	printf("ULONG_MAX: %lu\n", ULONG_MAX); // 18,446,744,073,709,551,615
}
*/


/**************************************** 
2-2 Write a loop equivalent to this for loop without using && or ||
	Loop is from the input function getaline() in chapter 1

	for (int i = 0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
		s[i] = c;

	Boolean clauses to handle: do statement if all three true
		i<lim-1
		c=getchar()) != '\n'
		c != EOF

	for (int i = 0; i < lim-1; ++i) {
		if (c=getchar()) != '\n' {
			if (c != EOF) {
				s[i] = c;
			}
		}
	}
*/


#include <stdio.h>
#define MAXLINE 100 // maximum chars in a line

int getaline(char line[], int maxline);

int main() {
	int len; 			   // length current line
	char line[MAXLINE];    // current input line
	char longest[MAXLINE];    // longest line saved here

	while ((len = getaline(line, MAXLINE)) > 0)
		printf("%s\n", line);
	return 0;
}

// read a line into s, return length
int getaline(char s[], int lim) {
	int c, i;

	for (i = 0; i < lim-1; i++) {
		c = getchar();
		if (c == EOF) {
			break;
		} else if (c == '\n') {
			break;
		} else {
			s[i] = c;
		}
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}