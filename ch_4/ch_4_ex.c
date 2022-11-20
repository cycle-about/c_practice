/*
Combined compile and run command
gcc -o ch_4_ex ch_4_ex.c && ./ch_4_ex
*/

/**************************************** 
4-1 Write the function strrindex(s,t) which returns the position of the rightmost
occurrence off t in s, or -1 if there is none

Starting point: page 69, find all lines matching pattern

Test input to use:
	
here
heeeeere

*/

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