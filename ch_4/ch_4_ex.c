/*
Combined compile and run command

if NOT using math.h
gcc -o ch_4_ex ch_4_ex.c && ./ch_4_ex

if using math.h
gcc -o ch_4_ex ch_4_ex.c -lm && ./ch_4_ex
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
		// printf("minus sign found, followed by: ");
		// putchar(next);
		// printf("\n");
		if (next == ' ' || next == '\t' || next == '\n') {	// return subtraction operator if whitespace after
			// printf("subtraction operand\n");
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
*/


/******************************************************************************** 
4-4 Add commands to:
	/ 1. Print top element of the stack without popping
	/ 2. Duplicate top element of stack
	/ 3. Swap the top two elements
	/ 4. Clear the stack

Need before starting these
	/ Way to print entire stack

Note: duplicating the top of the stack has effect that there is a number left on the stack
if another operand is not added


#include <stdio.h>
#include <stdlib.h>    	// for atof()

#define MAXOP 	100 	// max size of operand or operator
#define NUMBER 	'0'    	// signal that a number was found and added to stack

int getop(char []);
void push(double);
double pop(void);
void print_stack(void);
void print_top(void);
void duplicate_top(void);
void swap_top(void);
void clear_stack(void);

// reverse Polish notation calculator
int main() {
	int type;
	double op2;
	char s[MAXOP];    // characters of a single number to be added to stack

	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			// printf("string: %s\n", s);
			push(atof(s));
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
		case 'p': 			// print top of stack without popping
			print_top();
			break;
		case 'd': 			// duplicate top element of stack
			duplicate_top();
			break;
		case 's': 			// swap top two elements of stack
			swap_top();
			break;
		case 'c': 			// clear stack
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

int sp = 0; 			// next free stack position
double val[MAXVAL]; 	// value stack

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
	int i, c, next;

	while ((s[0] = c = getch()) == ' ' || c == '\t')    // skip whitespace, between chars
		;
	s[1] = '\0';

	// char is not part of a number, so return it
	if (!isdigit(c) && c != '.' && c != '-')
		return c; 		

	i = 0;
	if (c == '-') { 	// check whether subtraction operator, or negative number
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
*/


/******************************************************************************** 
4-5 Add access to library functions like sin, exp, and pow. See <math.h> in Appendix B,
Section 4

Syntax of these functions
	sin(x) - sine of x. One operand
	exp(x) - exponential function e^x. One operand
	pow(x,y) - x^y. Errors out if x=0 and y<=0, or if x<0 and y not an int. Two operands

Compile command needs to be changed to use math.h: add '-lm' must be at END of command
	gcc -o ch_4_ex ch_4_ex.c -lm && ./ch_4_ex

Try out what this means about errors for pow() for "x<0 and y not an int", and whether to handle
	Decision: keep as is, don't cast in that case, it shows 'nan' fine
	Seems that pow() handles the check of losslessly casting to int if base is negative
	If can't be, returns nan; otherwise returns result fine
		-3 1.5 p
			-> nan
		-3 2 p
			-> 9


#include <stdio.h>
#include <stdlib.h>    	// for atof()
#include <math.h> 		// for sin, exp, pow

#define MAXOP 	100 	// max size of operand or operator
#define NUMBER 	'0'    	// signal that a number was found and added to stack

int getop(char []);
void push(double);
double pop(void);
void print_stack(void);
void print_top(void); 		// t
void duplicate_top(void); 	// d
void swap_top(void); 		// w
void clear_stack(void); 	// c


// reverse Polish notation calculator
int main() {
	int type;
	double op2, op1;
	char s[MAXOP];    // characters of a single number to be added to stack

	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			// printf("string: %s\n", s);
			push(atof(s));
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
		case 's': 			// sine of x
			printf("sine\n");
			push(sin(pop()));
			break;
		case 'e': 			// e^x
			printf("e^x\n");
			push(exp(pop()));
			break;
		case 'p': 			// x^y. Error if x=0 and y<=0, or if x<0 and y not an int
			printf("x^y\n");
			op2 = pop();
			op1 = pop();
			if (op1 != 0 || op2 != 0) // both cannot be zero
				push(pow(op1, op2));
			else
				printf("error: exp when both base and power are 0\n");
			break;
		case 't': 			// print top of stack without popping
			print_top();
			break;
		case 'd': 			// duplicate top element of stack
			duplicate_top();
			break;
		case 'w': 			// swap top two elements of stack
			swap_top();
			break;
		case 'c': 			// clear stack
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

int sp = 0; 			// next free stack position
double val[MAXVAL]; 	// value stack

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
	int i, c, next;

	while ((s[0] = c = getch()) == ' ' || c == '\t')    // skip whitespace, between chars
		;
	s[1] = '\0';

	// char is not part of a number, so return it
	if (!isdigit(c) && c != '.' && c != '-')
		return c; 		

	i = 0;
	if (c == '-') { 	// check whether subtraction operator, or negative number
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
*/


/******************************************************************************** 
4-6 Add commands for handling single variables. (It's easy to provide twenty-six variables with
single-letter names.) Add a variable for the most recently printed variable.

Clear thing to implement for this
	/ 1. Replace using lower-case letters as both math.h operands, and 'commands'
		/ Math operands to non a-z chars
		/ Commands to capital letters
	/ 2. Add a variable for the most recently printed variable
		- Interpret this as: most recent value printed as calculator result, so after '\n'
		- Use 'r', setup for mention of 26 single-letter vars (for now don't make changes to 
		differentiate commands added in 4-5 from variables added here)
		- Where does it need to be: depends on whether needs access to stack or not
			-> only in main, since only involves a pop from stack, none of its other values

Followup step (I think)
	/ 1. Add a way to use 'r' variable in calculations
	/ 2. Add 26 single-letter variable names
		/ Can variables be declared in a loop (not only defined)? Not clear, do manually
	/ 3. Add a 'symbol' like NUMBER to indicate a lower-case variable was found
	/ 4. Handle assignment operator = when first operand is a valid variable name (a-z)
	5. Use those variables in other calculations

What is happening with variable assignment now
	getop() returns signal 'VAR' when a char a-z (variable) is pushed onto stack
		That separate method puts char on stack without converting chars to float, as with NUMBER
	Assignment operator = assigns 

/ Revise structure to handling values assigned to vars a-z
	/ Use a int[26], where index is (char - 'a'), and value there is var's value

Handling needed for vars, where to do each case TBD
	1. Assignment: indicated by '=' operator exactly two entries later
		Action: returns 'VAR', and pushes letter char to stack
	2. Use: else case for 1
		Action: finds value for index in vars[], and returns it as NUMBER
	*** handle this difference in getop(), which can read stack directly ***

*/

#include <stdio.h>
#include <stdlib.h>    	// for atof()
#include <math.h> 		// for sin, exp, pow
#include <ctype.h>

#define MAXOP 	100 	// max size of operand or operator
#define NUMBER  '0'    	// signal that number was added to stack
#define ASSIGN 	'1'	 	// signal that variable to be assigned was added to stack
#define VAR 	'2'     // signal that var's value should be added to stack
#define LETTERS	26

int getop(char []);
void push(double);
double pop(void);
void print_stack(void);
void print_top(void); 		// t
void duplicate_top(void); 	// d
void swap_top(void); 		// w
void clear_stack(void); 	// c


// reverse Polish notation calculator

// use rules
//     assignment: to make "w = 3", enter exactly "3 w ="

int main() {
	int type, i;
	double op2; 		// most recently pushed number (op1 op2 /  -->  op1 / op2)
	double op1; 		// second most recently pushed number
	double r;    		// result of most recent calculation
	char s[MAXOP];    	// characters of a single number to add to stack
	double vars[LETTERS];	// array for values of variables, found via 26 lower-case letters

	for (i = 0; i < LETTERS; i++) {
		vars[i] = 0;
	}

	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			// printf("string: %s\n", s);
			push(atof(s));
			break;
		case ASSIGN: 			// push char itself to stack, to be assigned value in vars[]
			printf("pushing var name for assignment: ");
			putchar(s[0]);
			printf("\n");
			push((double) s[0]);
			break;
		case VAR:
			i = s[0] - 'a'; 	// push char's value in vars[], via offset to letters a-z
			printf("using value of vars[] at index %d\n", i);
			push(vars[i]);
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
		case '#': 			// e^x
			printf("e^x\n");
			push(exp(pop()));
			break;
		case '^': 			// x^y. Error if x=0 and y<=0, or if x<0 and y not an int
			printf("x^y\n");
			op2 = pop();
			op1 = pop();
			if (op1 != 0 || op2 != 0) // both cannot be zero
				push(pow(op1, op2));
			else
				printf("error: exp when both base and power are 0\n");
			break;
		case '=': 			// assign value to variable a-z
			op2 = pop(); 	// value for var
			i = (int) pop(); 	// letter in a-z array to get assignment, aka index in vars[]
			// printf("try to assign %f to %f\n", op1, op2);
			if (islower(op1))
				vars[i-'a'] = op2;
			else
				printf("error: assigning to not valid variable, %d\n", i);
			// printf("new values op1 and op2: %f and %f", op1, op2);
			printf("Vars values: ");
			for (i = 0; i < LETTERS; i++) {
				printf(" %.0f", vars[i]);
			}
			printf("\n");
			break;
		
		/**** NON-OPERATION COMMANDS ADDED IN EX 4-4: CAPTIAL LETTERS ****/
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
		/**** END NON-OPERATION COMMANDS ADDED IN EX 4-4 ****/

		/**** VARIABLE ADDED IN EX 4-6 ****/
		case 'r':	 		// push value of most recent calc result to stack
			push(r);
			break;
		/**** VARIABLE ADDED IN EX 4-6 ****/

		case '\n':
			r = pop(); 		// assign result to variable, can use in future calculations
			printf("\tCalculator Result: %.8g\n", r);
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

int sp = 0; 			// next free stack position
double val[MAXVAL]; 	// value stack

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
	int i, c, next, next1;

	while ((s[0] = c = getch()) == ' ' || c == '\t')    // skip whitespace, between chars
		;
	s[1] = '\0';

	// char is not a variable a-z, or part of a number, so return it
	if (!islower(c) && !isdigit(c) && c != '.' && c != '-')
		return c;

	i = 0;
	if (islower(c)) {    	// check whether assigning value to var, or using its value
		s[i] = c; 		 	// string gets the letter in both cases
		s[i+1] = '\0';
		next = getch();
		next1 = getch();
		printf("after lower: ");
		putchar(next);
		putchar(next1);
		printf("\n");
		if (next1 == '=') {
			printf("assign to variable named: %d\n", c);
			ungetch(next);
			ungetch(next1);
			return ASSIGN;
		} else {
			printf("use variable named: %d\n", c);
			ungetch(next);
			ungetch(next1);
			return VAR;
		}
	} else {    			// handle number
		if (c == '-') { 	// check whether subtraction operator, or negative number
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
	return NUMBER;    // returns signal that a number or operand was found: NOT ITS VALUE
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


/******************************************************************************** 
4-7 

*/