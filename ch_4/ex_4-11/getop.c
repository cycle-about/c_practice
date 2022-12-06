#include <stdio.h>
#include <ctype.h>
#include "calc.h"

// internal static variable: remain in existence in between function calls
// they provide private, permanent storage within a function

// returns when: reaches an operator, or end of a number
int getop(char s[]) {
	int c, i;
	static int cached = 0; 		// true or false for whether to use prior char
	static int prior = '\0';    // keep the next char between runs

	// while ((s[0] = c = getch()) == ' ' || c == '\t')
	// 	;

	if (cached == 1)
		c = prior;
	else
		c = getchar();
    s[0] = c;
    while (c == ' ' || c == '\t') {
        c = getch();
        s[0] = c;
    }

	s[1] = '\0';
	if (!isdigit(c) && c != '.') {
		cached = 0;
		return c; 		// not a number
	}
	i = 0;
	if (isdigit(c))    	// collect integer part
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	cached = 1;
	prior = c;    		// keep un-handled char between runs
	return NUMBER;
}