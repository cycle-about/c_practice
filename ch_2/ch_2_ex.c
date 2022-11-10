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

//////////////// 11/6/22 ////////////////

/**************************************** 
2-6 Write a function setbits(x,p,n,y) that returns x with the n bits that begin at 
position p set to the rightmost n bits of y, leaving the other bits unchanged

x and y must be integral operands: char, short, int, long, signed or unsigned

Assume: p counted from same side as example getbits(), so from RIGHT

Breakdown of steps
	1. locate the bits in x to be replaced (counted from index 0 on right)
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


Test case 1
	x = 291, binary 100100011
	y = 391, binary 110000111
	p = 4
	n = 3
	Result should be: 100111111 (decimal 319)

Test case 1 printouts
	original bits of x: 100100011
	original bits of y: 110000111
	modifying x starting at index: 4
	number of digits to replace: 3
	bits in x to be replaced: 
	bits in y to swap in: 111
	mask: 11100
	x after masking: 100111111

--------

Test case 2
	y = 135, binary 10000111
	y = 15, binary 1111
	p = 6
	n = 4

Test case 2 printouts
	original bits of x: 10000111
	original bits of y: 1111
	modifying x starting at index: 6
	number of digits to replace: 4
	bits in x to be replaced: 
	bits in y to swap in: 1111
	mask: 1111000
	x after masking: 11111111


#include <stdio.h>

int setbits(int x, int p, int n, int y);
void int_to_binary(int n);
unsigned getbits(unsigned x, int p, int n);

int main() {
	setbits(135, 6, 4, 15);
}

int setbits(int x, int p, int n, int y) {
	printf("original bits of x: ");
	int_to_binary(x);
	printf("original bits of y: ");
	int_to_binary(y);
	
	printf("modifying x starting at index: %d\n", p);
	printf("number of digits to replace: %d\n", n);

	// step 1 locate what to replace in in x
	printf("bits in x to be replaced: ");
	int rep_x = getbits(x, p, n);
	int_to_binary(rep_x);

	// step 2 get bits from y, rightmost n count
	printf("bits in y to swap in: ");
	int swap_y = getbits(y, n-1, n);
	int_to_binary(swap_y);

	// step 3 make mask
	int mask = swap_y << p-n+1;
	printf("mask: ");
	int_to_binary(mask);

	// step 4 apply mask with OR
	x = x | mask;
	printf("x after masking: ");
	int_to_binary(x);

	return x;
}
*/

/****************************************
 * first effort, abandoned
2-7 Write a function invert(x, p, n) that returns x with the n bits that begin at position p
inverted (ie 1 changed into 0 and vice versa), leaving the others unchanged

Two operations that can keep bit unchanged with mask:
	and & 1
	or  | 0

test case 1
	x = 341, binary 101010101
	p = 5
	n = 4
Result should be: 101101001 (decimal 361)


#include <stdio.h>

int invert(int x, int p, int n);
unsigned getmask(unsigned x, int p, int n);
void int_to_binary(int n);

int main() {
	printf("%d\n", invert(341, 5, 4));
}

int invert(x, p, n) {
	printf("original bits of x: ");
	int_to_binary(x);
	printf("x invert starting at index: %d\n", p);
	printf("number of digits to invert: %d\n", n);

	// make mask
	unsigned mask = getmask(x, p, n);
	printf("mask decimal: %d\n", mask);
	printf("mask bits (shift inverted): ");
	int_to_binary(mask);

	// apply mask
	x = x & mask;
	printf("x after mask: ");
	int_to_binary(x);

	return x;
}

unsigned getmask(unsigned x, int p, int n) {
	unsigned temp = ~(x >> (p + 1 - n)) & ~(~0 << n);
	return ~(temp << p-n+1);
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
*/

//////////////// 11/9/22 ////////////////

/****************************************
 * second effort, started over
2-7 Write a function invert(x, p, n) that returns x with the n bits that begin at position p
inverted (ie 1 changed into 0 and vice versa), leaving the others unchanged

Needed operation: XOR

Should get for invert(341, 4, 3)
	101010101
 -> 101001001

Should get for invert(585, 5, 2)
	1001001001
 -> 1001111001


#include <stdio.h>

int invert(int x, int p, int n);
void print_bits(int n);

int main() {
	invert(585, 5, 2);
}

int invert(int x, int p, int n) {
	printf("start x bits: ");
	print_bits(x);
	for (int i =0 ; i < n; i++)
		x ^= (0x1 << p-i);
	printf("end x bits: ");
	print_bits(x);
	return x;
}

// print int in binary
void print_bits(int n) {
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
*/


/****************************************
2-8 Write a function rightrot(x,n) that returns the value of the integer x rotated to the
right by n bit positions

Bit Rotation: A rotation (or circular shift) is an operation similar to shift except that 
the bits that fall off at one end are put back to the other end.

Algorithm from search results preview only
	Loop n times, x >> 1 each iteration; if the old low bit of x was 1, set the new high bit.

Check rightmost bit: bitwise and & with one-bit mask of 1

Should get for rotate(143, 2)
	0000000010001111
 -> 1100000000100011  (decimal 49,187)

Should get for rotate(49293, 3)
	1100000010001101
 -> 1011100000010001  (decimal 47,121)

happening for "x |= (1 << INT_BITS);"
	warning: left shift count >= width of type
https://stackoverflow.com/questions/4201301/warning-left-shift-count-width-of-type
Resolution: set to presumes highest bit position is 16


#include <stdio.h>

#define BITS 15

int rotate(int x, int n);
void print_bits(int n);

int main() {
	printf("result: %d\n", rotate(49293, 3));
}

int rotate(int x, int n) {
	printf("start x bits: ");
	print_bits(x);
	int low;
	for (int i = 0 ; i < n; i++) {
		low = x & 0x1;    // low gets value of start rightmost bit
		x >>= 1;
		if (low == 1) {
			int mask = (1 << BITS);
			printf("mask: ");
			print_bits(mask);
			x |= mask;    // set highest bit to 1 if prior low was 1
		}
	}
	printf("end x bits: ");
	print_bits(x);
	return x;
}

// print int in binary
void print_bits(int n) {
	int a[32], i;
	
	for(i = 0; n > 0; i++) {    
		a[i] = n % 2;    
		n = n / 2;    
	}
	for(i = i - 1; i >= 0; i--) {    
		printf("%d", a[i]);    
	}
	printf("\n");
}
*/ 


/****************************************
2-9 In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit in x.
Explain why. Use this observation to write a faster version of 'bitcount'.

1. Getting x-1 in two's complement has the effect of 'carrying' the subtract leftwards until
reaching the first bit set to 1. That then becomes 0, and 'carrying' the value back rightwards
has the effect of flipping all bits from that first 1 to the least significant bit, inclusive
of the first 1

When doing an & with that flipped-until-first-1 value for x-1, the least significant 1 in the
original is now 0 in x-1, so with & becomes 0 in the result. All following less-significant 0's 
in the original are 0 in the & result.

2. How to use this for alternate version of bitcount
Call x &= x-1 until x is 0. Count those calls. It will only loop until 1's are gone, rather than 
every digit as in the original version

*/

#include <stdio.h>

void print_bits(int n);
void and_prints(int x);
int bitcount_orig(unsigned x);
int bitcount_new(unsigned x);

int main() {
	int x = 343;
	print_bits(x);
	bitcount_new(x);
	bitcount_orig(x);
}

// using mask: count bits in x set to 1
int bitcount_new(unsigned x) {
	int i; // loops used for calculation: one per bit found

	printf("\nnew bitcount\n");
	// termination condition: when x is 0, so once there are no 1's left in it
	// incrementor: & mask to turn the next 1 to a 0
	for (i = 0; x != 0; i++) {
		print_bits(x);
		x &= x-1;
	}
	printf("  loops used: %d\n", i);
	printf("  ones count: %d\n", i);
	return i;
}

// original: count bits in x set to 1
int bitcount_orig(unsigned x) {
	int b; // 1 bits counted
	int i; // loops used for calculation

	printf("\noriginal bitcount\n");
	// termination condition: end when x is 0, so once there are no 1's left in it
	// incrementor: right shift by one, so remove least sig bit
	for (b = i = 0; x != 0; x >>= 1, i++) {
		print_bits(x);
		if (x & 01) // bitwise and of the least sig bit, with a 1: check bit, returns 1 if bit was 1
			b++;
	}
	printf("  loops used: %d\n", i);
	printf("  ones count: %d\n", b);
	return b;
}

void and_prints(int x) {
	print_bits(x);
	printf("    (x: %d)\n", x);
	print_bits(x-1);
	printf("    (x-1: %d)\n", x);
	x &= (x-1);
	print_bits(x);
	printf("    (& masked: %d)\n", x);
}

// print int in binary
void print_bits(int n) {
	int a[32], i;
	
	for(i = 0; n > 0; i++) {    
		a[i] = n % 2;    
		n = n / 2;    
	}
	for(i = i - 1; i >= 0; i--) {    
		printf("%d", a[i]);    
	}
	printf("\n");
}