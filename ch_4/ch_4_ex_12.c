// gcc -o ch_4_ex_12 ch_4_ex_12.c && ./ch_4_ex_12

/******************************************************************************** 
4-12 Adapt the ideas of printd to write a recursive version of itoa; that is,
convert an integer into a string by calling a recursive routine

	printd: takes int and s[], puts chars right to left into s[], reverses s[]
	itoa_orig: takes int, prints its chars to left to right

printd orig with printouts
	n: -12345
	-n: 1234
	n: 123
	n: 12
	n: 1
	12345


#include <stdio.h>
#include <string.h>

void itoa_recursive(int n, char s[]);
void itoa_orig(int n, char s[]);
void printd(int n);
void reverse(char s[]);

int main() {
	char s[100];
	//itoa_orig(-65432, s);
	itoa_recursive(-43210, s);
	printf("%s\n", s);
	
	//printd(-12345);
	//printf("\n");
}

// recursive itoa: take int and s[], recursively write chars into s[]
// design decision: private static vars to preserve state across recursive calls
void itoa_recursive(int n, char s[]) {
	static int i = 0;
	static int sign;
	//printf("hi n: %d, i: %d\n", n, i);

	if (i == 0) {		// only on first loop
		if ((sign = n) < 0) 	// sign gets original value of n
			n = -n; 			// make n positive if it was negative
		s[i++] = n % 10 + '0';
		itoa_recursive(n, s);
	} else if ((n /= 10) > 0) {
		s[i++] = n % 10 + '0';   // get 0-indexed char value
		itoa_recursive(n, s);
	} else { 				// after getting all digits: sign, reverse
		if (sign < 0)
			s[i++] = '-';
		s[i] = '\0';
		reverse(s);
	}
}

// original itoa, page 64
// convert int n to chars in s[]
void itoa_orig(int n, char s[]) {
	int i, sign;

	if ((sign = n) < 0) 	// sign gets original value of n
		n = -n; 			// make n positive if it was negative

	i = 0;
	do { 						// generate digits in reverse order
		s[i++] = n % 10 + '0'; 	// get next digit
	} while ((n /= 10) > 0); 	// delete digit added to s
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s); 	// corect order of s
}

// recursive printd: print n in decimal
void printd(int n) {
	//printf("n: %d\n", n);
	if (n < 0) {
		putchar('-');
		n = -n;
	}
	// if digit is one's place: print it
	if (n / 10) 			// if not equal to 0
		printd(n / 10);
	putchar(n % 10 + '0');
}

void reverse(char s[]) {
	int c, i, j;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
*/

/******************************************************************************** 
4-13 Write a recursive version of the function reverse(s), which reverses
the string s in place

Note: cannot do "static int j = strlen(s);" errors out as "initializer not constant"

*/

#include <stdio.h>
#include <string.h>

void itoa_orig(int n, char s[]);
void reverse(char s[]);
void reverse_recurse(char s[]);

int main() {
	//char s[100] = "12345";
	//printf("%ld\n", strlen(s)/2);   // floor division
	
	char s[100];
	itoa_orig(-654321, s);
	printf("%s\n", s);
}

// original itoa, page 64: convert int n to chars in s[]
void itoa_orig(int n, char s[]) {
	int i, sign;

	if ((sign = n) < 0) 	// sign gets original value of n
		n = -n; 			// make n positive if it was negative

	i = 0;
	do { 						// generate digits in reverse order
		s[i++] = n % 10 + '0'; 	// get next digit
	} while ((n /= 10) > 0); 	// delete digit added to s
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	printf("before reverse: %s\n", s);
	reverse_recurse(s); 	// corect order of s
}

void reverse(char s[]) {
	int c, i, j;

	for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

void reverse_recurse(char s[]) {
	static int i = 0;
	int len, c;

	len = strlen(s);
	//printf("len: %d, i: %d\n", len, i);
	if (i < len / 2) {
		c = s[i];
		s[i] = s[len-i-1];
		s[len-i-1] = c;
		i++;
		reverse_recurse(s);
	}
}