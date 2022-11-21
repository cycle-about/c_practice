/*
Combined compile and run command
gcc -o ch_4_ex ch_4_ex.c && ./ch_4_ex
*/

/**************************************** 
4-1 Write the function strrindex(s,t) which returns the position of the rightmost
occurrence off t in s, or -1 if there is none

Starting point: page 69, find all lines matching pattern


#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int getaline(char line[], int max);
int strrindex(char source[], char t);

int main() {
	char line[MAXLINE];
	char t = 'd';
	int i;

	while(getaline(line, MAXLINE) > 0) {
		i = strrindex(line, t);
		printf("\nchar searched: ");
		putchar(t);
		printf("\nleftmost index: %d\n", i);
	}
}

// return index of t in s, or -1 if none
int strrindex(char s[], char t) {
	long unsigned len = strlen(s)-1;    // do not include terminal char

	for (int i = len; s[i] != '\0' && i >= 0; i--) {
		if (s[i] == t)
			return i+1;
	}
	return -1;
}

// get line into s, return length
int getaline(char s[], int lim) {
	int c, i;

	i = 0;
	while (--lim > 0 && (c=getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}
*/


/**************************************** 
4-2 Extend atof to handle scientific notation of the form "123.45e-6" where a floating-point
number may be followed by 'e' or 'E' and an optionally signed exponent

How to handle that kind of string:
	Read chars left to right
	if reach an 'E' or 'e'

*/

#include <stdio.h>
#include <ctype.h>

double atof_orig(char s[]);
double atof_new(char s[]);

int main() {
	//printf("%f\n", atof_orig("4321"));
	printf("%f\n", atof_orig("7654.321"));
}

// convert string s to double
double atof_new(char s[]) {
	double val, power;
	int i, sign;

	for (i = 0; isspace(s[i]); i++)    // skip white space
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + s[i] - '0';
		power *= 10.0;
	}
	return sign * val / power;
}

// convert string s to double, page 71
double atof_orig(char s[]) {
	double val;    	// 
	double power; 	// 
	int i; 			// iterator to read string from left to right
	int sign; 		// -1 if orig string had a "-", else +1

	// read string from left to right, ignore whitespace
	for (i = 0; isspace(s[i]); i++)
		;
	
	// first non-whitespace char: if '-, int 'sign' set to -1, else +1
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	
	// for each digit in string, stop once reaches non-digit (ie period)
	// For all digits with positive exponents: add to cumulative val
	//     that digit's value * 10
	printf("\nFirst Loop\n");
	for (val = 0.0; isdigit(s[i]); i++) {
		// order of operations: 	(10.0 * val) + (s[i] - '0');
		//     multiply current 'val' by 10, then add decimal value of index in string
		val = 10.0 * val + (s[i] - '0');
		printf("val at loop %d: %f\n", i, val);
	}
	
	if (s[i] == '.') {
		printf("period found\n");
		i++;
	}
	
	// for remaining digits in string, after a period
	//     add in same way to val the digit's val * 10
	//     but additionally, count how many steps in negative exponent direction number goes
	printf("\nSecond Loop\n");
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + s[i] - '0';
		power *= 10.0;
		printf("val at loop %d: %f\n", i, val);
		printf("power at loop %d: %f\n", i, power);
	}
	// multiply by either -1 or +1, and DIVIDE cumulative value of digits
	//     by count of how many negative exponents it had (ie digits after period)
	return sign * val / power;
}