// gcc -o ch_4_ex_9 ch_4_ex_9.c && ./ch_4_ex_9

/******************************************************************************** 
4-9 Our 'getch' and 'ungetch' do not handle a pushed-back EOF correctly. Decide what
their properties ought to be if an EOF is pushed back, then implement your design

Currently: if ungetch() puts back an EOF, program terminates

Alternate implementation: if supposed to be pushed back, have ungetch() not do that.
Do not see any other way to do that without changing the loop in main, which does
not seem useful

*/
#include <stdio.h>
#include <stdlib.h>    	// for atof()
#include <string.h>

#define MAXOP 	100 	// max size of operand or operator
#define NUMBER 	'0' 	// signal that a number was found

int getop(char []);
void push(double);
double pop(void);
void init_buffer(void);
void ungets(char[]);
void print_buf(void);

// reverse Polish calculator
int main() {
	int type;
	double op2;
	char s[MAXOP];

	void init_buffer() {
		char line[MAXOP] = "6 7 + 4";
		line[strlen(line)] = EOF;
		ungets(line);
	}

	init_buffer();
	print_buf();

	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			printf("Number: %s\n", s);
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

void putch(char line[]);

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

void ungets(char line[]) {
	putch(line);
}


#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char s[]) {
	int i, c;

	// while ((s[0] = c = getch()) == ' ' || c == '\t')
	// 	;

	c = getch();
    s[0] = c;
    while (c == ' ' || c == '\t') {
        c = getch();
        s[0] = c;
    }
	
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

	ungetch(c);


	// TODO change handling of EOF
	//if (c != EOF) {
		//printf("char is not EOF; unget\n");
		//ungetch(c); 	// if first non-digit char was anything but EOF, still needs to be read
	//} else {
		//printf("EOF, skipped\n");
		// ungetch(c);		// finding: if EOF is returned, program terminates
	//}
	return NUMBER;
}


#define BUFSIZE 100

char buf[BUFSIZE]; 	// buffer for ungetch
int bufp = 0; 		// next free position in buf

void print_buf() {
	for (int i = 0; i < strlen(buf); i++) {
		putchar(buf[i]);
	}
	putchar('\n');
}

int getch(void) { 	// get a (possibly pushed back) character
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) { 	// push character back on input, if not EOF
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters");
	else if (c != EOF)
		buf[bufp++] = c;
}

// puts 'line' onto 'buf', in reverse order
void putch(char line[]) {
	for (int i = strlen(line)-1; i >= 0 ; i--) {
		buf[bufp++] = line[i];
	}
}