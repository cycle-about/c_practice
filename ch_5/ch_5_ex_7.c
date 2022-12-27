// gcc -o ch_5_ex_7.o ch_5_ex_7.c && ./ch_5_ex_7.o

// pages 108-110 setup for 5-7

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000    	// max number of lines to be sorted

// char *lineptr[MAXLINES]: lineptr is an array of MAXLINES elements,
//     each element of which is a pointer to a char
// lineptr[i]: a char pointer
// *lineptr[i]: char it points to, the first character of the i-th saved text line
char *lineptr[MAXLINES]; 	// array of pointers, each element is pointer to a line's first char

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

// to execute sorting: type last line, 'enter', then ctrl+d
// page 108: sort input lines
int main() {
	int nlines; 	// number of input lines read

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

#define MAXLEN 1000 	// max length of any input line
int getaline(char *, int);
char *alloc(int);

// ********************************************************************************
// 5-7
// Part 1. Rewrite readlines to store lines in an array supplied by main, rather than
// calling alloc to maintain storage. 
// Part 2. How much faster is the program?
// ********************************************************************************

// read input lines: collect and save chars of each line,
//     put pointers to the lines in array for use by rest of program, and return count of input lines
// it modifies char *lineptr[], which is used elsewhere in program
int readlines(char *lineptr[], int maxlines) {
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	// loop and get lines until terminal input is length 0
	while ((len = getaline(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || (p = alloc(len)) == NULL) {
			return -1;
		} else {
			line[len-1] = '\0';  // delete newline
			// strcpy library function p 249: copy 'line' (type: const char *) into 'p' (type: char *)
			// 'p' gets contents of 'line'
			strcpy(p, line);
			lineptr[nlines++] = p; // put pointer to line into variable used throughout program
		}
	}
	return nlines;
}

// sort v[left]...v[right] into increasing order
// based on quicksort page 87: pick element, subset others by greater or less than it,
//     then sort those subsets. Base case is single-element subset
// each iteration of quicksort moves ONE ITEM (the pivot) into its CORRECT FINAL position,
//     where all items to left all smaller, and all items to right are larger
void qsort(char *v[], int left, int right) {
	int i, last;
	void swap(char *v[], int i, int j);

	if (left >= right)  // do nothing if array contains fewer than 2 elements
		return;
	swap(v, left, (left + right)/2);  // move pivot (partition element) to v[0]
	last = left;
	for (i = left+1; i <= right; i++)  // partition
		// library strcmp (p 249): return <0 if element i is less, >0 if left is less, 0 if equal
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);  // restore partition element
	qsort(v, left, last-1);
	qsort(v, last+1, right);
}

// write output lines in order they appear in 'lineptr',
//     where they were already put in sorted order
void writelines(char *lineptr[], int nlines) {
	printf("\nLines after sorting:\n");
	while (nlines-- > 0)
		printf("%s\n", *lineptr++); // print char array pointed to by next element in lineptr
}

// page 110: interchange v[i] and v[j]
void swap(char *v[], int i, int j) {
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
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



