/*
Combined compile and run command
gcc -o ch_1_ex ch_1_ex.c && ./ch_1_ex
*/

//////////////// DONE 10/15/22 ////////////////
/**************************************** 
1-1 run hello world 
needed to run 'apt get gcc'
$ gcc -o ch_1_ex ch_1_ex.c ' 
$ ./ch_1_ex

error without last ": explicitly says missing it, and where is first one
likewise for omitting ;
errors out on gcc command


#include <stdio.h>

int main() {
	printf("hello, world\n");
}
*/


/****************************************
1-2 try out with \a, \c, \w, \d
\c, \w, \d errors out with 'unknown escape sequence'
	These are also highlighted red by syntax editor in sublime
\a and \e do not print anything, and no whitespace after
\v prints words, then newline, then indent
\b cuts off last character, the 'd'
full list: https://en.wikipedia.org/wiki/Escape_sequences_in_C

#include <stdio.h>

int main() {
	printf("hello, world\");
}
*/


/**************************************** 
1-3 add heading above temp conversion table

#include <stdio.h>

int main() {
	float fahr, celsius;
	int lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;

	fahr = lower;
	printf("Table to convert Fahrenheit to Celsius\n");
	printf("%s %s\n", "Fahr.", "Cel.");
	while (fahr <= upper) {
		celsius = (5.0/9.0) * (fahr-32.0);
		printf("%3.0f %6.1f\n", fahr, celsius);
		fahr = fahr + step;
	}
}
*/


/**************************************** 
1-4 convert celsius to fahrenheit

#include <stdio.h>

int main() {
	float fahr, celsius;
	int lower, upper, step;

	lower = -20;
	upper = 150;
	step = 11;

	celsius = lower;
	printf("Table to convert Celsius to Fahrenheit\n");
	printf("%s   %s\n", "Cel.", "Fahr.");
	while (celsius <= upper) {
		fahr = (celsius / (5.0/9.0)) + 32.0 ;
		printf("%5.1f %6.1f\n", celsius, fahr);
		celsius = celsius + step;
	}
}
*/


/**************************************** 
1-5 in for loop, print conversion from F to C, from 300 to 0

#include <stdio.h>

int main() {
	int fahr;

	for (fahr = 300; fahr >= 0; fahr -= 20) {
		printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
	}
}
*/


/****************************************
example page 17 read and print from stream
result: enter characters into terminal, then press enter: they are reprinted on new line
observation: if enter "EOF" or "-1" it just echos those also, same with "" or '' and escape characters

Alternating between ctrl + d and other characters will just keep printing characters entered all on the same line

Enter followed by other characters echoes the characters entered on a new line

observation: two ways to end execution
	- enter, followed by ctrl + d
	- ctrl + d, then another ctrl + d right after [ie enter characters, ctrl + d once will print them on same line, and then a second ctrl + d will end program]

Explanation of this finding about EOF (https://stackoverflow.com/questions/54978143/usage-of-eof-in-c)
	"It should be noted that control-D results in EOF only at the beginning of a line or when pressed twice. It does not actually generate EOF. Rather, it sends the contents of the keyboard input buffer to the program. The input handling software interprets a read request that receives zero characyers as EOF. So control-D when no characters are pending causes EOF behavior. Control-D when characters are pending just sends them immediately instead of when enter is pressed, without causing EOF behavior.  – Eric Postpischil, Mar 4, 2019 at 14:18"

# include <stdio.h>

int main() {
	int c;

	while ((c = getchar()) != EOF)
		putchar(c);
}
*/


/****************************************
1-6 check that "getchar() != EOF" is 0 or 1
version a. this shows it is equal to 1

#include <stdio.h>

int main() {
	int c;

	while (((c = getchar()) != EOF) == 1)
		putchar(c);
}

version b.
How to get 'EOF' entered from command line: ctrl + d
observation: for int c, if print as %d, shows ASCII numeric value
	and errors out with %s since c is int
	but, putchar prints the character

sample output of this: note that 'Enter' after 'hello' prints as newline when echoed

hello
in loop, letter is h, evalutation is 1
in loop, letter is e, evalutation is 1
in loop, letter is l, evalutation is 1
in loop, letter is l, evalutation is 1
in loop, letter is o, evalutation is 1
in loop, letter is 
, evalutation is 1
exited loop evaluation is 0

#include <stdio.h>

int main() {
	int c;

	// must assign separately from comparing, to not call getchar() repeatedly
	c = getchar();
	while (c != EOF) {
		printf("in loop, letter is ");
		putchar(c);
		printf(", evalutation is %d\n", (c != EOF));
		c = getchar();
	}
	printf("exited loop evaluation is ");
	printf("%d\n", (c != EOF));
}
*/


/****************************************
1-7 print value of EOF
it is "-1"

# include <stdio.h>

int main() {
	printf("%d\n", EOF);
}
*/


/****************************************
example page 19: count lines

#include <stdio.h>

int main() {
	int c, nl;

	while((c = getchar()) != EOF)
		if (c == '\n')
			++nl;
	printf("%d\n", nl);
}
*/


/****************************************
1-8 write program to count blanks, tabs, newlines

test string: should have 4 spaces, 3 tabs, 1 newline
one-space one-tab	three-space   two-tab		end

#include <stdio.h>

int main() {
	int c, nl, sp, tb;

	while((c = getchar()) != EOF)
		if (c == '\n')
			++nl;
		else if (c == ' ')
			++sp;
		else if (c == '\t')
			++tb;
	printf("%d %d %d\n", nl, sp, tb);
}
*/


/****************************************
example page 20 count words, lines, characters

# include <stdio.h>

#define IN  1  // inside a word
#define OUT 0  // outside a word

int main() {
	int c, nl, nw, nc, state;

	state = OUT;
	nl = nw = nc = 0;
	while ((c = getchar()) != EOF) {
		++nc;
		if (c == '\n')
			++nl;
		if (c == ' ' || c == '\n' || c == '\t')
			state = OUT;
		else if (state == OUT) {
			state = IN;
			++nw;
		}
	}
	printf("%d %d %d\n", nl, nw, nc);
}
*/

//////////////// DONE 10/16/22 ////////////////
/****************************************
1-9 copy input to output, replacing all strings of 1+ blanks with single blank

# include <stdio.h>

#define IN  1  // inside a word, last char was non-blank
#define OUT 0  // outside a word, last char was blank

int main() {
	int c, state;

	state = OUT;
	while ((c = getchar()) != EOF) {
		// case: next character is a non-blank
		if (c != ' ' && c != '\n' && c != '\t') {
			state = IN;
			putchar(c);
		// case: last char was non-blank, and next char is blank
		} else if (state == IN && (c == ' ' || c == '\n' || c == '\t')) {
			state = OUT;
			putchar(' ');
		}
		// case: last char was blank, and next char is blank
		// do nothing
	}
}
*/


/****************************************
1-10 write input to output, replacing tab with \t, backspace with \b, backslash with \\

	tried this to automate input, EOF not working as intended
	printf("hello\b\thello helloEOF");
	printf("hello\b\thello hello\0");
	printf("%d", EOF);

	how to get a 'backspace' via terminal input: ctrl + h
	terminal when running program shows '^H' for the ctrl + h, then replaces with \b for print:
		hello^Hhi
		hello\bhi

# include <stdio.h>

int main() {
	int c;

	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			putchar('\\');
			putchar('t');
		} else if (c == '\b') {
			putchar('\\');
			putchar('b');
		} else if (c == '\\') {
			putchar('\\');
		} else
			putchar(c);
	}
}
*/


/****************************************
1-11 how would you test word count program, what kinds of inputs are most likely to uncover bugs if there are any?

Likely issues: 
	- Whitespaces not counted for breaks between words (see https://en.wikipedia.org/wiki/Escape_sequences_in_C): enter?
		* Result when these entered:
			hello, enter, hello -> 2 words [interesting and surprising, correct]
			ctrl + h -> (aka backspace) 1 word
			ctrl + h three times, space, ctrl + h -> 2 words  [interesting and surprising, correct]
	- What happens with hex values? \x
	- Chars preceded with \ that aren't designated as escaped
		\q -> counts as single word
	- Single \
		\ \   -> 2 words
		\\ \\ -> 2 words
	- Run it with no input -> counts 0, correct
	- Count a single space or tab -> correctly returns 0

# include <stdio.h>

#define IN  1  // inside a word
#define OUT 0  // outside a word

int main() {
	int c, nw, state;

	state = OUT;
	nw = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t')
			state = OUT;
		else if (state == OUT) {
			state = IN;
			++nw;
		}
	}
	printf("%d\n", nw);
}
*/


/****************************************
Program that prints its input one word per line
also treats multiple whitespaces as only single whitespace

# include <stdio.h>

#define IN  1  // inside a word
#define OUT 0  // outside a word

int main() {
	int c, state;

	state = OUT;
	while ((c = getchar()) != EOF) {
		// case: next char is not whitespace
		if (c != ' ' && c != '\n' && c != '\t') {
			state = IN;
			putchar(c);
		// case: prior char was not whitespace, and next char is whitespace
		} else if (state == IN && (c == ' ' || c == '\n' || c == '\t')) {
			state = OUT;
			putchar('\n');
		}
		// case: prior char was whitespace, and next char is whitespace
		// do nothing
	}
}
*/


/****************************************
example page 20, count occurrences of each digit, whitespace char, and all other chars
sample input and output
	1222345 67890000
	digits = 4 1 3 1 1 1 1 1 1 1, white space = 2, other = 0

# include <stdio.h>

#define IN  1  // inside a word
#define OUT 0  // outside a word

int main() {
	int c, i, nwhite, nother;
	int ndigit[10];

	nwhite = nother = 0;
	for (i = 0; i < 10; i++)
		ndigit[i] = 0;

	while((c = getchar()) != EOF)
		if (c >= '0' && c <= '9')
			++ndigit[c-'0'];
		else if (c == ' ' || c == '\n' || c == '\t')
			++nwhite;
		else
			++nother;

	printf("digits =");
	for (i = 0; i < 10; ++i)
		printf(" %d", ndigit[i]);
	printf(", white space = %d, other = %d\n", nwhite, nother);
}
*/


/****************************************
1-13 version 1. bars horizontal histogram of lengths of words in input
planned limitation: does not count longer than 100, or print longer than 20

# include <stdio.h>

#define IN  1  // inside a word
#define OUT 0  // outside a word
#define MAXLEN 100 // does not count more than 100 digits

int main() {
	int c, i, nc, state;
	int nchar[MAXLEN];

	for (i = 0; i <= MAXLEN; i++)
		nchar[i] = 0;

	state = OUT;
	while ((c = getchar()) != EOF) {
		// case: next char is not whitespace
		if (c != ' ' && c != '\n' && c != '\t') {
			nc++;
			state = IN;
		// case: prior char was not whitespace, and next char is whitespace
		} else if (state == IN && (c == ' ' || c == '\n' || c == '\t')) {
			++nchar[nc];
			state = OUT;
			nc = 0;
		}
	}
	for (i = 0; i <= 20; ++i) {
		printf("length %d count : ", i);
		for (int j = 0; j < nchar[i]; j++) {
			printf("*");
		}
		printf("\n");
	}
}
*/


/****************************************
1-13 version 2. bars vertical histogram of lengths of words in input
planned limitation: max length counted for a word is 20 char

# include <stdio.h>

#define IN  1  // inside a word
#define OUT 0  // outside a word
#define MAXLEN 30 // maximum length of a word that will be counted

int main() {
	int c, i, nc, state;
	int nchar[MAXLEN];
	int most;

	most = 0;
	for (i = 0; i < MAXLEN; i++)
		nchar[i] = 0;

	// get array of frequencies of word lengths
	state = OUT;
	while ((c = getchar()) != EOF) {
		// case: next char is not whitespace
		if (c != ' ' && c != '\n' && c != '\t') {
			nc++;
			state = IN;
		// case: prior char was not whitespace, and next char is whitespace
		} else if (state == IN && (c == ' ' || c == '\n' || c == '\t')) {
			// only add to array if within countable lengths
			if (nc < MAXLEN)
				++nchar[nc];
			state = OUT;
			nc = 0;
		}
	}

	// get most occurrences of a word length
	for (i = 0; i < MAXLEN; i++)
		if (nchar[i] > most)
			most = nchar[i];

	// print * histogram horizontal
	for (i = most; i > 0; i--) {
		for (int j = 0; j < MAXLEN; j++) {
			if (nchar[j] >= i)
				printf(" *");
			else
				printf("  ");
		}
		printf("\n");
	}

	// print values of array, to check with * prints
	for (i = 0; i < MAXLEN; i++)
		printf(" %d", nchar[i]);
	printf("\n");
}
*/


/****************************************
1-14 print histogram of frequencies of different chars of input

# include <stdio.h>

#define IN  1  // inside a word
#define OUT 0  // outside a word
#define MAXLEN 128 // only handle this many ASCII characters

int main() {
	int c, i;
	int nchar[MAXLEN];

	for (i = 0; i < MAXLEN; i++)
		nchar[i] = 0;

	while((c = getchar()) != EOF)
		++nchar[c];

	// begin with printable chars by ASCII value
	for (i = 33; i < MAXLEN; ++i) {
		putchar(i);
		printf(" has count: %d\n", nchar[i]);
	}
}
*/


/****************************************
1-15 rewrite section 1.2 temp conversion to use a function

#include <stdio.h>

double convert(int fahr);

int main() {
	int fahr;

	for (fahr = 300; fahr >= 0; fahr -= 20) {
		printf("%3d %6.1f\n", fahr, convert(fahr));
	}
}

double convert(int fahr) {
	return (5.0/9.0)*(fahr-32);
}
*/


/****************************************
example page 29 print the longest line of input, up to 1000 char
issue found in book: 'getline()' already exists in stdio
error resolved when changed method to 'getaline()'
code only version

#include <stdio.h>
#define MAXLINE 1000 // maximum chars in a line

int getaline(char line[], int maxline);
void copy(char to[], char from[]);

int main() {
	int len;    // current line length
	int max;    // max current length seen so far
	char line[MAXLINE];    // current input line
	char longest[MAXLINE];    // longest line saved here

	max = 0;
	while ((len = getaline(line, MAXLINE)) > 0)
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	if (max > 0)    // there was a line
		printf("%s", longest);
	return 0;
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

// copy 'from' into 'to', assumes 'to' is big enough
void copy(char to[], char from[]) {
	int i;

	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}
*/


/****************************************
example page 29 print the longest line of input, up to 1000 char
version with my comments

#include <stdio.h>
#define MAXLINE 1000 // maximum chars in a line

int getaline(char line[], int maxline);
void copy(char to[], char from[]);

int main() {
	int len;    // current line length
	int max;    // max current length seen so far
	char line[MAXLINE];    // current input line
	char longest[MAXLINE];    // longest line saved here

	max = 0;
	// getaline() as side effect creates 'line' by assigning characters from getchar()
	while ((len = getaline(line, MAXLINE)) > 0) {
		// check and handle if line is the new longest
		if (len > max) {
			max = len;
			// original arrays are modifiable by the function (unlike other var types)
			// even though no return value, 'longest' has contents of 'line' copied into it
			copy(longest, line);
		}
	}
	if (max > 0)    // there was a line
		printf("%s", longest);
	return 0;
}

// get length of a line, up to length 'lim'
// it will not copy past the size limit
int getaline(char s[], int lim) {
	int c, i;

	// add chars to array until hit size limit, EOF or newline
	for (i = 0; i < lim-1 && (c = getchar()) != EOF && c !='\n'; ++i)
		s[i] = c;
	// if hit newline, add it to array, iterate count
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	// add terminal character to indicate end of line, as used by 'copy()'
	s[i] = '\0';
	return i;
}

// copy 'from' into 'to'
// user already knows size needed for 'to', so do NOT check size here
void copy(char to[], char from[]) {
	int i;

	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}
*/

//////////////// 10/22/22 ////////////////

// Lot of trying out with arrays in separate doc

/****************************************
1-16 revise main of longest-line so it will:
	- correctly print length of arbitrarily long lines
	- print as much as possible of the text
Function copy() shows how arrays (unlike other vars) are passed by reference not value, and so the originals are changeable within a function: the passed array

Design hint in book: 'by testing the length and the last character returned, main can determine whether the line was too long, and cope as it wishes'

Revised interpretation of this:
	1. once exceeds maxline, don't copy, ONLY count the length
	2. unsure what printing means, just print to maxline


#include <stdio.h>
#define MAXLINE 10 // maximum chars in a line

int getaline(char line[], int maxline);
void copy(char to[], char from[]);
void copy_safe(char to[], char from[], int lim);

int main() {
	int len;    // current line length
	int max;    // max current length seen so far
	char line[MAXLINE];    // current input line
	char longest[MAXLINE];    // longest line saved here

	max = 0;
	while ((len = getaline(line, MAXLINE)) > 0) {
		printf("Line length: %d\n", len);
		if (len > max) {
			printf("New longest found\n");
			max = len;
			if (len < MAXLINE)
				copy(longest, line);
			else
				copy_safe(longest, line, MAXLINE);
		}
	}
	if (max > 0)    // there was a line
		printf("Length of longest line: %d\n", max);
		printf("Longest line printed to %d characters\n", MAXLINE);
		printf("%s", longest);
	return 0;
}

// read a line into s, return length
int getaline(char s[], int lim) {
	int c, i;

	// for (i = 0; i<lim-1 && (c=getchar())!=EOF && c !='\n'; ++i)
	for (i = 0; (c=getchar())!=EOF && c !='\n'; ++i)
		if (i < lim - 1)
			s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

// copy 'from' into 'to', assumes 'to' is big enough
void copy(char to[], char from[]) {
	int i;

	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}

// copies array, only to index 'lim'
void copy_safe(char to[], char from[], int lim) {
	int i;

	i = 0;
	while (i < lim && (to[i] = from[i]) != '\0')
		++i;
}
*/

//////////////// 10/23/22 ////////////////

// more practice in separate doc with array read, write, and print

/****************************************
1-17 print all input lines longer than 80 characters
-> making this 20 char for simpler testing

#include <stdio.h>
#define MAXLINE 1000 // maximum chars in a line
#define PRINT_LEN 20

int getaline(char line[], int maxline);
void copy(char to[], char from[]);

int main() {
	int len;    // current line length
	char line[MAXLINE];    // current input line

	// getaline() as side effect creates 'line' by assigning characters from getchar()
	while ((len = getaline(line, MAXLINE)) > 0) {
		if (len > PRINT_LEN) {
			printf("%s", line);
		}
	}
	return 0;
}

// get length of a line, up to length 'lim'
int getaline(char s[], int lim) {
	int c, i;

	// add chars to array until hit size limit, EOF or newline
	for (i = 0; i < lim-1 && (c = getchar()) != EOF && c !='\n'; ++i)
		s[i] = c;
	// if hit newline, add it to array, iterate count
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	// add terminal character to indicate end of line, as used by 'copy()'
	s[i] = '\0';
	return i;
}
*/

/****************************************
1-18 remove trailing blanks and tabs from input lines, and delete blank lines

Surprising finding: empty character constant '' causes an error
	Instead, use terminal string character '\0'

#include <stdio.h>
#define MAXLINE 1000 // maximum chars in a line

int getaline(char line[], int maxline);
void copy(char to[], char from[]);

int main() {
	int i;
	int len;    // current line length
	char line[MAXLINE];    // current input line

	// getaline() as side effect creates 'line' by assigning characters from getchar()
	while ((len = getaline(line, MAXLINE)) > 0) {
		printf("Before: %s<END>\n", line);
		for (i = len-1; i >=0; i--) {
			if (line[i] == ' ' || line[i] == '\t') {
				line[i] = '\0';
				//printf("remove one ");
			} else {
				break;
			}
		}
		printf("After: %s<END>\n", line);
	}
	return 0;
}

// removed part of adding newline to end, to better verify line-end printing
int getaline(char s[], int lim) {
	int c, i;

	// add chars to array until hit size limit, EOF or newline
	for (i = 0; i < lim-1 && (c = getchar()) != EOF && c !='\n'; ++i)
		s[i] = c;
	// add terminal character to indicate end of line
	s[i] = '\0';
	return i;
}
*/

/****************************************
1-19 write function reverse(s) that reverses character string: use it to write program that reverses input a line at a time


#include <stdio.h>
#define MAXLINE 1000 // maximum chars in a line

int getaline(char line[], int maxline);

int main() {
	int i, j;
	int len;    // length of input line
	char line[MAXLINE];    // current input line
	char reversed[MAXLINE];

	// getaline() as side effect creates 'line' by assigning characters from getchar()
	while ((len = getaline(line, MAXLINE)) > 0) {
		for (i = len-1, j=0; i >=  0; i--, j++) {
			reversed[j] = line[i];
		}
		reversed[j] = '\0';
		printf("Reversed: %s\n", reversed);
	}
	return 0;
}

// removed part of adding newline to end, to better verify line-end printing
int getaline(char s[], int lim) {
	int c, i;

	// add chars to array until hit size limit, EOF or newline
	for (i = 0; i < lim-1 && (c = getchar()) != EOF && c !='\n'; ++i)
		s[i] = c;
	// add terminal character to indicate end of line
	s[i] = '\0';
	return i;
}
*/

//////////////// 10/25/22 ////////////////

/****************************************
1-20 write program 'detab' that replaces tabs in input with the proper number of blanks to space to the next tab. Assume a fixed set of tab stops, say every n columns. Should 'n' be a variable or a symbolic parameter?

Approach
	Get a input of input
	Look for '\t'
	When find '/t': count chars up until that point, to get its location
	Have a modulus operation to get remainder to next tab stop (choice: every 4 char is tab stop)
	Replace the '\t' with that many spaces


#include <stdio.h>
#define MAXLINE 1000 // maximum chars in a line
#define TAB_STOP 8   // spaces between each tab stop

int getaline(char line[], int maxline);
void detab(char from[], int len, char to[]);
void add_space(char to[], int start, int spaces);

int main() {
	int len;    // current line length
	char line[MAXLINE];    // current input line
	char detabbed[MAXLINE]; // tab-stop-adjusted version of input line

	while ((len = getaline(line, MAXLINE)) > 0) {
		detab(line, len, detabbed);
		printf("%s\n", detabbed);
	}		
	return 0;
}

// removed part of adding newline to end, to better verify line-end printing
int getaline(char s[], int lim) {
	int c, i;

	// add chars to array until hit size limit, EOF or newline
	for (i = 0; i < lim-1 && (c = getchar()) != EOF && c !='\n'; ++i)
		s[i] = c;
	// add terminal character to indicate end of line
	s[i] = '\0';
	return i;
}

// change tabs to next tab stop, and write into 'detabbed'
void detab(char orig[], int len, char detabbed[]) {
	int i;
	int j; // index in detabbed array
	int spaces; // spaces to next tab stop

	spaces = 0;
	for (i = 0, j = 0; i < len ; i++) {
		if (orig[i] == '\t') {
			spaces = TAB_STOP - (i % TAB_STOP);
			// todo messy but have not come up with another way
			if (spaces == TAB_STOP)
				spaces = 0;
			add_space(detabbed, j, spaces);
			j += spaces;
		} else {
			// printf("    added from orig: ");
			// putchar(orig[i]);
			// printf(", at j[%d]\n", j);
			detabbed[j] = orig[i];
			j++;
		}
	}
	detabbed[j] = '\0';
}

void add_space(char detabbed[], int start, int spaces) {
	int i;

	for (i = 0; i < spaces; i++) {
		// printf("    space added to j[%d]\n", start+i);
		detabbed[start + i] = ' ';
	}
}
*/

//////////////// NEXT ////////////////


/****************************************
1-21 write program 'entab' that replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing. Use the same tab stops as for 'detab'. When either a tab or a single blank would suffice to reach a tab stop, which should be given preference?

Approach
	Get an input line
	Read input line, copy into other array, and stop and check at each space (' ')
		Get the number of spaces in a row
		Floor division by TAB_SPACE to get number of tab replacements
		Modulo division by TAB_SPACE to get number of space replacements
		Write that number of spaces and tabs into
		---- handle array counters ----
		Increment the 'to' array counter by tabs + spaces added
		Increment the 'from' counter by the original space found
	Resume reading the line
	Print the entabbed line
*/

#include <stdio.h>
#define MAXLINE 1000 // maximum chars in a line
#define TAB_STOP 4   // spaces in a tab
#define TRUE 1
#define FALSE 0

int getaline(char line[], int maxline);
void entab(char orig[], int len, char entabbed[]);
void add_char(char to[], char c, int num, int start);

int main() {
	int len;    // current line length
	char line[MAXLINE];    // current input line
	char entabbed[MAXLINE]; // tab-stop-adjusted version of input line

	while ((len = getaline(line, MAXLINE)) > 0) {
		entab(line, len, entabbed);
		printf("%s<>\n", entabbed);
	}		
	return 0;
}


// change tabs to next tab stop, and write into 'entabbed'
void entab(char orig[], int len, char entabbed[]) {
	int in_blanks; 		// boolean for whether in string of blanks
	int i; 				// index in orig array
	int j; 				// index in entabbed array
	int spaces; 		// count of spaces in a row in orig array
	int tab_rep; 		// count of tabs to replace to entabbed array
	int space_rep	; 	// count of spaces to replace to entabbed array

	spaces = 0;
	in_blanks = FALSE;
	for (i = 0, j = 0; i <= len ; i++) {
		// first blank after non-blank
		if (orig[i] == ' ' && in_blanks == FALSE) {
			in_blanks = TRUE;
			spaces = 1;
		// another blank after a blank
		} else if (orig[i] == ' ' && in_blanks == TRUE) {
			spaces++;
		// first non-blank after blank(s)
		} else if (orig[i] != ' ' && in_blanks == TRUE) {
			in_blanks = FALSE;
			// printf("orig spaces in a row: %d\n", spaces);
			tab_rep = spaces / TAB_STOP;
			space_rep = spaces % TAB_STOP;
			// printf("tabs to add: %d\n", tab_rep);
			// printf("spaces to add: %d\n", space_rep);
			add_char(entabbed, '\t', tab_rep, j);
			add_char(entabbed, ' ', space_rep, j + tab_rep);
			j += (tab_rep + space_rep);
			printf("    iterated value of j: %d\n", j);
			printf("    non-blank added after spaces: ");
			putchar(orig[i]);
			printf("\n");
			entabbed[j] = orig[i]; // add the non-blank char
			j++;
		// another non-blank after a non-blank
		} else if (orig[i] != ' ' && in_blanks == FALSE){
			printf("    added from orig: ");
			putchar(orig[i]);
			printf(", at j[%d]\n", j);
			entabbed[j] = orig[i];
			j++;
		// end of line, with trailing spaces
		} else if (orig[i] == '\0' && in_blanks == TRUE) {
			tab_rep = spaces / TAB_STOP;
			space_rep = spaces % TAB_STOP;
			// printf("tabs to add: %d\n", tab_rep);
			// printf("spaces to add: %d\n", space_rep);
			add_char(entabbed, '\t', tab_rep, j);
			add_char(entabbed, ' ', space_rep, j + tab_rep);
			entabbed[j] = orig[i];
		// end of line, no trailing spaces
		} else if (orig[i] == '\0' && in_blanks == FALSE) {
			entabbed[j] = orig[i];
		}
	}
}

// add 'num' instances of char 'c' to array 'to[]', beginning at array 'start'
void add_char(char to[], char c, int num, int start) {
	int i;

	for (i = 0; i < num; i++) {
		// printf("    ascii %d added at j[%d]\n", c, start+i);
		to[start + i] = c;
	}
}

// removed step of adding newline to end, to better verify line-end printing
int getaline(char s[], int lim) {
	int c, i;

	// add chars to array until hit size limit, EOF or newline
	for (i = 0; i < lim-1 && (c = getchar()) != EOF && c !='\n'; ++i)
		s[i] = c;
	// add terminal character to indicate end of line
	s[i] = '\0';
	return i;
}