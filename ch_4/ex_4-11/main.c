// gcc -o ex_4-11 main.c getch.c getop.c stack.c && ./ex_4-11

#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

#define MAXOP 100

// reverse Polish notation calculator
int main() {

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