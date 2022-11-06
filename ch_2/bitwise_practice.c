/*
Combined compile and run command
gcc -o bitwise_practice bitwise_practice.c && ./bitwise_practice
*/

//////////////// 11/5/22 ////////////////

/*
Things to figure out before exercises on bitwise operators
	/ 1. How to get bit value of integral operators (char, short, int, long; signed and unsigned)
		/ Versions found that use modulo, and bit operators to do this
		/ One keeps leading zeros, other does not
	2. How to get the char, short etc from bits
	3. Do conversions to/from binary need to be handled differently for char vs short vs int, etc?
		Accepting char, int, short, long are INTERCHANGEABLE. Chars are evaluated as their int values
		Returning also interchangeable, change printing to print as char rather than int

Useful: I was basically looking for this question, and the answer is no 
(https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format)

Also useful, it linked to the printf question: "The fundamental problem is that you're trying to 
use an int to store your binary representation. An int is just that, an integer. In memory it's 
represented in binary, but the C syntax allows you to use base 10 and base 16 literals when assigning 
or doing other operations on ints. This might make it seem like it's not being treated as a binary 
number, but it really is. In your program you are confusing the base 2 representation and the base 
10 representation. 891717742 (base 10) converted to binary is 110101001001101000100001101110. What 
your algorithm is essentially trying to do is store the base 10 number 110101001001101000100001101110 
in an int. That base 10 number is larger than even a 64 bit number, it would actually would take 
97 bits to store."
(https://stackoverflow.com/questions/52548304/converting-decimal-to-binary-with-long-integer-values-c)


Findings about int_to_binary_modulo(), for various arg types
	'c' 			-> 99 to binary: 1100011
	17 				-> 17 to binary: 10001
	17L 	 		-> 17 to binary: 10001
	short n = 17 	-> 17 to binary: 10001
	char c = 65 	-> 65 to binary: 1000001
	char 'A' 		-> 65 to binary: 1000001
	65 				-> 65 to binary: 1000001

Compare with binary_to_int_modulo(int n)
	1100011			-> binary 1100011 to int: 99
	1000001			-> binary 1000001 to decimal: 65
*/

/*
#include <stdio.h>
#include <string.h>

void int_to_binary_bitwise(int n);
void int_to_binary_modulo(int n);
int binary_to_int_modulo(int n);

int main() {

	// int_to_binary_modulo(65); // prints value only
	
	// int_to_binary_bitwise(8); // CAUTION only accepts 32 bit int. Prints value only
	printf("%d\n", binary_to_int_modulo(11111111)); // returns int
}

// print int as bits [copied from internet]
void int_to_binary_modulo(int n) {
	printf("%d to binary: ", n);
	
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

// this method will print all the 32 bits of a number
// copied from https://www.scaler.com/topics/decimal-to-binary-in-c/
void int_to_binary_bitwise(int n) {
	printf("bitwise int %d to binary: ", n);

    // assuming 32-bit integer
    for (int i = 31; i >= 0; i--) {
        
        // calculate bitmask to check whether
        // ith bit of num is set or not
        int mask = (1 << i);
        
        // ith bit of num is set 
        if (n & mask)
           printf("1");
        // ith bit of num is not set   
        else 
           printf("0");
    }
    printf("\n");
}

// CAUTION this is using int to store a binary representation, not intended use of int
// also copied from internet
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
*/

//////////////// 11/6/22 ////////////////

/* try out shift operators

Results with x = 13, binary 1101
left shifts (point left, <<)
	x = x << 0 		-> 1101   		-> decimal 13
	x = x << 1 		-> 11010 		-> decimal 26
	x = x << 2 		-> 110100 		-> decimal 52
	x = x << 3 		-> 1101000 		-> decimal 104
	x = x << 4  	-> 11010000 	-> decimal 208

Results with x = 53, binary 110101
right shifts (point right, >>)
	x = x >> 0 		-> 110101 		-> decimal 53
	x = x >> 1 		-> 11010 		-> decimal 26
	x = x >> 2 		-> 1101			-> decimal 13
	x = x >> 3 		-> 110 			-> decimal 6
	x = x >> 4 		-> 11 			-> decimal 3

Conclusion: left shift add that int count of zeros to right end of number, doubling it for each digit
right shift deletes that number of bits from right end, halving it for each digit


#include <stdio.h>

void int_to_binary(int n);
int binary_to_int_modulo(int n);

int main() {
	printf("int from binary = %d\n", binary_to_int_modulo(101101001));

	int x = 53;
	// printf("start as int: %d\n", x);
	//printf("start as binary: ");
	//int_to_binary(x);

	x = x >> 4;
	printf("binary after shift: ");
	int_to_binary(x);
	printf("decimal after shift: %d\n", x);
}
*/


/***********************************
try out inversion operator

*/

#include <stdio.h>

void int_to_binary(int n);

int main() {
	int x = 5;
	printf("original int: %d\n", x);
	printf("original binary: ");
	int_to_binary(x);
	
	x = ~(x);
	printf("int after one's complement: %d\n", x);
	printf("binary after one's complement: ");
	int_to_binary(x);
	return 0;
}

///////////////// use these methods with all mains /////////////////

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