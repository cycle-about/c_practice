// gcc -o ch_4_ex_10 ch_4_ex_10.c && ./ch_4_ex_10

/******************************************************************************** 
4-10 An alternate organization uses 'getline' to read an entire input line; this
makes 'getch' and 'ungetch' unnecessary. Revise the calculator to use this approach.

Plan: build off of ungets() from 4-7.
*/


#include <stdio.h>
#include <stdlib.h>    	// for atof()

#define MAXOP 	100 	// max size of operand or operator
#define NUMBER 	'0' 	// signal that a number was found

int getop(char []);
void push(double);
double pop(void);
void write_buf(char line[]);

// reverse Polish calculator
int main() {
	int type;
	double op2;
	char s[MAXOP];

	write_buf("6 7 *");

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
#include <string.h>

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
	return NUMBER;
}


#define BUFSIZE 100
#define MAXLINE 1000

int getaline(char line[], int maxline);
void print_buf(void);

char buf[BUFSIZE]; 	// buffer for ungetch
int bufp = 0; 		// next free position in buf
char line[MAXLINE]; // input line from terminal

// prints buf up to bufp
void print_buf() {
	printf("\nbufp: %d\n", bufp);
	printf("buffer: ");
	for (int i = 0; i < bufp; i++) {
		putchar(buf[i]);
	}
	putchar('\n');
}

int getch(void) {
	//return (bufp > 0) ? buf[--bufp] : getchar();
	if (bufp == 0) {
		getaline(line, MAXLINE);	// get line from terminal, copy into buf
		//printf("new line from terminal: %s\n", line);
		write_buf(line);
	} 
	return buf[--bufp];

	// debugging print statements
	//else {
	//	printf("using buffer\n");
	//}
	//bufp -= 1;
	//int ch = buf[bufp];
	//printf("returned: ");
	//putchar(ch);
	//printf("\n");
	//return ch;
}


// writes string in reverse order onto buffer, increments bufp
void write_buf(char line[]) {
	bufp = 0;

	for (int i = strlen(line)-1; i >= 0 ; i--) {
		buf[bufp++] = line[i];
	}
	print_buf();
}

int getaline(char s[], int lim) {
	int c, i;

	for (i=0; i<lim-1 && (c=getchar()) != EOF && c != '\n'; i++)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}