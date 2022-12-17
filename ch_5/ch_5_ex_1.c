// gcc -o ch_5_ex_1 ch_5_ex_1.c && ./ch_5_ex_1

// if using math.h
// gcc -o ch_5_ex_1 ch_5_ex_1.c -lm && ./ch_5_ex_1

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
However, pointer is to a float

Code about how to get a float one char at a time: page 78, getop() part of reverse
Polish calculator. That though only moves chars onto string, not handle powers of 10 values

Roundabout way but more clear to me
	put digits and '.' into string: smallest decimals will be first
	loop over that string:
		before '.', value /=10 of the digit [float should handle the decimal]
		after '.', value *=10
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

int getfloat(float *pn);
int getch(void);
void ungetch(int);

int main() {

	float x = 3.45;
	float *np; 	// np is pointer to an float

	np = &x; 	// np points to x
	// printf("start value of *np: %d\n", *np);

	// re-assign *np to the next float in terminal input
	int n = getfloat(np);

	if (n > 0)
		printf("new value of *np: %f\n", *np);
	else
		printf("invalid input, return code is: %d\n", n);
}

int getfloat(float *pn) {
	int c, sign, i;
	char s[100];
	char non_decimal[100];
	char decimal[100];

	*pn = 0;    // set pn to 0

	while (isspace(c = getch())) 	// skip white space
		;
	
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); 	// not a number
		return 0;
	}
	
	sign = (c == '-') ? -1 : 1;
	
	if (c == '+' || c == '-') {
		c = getch();
		if (!isdigit(c)) {    // sign followed by non-digit is invalid input
			ungetch(c);
			return 0;
		}
	}
	
	// copy all consecutive digits and '.' into string
	for (i = 0; isdigit(c) || c == '.'; c = getch(), i++) {
		s[i] = c;
	}
	s[i] = '\0';
	printf("string: %s\n", s);

	// get decimal and non-decimal parts into separate strings
	int dec = 0;    // boolean for whether in decimal part of number
	int d, nd = 0;

	for (i = 0; i < strlen(s); i++) {
		c = s[i];
		if (c == '.') {    // once reach a decimal, reset flag
			dec = 1;
			continue;
		}
		if (dec) {
			decimal[d++] = c;
		} else {
			non_decimal[nd++] = c;
		}
	}
	decimal[d] = '\0';
	non_decimal[nd] = '\0';

	printf("decimal string: %s\n", decimal);
	printf("non-decimal string: %s\n", non_decimal);

	// get values from strings
	for (i = 0; i < strlen(non_decimal); i++) {
		c = non_decimal[i];
		*pn = (10 * *pn) + (c - '0');
		printf("handled non-decimal: %f\n", *pn);
	}

	float f = 0.0;
	float temp, p = 0.0;
	for (i = 0; i < strlen(decimal); i++) {
		c = decimal[i];
		*pn += ((float) (c - '0')) / pow(10, i+1);
		//printf("next dec char: %f\n", temp);
		//printf("next pow: %f\n", p);
		//printf("next decimal: %f\n", f);
		//printf("handled decimal: %f\n", f);
	}

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