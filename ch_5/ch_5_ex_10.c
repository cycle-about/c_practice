// gcc -o ch_5_ex_10.o ch_5_ex_10.c && ./ch_5_ex_10.o

// compile and run separately if entering args
//     gcc -o ch_5_ex_10.o ch_5_ex_10.c
//     ./ch_5_ex_10.o 2 3 4 + *

/********************************************************************************
Example page 115

#include <stdio.h>

// echo command line arguments
int main(int argc, char *argv[]) {
	while (--argc > 0) {
		printf("%s%s", *++argv, (argc > 1) ? " " : "");
	}
	printf("\n");
	return 0;
}
*/

/********************************************************************************
5-10 Write the program expr, which evaluates a reverse Polish expression from the
command line, where each operator or operand is a separate argument. For example,
	expr 2 3 4 + *
evaluates: 2 * (3+4)


#include <stdio.h>
#include <stdlib.h>    	// for atof()

#define MAXOP 	100 	// max size of operand or operator
#define NUMBER 	'0'    	// signal that a number was found

int getop(char []);
void push(double);
double pop(void);

// reverse Polish notation calculator
// change made: args must end with '=' (rather than '\n') to print result
int main(int argc, char *argv[]) {
	int type;
	double op2;
	char *s;

	while (--argc > 0) {
		// printf("arg: %s\n", *++argv);
		s = *++argv;
		type = getop(s);
		printf("type: %d\n", type);
		
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
		case '/': 	// order of operands and value of op2 matter
			op2 = pop();
			if (op2 != 0.0)
				push(pop() / op2);
			else
				printf("error: zero divisor\n");
			break;
		case '=':
			printf("\t%.8g\n", pop());
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
#include <string.h>

// getop: get next operator or numeric operand
int getop(char *s) {
	printf("arg in getop: %s\n", s);
	int i, c;

	if (strlen(s) == 1 && !isdigit(*s)) {
		return *s;  // return operand
	} else {
		return NUMBER;
	}
}
*/