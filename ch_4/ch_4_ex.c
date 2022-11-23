/*
Combined compile and run command
gcc -o ch_4_ex ch_4_ex.c && ./ch_4_ex
*/

/******************************************************************************** 
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


/******************************************************************************** 
4-2 Extend atof to handle scientific notation of the form "123.45e-6" where a floating-point
number may be followed by 'e' or 'E' and an optionally signed exponent

Original syntax handled 	7654.321
Additional syntax 			123.45e-6

How to handle that kind of string:
	Read chars left to right
	if reach an 'E' or 'e'
		change 'power' by that amount
			negative after e: 	power *= 10   (make eventual division greater)
			positive after e:  	power /= 10   (make eventual division smaller)


#include <stdio.h>
#include <ctype.h>

double atof_orig(char s[]);
double atof_new(char s[]);

int main() {
	printf("%f\n", atof_new("4321"));
	printf("Result: %f\n", atof_new("123.45e3"));
}

// convert string s to double
double atof_new(char s[]) {
	double val, power, e_val;
	int i, sign, e_sign;

	printf("Original String: %s\n", s);

	for (i = 0; isspace(s[i]); i++)    // skip white space
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;

	//printf("\nBefore Period\n");
	for (val = 0.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		//printf("val at loop %d: %f\n", i, val);
	}
	
	if (s[i] == '.') {
		i++;
		//printf("\nperiod found\n");
	}
	
	//printf("\nAfter Period\n");
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + s[i] - '0';
		power *= 10.0;
		//printf("val at loop %d: %f\n", i, val);
		//printf("power at loop %d: %f\n", i, power);
	}

	if (s[i] == 'e' || s[i] == 'E') {
		i++;
		//printf("\nexponent found: ");

		e_sign = (s[i] == '-') ? 0 : 1;
		//printf("%d\n\n", e_sign);
		if (s[i] == '+' || s[i] == '-')
			i++;

		//printf("After exponent\n");
		for (e_val = 0.0 ; isdigit(s[i]); i++) {
			e_val = 10.0 * e_val + s[i] - '0';
			//printf("e_val at loop %d: %f\n", i, e_val);
		}

		for (i = 0; i < e_val; i++) {
			if (e_sign) {
				//printf("positive exponent\n");
				power /= 10.0;
			} else {
				//printf("negative exponent\n");
				power *= 10.0;
			}
			//printf("Power after adjust for exponent: %f\n", power);
		}
	}
	return sign * val / power;
}
*/

/*
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
*/


/******************************************************************************** 
4-3 Given the basic framework, it's straightforward to extend the calculator. Add the
modulus (%) operator and provisions for negative numbers.

*/

#include <stdio.h>
#include <stdlib.h>    	// for atof()

#define MAXOP 	100 	// max size of operand or operator
#define NUMBER 	'0'    	// signal that a number was found

int getop(char []); 	// ? why does this and push not name the args ?
void push(double);
double pop(void);

// reverse Polish notation calculator
int main() {
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			printf("string: %s\n", s);
			push(atof(s));
			break;
		case 'p':
			printf("letter p found\n");
			break;
		case '+':
			// printf("addition"); // ???? why does this not print?
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-': 	 			// order of operands matters
			op2 = pop(); 		// most recent operand
			push(pop() - op2);	// second most recent - most recent
			break;
		case '/': 				// order of operands and value of op2 matter
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero divisor\n");
			break;
		case '%': 				// order of operands and value of op2 matter
			op2 = pop();
			if (op2 != 0.0)
				push((int) pop() % (int) op2);    // modulo can't take double
			else
				printf("error: zero modulo\n");
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("second line");
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}


// stack and stack pointer are used by both push and pop, so declared external to them
// hidden from main due to declared after main
#define MAXVAL 	100 	// max depth of val stack

int sp = 0; 			// next free stack position
double val[MAXVAL]; 	// value stack

// push: push f onto value stack
void push(double f) {
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}


// pop: pop and return top value from stack
double pop(void) {
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}


#include <ctype.h>

int getch(void);
void ungetch(int);

// getop: get next operator or numeric operand
int getop(char s[]) {
	int i, c, next;

	while ((s[0] = c = getch()) == ' ' || c == '\t')    // skip whitespace, between chars
		;
	s[1] = '\0';

	// char is not part of a number, so return it
	if (!isdigit(c) && c != '.' && c != '-')
		return c; 		

	i = 0;
	// check if '-' is subtraction operator, or means negative number
	if (c == '-') { 		
		next = getch();
		printf("minus sign found, followed by: ");
		putchar(next);
		printf("\n");
		if (next == ' ' || next == '\t' || next == '\n') {	// return subtraction operator if whitespace after
			printf("subtraction operand\n");
			return c;
		}
		ungetch(next);
	}

	if (isdigit(c) || c == '-')    	// collect sign and integer part
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')		// get part after a decimal
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;    // signal that a number was found: NOT VALUE OF NUMBER
}


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