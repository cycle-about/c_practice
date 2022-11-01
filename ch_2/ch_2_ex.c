/*
Combined compile and run command
gcc -o ch_2_ex ch_2_ex.c && ./ch_2_ex
*/

//////////////// 10/29/22 ////////////////

/**************************************** 
2-1 Write a program to determine the ranges of char, short, int, and long variables,
	both signed and unsigned, by printing appropriate values from standard headers 
	and by direct computation. Harder if you compute them: determine the ranges of 
	the various floating-point types.

	Version A. compute the values

#include <stdio.h>

int main() {

	// signed char i, j;  		// max: 127 		min: -128
	// unsigned char i, j; 		// max: 255 		min:  0
	
	// signed short i, j; 		// max: 32,767		min: -32,768
	// unsigned short i, j;		// max: 65,535 		min: 0
	
	//// must change print statement to use '%ld' for 'unsigned int'
	//// oddly it prints '-1' with %d, even with 'max' still declared as int only
	// signed int i, j; 		// max: 2,147,483,647 		min: -2,147,483,648
	// unsigned int i, j;		// max: 4,294,967,295 		min: 0

	//// use print statements with '%ld'
	//// change max and min to long
	// left this running for over 10 min without it finishing
	// signed long i, j;			// max:  		min: 

	long max, min;
	int max_done, min_done;

	max = min = max_done = min_done = 0;

	for (i = j = 0; (max_done + min_done) < 2; i++, j--) {
		// printf("i: %d, j: %d\n", i, j);
		// printf("max: %d, min: %d\n", max, min);
		if (max > i) {    // value of i has looped
			max_done = 1;
		}
		if (max < i) {
			max = i;
		}
		if (min > j) {    // value of j has looped
			min_done = 1;
		}
		if (max_done && min == j) { // unsigned case, j has looped but never goes negative
			min_done = 1;
		}
		if (min > j) {
			min = j;
		}

	}
	printf("maximum: %ld\n", max);
	printf("minimum: %ld\n", min);
}
*/

//////////////// 10/30/22 ////////////////

/**************************************** 
2-1 Version B. Print appropriate values from standard headers
	See Appendix B11, page 257 for headers info
	Values returned are *minimums* only, actual system could use larger

	Note: there is no min defined for UCHAR, UINT, ULONG (they're 0)
	Bits needed for decimal x = log2(x)


#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
	// char: 8 bits = 1 byte
	printf("CHAR_BIT: %d\n", CHAR_BIT); // 8
	printf("SCHAR_MAX: %d\n", SCHAR_MAX); // 127
	printf("SCHAR_MIN: %d\n", SCHAR_MIN); // -128
	printf("UCHAR_MAX: %d\n", UCHAR_MAX); // 255

	// short: log2(65,536) = 16 bits = 2 bytes
	printf("SHRT_MAX: %d\n", SHRT_MAX); // 32,767
	printf("SHRT_MIN: %d\n", SHRT_MIN); // -32,768
	printf("USHRT_MAX: %d\n", USHRT_MAX); // 65,535

	// int: 32 bits = 4 bytes
	printf("INT_MAX: %d\n", INT_MAX); // 2,147,483,648
	printf("INT_MIN: %d\n", INT_MIN); // -2,147,483,648
	printf("UINT_MAX: %ud\n", UINT_MAX); // 4,294,967,295

	// long: 64 bits = 8 bytes
	printf("LONG_MAX: %ld\n", LONG_MAX); // 9,223,372,036,854,775,807
	printf("LONG_MIN: %ld\n", LONG_MIN); // -9,223,372,036,854,775,808
	printf("ULONG_MAX: %lu\n", ULONG_MAX); // 18,446,744,073,709,551,615
}
*/


/**************************************** 
2-2 Write a loop equivalent to this for loop without using && or ||
	Loop is from the input function getaline() in chapter 1

	for (int i = 0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
		s[i] = c;

	Boolean clauses to handle: do statement if all three true
		i<lim-1
		c=getchar()) != '\n'
		c != EOF

	first draft: did *not* work since no breaks
		for (int i = 0; i < lim-1; ++i) {
			if (c=getchar()) != '\n' {
				if (c != EOF) {
					s[i] = c;
				}
			}
		}


#include <stdio.h>
#define MAXLINE 100 // maximum chars in a line

int getaline(char line[], int maxline);

int main() {
	int len; 			   // length current line
	char line[MAXLINE];    // current input line
	char longest[MAXLINE];    // longest line saved here

	while ((len = getaline(line, MAXLINE)) > 0)
		printf("%s\n", line);
	return 0;
}

// read a line into s, return length
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
2-3 Write the function 'htoi(s)' which converts a string of hexadecimal digits (including an
optional 0x or 0X) into its equivalent integer value. The allowable digits are '0' to '9', 
'a' through 'f', and 'A' through 'F' 

// page 43 example
// atoi: convert s to integer

#include <stdio.h>
#include <ctype.h>

int atoi(char s[]);

int main() {
	char s[] = "12345";
	printf("%d\n", atoi(s));
}

int atoi(char s[]) {
	int i, n;
	n = 0;
	for (i = 0; isdigit(s[i]); ++i) {
		n = 10 * n + (s[i] - '0');
	}
	return n;
}

Pieces that need to be changed for hex
	Make the input var a hex
	Loop checks that input chars are : digit, a-f, or A-F
	Skip first two chars IF they are 0x or 0X

//////////////// 10/30/22 and 10/31/22 ////////////////

#include <stdio.h>
#include <ctype.h>

int htoi(char s[]);

int main() {
	char s[] = "0X233Fa4";
	printf("%d\n", htoi(s));
}

int htoi(char s[]) {
	int i, n;
	n = 0;

	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
		i = 2;
	} else
		i = 0;
	printf("start index: %d\n", i);
	
	for (i; isdigit(s[i]) || (s[i] >= 'a' && s[i] <= 'f') || (s[i] >= 'A' && s[i] <= 'F'); ++i) {
		printf("s[i]: %d\n", s[i]);
		if (isdigit(s[i])) {
			printf("digit\n");
			n = 16 * n + (s[i] - '0');
		}
		else if (s[i] >= 'a' && s[i] <= 'f') {
			printf("lower\n");
			n = 16 * n + (s[i] - 'a' + 10);
		}
		else {
			printf("upper\n");
			n = 16 * n + (s[i] - 'A' + 10);
		}
	}
	return n;
}
*/

/**************************************** 
2-4 Write an alternate version of squeeze(s1, s2) that deletes each character in s1 
that matches any char in the *string* s2

// original squeeze: delete all c from s (page 47)

#include <stdio.h>

void squeeze(char s[], int c);

int main() {
	char s[] = "test of removing characters";
	squeeze(s, 'a');
	printf("%s\n", s);
}

void squeeze(char s[], int c) {
	int i, j;

	for (i = j = 0; s[i] != '\0'; i++)
		if (s[i] != c)
			s[j++] = s[i];
	s[j] = '\0';
}

//////////////// 11/1/22 ////////////////

#include <stdio.h>
#include <ctype.h>

// each index has a T/F for whether to copy the corresponding letter
// upper case letters indices 0 to 26, lower case letters indices 27 to 52
#define alphabet 52 

enum boolean { FALSE, TRUE };

void squeeze(char s[], int copy[]);
void get_copy_arr(char r[], int copy[]);
int get_letter_index(char c);

int main() {
	char s[] = "123_AaBbCcDdEe+-pm3333";
	char r[] = "AcDm";
	int copy[alphabet]; 

	get_copy_arr(r, copy);
	squeeze(s, copy);
	printf("%s\n", s);
}

void get_copy_arr(char r[], int copy[]) {
	int i, letter_index;
	// initialize array of what to copy as all true
	for (i = 0; i < alphabet; i++) {
		copy[i] = TRUE;
	}
	// set index of all letters to be skipped to false
	for (i = 0; r[i] != '\0'; i++) {
		if (isalpha(r[i])) {
			letter_index = get_letter_index(r[i]);
			copy[letter_index] = FALSE;
		}
	}
}

void squeeze(char s[], int copy[]) {
	int i, j, letter_index;

	for (i = j = 0; s[i] != '\0'; i++) {
		if (isalpha(s[i])) {
			letter_index = get_letter_index(s[i]);
			if (copy[letter_index] == TRUE) {
				s[j++] = s[i];
			}
		} else {
			s[j++] = s[i];
		}
	}
	s[j] = '\0';
}

// should be passed alpha chars only
int get_letter_index(char c) {
	if (isupper(c)) {
		return c - 'A';
	}
	else if (islower(c)) {
		return c - 'a' + 26; // in copy index after upper case
	}
}
*/

/**************************************** 
2-5 Write the function any(s1, s2), which returns the first location in the string s1
where any character from the string s2 occurs, or -1 if s1 contains no characters
from s2. (The standard library function 'strpbrk' does the same job but returns a pointer
to the location.)

*/

#include <stdio.h>
#include <ctype.h>

// each index has a T/F for whether to copy the corresponding letter
// upper case letters indices 0 to 26, lower case letters indices 27 to 52
#define alphabet 52 

enum boolean { FALSE, TRUE };

void any(char s[], int find[]);
void get_find_arr(char r[], int find[]);
int get_letter_index(char c);

int main() {
	char s[] = "123_AaBbCcDdEe+-pm3333";
	char r[] = "AcDm";
	int find[alphabet]; 

	get_find_arr(r, find);
	any(s, find);
	printf("%s\n", s);
}

void get_find_arr(char r[], int find[]) {
	int i, letter_index;
	// initialize array of what to find as all false
	for (i = 0; i < alphabet; i++) {
		find[i] = FALSE;
	}
	// set index of all letters to be skipped to false
	for (i = 0; r[i] != '\0'; i++) {
		if (isalpha(r[i])) {
			letter_index = get_letter_index(r[i]);
			find[letter_index] = TRUE;
		}
	}
}

void any(char s[], int find[]) {
	int i, j, letter_index;

	for (i = j = 0; s[i] != '\0'; i++) {
		if (isalpha(s[i])) {
			letter_index = get_letter_index(s[i]);
			if (find[letter_index] == TRUE) {
				s[j++] = s[i];
			}
		} else {
			s[j++] = s[i];
		}
	}
	s[j] = '\0';
}

// should be passed alpha chars only
int get_letter_index(char c) {
	if (isupper(c)) {
		return c - 'A';
	}
	else if (islower(c)) {
		return c - 'a' + 26; // in array after upper case
	}
}