/*
Combined compile and run command
gcc -o ch_4_functions ch_4_functions.c && ./ch_4_functions
*/

/*********************************
page 69 find all lines matching pattern

Test input to use:
	
Ah Love! could you and I with Fate conspire
To grasp this sorry Scheme of Things entire,
Would not we shatter it to bits -- and then
Re-mould it nearer to the Heart's Desire!

*/

#include <stdio.h>
#define MAXLINE 1000

int getaline(char line[], int max);
int strindex(char source[], char searchfor[]);

char pattern[] = "ould";    // pattern to search for

int main() {
	char line[MAXLINE];
	int found = 0;

	while(getaline(line, MAXLINE) > 0) {
		if (strindex(line, pattern) >= 0) {
			printf("\nmatched: %s", line);
			found++;
		}
	}
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

// return index of t in s, or -1 if none
int strindex(char s[], char t[]) {
	int i, j, k;

	for (i = 0; s[i] != '\0'; i++) {
		for (j=i, k=0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			return i;
	}
	return -1;
}