// gcc -o ch_5_ex_7.o ch_5_ex_7.c && ./ch_5_ex_7.o

#include <stdio.h>
#include <string.h>

#define MAXLINES 5000    	// max number of lines to be sorted

char *lineptr[MAXLINES]; 	// pointers to text lines

int readlines(char *lineptr[], int nlines);
void writelines_v0(char *lineptr[], int nlines);
void writelines_v1(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

// page 108
// sort input lines
int main() {
	int nlines; 	// number of input lines read

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort(lineptr, 0, nlines-1);
		writelines_v1(lineptr, nlines);
		return 0;
	} else {
		printf("error: input too big to sort\n");
		return 1;
	}
}

#define MAXLEN 1000 	// max length of any input line
int getaline(char *, int);
char *alloc(int);

// read input lines
int readlines(char *lineptr[], int maxlines) {
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getaline(line, MAXLEN)) > 0) {
		if (nlines >= maxlines || (p = alloc(len)) == NULL) {
			return -1;
		} else {
			line[len-1] = '\0';  // delete newline
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	}
	return nlines;
}

// write output lines
void writelines_v0(char *lineptr[], int nlines) {
	int i;

	for (i = 0; i < nlines; i++) {
		printf("%s\n", lineptr[i]);
	}
}

// write output lines, using pointers
void writelines_v1(char *lineptr[], int nlines) {
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

// sort v[left]...v[right] into increasing order
void qsort(char *v[], int left, int right) {
	int i, last;
	void swap(char *v[], int i, int j);

	if (left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last-1);
	qsort(v, last+1, right);
}

// interchange v[i] and v[j]
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


/******************************************************************************** 
5-7 Rewrite readlines to store lines in an array supplied by main, rather than
calling alloc to maintain storage. How much faster is the program?

*/
