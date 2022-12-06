
/******************************************************************************** 
4-6 Attempt with variable assignment: not completed
Add commands for handling variables. (It's easy to provide 26 variables with single-letter
names.) Add a variable for the most recently printed value.

Differentiation
	When pop() returns an a-z char in "case = "
		use the char as char itself
		-> make a separate method "pop_assign" that does this, use it only in case_assign
	When pop() returns a-z char in all other operator cases:
		use the VALUE of the char's variable
		-> modify standard pop() to find the VALUE of the char, and RETURN THAT INSTEAD OF CHAR

	*** 
	After trying to implement this, issue found:
		Once something on the stack, since everything is cast to double, there is no way 
		of knowing whether it was originally letter or number, so can't tell whether it should be 
		dereferenced a variable or just returned
	***

New method pop_assign()
	Use *only* in "case = ", and use for only the SECOND pop (ie get i from "i 3 =")
	get the value of pop() from stack: call that method as normal, and interate stack pointer
	Check whether the popped value is a lower-case char
		if is lower-case char
			look up the value of that var in double[26], indexed adjusted for 'a' as 0
		if not
			print an error message for assigning to invalid variable

Changes needed before implementing this
	/ Change the earlier-defined commands to use CAPITAL or other symbols, to differentiate
	/ Push lower-case chars to stack, like numbers
		/ Need to NOT run atof() on them
		/ Handle difference in the case statement, or in getop(): getop(), case doesn't need to see it
	/ Make double[26] to store values corresponding to a-z variables (don't need to declare those vars)
		/ That only needs to be in the stack-manipulating part, NOT main


Another approach, after trying to handle vars during pop()
	Handle during push() instead
	Check if 

--------

Pseudocode for cases involving variables

1. Whole entered statement is ONLY an assignment

	i 6 = \n

	read i
	push i to stack ***want to keep as char***
	read 6
	push 6 to stack
	read =
	pop2 is 6
	pop1 is i ***want to keep as char***
	Execute pop1 = pop2, and print assignment
	read \n
	pop stack, but is empty, okay to print 'is empty' error message

--------

2. Statement has an assignment and a numbers-only operation

	i 6 = 5 2 - \n

	read i
	push i to stack ***want to keep as char***
	read 6
	push 6 to stack
	read =
	pop2 is 6
	pop1 is i ***want to keep as char***
	Execute pop1 = pop2, and print assignment
	read 5
	push 5 to stack
	read 2
	push 2 to stack
	read -
	pop2 is 2
	pop1 is 5
	Execute pop1 - pop2, result is 3
	push 3 to stack
	read \n
	pop 3, and print it

--------

3. Statement uses a previously assigned var: here, with i already assigned to 6

	i 4 +

	read i
	push ***either i or its value*** to stack
	read 4
	push 4 to stack
	read +
	pop1 is 4
	pop2 is ***either either i, or its value***
	Execute pop1 + pop2 (order doesn't matter), result is 10
	push 10 to stack
	read \n
	pop 10, and print it
*/

#include <stdio.h>
#include <stdlib.h>    	// for atof()
#include <math.h> 		// for sin, exp, pow, floor, ceil
#include <ctype.h>

#define MAXOP 	100 	// max size of operand or operator
#define NUMBER 	'0'    	// signal that a number was found and added to string s
#define VAR 	'1'		// signal that a variable a-z found and added to string s
#define DEREF 	'2' 	// signal that value of derefernced var assigned to global 'deref'

double deref; 			// external, dereferenced variable's value to push to stack

int getop(char []);
void push(double);
double pop(void);
void assign_var(void);
void initialize_vars(void);
void print_stack(void);
void print_top(void); 		// T
void duplicate_top(void); 	// D
void swap_top(void); 		// W
void clear_stack(void); 	// C


// reverse Polish notation calculator
int main() {

	int type;
	double op2, op1;
	char s[MAXOP];    // characters of a single number to be added to stack
	extern double deref;

	initialize_vars();

	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:    // including values of vars
			// printf("string: %s\n", s);
			push(atof(s));
			break;
		case VAR: 	// push single char a-z to stack, to be assigned
			printf("variable to be assigned\n");
			push(s[0]);
			break;
		case DEREF:
			push(deref);
			break;
		case '+':
			push(pop() + pop());
			break;
		case '*':
			push(pop() * pop());
			break;
		case '-': 	 			// order of operands matters
			op2 = pop();
			push(pop() - op2);
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
				push((int) pop() % (int) op2);    // modulo can't use double, cast to ints
			else
				printf("error: zero modulo\n");
			break;
		case '~': 			// sine of x
			printf("sine\n");
			push(sin(pop()));
			break;
		case '=': 			// assign value to a variable
			assign_var();
			break;
		case 'E': 			// e^x
			printf("e^x\n");
			push(exp(pop()));
			break;
		case 'P': 			// x^y. Error if x=0 and y<=0, or if x<0 and y not an int
			printf("x^y\n");
			op2 = pop();
			op1 = pop();
			if (op1 != 0 || op2 != 0) // both cannot be zero
				push(pow(op1, op2));
			else
				printf("error: exp when both base and power are 0\n");
			break;
		case 'T': 			// print top of stack without popping
			print_top();
			break;
		case 'D': 			// duplicate top element of stack
			duplicate_top();
			break;
		case 'W': 			// swap top two elements of stack
			swap_top();
			break;
		case 'C': 			// clear stack
			clear_stack();
			break;
		case '\n':
			printf("\tCalculator Result: %.8g\n", pop());
			break;
		default:
			printf("error: unknown command %s\n", s);
			break;
		}
	}
	return 0;
}


// stack and stack pointer are used by both push and pop, so declared external to them
#define MAXVAL 	100 	// max depth of val stack
#define LETTERS  26 	// size of array for values of variables a-z

int sp = 0; 			// next free stack position
double val[MAXVAL]; 	// value stack
double vars[LETTERS];	// values of variables a-z

// initialize all variables to zero
void initialize_vars(void) {
	for (int i = 0; i < LETTERS; i++)
		vars[i] = 0.0;
}

void print_stack(void) {
	printf("stack:");
	for (int i = 0; i < sp; i++) {
		printf(" %.1f", val[i]);    // print to 1 decimal place only
	}
	printf("\n");
}

// push: push f onto value stack
void push(double f) {
	if (sp < MAXVAL) {
		val[sp++] = f;
		printf("push, ");
		print_stack();
	}
	else
		printf("error: stack full, can't push %g\n", f);
}


// pop: pop and return top value from stack
double pop(void) {
	if (sp > 0) {
		printf("pop: %.1f\n", val[sp-1]);
		return val[--sp];
	} else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

// TODO this is broken, eg for char 'i' says assigned to -97
void assign_var(void) {
	double value = pop();
	int letter = (int) pop() - 'a';
	vars[letter] = value;
	printf("assigned %f to variable %d\n", value, letter);
}

// print top of stack, without poping
void print_top(void) {
	printf("top of stack: %.1f\n", val[sp-1]);
}

// duplicate top element of stack
void duplicate_top(void) {
	val[sp++] = val[sp-1];
	printf("duplicated top, ");
	print_stack();
}

// duplicate top element of stack
void swap_top(void) {
	double temp = val[sp-1];
	val[sp-1] = val[sp-2];
	val[sp-2] = temp;
	printf("swapped top, ");
	print_stack();
}

// clear stack
void clear_stack(void) {
	sp = 0;
}


#include <ctype.h>

int getch(void);
void ungetch(int);

// getop: get next operator or numeric operand
int getop(char s[]) {
	int i, c, next, next1, next2, next3;
	extern double deref;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';

	// char is not part of a number, or a variable a-z, so return it as operator
	if (!islower(c) && !isdigit(c) && c != '.' && c != '-')
		return c; 		

	i = 0;
	if (islower(c)) {    // handle single-char variable: check whether assigned or dereferenced
		// rule: if two positions away is a number,
		//     then get four positions away
		//     if four positions away is =, then is assignment
		// 	   otherwise, dereference
		printf("lower found\n");
		next = getch();
		//printf("next: %d\n", next);
		next1 = getch();
		//printf("next1: %d\n", next1);
		if (isdigit(next1)) {
			next2 = getch();
			//printf("next2: %d\n", next2);
			next3 = getch();
			//printf("next3: %d\n", next3);
			if (next3 == '=') {
				printf("letter to be assigned\n");
				s[0] = c;
				s[1] = '\n';
				ungetch(next3);
				ungetch(next2);
				ungetch(next1);
				ungetch(next);
				return VAR;
			} else {
				printf("deref from next3\n");
				ungetch(next3);
				ungetch(next2);
				ungetch(next1);
				ungetch(next);
				deref = vars[c - 'a'];
				return DEREF;
			}
		} else {
			printf("deref from next1\n");
			ungetch(next1);
			ungetch(next);
			deref = vars[c - 'a'];
			return DEREF;
		}
	} else {    			// handle a number, can have negative sign and decimal
		if (c == '-') { 	// check whether subtraction operator or negative number
			next = getch();
			if (next == ' ' || next == '\t' || next == '\n') {	// return as operator if whitespace after
				ungetch(next);
				return c;
			}
			ungetch(next);
		}

		if (isdigit(c) || c == '-')    	// collect sign and integer part of number
			while (isdigit(s[++i] = c = getch()))
				;
		if (c == '.')					// get part of number after a decimal
			while (isdigit(s[++i] = c = getch()))
				;
		s[i] = '\0';
		if (c != EOF)
			ungetch(c);
	}
	return NUMBER;    // returns signal that a number was found: NOT VALUE OF NUMBER
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
