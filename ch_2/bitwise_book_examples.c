/*
Combined compile and run command
gcc -o bitwise_book_examples bitwise_book_examples.c && ./bitwise_book_examples
*/

//////////////// 11/5/22 ////////////////

/**************************************** 
Section 2.9 page 48 example 1
	"bitwise AND operator & is often used to mask *off* some set of bits"
	-> any bits that are 0 in mask will be 0 in the output
	-> mask and input are aligned at their right ends

Sample outputs
	int at start: 255
	binary at start: 11111111 		-> 8 ones
	int after mask "& 0177": 127
	binary after mask: 1111111 		-> 7 ones
	
	int at start: 500
	binary at start: 111110100 		-> 9 bits
	int after mask "& 0177": 116
	binary after mask: 1110100 		-> rightmost 7 bits only, unchanged

	int at start: 2010 
	binary at start: 11111011010	-> 11 bits
	int after mask "& 0177": 90
	binary after mask: 1011010 		-> rightmost 7 bits only, unchanged

	int at start: 125 				
	binary at start: 1111101
	int after mask "& 0177": 125
	binary after mask: 1111101 		-> unchanged if orig number 7 bits or under
*/

/*
#include <stdio.h>

void int_to_binary(int n);
int binary_to_int_modulo(int n);

int main() {
	int n = 125;
	printf("int at start: %d\n", n);
	printf("binary at start: ");
	int_to_binary(n);

	// "sets to zero all but the lower-order 7 bits of n"
	// leading 0 means '0177' is an octal
	// 177 in octal = 127 in decimal = 1111111 in binary [ie 7 ones]
	// note: binary with 7 zeros actually has 32-7 leading zeros
	// this mask means: copy the rightmost 7 bits as they are, all others to 0
	//     leading zeros where mask is zero (before it starts), because a 0 & will always be 0
	// zero in mask means zero in output
	n = n & 0177;
	printf("int after mask \"& 0177\": %d\n", n);
	printf("binary after mask: ");
	int_to_binary(n);
}
*/


/**************************************** 
Section 2.9 page 48 example 2, version 1
	"bitwise OR operator | is used to turn bits off"

Example runs, for "SET_ON 1111"
	int at start: 500
	binary at start: 111110100 			-> 9 digits
	int after mask: 1527
	binary after mask: 10111110111 		-> 11 digits

	int at start: 257
	binary at start: 100000001 			-> 9 digits
	int after mask: 1367
	binary after mask: 10101010111 		-> 11 digits

Example runs, for int n = 257, binary 100000001
	
	SET_ON 1 	-> 100000001
	SET_ON 2 	-> 100000011
	SET_ON 3 	-> 100000011
	SET_ON 4 	-> 100000101
	SET_ON 64 	-> 101000001
	SET_ON 127 	-> 101111111
	SET_ON 1024  ->10100000001


#include <stdio.h>

void int_to_binary(int n);

// issue though: defined values can't be printed, so difficult to debug with this setup
#define SET_ON 64 // this is treated as an int, its binary then made into the mask

int main() {
	int n = 257;
	//printf("int at start: %d\n", n);
	//printf("binary at start: ");
	//int_to_binary(n);

	// "sets to one in x the bits that are set to one in SET_ON"
	// bitwise or mask means any 1 in mask is 1 in output
	// 0 in mask means result there is unchanged from input
	n = n | SET_ON;
	//printf("int after mask: %d\n", n);
	printf("binary after mask: ");
	int_to_binary(n);
}
*/


/**************************************** 
Section 2.9 page 48 example 2, version 2

Example run with mask printable
	int at start: 257
	binary at start: 100000001
	binary of mask: 1000000
	int after mask: 321
	binary after mask: 101000001

	int at start: 257
	binary at start: 100000001
	binary of mask: 10000
	int after mask: 273
	binary after mask: 100010001


#include <stdio.h>

void int_to_binary(int n);

int main() {
	int n = 257;
	printf("int at start: %d\n", n);
	printf("binary at start: ");
	int_to_binary(n);

	int mask = 16;
	printf("binary of mask: ");
	int_to_binary(mask);
	
	// "sets to one in x the bits that are set to one in mask"
	// bitwise or mask means any 1 in mask is 1 in output
	// 0 in mask means result there is unchanged from input
	n = n | mask;

	printf("int after mask: %d\n", n);
	printf("binary after mask: ");
	int_to_binary(n);
}
*/


/**************************************** 
Section 2.9 page 49 example 1, part 1

"The unary operator ~ yields the one's complement of an integer; that is, it converts
each 1-bit into a 0-bit and vice versa"

Example output: mask prints empty, since all zeros
	n at start: 257
	n binary at start: 100000001
	mask binary start: 111111
	mask binary after ~ : 
	n after & with ~ of mask: 100000000

Effect here: mask is initially 111111, then after ~ applied it is 000000,
then that & with another number, last 6 digits of it are set to zero

# include <stdio.h>

void int_to_binary(int n);

int main() {
	int n = 257;
	printf("n at start: %d\n", n);
	printf("n binary at start: ");
	int_to_binary(n);

	// octal 077 = decimal 63 = binary 111111
	printf("mask binary start: ");
	int_to_binary(63);

	int mask = ~63;
	printf("mask binary after ~ : ");
	int_to_binary(mask);

	n = n & mask;
	printf("n after & with ~ of mask: ");
	int_to_binary(n);
}
*/


/**************************************** 
Section 2.9 page 49 example 1, part 2

Difference it mentions between "x & ~077" (independent of word length) 
versus "x & 0177700" (presumes that x is 16 bits)

octal 077 		= decimal 63  		= binary 111111
octal ~077 		= 0
octal 0177700 	= decimal 65472 	= binary 1111111111000000

(oct) 077 to binary: 111111
~077 to binary: 
(oct) 0177700 to binary: 1111111111000000

Point: the second one has 6 zeros, but *after filling in leading ones to fill 16 bits*
First one only populates (with zeros) the 6 digits to be masked

# include <stdio.h>

void int_to_binary(int n);

int main() {
	int mask_1 = 63;
	printf("(oct) 077 to binary: ");
	int_to_binary(mask_1);
	printf("~077 to binary: ");
	int_to_binary(~mask_1);

	int mask_2 = 65472;
	printf("(oct) 0177700 to binary: ");
	int_to_binary(mask_2);
}
*/

//////////////// 11/5/22 ////////////////

/**************************************** 
Section 2.9 page 49 example 2

Results all with x = 657, binary 1010010001
	getbits(x, 4, 3) 	-> binary 100 (int 4)
	getbits(x, 4, 5) 	-> binary 10001 (int 17)
	getbits(x, 7, 4) 	-> binary 1001 (int 9)
	getbits(x, 9, 3) 	-> binary 101 (int 5)
	getbits(x, 3, 3) 	-> binary [none] (int 0)
	getbits(x, 3, 4) 	-> binary 1 (int 1)  		omits leading zeros
*/

#include <stdio.h>

void int_to_binary(int n);
unsigned getbits(unsigned x, int p, int n);

int main() {
	int x = 657;
	printf("start as int: %d\n", x);
	printf("start as binary: ");
	int_to_binary(x);
	unsigned end = getbits(x, 3, 4);
	printf("result as int: %d\n", end);
	printf("result in binary: ");
	int_to_binary(end);
}

// function get n bits from position p
// returns the (right adjusted) n-bit field of x that begins at position p
// assume that bit position 0 is at right, n and p are positive
// eg getbits(x, 4, 3) returns the three bits in positions 4, 3, and 2, right adjusted

// expression x >> (p + 1 - n) moves desired field to right end of the word
// ~0 is all 1-bits
// shifting it [1-bits] left n bit positions with ~0 << n places zeros in rightmost n bits
// complementing that with ~ makes a mask with ones in the rightmost n bits 
unsigned getbits(unsigned x, int p, int n) {
	return (x >> (p + 1 - n)) & ~(~0 << n);
}


///////// HELPER FUNCTIONS, USE FOR ALL EXAMPLES /////////

// print int in binary
void int_to_binary(int n) {
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

int binary_to_int_modulo(int n) {
	printf("binary %d to decimal: ", n);

    int dec_value = 0;
    int base = 1; // initialize base value to 1, i.e 2^0
  
    int temp = n;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;
        dec_value += last_digit * base;
        base = base * 2;
    }
    return dec_value;
}