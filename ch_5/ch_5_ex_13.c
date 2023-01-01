// gcc -o ch_5_ex_13.o ch_5_ex_13.c && ./ch_5_ex_13.o

// compile and run separately if entering args
//     gcc -o ch_5_ex_13.o ch_5_ex_13.c
//     ./ch_5_ex_13.o 4

/********************************************************************************
5-13 Write the program tail, which prints the last n lines of its input
	By default, n is 10, but can be changed by an optional arg, so "tail -n" prints the
		last n lines. 
	Should behave rationally even with unreasonable input or value of n. 
	Write so it makes best use of available storage: store lines as in sorting
		program of 5.6, not 2-D array of fixed size.

Substeps
	/ 1. Get multiple lines from input, store in pointer array, and print them all
		Starting point: ex 5-7, page 108 setup for qsort with pointers to char *
	/ 2. Add variable for the number of lines to be printed, from the end
	/ 3. Get correct lines printing with 'tail' hardcoded
	4. Assign tail from terminal input
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000    	// max number of lines that will be read
#define TAIL 3 				// default count of end lines to print

// char *lineptr[MAXLINES]: lineptr is an array of MAXLINES elements,
//     each element of which is a pointer to a char
// lineptr[i]: a char pointer
// *lineptr[i]: char it points to, the first character of the i-th saved text line
char *lineptr[MAXLINES]; 	// array of pointers, each element is pointer to a line's first char

int readlines(char *lineptr[], int nlines);
void writetail(char *lineptr[], int nlines, int tail);
int valid(char *args);

// to execute sorting: type last line, 'enter', then ctrl+d
// assumes either zero or one arg, which must be an int
// page 108: sort input lines
int main(int argc, char *argv[]) {
	int nlines; 	// number of input lines read
	int tail;  // number of lines from the end to print

	if (argc == 2) {
		char *arg = argv[1];
		if (valid(arg) == 0) {
			printf("Error: value for tail is not a number\n");
			exit(1);
		}
		tail = atoi(arg);  // note: if done on chars, assigns tail to 0
	} else {
		tail = TAIL;
	}
	
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		writetail(lineptr, nlines, tail);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

int valid(char *args) {
	char *temp = args;
	while (*temp != '\0') {
		if (!isdigit(*temp)) {
			return 0;  // not a valid integer
		}
		temp++;
	}
	return 1;  // is a valid integer
}

#define MAXLEN 1000 	// max length of any input line
int getaline(char *, int);
char *alloc(int);

// read input lines: collect and save chars of each line,
//     put pointers to the lines in array for use by rest of program, and return count of input lines
// it modifies char *lineptr[], which is used elsewhere in program
int readlines(char *lineptr[], int maxlines) {
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	// loop and get lines until terminal input is length 0
	while ((len = getaline(line, MAXLEN)) > 0) {
		// if (nlines >= maxlines || (p = alloc(len)) == NULL) {
		if (nlines >= maxlines) {
			return -1;
		}
		p = alloc(len); // if len fits in array, allocp iterates by len, and returns the OLD allocp value 
		if (p == 0) {  	// alloc returns 0 if value did not fit
			return -1;
		}
		else {
			line[len-1] = '\0';  // delete newline
			// strcpy library function p 249: copy 'line' (type: const char *) into 'p' (type: char *)
			// 'p' gets contents of 'line'
			strcpy(p, line);  // put line into next empty value of array
			lineptr[nlines++] = p; // put pointer to line into variable used throughout program
		}
	}
	return nlines;
}

// write tbe last 'tail' output lines in order they appear in 'lineptr'
void writetail(char *lineptr[], int nlines, int tail) {
	if (tail > nlines) {
		printf("Error: too few lines\n");
		return;
	}
	printf("\nLines echoed:\n");
	for (int i = nlines-tail; i < nlines; i++) {
		printf("%s\n", *(lineptr+i)); // print char array pointed to by next element in lineptr
	}
		
}

// page 101
#define ALLOCSIZE 10000    // size of available space

static char allocbuf[ALLOCSIZE];  // storage for alloc
static char *allocp = allocbuf;  // next free position

char *alloc(int n) {    // return pointer to n characters
	if (allocbuf + ALLOCSIZE - allocp >= n) {  // it fits
		allocp += n;
		return allocp - n;  // old p
	} else {
		return 0;
	}
}

// page 29
int getaline(char s[], int lim) {
	int c, i;

	for (i=0; i<lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}