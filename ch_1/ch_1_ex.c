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
*/

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

//////////////// END DONE 10/16/22 ////////////////


/****************************************
1-16 revise main of longest-line so it will:
	- correctly print length of arbitrarily long lines
	- print as much as possible of the text
Function copy() shows how arrays (unlike other vars) are passed by reference not value, and so the originals are changeable within a function: the passed array

Design hint in book: 'by testing the length and the last character returned, main can determine whether the line was too long, and cope as it wishes'
*/

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
		// check if line was longer than allowed size
		if ((len == MAXLINE) && (line[MAXLINE] != '\0')) {
			char line[MAXLINE*2];

		}
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