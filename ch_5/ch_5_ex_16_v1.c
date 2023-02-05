/********************************************************************************
5-16 Add the -d ("directory order") option, which makes comparisons only on letters, 
numbers, and blanks. Make sure it works in conjunction with -f.

Compare only chars when this is true:
	
	(isalnum(c) != 0 || c == ' ')

Revised idea:
	flag options 'nocase' and 'alnum' can be done by modifying the strings as in 5-15
	Maybe do those in main, before passing to one sort function again

*/

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 		// max number of lines to be sorted
char *lineptr[MAXLINES]; 	// pointers to text lines

int readlines(char *lineptr[], int nlines);
int checkflag(char s[], int argc, char *argv[]);
void writelines(char *lineptr[], int nlines);
void qsort_ex(int reverse, void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);

// sort input lines, default is lexicographic ascending 
// gcc -o ch_5_ex_14.o ch_5_ex_14.c && ./ch_5_ex_14.o -n -r
int main(int argc, char *argv[]) {
	int nlines;  		// number of input lines read
	int numeric = 0;
	int reverse = 0;
	int nocase = 0;

	numeric = checkflag("-n", argc, argv);  // sort as numeric, not lexicographic
	reverse = checkflag("-r", argc, argv);	// sorts in reverse (descending) order
	nocase = checkflag("-f", argc, argv);  	// ignore capitalization
	alnum = checkflag("-d", argc, argv); 	// compare only letters, numbers, and ' '

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		// in qsort call: 'strcmp' and 'numcmp' are addresses of functions
		// 'numcmp' defined below, 'strcmp' is in 'string' library
		
		printf("\nUsing original qsort\n");
		qsort_ex(reverse, nocase, (void **) lineptr, 0, nlines-1, (int (*)(void*,void*))(numeric ? numcmp : strcmp));
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("input too big to sort\n");
		return 1;
	}
}

// returns 1 if provided string is in args array
int checkflag(char s[], int argc, char *argv[]) {
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], s) == 0) {
			return 1;
		}
	}
	return 0;
}

// sort v[left]...v[right] into increasing order
// int (*comp)(void *, void *)  -> 'comp' is pointer to a function with two void * args, returns int
// comp 						-> pointer to a function
// *comp 						-> the function
// (*comp)(v[i], v[left]) 		-> call to the function made by qsort
#include <stdlib.h>
void qsort_ex(int reverse, int nocase, int alnum, void *v[], int left, int right, int (*comp)(void *, void *)) {
	int i, last, compared;
	char left_mod[100];  	// array to store processed version of string
	char i_mod[100];
	char *leftptr;  		// pointer to the processed arrays to use in compare function
	char *iptr;
	void swap(void *v[], int, int);
	void intolower(const char *str, char dest[]);

	if (left >= right) 		// do nothing if array contains fewer than 2 elements
		return;
	
	swap(v, left, (left+right)/2);  // make middle element the pivot, and move it into leftmost position
	last = left;
	
	// printf("left orig: %s\n", (char *) v[left]);
	if (nocase) 
		intolower((char *) v[left], left_mod);  // put lower-case version of string at 'left' into 'left_mod'
	else
		leftptr = v[left];
	
	// printf("left lower arr: %s\n", left_mod);
	leftptr = left_mod;
	// printf("left lower ptr: %s\n", leftptr);
	
	for (i = left+1; i <= right; i++) {
		// printf("i: %s\n", (char *) v[i]);
		intolower((char *) v[i], i_mod);  // put lower-case version of string at i into 'i_mod'
		// printf("i_mod arr: %s\n", i_mod);
		iptr = i_mod;
		// printf("i_mod ptr: %s\n", iptr);

		compared = (*comp)(iptr, leftptr);  // compare the modified-if-needed string versions
		
		// swap locations of the original strings as needed
		if (!reverse) { 	// ascending order
			if (compared < 0) {
				swap(v, ++last, i);
			}
		} else { 			// reverse order
			if (compared > 0) {
				swap(v, ++last, i);
			}
		}
		
	}
	swap(v, left, last);  // move pivot to its correct position
	qsort_ex(reverse, v, left, last-1, comp);
	qsort_ex(reverse, v, last+1, right, comp);
}

#include <ctype.h>

// put only letters, numbers, and ' ' into array for comparison
void intoalnum(const char *str, char dest[]) {
	int i, j, c;
	char *strlow;
	for (i = 0, j = 0; i < strlen(str); i++) {
		c = str[i]
		if (isalnum(c) != 0 || c == ' ')
			dest[j++] = c;
	}
	dest[j] = '\0';
}

// put to-lower-case chars at pointer 'str' into array 'dest'
void intolower(const char *str, char dest[]) {
	int i;
	char *strlow;
	for (i = 0; i < strlen(str); i++) {
		dest[i] = tolower(str[i]);
	}
	dest[i] = '\0';
}

// put to-lower-case chars at pointer 'str' into array 'dest'
void intolower(const char *str, char dest[]) {
	int i;
	char *strlow;
	for (i = 0; i < strlen(str); i++) {
		dest[i] = tolower(str[i]);
	}
	dest[i] = '\0';
}

#include <stdlib.h>

// compare s1 and s1 numerically
int numcmp(char *s1, char *s2) {
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

void swap(void *v[], int i, int j) {
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/********************************************************************************
Functions for line reading and writing used in all versions
from pages 108-110, in setup for 5-7
*/

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

// write output lines in order they appear in 'lineptr',
//     where they were already put in sorted order
void writelines(char *lineptr[], int nlines) {
	printf("\nLines after sorting:\n");
	while (nlines-- > 0)
		printf("%s\n", *lineptr++); // print char array pointed to by next element in lineptr
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