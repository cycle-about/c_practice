// gcc -o ch_4_ex_10 ch_4_ex_10.c && ./ch_4_ex_10

/******************************************************************************** 
4-10 An alternate organization uses 'getline' to read an entire input line; this
makes 'getch' and 'ungetch' unnecessary. Revise the calculator to use this approach
*/


#include <stdio.h>
#include <stdlib.h>    	// for atof()
#include <string.h>

#define MAXOP 	100 	// max size of operand or operator
#define NUMBER 	'0' 	// signal that a number was found

int getaline(char line[], int maxline);
int getop(char input[], char s[]);
void push(double);
double pop(void);
void init_input(void);
void putline(char input[], char line[]);

int i_line; 			// current index of input line, used across calls to getop()

// reverse Polish calculator
int main() {
	int type, len;
	double op2;
	char s[MAXOP];
	char input[MAXOP];

	void init_buffer() {
		putline(input, "6 7 *");
	}

	init_buffer();

	//while ((type = getop(s)) != EOF) {
	while ((len = getaline(input, MAXOP)) > 0 != EOF) {
		while ((type = getop(input, s)) != EOF) {
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
	}
	return 0;
}

#include <ctype.h>

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

void putline(char input[], char line[]) {
	for (int i = strlen(line)-1, j=0; i >= 0 ; i--, j++) {
		input[j] = line[i];
	}
}

int getop(char input[], char s[]) {
	int i, c;

	extern int i_line;

	while (i_line < strlen(input)) {

		c = input[i_line];

		while (c == ' ' || c == '\t') {
	        c = input[++i_line];
	        s[0] = c;
	    }
		
		s[1] = '\0';
		if (!isdigit(c) && c != '.')
			return c; 			// not a number: return operand to main case/switch
		
		i = 0;
		if (isdigit(c)) 		// collect integer part
			while (isdigit(s[++i] = c = input[++i_line]))
				;
		if (c == '.')   		// collect fraction part
			while (isdigit(s[++i] = c = input[++i_line]))
				;
		s[i] = '\0';
		return NUMBER;

	}
}

int getaline(char s[], int lim) {
	int c, i;

	extern int i_line;
	i_line = 0;

	for (i=0; i<lim && (c=getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
	}
}

/*
#include <ctype.h>

int getch(void);
void ungetch(int);

int getop(char s[]) {
	int i, c;

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

	if (c != EOF)
		ungetch(c); 	// if first non-digit char was anything but EOF, still needs to be read

	return NUMBER;
}



#define BUFSIZE 100

char buf[BUFSIZE]; 	// buffer used by ungetch()
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
*/