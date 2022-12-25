// gcc -o ch_5_ex_6.o ch_5_ex_6.c && ./ch_5_ex_6.o

/******************************************************************************** 
5-6 Rewrite appropriate programs from earlier chapters and exercises with pointers
instead of array index handling. Good possiblities include:	
	/ getline - page 32
	/ atof and its variants - page 71
	itoa and its variants - page 64
	reverse - 62
	strindex - page 69
	getop - page 78

*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAXLINE 1000

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

	/**** PART 3 OF 6 ****/
	// test reverse function separately
	char t[100] = "9876543";
	printf("original string: %s\n", t);
	reverse_p(t);
	printf("after reverse: %s\n", t);
	
	char s[100];
	int i = 765432;
	printf("original int: %d\n", i);
	itoa_p(i, s);
	reverse_p(s);
	printf("as string: %s\n", s);

	/**** PART 2 OF 6 ****/
	// printf("%f\n", atof_p("360.009873"));

	/**** PART 1 OF 6 ****/
	// int len;
	// char line[MAXLINE];
	// while ((len = getaline_p(line, MAXLINE)) > 0)
	//	printf("%s", line);
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
	//reverse_p(s);  // issue: this pointer is now at the END of s
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