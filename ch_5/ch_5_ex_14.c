// default (lexicographic) sorting
//     gcc -o ch_5_ex_14.o ch_5_ex_14.c && ./ch_5_ex_14.o

// with -n flag for numeric sorting
//     gcc -o ch_5_ex_14.o ch_5_ex_14.c && ./ch_5_ex_14.o -n

/***********************************************************
page 119 continuation of qsort_ex
	/ 1. Type out all the functions
	/ 2. Get it to compile
	/ 3. Get it to run, with default: sorts and prints lines by lex, as in ex 5-7
	/ 4. Write in annotations from book description
	5. Next day: review and add to inline notes
	6. Run it with optional flags, and record what used

Notes about what this is doing
	- A C function is *not* a variable, but can make a pointer to function
	- Pointers to functions can be assigned to vars, placed in arrays, passed
		to functions, returned by functions, etc
	- This program changes a sort function so that the SORT part receives
		different comparison functions for numeric vs lex cases	
	- Sort part of program is still 'qsort'
	- Comparison part is either strcmp or numcmp function
	- strcmp and numcmp are declared ahead of main, and passed as args
	- Re-ordering function is same for both, swapping pointers (though 
		pointer type in it are now 'void' rather than char or ing)
	- strcmp and numcp return the same kind of comparison result, so
		can be used the same way by qsort

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 		// max number of lines to be sorted
char *lineptr[MAXLINES]; 	// pointers to text lines

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

// qsort renamed to not overlap with stdlib function 'qsort'
// 'comp' is pointer to a function with two pointer args (void *), and returns int
// that last arg (comp) is pointer for which sorting function to use, numeric or lex
void qsort_ex(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);

// sort input lines: default is lexicographically, but flag '-n' means sort numerically
int main(int argc, char *argv[]) {
	int nlines;  		// number of input lines read
	int numeric = 0;	// default is lex sort NOT numeric

	if (argc > 1 && strcmp(argv[1], "-n") == 0)
		numeric = 1;
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		// in qsort call: 'strcmp' and 'numcmp' are addresses of functions
		// 'numcmp' defined below, 'strcmp' is in 'string' library
		qsort_ex((void **) lineptr, 0, nlines-1, (int (*)(void*,void*))(numeric ? numcmp : strcmp));
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("input too big to sort\n");
		return 1;
	}
}

// sort v[left]...v[right] into increasing order
// int (*comp)(void *, void *)  -> 'comp' is pointer to a function with two void * args, returns int

// comp 						-> pointer to a function
// *comp 						-> the function
// (*comp)(v[i], v[left]) 		-> call to the function made by qsort
void qsort_ex(void *v[], int left, int right, int (*comp)(void *, void *)) {
	int i, last;
	void swap(void *v[], int, int);

	if (left >= right) 		// do nothing if array contains fewer than 2 elements
		return;
	swap(v, left, (left +right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort_ex(v, left, last-1, comp);
	qsort_ex(v, last+1, right, comp);
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
*/

/********************************************************************************
5-14 Modify the sort program to handle a '-r' flag, which indicates sorting in
reverse (decreasing) order. Be sure that -r works with -n.

Where to handle this change: main, qsort

What to keep the same: numcmp and strcmp, since strcmp is system library,
	and they must work the same

Options for handling the two cases in qsort
	x make a #define (symbolic constant) for ">=" and "<=", and pass those from main
		-> can these be passed as args? no
	x make a char * for ">=" and "<=", and pass those from main
		-> not clear how to turn the string back into part of an expression
	x make an enum for ">=" and "<="
		these ARE veriables, can be passed as args
		But: values for enums can only be char or int
		And, still issue of making it back to part of an expression
	- make a separate function for qsort descending
	- make separate comparator function for qsort to use for those clauses

Note: currently both the comparison AND its opposite are both used in qsort
	Maybe change one of the conditional statements so uses same one


#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 		// max number of lines to be sorted
char *lineptr[MAXLINES]; 	// pointers to text lines

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

// qsort renamed to not overlap with stdlib function 'qsort'
// 'comp' is pointer to a function with two pointer args (void *), and returns int
// that last arg (comp) is pointer for which sorting function to use, numeric or lex
void qsort_ex(int descending, void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);

// sort input lines: default is lexicographically, but flag '-n' means sort numerically
// flag -r means sort in reverse order
// gcc -o ch_5_ex_14.o ch_5_ex_14.c && ./ch_5_ex_14.o -n -r
int main(int argc, char *argv[]) {
	int nlines;  		// number of input lines read
	int numeric = 0;	// default is lex sort, NOT numeric
	int descending = 0;  // default is ascending order, NOT descending

	
	if (argc > 1) {    // handle first arg
		if (strcmp(argv[1], "-n") == 0)
			numeric = 1;
		else if (strcmp(argv[1], "-r") == 0)
			descending = 1;
	}
	if (argc > 2) {    // handle second arg
		if (strcmp(argv[2], "-n") == 0)
			numeric = 1;
		else if (strcmp(argv[2], "-r") == 0)
			descending = 1;
	}

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		// in qsort call: 'strcmp' and 'numcmp' are addresses of functions
		// 'numcmp' defined below, 'strcmp' is in 'string' library
		qsort_ex(descending, (void **) lineptr, 0, nlines-1, (int (*)(void*,void*))(numeric ? numcmp : strcmp));
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("input too big to sort\n");
		return 1;
	}
}

// sort v[left]...v[right] into increasing order
// int (*comp)(void *, void *)  -> 'comp' is pointer to a function with two void * args, returns int

// comp 						-> pointer to a function
// *comp 						-> the function
// (*comp)(v[i], v[left]) 		-> call to the function made by qsort
void qsort_ex(int descending, void *v[], int left, int right, int (*comp)(void *, void *)) {
	int i, last;
	void swap(void *v[], int, int);

	if (left >= right) 		// do nothing if array contains fewer than 2 elements
		return;
	
	swap(v, left, (left +right)/2);
	last = left;
	for (i = left+1; i <= right; i++) {
		if (!descending) {
			if ((*comp)(v[i], v[left]) < 0) {  // ascending case
				swap(v, ++last, i);
			}
		} else {
			if ((*comp)(v[i], v[left]) > 0) {  // descending case
				swap(v, ++last, i);
			}
		}
	}
	swap(v, left, last);
	qsort_ex(descending, v, left, last-1, comp);
	qsort_ex(descending, v, last+1, right, comp);
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
*/

/********************************************************************************
5-15 Add the option -f to fold upper and lower case together, so that case 
distinctions are not made during sorting: for example, 'a' and 'A' compare as equal

Things presuming to NOT change to do this
	- Keep original char *, so will reprint as they were originally
	- The statement that uses strcmp: (*comp)(v[i], v[left])

Related in standard library
	- Does strcmp have an 'ignore case' option/equivalent: no
	- Is there another thing in <string.h> that handles ignoring case: no
	- Most related to handling char case: <ctype.h> isupper(c), islower(c), toupper(c), tolower(c)

Idea: in the comparison, only when lex sorting and ignore case
	* make two new char * to be same-case versions
	* read the original char *, and add each char after running tolower(c)
	* compare the same-case copies
	* use the result of that to then reorder the ORIGINAL char *

*/

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000 		// max number of lines to be sorted
char *lineptr[MAXLINES]; 	// pointers to text lines

int readlines(char *lineptr[], int nlines);
int checkflag(char s[], int argc, char *argv[]);
void writelines(char *lineptr[], int nlines);
void qsort_ex(int reverse, void *lineptr[], int left, int right, int (*comp)(void *, void *));
void qsort_nocase(int reverse, void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);

// sort input lines: default is lexicographically, but flag '-n' means sort numerically
// flag -r means sort in reverse order
// gcc -o ch_5_ex_14.o ch_5_ex_14.c && ./ch_5_ex_14.o -n -r
int main(int argc, char *argv[]) {
	int nlines;  		// number of input lines read
	int numeric = 0;	// default is lex sort, NOT numeric
	int reverse = 0;	// default is ascending order, NOT reverse
	int nocase = 0;   	// default lex sorting differentiates capitalization

	numeric = checkflag("-n", argc, argv);
	reverse = checkflag("-r", argc, argv);
	nocase = checkflag("-f", argc, argv);

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		// in qsort call: 'strcmp' and 'numcmp' are addresses of functions
		// 'numcmp' defined below, 'strcmp' is in 'string' library
		
		// MESSY FOR NOW
		if (!numeric && nocase) {
			printf("\nUsing qsort_nocase\n");
			qsort_nocase(reverse, (void **) lineptr, 0, nlines-1, (int (*)(void*,void*))(numeric ? numcmp : strcmp));
		} else {
			printf("\nUsing original qsort\n");
			qsort_ex(reverse, (void **) lineptr, 0, nlines-1, (int (*)(void*,void*))(numeric ? numcmp : strcmp));
		}
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
void qsort_ex(int reverse, void *v[], int left, int right, int (*comp)(void *, void *)) {
	int i, last, compared;
	void swap(void *v[], int, int);

	if (left >= right) 		// do nothing if array contains fewer than 2 elements
		return;
	
	swap(v, left, (left+right)/2);  // make a new 'pivot': swap index 0 and midpoint
	last = left;
	printf("\nleft: %s\n", (char *) v[left]);
	
	for (i = left+1; i <= right; i++) {
		printf("i: %s\n", (char *) v[i]);
		compared = (*comp)(v[i], v[left]);
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
	swap(v, left, last);
	qsort_ex(reverse, v, left, last-1, comp);
	qsort_ex(reverse, v, last+1, right, comp);
}

#include <stdlib.h>

void intolower(const char *str, char dest[]);

// for use only with lexicographic sorting, ignoring case
void qsort_nocase(int reverse, void *v[], int left, int right, int (*comp)(void *, void *)) {
	int i, last, compared;
	void swap(void *v[], int, int);
	char leftlower[100];
	char ilower[100];
	char *leftptr;
	char *iptr;

	if (left >= right) 		// do nothing if array contains fewer than 2 elements
		return;
	
	swap(v, left, (left+right)/2);  // make a new 'pivot': in first loop left is 0
	last = left;
	
	// get string at left in all lower case
	printf("left orig: %s\n", (char *) v[left]);
	intolower((char *) v[left], leftlower);  // put lower-case version of v[left] into leftlower
	printf("left lower arr: %s\n", leftlower);
	leftptr = leftlower;
	printf("left lower ptr: %s\n", leftptr);
	
	for (i = left+1; i <= right; i++) {
		
		// get string at i in all lower case
		printf("i: %s\n", (char *) v[i]);
		intolower((char *) v[i], ilower);
		printf("ilower arr: %s\n", ilower);
		iptr = ilower;
		printf("ilower ptr: %s\n", iptr);

		compared = (*comp)(iptr, leftptr);  // compare values at pointers to lower-case array
		
		// compare the lowercase versions, and swap array locations
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
	swap(v, left, last);
	qsort_ex(reverse, v, left, last-1, comp);
	qsort_ex(reverse, v, last+1, right, comp);
}

#include <ctype.h>

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