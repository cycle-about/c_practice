// gcc -o ch_5_ex_1 ch_5_ex_1.c && ./ch_5_ex_1

/******************************************************************************** 
5-1 As written, getint treats a + or - not followed by a digit as a valid
representation of zero. Fix it to push such a character back on the input.

*/

#include <stdio.h>
#include <ctype.h>

int getint(int *pn);
int getch(void);
void ungetch(int);

int main() {

	int x = 800;
	int *np; 	// np is pointer to an int

	np = &x; 	// np points to x

	printf("Value at *np: %d\n", *np);

	// assign np to the next integer in terminal input
	
}

/*
// get next integer from input into *pn
int getint(int *pn) {
	int c, sign;

	while (isspace(c = getch())) 	// skip white space
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); 	// not a number
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}


// copied from ex 4-3
#define BUFSIZE 100

char buf[BUFSIZE]; 		// buffer for ungetch
int bufp = 0; 			// next free position in buf

int getch(void) { 		// get a (possibly pushed back) character
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {    // push char back on input
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters");
	else
		buf[bufp++] = c;
}
*/