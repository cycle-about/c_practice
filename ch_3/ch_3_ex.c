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

Draft approach
	Find any instance of char '-'
	Start a loop to print all chars in a range
		start char: check char before '-'
			if a space, it is first printable char
			if not a space, it is that preceding char
		end char: check char after '-'
			if a space, it is last printable char
			if not a space, it is that following char

ASCII benchmarks
	0 - 48
	9 - 57
	A - 65
	Z - 90
	a - 97
	z - 122

Cases to handle
	
	Keep these out of for loop
		2. Dash is first char (can't assign a before char)
			-> assign 'start' to start of following char's range 		-> response 2
		3. Dash is last char (can't assign a following char)
			-> assign 'end' to end of prior's range 					-> response 3

	Handle in for loop
		/ 1. Dash has a printable char both before and after it
			-> assign those chars to 'start' and 'end' 					-> response 1
		4. Dash is after nonprintable char
			-> assign 'end' to end of prior's range 					-> response 3
		5. Dash is before nonprintable char
			-> assign 'start' to start of following char's range 		-> response 2

*/

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

	// initialize strings to all nulls
	for (int i = 0; i < MAXLINE; i++) {
		line[i] = '\0';
		expanded[i] = '\0';
	}

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
			printf("\nrange copy");

			// case: dash is first char in line, has alpha after
			if (i_from == 0 && isalnum(from[i_from+1])) {
				end = from[i_from+1];
				start = get_start(end);
				i_from++;    				// already copied char after dash
			}

			// case: range defines its own start and end
			else {
				start = from[i_from-1];    	// start char for loop
				end = from[i_from+1];      	// end char for loop
				i_from++;    				// already copied char after dash
			}

			// all range-filling cases: fill in range from start to end
			printf("\nstart char: ");
			putchar(start);
			printf("\nend char: ");
			putchar(end);
			printf("\n");
			for (j = start; j <= end; j++) {
				to[i_to++] = j;
			}
		}

		// case: not a range, copy only
		else {    // case
			printf("\nNON-RANGE COPY: ");
			putchar(from[i_from]);
			printf("\nindex of from[]: %d\n", i_from);
			printf("index in to[]: %d\n", i_to);
			to[i_to++] = from[i_from];
			printf("check char at index in to[]: ");
			putchar(to[i_to]);
			printf("\n");
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