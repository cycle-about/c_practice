// commit fa587a0

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

Revise structure to handling values assigned to vars a-z
	Use a int[26], where index is (char - 'a'), and value there is var's value

*/

#include <stdio.h>
#include <stdlib.h>    	// for atof()
#include <math.h> 		// for sin, exp, pow
#include <ctype.h>

#define MAXOP 	100 	// max size of operand or operator
#define NUMBER  '0'    	// signal that number was added to stack
#define VAR 	'a'	 	// signal that variable a-z was added to stack
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
		case VAR: 		// push to stack: letter's index in a-z array, where a is 0
			push((double) s[0]);
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
			op1 = pop(); 	// letter in a-z array to get assignment, aka index in vars[]
			// printf("try to assign %f to %f\n", op1, op2);
			if (islower(op1))
				vars[(int) op1-'a'] = op2;
			else
				printf("error: assigning to not valid variable\n");
			// printf("new values op1 and op2: %f and %f", op1, op2);
			printf("Vars values: ");
			for (i = 0; i < LETTERS; i++) {
				printf(" %.0f", vars[i]);
			}
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
	int i, c, next;

	while ((s[0] = c = getch()) == ' ' || c == '\t')    // skip whitespace, between chars
		;
	s[1] = '\0';

	// char is not a variable a-z, or part of a number, so return it
	if (!islower(c) && !isdigit(c) && c != '.' && c != '-')
		return c;

	i = 0;
	if (islower(c)) {    // handle variable a-z
		s[i] = c; 		 // return string with only the one char
		s[++i] = '\0';
		return VAR;
	} else {    		// handle number
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