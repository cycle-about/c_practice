/*
Combined compile and run command
gcc -o ch_2_notes ch_2_notes.c && ./ch_2_notes
*/

#include <stdio.h>
#include <string.h>

int main() {

	/* ---- page 38 ----
		strings can be concatenated
	
	// printf("hello " "world\n");
	*/


	/* ---- page 39: strlen() ----
		strlen() is included in <string.h>
		it returns a long unsigned int
		info in Appendix page 249

		surprising finding: if declare 'char s[100]' and in a for loop assign ints to 
		the indices, no errors but printf %s with \n only prints the newline

		also note: when an eg for loop adds chars to char array here, it AUTOMATICALLY
		gets '/0' added at the end, so size and printing done correctly

	char s[100];
	int size;

	size = 5;
	for (int i = 0; i < size; i++) {
		s[i] = 'a';
	}

	printf("%s\n", s);
	printf("string length: %lu\n", strlen(s));
	*/

	/* --- page 39: enumerations ----
		Use these to define true/false
	*/

	enum boolean { NO, YES };
	printf("%d\n", NO);  // 0
	printf("%d\n", YES);  // 1

	enum escapes {BELL = '\a', BACKSPACE = '\b', TAB = '\t', NEWLINE = '\n', 
	VTAB = '\v', RETURN = '\r', LOWER_A = 'a'};
	putchar(LOWER_A);  // a
	printf("\n");
	printf("%c\n", LOWER_A);  // a

	enum months { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };
	printf("%d %d %d %d\n", FEB, JUN, OCT, DEC);
	// 2 6 10 12
}