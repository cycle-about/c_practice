// gcc -o ch_5_ex_1 ch_5_ex_1.c && ./ch_5_ex_1

/******************************************************************************** 
5-1 As written, getint treats a + or - not followed by a digit as a valid
representation of zero. Fix it to push such a character back on the input.

#include <stdio.h>
#include <ctype.h>

int getint_orig(int *pn);
int getint_new(int *pn);
int getch(void);
void ungetch(int);

int main() {

	int x = 800;
	int *np; 	// np is pointer to an int

	np = &x; 	// np points to x
	// printf("start value of *np: %d\n", *np);

	// re-assign *np to the next integer in terminal input
	int n = getint_new(np);

	if (n > 0)
		printf("new value of *np: %d\n", *np);
	else
		printf("invalid input, return code is: %d\n", n);
}

// revision of get next integer from input into *pn
// in the case of input "+" or "-" followed by non-digit:
//	   push back that char, rather than treat as 0
int getint_new(int *pn) {
	int c, sign;

	while (isspace(c = getch())) 	// skip white space
		;
	
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); 	// not a number
		return 0;
	}
	
	sign = (c == '-') ? -1 : 1;
	
	if (c == '+' || c == '-') {
		c = getch();
		if (!isdigit(c)) {
			ungetch(c);
			return 0;
		}
	}
	
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	
	*pn *= sign;
	
	if (c != EOF)
		ungetch(c);
	return c;
}

// book description about return value, though pointer arg is reassigned directly:
// 'returns EOF for end of file, zero if next input not number, positive value
// if input contains valid number'
// what happens if enter + or -, not followed by non-digit: "end value at *np: 0"

// get next integer from input into *pn
int getint_orig(int *pn) {
	int c, sign;

	while (isspace(c = getch())) 	// skip white space
		;
	
	// case: if input is not valid part of a number or is EOF, exit
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); 	// not a number
		return 0;
	}
	
	sign = (c == '-') ? -1 : 1;
	
	// get next char, if is sign
	if (c == '+' || c == '-')
		c = getch();
	
	// one char at a time, while digit:
	//     right to left, get chars, handling incrememts of tens places
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	
	// case: if exited loop due to not digit, and is not EOF, push back that char
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


/******************************************************************************** 
5-2 Write getfloat(), the floating-point analog of getint(). What type does getfloat()
return as its return value.

Still returns an int, since return value is just indicator of whether input was valid
*/

#include <stdio.h>
#include <ctype.h>

int getint_orig(int *pn);
int getint_new(int *pn);
int getch(void);
void ungetch(int);

int main() {

	int x = 800;
	int *np; 	// np is pointer to an int

	np = &x; 	// np points to x
	// printf("start value of *np: %d\n", *np);

	// re-assign *np to the next integer in terminal input
	int n = getint_new(np);

	if (n > 0)
		printf("new value of *np: %d\n", *np);
	else
		printf("invalid input, return code is: %d\n", n);
}

int getint_new(int *pn) {
	int c, sign;

	while (isspace(c = getch())) 	// skip white space
		;
	
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); 	// not a number
		return 0;
	}
	
	sign = (c == '-') ? -1 : 1;
	
	if (c == '+' || c == '-') {
		c = getch();
		if (!isdigit(c)) {
			ungetch(c);
			return 0;
		}
	}
	
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