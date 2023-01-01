// gcc -o ch_5_ex_12.o ch_5_ex_12.c && ./ch_5_ex_12.o

// compile and run separately if entering args
//     gcc -o ch_5_ex_12.o ch_5_ex_12.c
//     ./ch_5_ex_12.o 4

/********************************************************************************
5-12 Extend entab and detab to accept the shorthand "entab -m +n" to mean tab stops
every n columns, starting at column m. Choose convenient (for the user) default behavior

What this means for detab (interpreting this way)
	- Do nothing until passing char at index (m * n)
	- Any time a tab and/or spaces encountered: replace with ALL SPACES, lining up
	  with tab stops aligned at intervals of n

Changes needed in detab:
	- add a variable for startcol, with a default, set as 1 to make testable
		get this running first, before reading from terminal
	- read in two string args from terminal input
	- assign 'n' to tabstop
	- add a provision to do nothing until past index (m * n)


// **************** PART 1 - ORIGINAL DETAB (ex 1-20) ****************
// replace tabs with spaces
// how to run: start exe, enter chars on command tabstopline, end with newline
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000 // maximum chars in a line
#define TAB_STOP 8   // default spaces between each tab stop
#define START_COL 2  // default column to start tab stops

int getval(char *s);
int getaline(char line[], int maxline);
void detab(char from[], int len, char to[], int tabstop, int startcol);
void add_space(char to[], int start, int spaces);

// presumes either 0 or 2 args, and if given, both are single-digit ints
// example call: ./ch_5_ex_12.o -4 +1
int main(int argc, char *argv[]) {
	int len;    // current line length
	char line[MAXLINE];    // current input line
	char detabbed[MAXLINE]; // tab-stop-adjusted version of input line
	int tabstop;
	int startcol;

	if (argc == 3) {
		// increment to second item of args, a char *; then get value at its second char (ie remove the leading + or -)
		// presumes input after + or - is single char digit
		tabstop = *++(*++argv) - '0';  // get int value of char
		startcol = *++(*++argv) - '0';

	} else {
		tabstop = TAB_STOP;
		startcol = START_COL;
	}

	printf("tabstop %d, startcol %d\n", tabstop, startcol);
	while ((len = getaline(line, MAXLINE)) > 0) {
		detab(line, len, detabbed, tabstop, startcol);
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
// but only start looking after char at index (m * n),
//     counting tabs as the space equivalents
void detab(char orig[], int len, char detabbed[], int tabstop, int startcol) {
	int i; 		// index in original string
	int j; 		// index in 'detabbed' destination string
	int spaces; // spaces to next tab stop
	int index;  // count of how many space-tab equivalents have been covered, for
				//    when passes place to start adding tabstops

	spaces = 0;
	index = 0;
	for (i = 0, j = 0; i < len ; i++) {
		if (index < tabstop * startcol) {
			//printf("index %d, copy char only: ", i);
			//putchar(orig[i]);
			//printf("<>\n");
			detabbed[j] = orig[i];
			j++;
			if (orig[i] == '\t') {
				index += tabstop;
			} else {
				index++;
			}
			continue;
		}
		// when reach a tab char in source: determine index in DEST to next tab stop
		if (orig[i] == '\t') {
			printf("tab found, after start col\n");
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
#define START_COL 2  // default column to start tab stops
#define TRUE 1
#define FALSE 0

int getaline(char line[], int maxline);
void entab(char orig[], int len, char entabbed[], int tabstop, int startcol);
int handle_spaces(char to[], int spaces, int start, int tabstop);
void add_char(char to[], char c, int num, int start);

// example call: ./ch_5_ex_12.o -4 +2
int main(int argc, char *argv[]) {
	int len;    // current line length
	char line[MAXLINE];    // current input line
	char entabbed[MAXLINE]; // tab-stop-adjusted version of input line
	int tabstop;
	int startcol;

	if (argc == 3) {
		tabstop = *++(*++argv) - '0';  // get int value of char
		startcol = *++(*++argv) - '0';
	} else {
		tabstop = TAB_STOP;
		startcol = START_COL;
	}

	printf("tabstop %d, startcol %d\n", tabstop, startcol);
	while ((len = getaline(line, MAXLINE)) > 0) {
		entab(line, len, entabbed, tabstop, startcol);
		printf("%s<>\n", entabbed);
	}		
	return 0;
}

// change spaces into tabs when enough in a row, and write into 'entabbed'
void entab(char orig[], int len, char entabbed[], int tabstop, int startcol) {
	int in_blanks; 		// boolean for whether in string of blanks
	int i; 				// index in orig array
	int j; 				// index in entabbed array
	int spaces; 		// count of spaces in a row in orig array
	int chars_added;
	int index; 			// count of tabs+space distance for when to start tab stops

	spaces = 0;
	index = 0;
	in_blanks = FALSE;
	for (i = 0, j = 0; i <= len ; i++) {
		// do not add tab stops until past index (m * n)
		if (index < tabstop * startcol) {
			entabbed[j] = orig[i];
			j++;
			if (orig[i] == '\t') {
				index += tabstop;
			} else {
				index++;
			}
			continue;
		}

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