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
#include <limits.h>

#define NUM_CHARS UCHAR_MAX 

enum boolean { FALSE, TRUE };

void squeeze(char s[], int copy[]);
void get_copy_arr(char r[], int copy[]);

int main() {
	char s[] = "123_AaBbCcDdEe+-pm3333";
	char r[] = "2+Dd4";
	int copy[NUM_CHARS];  // each index has a T/F for whether to copy the corresponding char

	get_copy_arr(r, copy);
	squeeze(s, copy);
	printf("%s\n", s);
}

void get_copy_arr(char r[], int copy[]) {
	int i, letter_index;
	// initialize array of what to copy as all true
	for (i = 0; i < NUM_CHARS; i++) {
		copy[i] = TRUE;
	}
	// set index of all chars to be deleted to false
	for (i = 0; r[i] != '\0'; i++) {
		copy[r[i]] = FALSE;
	}
}

void squeeze(char s[], int copy[]) {
	int i, j;

	for (i = j = 0; s[i] != '\0'; i++) {
		if (copy[s[i]] == TRUE) {
			s[j++] = s[i];
		}
	}
	s[j] = '\0';
}
*/

/**************************************** 
2-5 Write the function any(s1, s2), which returns the first location in the string s1
where any character from the string s2 occurs, or -1 if s1 contains no characters
from s2. (The standard library function 'strpbrk' does the same job but returns a pointer
to the location.)

#include <stdio.h>
#include <limits.h>

#define NUM_CHARS UCHAR_MAX 

enum boolean { FALSE, TRUE };

int any(char s[], int find[]);
void get_find_arr(char r[], int find[]);

int main() {
	char s[] = "4123_AaBbCcDdEe+-pm3333";
	char r[] = "+Dd4";
	int find[NUM_CHARS];  // each index has a T/F for whether to copy the corresponding char

	get_find_arr(r, find);
	int first_match = any(s, find);
	printf("%d\n", first_match);
}

int any(char s[], int find[]) {
	int first_match = -1;  // initialize to no match found

	for (int i = 0; s[i] != '\0'; i++) {
		if (find[s[i]] == TRUE) {
			return i;
		}
	}
	return first_match;
}

void get_find_arr(char r[], int find[]) {
	int i, letter_index;
	// initialize array of what to find as all false
	for (i = 0; i < NUM_CHARS; i++) {
		find[i] = FALSE;
	}
	// set index of all chars to be deleted to true
	for (i = 0; r[i] != '\0'; i++) {
		find[r[i]] = TRUE;
	}
}
*/

/**************************************** 
2-6 Write a function setbits(x,p,n,y) that returns x with the n bits that begin at 
position p set to the rightmost n bits of y, leaving the other bits unchanged

x and y must be integral operands: char, short, int, long, signed or unsigned

Assume: p counted from same side as example getbits(), so from RIGHT

Breakdown of steps
	/ 1. locate the bits in x to be replaced (counted from index 0 on right)
	2. locate the bits in y to be subbed in (rightmost only)
	3. make a mask of those digits of y that will change only target bits in x,
	  and leave all others before and after unchaged (ie needs 'no effect' bits
	  on right end of mask)

Use from book for steps 1 and 2: getbits() function, 'get n bits from position p'

Test case draft
	x = 341, binary 101010101
	y = 9, binary        1001
	p = 4 					
	n = 3 					000011100
							101010101 <- substituted 3 digits, starting index 3 from right
								1001  <- replace with the 3 rightmost in y
Test case result should be: 101010011


Test case
	x = 291, binary 100100011
	y = 391, binary 110000111
	p = 4
	n = 3
	Result should be: 100111111 (decimal 319)

Mask rule
	Start with the bits from y
	Right shift by p-n+1 bits, so those are unchanged in x
	Operator for replacing bits with mask: OR

*/

#include <stdio.h>

int setbits(int x, int p, int n, int y);
void int_to_binary(int n);
unsigned getbits(unsigned x, int p, int n);

int main() {
	setbits(291, 4, 3, 391);
}

int setbits(int x, int p, int n, int y) {
	printf("original bits of x: ");
	int_to_binary(x);
	printf("original bits of y: ");
	int_to_binary(y);
	
	printf("modifying x starting at index: %d\n", p);
	printf("number of digits to replace: %d\n", n);

	// step 1 locate what to replace in in x
	printf("bits in x to be replaced: "); // for test case should be: 000
	int rep_x = getbits(x, p, n);
	int_to_binary(rep_x);

	// step 2 get bits from y, rightmost n count
	printf("bits in y to swap in: "); // for test case should be: bits 111, decimal 7
	int swap_y = getbits(y, n-1, n);
	int_to_binary(swap_y);

	// step 3 make mask
	int mask = swap_y << p-n+1; // should be 11100
	int_to_binary(mask);

	// step 4 apply mask with OR
	x = x | mask;
	int_to_binary(x); // should be 100111111

	return 0;
}

// return n bits from position p
unsigned getbits(unsigned x, int p, int n) {
	return (x >> (p + 1 - n)) & ~(~0 << n);
}

// print int in binary
void int_to_binary(int n) {
	int a[10], i;
	
	for(i = 0; n > 0; i++) {    
		a[i] = n % 2;    
		n = n / 2;    
	}
	for(i = i - 1; i >= 0; i--) {    
		printf("%d", a[i]);    
	}
	printf("\n");
}