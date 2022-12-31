// gcc -o ch_5_ex_11.o ch_5_ex_11.c && ./ch_5_ex_11.o

// compile and run separately if entering args
//     gcc -o ch_5_ex_11.o ch_5_ex_11.c
//     ./ch_5_ex_11.o 4

/********************************************************************************
5-11 Modify the programs entab and detab (ex 1-20 and 1-21, page 34) to accept 
a list of tab stops as arguments. Use the default tab settings if there are no args.

Note: started from copies of my prior answers, and did not modify them to eg use
pointers rather than array indexing

Part I. Detab
	1-20. Write a program detab that replaces tabs in the input with the proper
	number of blanks to space to the next tab stop. Assume a fixed set of tab stops,
	say every n columns. Should n be a variable or a symbolic parameter?

	Changes needed to detab
		?? What does LIST of tab stops mean, how not only a single item ??
		Add args to main()
		Arg described as a list: need to make char(s) into numeric
		If provided, replace TAB_STOP with the arg

Part II. Entab
	1-22. Write a probram entab that replaces strings of blanks by the minimum number
	of tabs and blanks to achieve the same spacing. Use the same tab stops as for detab.
	When either a tab or a single blank would suffice to reach a tab stop, which should
	be given preference?


// **************** PART 1 - ORIGINAL DETAB (ex 1-20) ****************
// how to run: start exe, enter chars on command tabstopline, end with newline
#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1000 // maximum chars in a line
// TODO this is default only, pass explicitly to detab, after optional reassignment
#define TAB_STOP 8   // default spaces between each tab stop

int getaline(char line[], int maxline);
void detab(char from[], int len, char to[], int tabstop);
void add_space(char to[], int start, int spaces);

// presumes at most one arg that is an int eg "./ch_5_ex_11.o 4"
int main(int argc, char *argv[]) {
	int len;    // current line length
	char line[MAXLINE];    // current input line
	char detabbed[MAXLINE]; // tab-stop-adjusted version of input line
	int tabstop;

	if (argc == 2) {
		tabstop = atoi(argv[1]);
	} else {
		tabstop = TAB_STOP;
	}

	while ((len = getaline(line, MAXLINE)) > 0) {
		detab(line, len, detabbed, tabstop);
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

// replace tabs with given number of spaces, and write result into 'detabbed'
void detab(char orig[], int len, char detabbed[], int tabstop) {
	int i; 		// index in original string
	int j; 		// index in 'detabbed' destination string
	int spaces; // spaces to next tab stop

	spaces = 0;
	for (i = 0, j = 0; i < len ; i++) {
		// when reach a tab char in source: determine index in DEST to next tab stop
		if (orig[i] == '\t') {
			spaces = tabstop - (j % tabstop);
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

// **************** PART 2 - ORIGINAL ENTAB (ex 1-21) ****************

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000 // maximum chars in a line
#define TAB_STOP 4   // default spaces in a tab
#define TRUE 1
#define FALSE 0

int getaline(char line[], int maxline);
void entab(char orig[], int len, char entabbed[], int tabstop);
int handle_spaces(char to[], int spaces, int start, int tabstop);
void add_char(char to[], char c, int num, int start);

int main(int argc, char *argv[]) {
	int len;    // current line length
	char line[MAXLINE];    // current input line
	char entabbed[MAXLINE]; // tab-stop-adjusted version of input line
	int tabstop;

	if (argc == 2) {
		tabstop = atoi(argv[1]);
	} else {
		tabstop = TAB_STOP;
	}

	while ((len = getaline(line, MAXLINE)) > 0) {
		entab(line, len, entabbed, tabstop);
		printf("%s<>\n", entabbed);
	}		
	return 0;
}

// change tabs to next tab stop, and write into 'entabbed'
void entab(char orig[], int len, char entabbed[], int tabstop) {
	int in_blanks; 		// boolean for whether in string of blanks
	int i; 				// index in orig array
	int j; 				// index in entabbed array
	int spaces; 		// count of spaces in a row in orig array
	int chars_added;

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
			chars_added = handle_spaces(entabbed, spaces, j, tabstop);
			j += chars_added;
			entabbed[j] = orig[i]; // add the non-blank char
			j++;
		// another non-blank after a non-blank
		} else if (orig[i] != ' ' && in_blanks == FALSE){
			entabbed[j] = orig[i];
			j++;
		// end of line, with trailing spaces
		} else if (orig[i] == '\0' && in_blanks == TRUE) {
			handle_spaces(entabbed, spaces, j, tabstop);
			entabbed[j] = orig[i];
		// end of line, no trailing spaces
		} else if (orig[i] == '\0' && in_blanks == FALSE) {
			entabbed[j] = orig[i];
		}
	}
}

// returns count of chars added to array
int handle_spaces(char to[], int spaces, int start, int tabstop) {
	int tab_rep; 		// count of tabs to replace to entabbed array
	int space_rep;  	// count of spaces to replace to entabbed array

	tab_rep = spaces / tabstop;
	space_rep = spaces % tabstop;
	add_char(to, '\t', tab_rep, start);
	add_char(to, ' ', space_rep, (start + tab_rep));
	return tab_rep + space_rep;
}

// add 'num' instances of char 'c' to array 'to[]', beginning at array 'start'
void add_char(char to[], char c, int num, int start) {
	int i;

	for (i = 0; i < num; i++) {
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