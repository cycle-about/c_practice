/*
Combined compile and run command
gcc -o ch_4_functions ch_4_functions.c -lm && ./ch_4_functions
*/

/******************************************************************
page 69 find all lines matching pattern

Test input to use:
	
Ah Love! could you and I with Fate conspire
To grasp this sorry Scheme of Things entire,
Would not we shatter it to bits -- and then
Re-mould it nearer to the Heart's Desire!


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
*/


/******************************************************************
page 75 pseudocode for reverse Polish notation

while (next operator or operand is not end-of-file indicator)
	if (number)
		push it
	else if (operator)
		pop operands
		do operations
		push result
	else if (newline) 		// end of that computation, so show result
		pop and print top of stack
	else
		error

page 76 implementation of reverse polish notation

Finding: if enter negative numbers, it DOES show the correct answer, but also
	the message "error: stack empty" before, since it tried to handle the '-'
	as an operator
		-> adding handling for negative numbers is part of ex 4-3

Result of test for whether the ORDER of declarations makes external variables
unaccessible to prior parts
	Setup: in main(), try printing using later declaration 'sp'
	'sp' is external, not defined in a function
	Errors out as undeclared
	If move it to above main(): then it works

	So: order of external variables DOES matter

#include <stdio.h>
#include <stdlib.h>    	// for atof()

#define MAXOP 	100 	// max size of operand or operator
#define NUMBER 	'0'    	// signal that a number was found

int getop(char []); 	// ? why does this and push not have named args ?
void push(double);
double pop(void);

// reverse Polish notation calculator
int main() {
	// test of using a later external variable
	//printf("stack pointer declared later: %d\n", sp);

	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-': 	// order of operands matters
			op2 = pop(); 		// most recent operand
			push(pop() - op2);	// second most recent - most recent
			break;
		case '/': 	// order of operands and value of op2 matter
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero divisor\n");
			break;
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}


// ???? should these defintions and vars be in same file as main ????
// note: these don't have their own include for stdio.h; though could be left off for brevity?
// mention on page 77 of hiding representations of stack from main
//     is it not able to access because declared after 'main' ???
//     TODO: test that

// stack and stack pointer are used by both push and pop, so declared external to them
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
		// DEBUGGING: this shows before correct answer if a negative number is entered
		printf("error: stack empty\n");
		return 0.0;
	}
}


#include <ctype.h>

int getch(void);
void ungetch(int);

// getop: get next operator or numeric operand
int getop(char s[]) {
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c; 		// not a number
	i = 0;
	if (isdigit(c))    	// collect integer part
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
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
*/


/******************************************************************
Tests related to finding whether stack items in ex 4-6 are valid variables

*** to use math.h, must change compile command to include -lm
	gcc -o ch_4_ex ch_4_ex.c -lm && ./ch_4_ex
*/

#include <stdio.h>
#include <math.h>
#include <ctype.h>

int main() {
	/*
	double i = 4.5;

	printf("%f\n", ceil(4.5));
	printf("%f\n\n", floor(4.5));

	printf("%f\n", ceil(4.0));
	printf("%f\n\n", floor(4.0));

	printf("%f\n", ceil(-4.5));
	printf("%f\n\n", floor(-4.5));

	printf("%f\n", ceil(-4.0));
	printf("%f\n\n", floor(-4.0));
	*/

	double v = (double) 'i';
	printf("%f\n", ceil(v));
	printf("%f\n", floor(v));
	printf("%d\n", (int) v - 'a');          // indexes 'a' to 0, eg 'i' is 8
	printf("%d\n", islower(v));
	printf("%d\n", islower((int) v));
}