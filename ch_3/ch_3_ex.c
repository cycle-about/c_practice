/*
Combined compile and run command
gcc -o ch_3_ex ch_3_ex.c && ./ch_3_ex
*/

/**************************************** 
3-1 Our binary search makes two tests inside the loop, when one would suffice
(at the price of more tests outside). Write a version with only one test inside
the loop and measure the difference in run-time.

Two-check runtimes
	0.000056
	0.000041
	0.000040
	0.000040

One-check runtimes
	0.000044
	0.000043
	0.000048
	0.000044

Loops for particular example: 4 with orig, and 5 with new
This new version continues bisect loop even if target is found


#include <stdio.h>
#include <time.h>

int binsearch_orig(int x, int v[], int n);
int binsearch_new(int x, int v[], int n);

int main() {
	int v[] = {-20, -10, -6, -1, 1, 5, 6, 9, 10, 12, 15, 16, 18, 20, 21, 22, 25, 27, 28, 30, 35, 38, 41};
	int n = sizeof(v) / sizeof(v[0]);
	int x = -20;

	double runtime = 0.0;
	clock_t begin = clock();

	int r = binsearch_new(x, v, n);
	printf("position of %d in array: %d\n", x, r);

	clock_t end = clock();
	runtime += (double) (end - begin) / CLOCKS_PER_SEC;
	printf("Elapsed time %f seconds\n", runtime);
}

int binsearch_new(int x, int v[], int n) {
	int low, high, mid, i;

	low = i = 0;
	high = n - 1;

	//printf("start max is %d\n", high);
	while (low <= high) {
		i++;
		mid = (low + high) / 2;
		//printf("index checked: %d\n", mid);
		if (x < v[mid]) {
			high = mid - 1;
			//printf("search lower, new max is %d\n", high);
		} else {
			low = mid + 1;
			//printf("search higher, new min is %d\n", low);
		}
	}
	printf("loops done: %d\n", i);
	if (v[low] == x)
		return low;
	else if (v[high] == x)
		return high;
	else 
		return -1;    // no match
}

int binsearch_orig(int x, int v[], int n) {
	int low, high, mid, i;

	low = i = 0;
	high = n - 1;
	while (low <= high) {
		i++;
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else {
			printf("loops done: %d\n", i);
			return mid;
		}
	}
	printf("loops done: %d\n", i);
	return -1;    // no match
}
*/


/**************************************** 
3-2 Write a function escape(s, t) that converts characters like newline and tab
into visible escape sequences like \n and \t as it copies the string s to t. Use
a switch. Write a function for the other direction as well, converting escape
sequences into the real characters.

Starting point: chapter 1 page 29 example that prints longest line of input


#include <stdio.h>

#include <stdio.h>
#define MAXLINE 1000 // maximum chars in a line

int getaline(char line[], int maxline);
void escape(char to[], char from[]);
void unescape(char to[], char from[]);

int main() {
	int len;    // current line length
	char line[MAXLINE];    // current input line
	char escaped[MAXLINE];    // escaped version saved here

	while ((len = getaline(line, MAXLINE)) > 0) {
		unescape(escaped, line);
		printf("%s", escaped);
	}
	return 0;
}

// replace newline and tab into visible escape sequences
// assumes 'to' is big enough
void escape(char to[], char from[]) {
	int i_from, i_to;

	i_from = i_to = 0;
	while (from[i_from] != '\0') {
		switch (from[i_from]) {
			case '\n':
				to[i_to] = '\\';
				to[++i_to] = 'n';
				break;
			case '\t':
				to[i_to] = '\\';
				to[++i_to] = 't';
				break;
			default:
				to[i_to] = from[i_from];
				break;
		}
		++i_from;
		++i_to;
	}
}

// replace visible escape sequences into newline and tab
// assumes 'to' is big enough
void unescape(char to[], char from[]) {
	int i_from, i_to;

	i_from = i_to = 0;
	while (from[i_from] != '\0') {
		if (from[i_from] == '\\') {
			// switch defined by expression, compared against 'cases'
			switch (from[i_from + 1]) { 	// is char after a '\' n or t
				case 'n': 				// case must be constatant integer value OR constant expression
					to[i_to] = '\n';
					i_from++; 			// increment to skip second char in orig
					break;
				case 't':
					to[i_to] = '\t';
					i_from++; 			// increment to skip second char in orig
					break;
				default:
					to[i_to] = from[i_from];
					break;
			}
		}
		else {
			to[i_to] = from[i_from];
		}
		++i_from;
		++i_to;
	}
	// copy last character
	to[i_to] = from[i_from];
}

// read a line into s, return length
int getaline(char s[], int lim) {
	int c, i;

	for (i = 0; i<lim-1 && (c=getchar())!=EOF && c !='\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
*/


/**************************************** 
3-3 Write a function expand(s1, s2) that expands shorthand notations like a-z in the string s1
into the equivalent complete list abc...xyz in s2. Allow for letters of either case and digits,
and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or
trailing - is taken literally.


#include <stdio.h>
#include <ctype.h>

#define MAXLINE 100 // maximum chars in a line

int getaline(char line[], int maxline);
void expand(char s1[], char s2[]);
int get_start(int end);
int get_end(int start);

int main() {

	int len; 			   		// length current line
	char line[MAXLINE];    		// current input line
	char expanded[MAXLINE]; 	// expanded version of input line

	while ((len = getaline(line, MAXLINE)) > 0) {
		expand(line, expanded);
		printf("expanded line: %s\n", expanded);
	}
}

void expand(char from[], char to[]) {
	int i_from, i_to, j;
	int c, start, end;

	for (i_from = i_to = 0; ((c = from[i_from]) != '\0'); i_from++) {
		
		// case: handle filling in range
		if (c == '-') {

			// case: dash is first char in line (cannot check char before), alpha after
			if (i_from == 0 && isalnum(from[i_from+1])) {
				end = from[i_from+1];
				start = get_start(end);
				i_from++;    				// range already wrote char after dash in from[]
			}

			// case: non-alpha before, alpha after
			else if ( !(isalnum(from[i_from-1])) && isalnum(from[i_from+1])) {
				end = from[i_from+1];
				start = get_end(start);
				i_from++;    				// range already wrote char after dash in from[]
			}

			// case: alpha before, non-alpha after (including null, meaning dash was last char in line)
			else if (isalnum(from[i_from-1]) && !(isalnum(from[i_from+1]))) {
				start = from[i_from-1];
				end = get_end(start);
				i_to--;    					// over-write already-copied start char of range
			}

			// case: alpha before, alpha after
			else if (isalnum(from[i_from-1]) && isalnum(from[i_from+1])) {
				start = from[i_from-1];    	// start char for loop
				end = from[i_from+1];      	// end char for loop
				i_from++;    				// range already wrote char after dash in from[]
				i_to--;    					// over-write already-copied start char of range
			}
			else {
				printf("RANGE UNDEFINED\n");
			}

			for (j = start; j <= end; j++) {
				to[i_to++] = j;
			}
		}

		// case: not a range, copy only
		else {
			to[i_to++] = from[i_from];
		}
	}
	to[i_to] = '\0';
}

int get_start(int end) {
	if isdigit(end)
		return '0';
	else if (isupper(end))
		return 'A';
	else if (islower(end))
		return 'a';
}

int get_end(int start) {
	if isdigit(start)
		return '9';
	else if (isupper(start))
		return 'Z';
	else if (islower(start))
		return 'z';
}

// read a line into s, return length of line
int getaline(char s[], int lim) {
	int c, i;

	for (i = 0; i < lim-1; i++) {
		c = getchar();
		if (c == EOF) {
			break;
		} else if (c == '\n') {
			break;
		} else {
			s[i] = c;
		}
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
*/

/**************************************** 
3-4 In a two's compliment number representation, our version of itoa does not handle the largest
negative number, that is, the value of n equal to -(2^(wordsize-1)). Explain why not. Modify it
to print that value correctly, regardless of the machine on which it runs.

Conversions for 8-bit word size

	Decimal 	Binary 			Twos Complement
	 127 		0111 1111		1000 0001
	 126 		0111 1110 		1000 0010
	  64 		0100 0000 		1100 0000
	  63 		0011 1111 		1100 0001
	   5 		0000 0101 		1111 1011
	   4 		0000 0100 		1111 1100
	   3 		0000 0011 		1111 1101
	   2 		0000 0010 		1111 1110
	   1 		0000 0001 		1111 1111
	   0  		0000 0000 		0000 0000
	  -1 		1111 1111  		0000 0001
	  -2 		1111 1110 		0000 0010
	  -3 		1111 1101 		0000 0011
	  -4 		1111 1100 		0000 0100
	  -5 		1111 1011 		0000 0101
	 -63 		1100 0001 		0011 1111
	 -64 		1100 0000 		0100 0000
	-127 		1000 0001		0111 1111
	-128 		1000 0000		1000 0000

orig itoa() cannot print eg -128 because: at the conditional to check for negative, it executes
"n = -(-128)", and this overflows the maximum positive int that can be in n.

Trace of what happens to -128 (two's complement: 1000 0000) in itoa()

void itoa_orig(int -128, char s[]) {
	int i, sign;

	if ((sign = n) < 0)   	// sign = -128			
		n = -n; 			// n = 128 decimal, outside range for max positive number
	i = 0;

What is output with most negative int
	printf("%d", INT_MIN) 		-> "-2147483648"
	itoa(INT_MIN) 				-> "-("
	ascii value of '('
		printf("%d", '(') 		-> 40, binary: 

Compare with max positive int: itoa(INT_MAX)
	printf("%d", INT_MIN) 		-> "2147483647"
	itoa(INT_MIN) 				-> "2147483647"

Approaches considered for handling largest negative number
	
	Tried
		1. Move first ones place to string before handling sign
			This does still work for all positive numbers
			This somehow mangles original ones place digit, int an eg ',' or '('
			? Does this show something additional about problem, is it actually what I think it is ?

				Ones place in
				negative number 	Char put in string 	ASCII of char 	ASCII of digit
					1  					/ 					47 					49
					2 					. 					46 					50
					3 					- 					45 					51
					7 					

	Do not see a way to undo after putting into string
		2. Add 1 to the number before making it positive
		3. Bit shift

	Seems relevant, do not see how to implement
		4. Bit mask

*/

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <ctype.h>

#define MAXCHAR 32

void itoa_orig(int n, char s[]);
void itoa_new(int n, char s[]);
void reverse(char s[]);

int main() {
	int i = -7;
	char s[MAXCHAR];
	itoa_new(i, s);
	printf("string value: %s\n", s);
}

// convert n to characters in s
void itoa_new(int n, char s[]) {
	int i, sign;

	i = 0;
	
	printf("first n: %d\n", n);
	s[i++] = n % 10 + '0';  // put ones place digit into fist string index
	printf("first ones digit: ");
	putchar(n % 10 + '0');
	printf("\n");
	
	n /= 10; 				// delete that ones place from number
	printf("n after division: %d\n", n);


	if ((sign = n) < 0)   	// assign 'sign' to remaining n (without orig ones digit)
		n = -n; 			// make n positive if it was negative originally
	printf("n after handle sign: %d\n", n);
	
	for (; n > 0; n /= 10) {
		printf("n in loop: %d\n", n);
		s[i++] = n % 10 + '0';     	// assign left
		printf("ones digit: ");
		putchar(n % 10 + '0');
		printf("\n\n");
	}

	if (sign < 0)
		s[i++] = '-'; 	// if original value of n was negative, add '-' to end of string
	
	s[i++] = '\0';
	reverse(s);
}

// convert n to characters in s
void itoa_orig(int n, char s[]) {
	int i, sign;

	if ((sign = n) < 0)   	// assign 'sign' to n
		n = -n; 			// make n positive if it was negative originally
	i = 0;
	do {
		// assign to string s from left to right: leftmost digit of n (one's place)
		s[i++] = n % 10 + '0';     	// assign left
		// after each assignment, REMOVE one's place from n 
	} while ((n /= 10) > 0); 		// delete it
	if (sign < 0)
		s[i++] = '-'; 	// if original value of n was negative, add '-' to end of string
	s[i++] = '\0';
	reverse(s);
}

// page 62: reverse string in place
void reverse(char s[]) {
	int c, i, j;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}