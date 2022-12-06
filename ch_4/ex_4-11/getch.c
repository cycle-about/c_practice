#include <stdio.h>

#define BUFSIZE 100

// static declaration limits these vars to only this file
// so, methods getch() and ungetch() are accessible by other files, 
// but the external variables they use are not

static char buf[BUFSIZE]; 		// buffer for ungetch
static int bufp = 0; 			// next free position in buf

int getch(void) { 		// get a (possibly pushed back) character
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {    // push char back on input
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters");
	else
		buf[bufp++] = c;
}