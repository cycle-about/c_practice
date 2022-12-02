/******************************************************************************** 
4-7 Write a routine unget(s) that will push back an entire string onto the input.
Should 'ungets' know about 'buf' and 'bufp', or should it just use 'ungetch'?

Starting point: only the baseline reverse Polish calculator, to have less to
navigate around while doing this. Retype all of it.

Steps
	/ 1. Re-do my inline comments about what each part of this program does
	2. Decide where to put new function 'unget(s)': use questions in the ex
	3. Pseudocode for new function

Questions the ex gives about setup for 'unget(s)'
	Should it have direct access to buf and bufp, or only use 'ungetch'
		ie should it be IN program section 4 or not
		or, can it be like section 3, and only get results of the chars

Unclear about question
	When it says 'onto the intput', what does that mean, there is no explicit structure for the input
	What could it go back to, ie would need to make new structure, or way to revers stdlib's 'getchar'
	Would then also need to differentiate 'pushing back' to that input structure, or buffer for single chars?
	What is a case to test with where whole string should be put back onto input

High-level code structure of reverse Polish calculator

	1. main
		decision tree that handles user's input
		uses: 2, 3
	
	2. stack
		declares: stack array
		implements: push() and pop() on stack

	3. operators_operands
		returns operators to part 1
		puts operands on stack managed by 2
		uses: 4, in case reads past the end of a number

	4. buffer characters
		provides chars to program
		if any were 'put back', returns those first, else reads from terminal

Chain of calls to get the input
	main()
	getop()


*/

#include <stdio.h>
#include <stdlib.h>    	// for atof()

#define MAXOP 	100 	// max size of operand or operator
#define NUMBER 	'0' 	// signal that a number was found

int getop(char []);
void push(double);
double pop(void);

// reverse Polish calculator
int main() {
	int type;
	double op2;
	char s[MAXOP];

	// s is modified directly in getop()
	// s will only contain chars to turn into a number
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
		case '-':
			op2 = pop();
			push(pop() - op2);
			break;
		case '/':
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero divisor");
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


#define MAXVAL 	100    	// maximum depth of val stack

int sp = 0;				// next free stack position
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
		printf("error: stack empty");
		return 0.0;
	}
}


#include <ctype.h>

int getch(void);
void ungetch(int);

// note: this DOES NOT directly use the terminal-reading standard library method; instead custom 'getch()'
// getop: get next operator or numeric operand
int getop(char s[]) {
	int i, c;

	// I don't understand while this line isn't an 'if', since does not iterate
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c; 			// not a number: return operand to main case/switch
	
	i = 0;
	if (isdigit(c)) 		// collect integer part
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')   		// collect fraction part
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c); 		// if first non-digit char was anything but EOF, put back to handle
	return NUMBER;
}

// book description of why this is needed (page ): "it is often the case that a program cannot
// determine that it has read enough input until it has read too much. One instance is collecting 
// the characters that make up a number: until the first non-digit is seen, the number is not
// complete. But then the program has read a character too far" so put that one back

#define BUFSIZE 100

// buf is checked before calling a new getch(), and if has values, those are returned first
char buf[BUFSIZE]; 	// buffer for ungetch
int bufp = 0; 		// next free position in buf

// this is the ONLY place where terminal input is read
// this EITHER returns item from buffer, OR calls a new getchar() to read input string
// getchar() it uses is the standard library one that reads terminal input
int getch(void) { 	// get a (possibly pushed back) character
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) { 	// push character back on input
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters");
	else
		buf[bufp++] = c;
}