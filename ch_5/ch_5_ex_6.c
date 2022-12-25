// gcc -o ch_5_ex_6.o ch_5_ex_6.c && ./ch_5_ex_6.o

/******************************************************************************** 
5-6 Rewrite appropriate programs from earlier chapters and exercises with pointers
instead of array index handling. Good possiblities include:	
	/ getline - page 32
	/ atof and its variants - page 71
	/ itoa and its variants - page 64
	/ reverse - 62
	/ strindex - page 69
	getop - page 78

*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAXLINE 1000

int getop_p(char *s);
int getop_orig(char s[]);
int getop_p(char *s);
int strindex_p(char *source, char *searchfor);
int strindex_orig(char source[], char searchfor[]);
void itoa_p(int n, char s[]);
// void reverse_p(char s[]);  // works when declared this way
void reverse_p(char *s);  // actual param when used
void swap(char *px, char *py);
void itoa_orig(int n, char s[]);
void reverse_orig(char s[]);
double atof_orig(char s[]);
double atof_p(char s[]);
int getaline_orig(char line[], int max);
int getaline_p(char line[], int max); // odd: does not show error with declaration as [], called with *s

int main() {

	/**** PART 6 OF 6 ****/
	char s[100] = "initial";
	int r;
	while ((r = getop_p(s)) != EOF) {  // CAUTION: return value -1 terminates loop
		if (r == 0) {
			printf("number: %s\n", s);
		} else {
			printf("operand: ");
			putchar(r);
			putchar('\n');
		}
	}

	/**** PART 5 OF 6 ****/
	// char s[100] = "sun is shining";
	// char t[100] = "i";
	// printf("index found: %d\n", strindex_p(s, t));

	/**** PARTS 3 AND 4 OF 6 ****/
	// test reverse function separately
	// char t[100] = "9876543";
	// printf("original string: %s\n", t);
	// reverse_p(t);
	// printf("after reverse: %s\n", t);
	
	// char s[100];
	// int i = 765432;
	// printf("original int: %d\n", i);
	// itoa_p(i, s);
	// reverse_p(s);
	// printf("as string: %s\n", s);

	/**** PART 2 OF 6 ****/
	// printf("%f\n", atof_p("360.009873"));

	/**** PART 1 OF 6 ****/
	// int len;
	// char line[MAXLINE];
	// while ((len = getaline_p(line, MAXLINE)) > 0)
	//	printf("%s", line);
}

int getop_p(char *s) {
	int c;

	c = getchar();
	*s = c;
	while (c == ' ' || c == '\t') {
		c = getchar();
		*s = c;
	}
	*++s = '\0';
	if (!isdigit(c) && c != '.') {
		// printf("not part of a number\n");
		return c;
	}
	if (isdigit(c)) {  // collect integer part into string
		while (isdigit(*s = c = getchar())) {
			*++s;
			// putchar(c);
			// putchar('\n');
		}
	}
	if (c == '.') {    // collect decimal part into string
		*++s = c;
		while (isdigit(*s = c = getchar()))
			*++s;
	}
	*s = '\0';
	// printf("s at end getop: %s", s);
	return 0;
}

// page 78: get next operator or numeric operand
// returns an operator, or writes chars of a number to string (latter case: returns -1)
// reads from input to terminal
// note: does not use the buffer for getch and ungetch
int getop_orig(char s[]) {
	int i, c;

	// while ((s[0] = c = getchar()) == ' ' || c == '\t')
	// 	;

	// alternate way to do while loop
	c = getchar();
    s[0] = c;
    while (c == ' ' || c == '\t') {
        c = getchar();
        s[0] = c;
    }

	s[1] = '\0';
	if (!isdigit(c) && c != '.') {
		// printf("not part of a number\n");
		return c;
	}
	// printf("current value of c: ");
	// putchar(c);
	// putchar('\n');
	i = 0;
	if (isdigit(c)) {  // collect integer part into string
		while (isdigit(s[++i] = c = getchar())) {
			// putchar(c);
			// putchar('\n');
		}
	}
	if (c == '.')    // collect decimal part into string
		while (isdigit(s[++i] = c = getchar()))
			;
	s[i] = '\0';
	// printf("s at end getop: %s", s);
	return 0;
}

// t has length 1
int strindex_p(char *s, char *t) {
	for (int i = 0; *(s+i) != '\0'; i++) {
		if (*(s+i) == *t)
			return i;
	}
	return -1;
}

// page 69: return index of t in s, or -1 if none
// t has length 1
int strindex_orig(char s[], char t[]) {
	int i, j, k;

	for (i = 0; s[i] != '\0'; i++) {
		for (j = i, k = 0; t[k] != '0' && s[j] == t[k]; j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			return i;
	}
	return -1;
}

// page 64: convert n to characters in s
void itoa_p(int n, char *s) {
	int sign;

	if ((sign = n) < 0)
		n = -n;
	do {
		*s++ = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (sign < 0)
		*s++ = '-';
	*s = '\0';
	//reverse_p(s);  // can't call like this: this pointer is now at the END of s
}

// void reverse_p(char s[]) {  // THIS DOES NOT WORK, EVEN IF DECLARING IT LIKE THIS DOES
void reverse_p(char *s) {
	int c, i, j;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = *(s+i);
		*(s+i) = *(s+j);
		*(s+j) = c;
	}
}

// page 64: convert n to characters in s
void itoa_orig(int n, char s[]) {
	int i, sign;

	if ((sign = n) < 0) 		// record sign
		n = -n; 				// make n positive
	i = 0;
	do {
		s[i++] = n % 10 + '0';  // get next digit
	} while ((n /= 10) > 0); 	// delete it
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse_orig(s);
}


// page 62: reverse string s in place
void reverse_orig(char s[]) {
	int c, i, j;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

double atof_p(char *s) {
	double val = 0.0;
	double power = 1.0;
	int sign;

	printf("original string %s\n", s);
	while (isspace(*s++))  // skip white space
		;
	*--s;  // go back one
	// printf("string after skip whitespace: %s\n", s);
	
	// printf("string before handle sign: %s\n", s);
	sign = (*s == '-' ? -1 : 1);
	if (*s == '+' || *s == '-')
		*s++;
	// printf("string after handle sign: %s\n", s);
	while (isdigit(*s)) {
		// putchar(*s);
		// putchar('\n');
		val = 10.0 * val + (*s - '0');
		// printf("val: %f\n", val);
		*s++;
	}
	if (*s == '.')
		*s++;
	while (isdigit(*s)) {
		val = 10.0 * val + (*s - '0');
		power *= 10.0;
		*s++;
	}
	return sign * val / power;
}

// page 71: convert string s to double
double atof_orig(char s[]) {
	double val, power;
	int i, sign;

	for (i=0; isspace(s[i]); i++)  // skip white space
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	return sign * val / power;
}

int getaline_p(char *s, int lim) {
	int c, i;

	for (i=0; i<lim-1 && (c=getchar()) != EOF && c != '\n'; i++, *s++) {
		*s = c;
	}
	if (c == '\n') {
		*s++ = c;
		i++;
	}
	*s = '\0';
	return i;
}

// page 32
int getaline_orig(char s[], int lim) {
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