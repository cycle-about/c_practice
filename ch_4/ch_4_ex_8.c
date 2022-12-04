// gcc -o ch_4_ex_8 ch_4_ex_8.c && ./ch_4_ex_8

/******************************************************************************** 
4-8 Suppose that there will never be more than one character of pushback. Modify
getch and ungetch accordingly

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

int getop(char s[]) {
	int i, c;

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
		ungetch(c); 	// if first non-digit char was anything but EOF, still needs to be read
	return NUMBER;
}

#define BUFSIZE 100

// buffer mods for only ever need char: only need single char, not array and buffer
// assign that char to '\0' if it's 'empty'

char buf, temp;

int getch(void) {
	if (buf != '\0') {    // if not empty: return buf, set it to empty
		temp = buf;
		buf = '\0';
		return temp;
	} else
		getchar();
}

void ungetch(int c) {
	buf = c;
}


//char buf[BUFSIZE]; 	// buffer for ungetch
//int bufp = 0; 		// next free position in buf

//int getch(void) { 	// get a (possibly pushed back) character
//	return (bufp > 0) ? buf[--bufp] : getchar();
//}

//void ungetch(int c) { 	// push character back on input
//	if (bufp >= BUFSIZE)
//		printf("ungetch: too many characters");
//	else
//		buf[bufp++] = c;
//}
*/


/******************************************************************************** 
4-10 An alternate organization uses 'getline' to read an entire input line; this makes
'getch' and 'ungetch' unnecessary. Revise the calculator to use this approach.
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

	// 'type' is any non-number in the input, including could be EOF
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

#define MAXLINE 1000

// replace these with 'getline'
//int getch(void);
//void ungetch(int);
int getaline();

int getop(char s[]) {
	int i_s, i_line, c;
	char line[MAXLINE]; // line entered into terminal

	getaline(line, MAXLINE);
	i_line = 0;

	while ((s[0] = c = line[i_line++]) == ' ' || c == '\t')
		;
	
	s[1] = '\0';
	// this would return 
	if (!isdigit(c) && c != '.')
		return c; 			// not a number: return operand to main case/switch
	
	i_s = 0;
	if (isdigit(c)) 		// collect integer part
		while (isdigit(s[++i_s] = c = line[i_line++]))
			;
	if (c == '.')   		// collect fraction part
		while (isdigit(s[++i_s] = c = line[i_line++]))
			;
	s[i_s] = '\0';	
	
	return NUMBER;
}

// page 29
// might not need the length counter
int getaline(char s[], int lim) {
	int c, i;

	for (i=0; i<lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/*
#define BUFSIZE 100

char buf, temp;

int getch(void) {
	if (buf != '\0') {    // if not empty: return buf, set it to empty
		temp = buf;
		buf = '\0';
		return temp;
	} else
		getchar();
}

void ungetch(int c) {
	buf = c;
}
*/