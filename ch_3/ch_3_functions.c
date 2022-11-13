/*
Combined compile and run command
gcc -o ch_3_functions ch_3_functions.c && ./ch_3_functions
*/

//////////////// 11/13/22 ////////////////

/**************************************** 
Section 3.4 on Switch, page 59
*/

#include <stdio.h>

// count digits, white space, others
// note: does the same as example in ch 1 on page 20, which uses if/else
int main() {
	printf("hello\n");
	
	int c, i, nwhite, nother, ndigit[10];

	nwhite = nother = 0;
	for (i = 0; i < 10; i++)
		ndigit[i] = 0;
	
	while ((c = getchar()) != EOF) {	
		switch (c) {
			case '0': case '1':case '2': case '3': case '4':
			case '5': case '6': case '7': case '8': case '9':
				ndigit[c-'0']++;
				break;
			case ' ':
			case '\n': 
			case '\t':
				nwhite++;
				break;
			default:
				nother++;
				break;
		}
	}
	printf("digits =");
	for (i = 0; i < 10; i++)
		printf(" %d", ndigit[i]);
	printf(", white space = %d, other = %d\n", nwhite, nother);
	return 0;
}