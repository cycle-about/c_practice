// gcc -o ch_5_ex_16_v2.o ch_5_ex_16_v2.c && ./ch_5_ex_16_v2.o

/********************************************************************************
5-16 Add the -d ("directory order") option, which makes comparisons only on letters, 
numbers, and blanks. Make sure it works in conjunction with -f.

[Adding -f sorts ignoring case, and was ex 5-15. Ex 5-14 was sorting in reverse order]

Decision to resume: start from base case, add -d, and only then add back -f
Base to use: sort program page 119, retype

Decisions
	For now, do not include -f
	What is most probable place to change so it compares only letters, numbers, blanks
		Where do the actual char comparisons happen: strcomp and numcmp
			Those though not promising place to edit since are shared
		Upstream option, think used in other questions: modify the char * compared
			Do that before passing to qsort
				Pointers to original text lines: char *lineptr[MAXLINES]
				Pointers to modified text lines: char *modptr[MAXLINES]
*/

// page 119, original sort program
#include <stdio.h>
#include <string.h>

#define MAXLINES 5000     // max number of lines to be sorted

char *lineptr[MAXLINES];  // pointers to orginal text lines

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int strcomp(char *s, char *t);  // renamed from strcmp to not conflict with standard library method
int numcmp(char *, char *);
double atof(char s[]);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);

// sort input lines
int main(int argc, char *argv[]) {
	int nlines;       // number of input lines read
	int numeric = 0;  // 1 if numeric sort

	if (argc > 1 && strcomp(argv[1], "-n") == 0) {
		numeric = 1;
	}

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort((void  **) lineptr, 0, nlines-1, (int (*)(void*,void*))(numeric ? numcmp : strcomp));
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("input too big to sort\n");
		return 1;
	}
}

// sort v[left]...v[right] into increasing order
void qsort(void *v[], int left, int right, int (*comp)(void *, void *)) {
	int i, last;
	void swap(void *v[], int, int);

	if (left >= right) {  // do nothing if array contains fewer than 2 elements
		return;
	}
	swap(v, left, (left+right)/2);
	last = left;
	for (i = left+1; i <= right; i++) {
		if ((*comp)(v[i], v[left]) < 0) {
			swap(v, ++last, i);
		}
	}
	swap(v, left, last);
	qsort(v, left, last-1, comp);
	qsort(v, last+1, right, comp);
}

// return <0 if s<t, 0 if s==t, >0 if s>t (page 106)
int strcomp(char *s, char *t) {
	for ( ; *s == *t; s++, t++)  // iterate over char *, until *s and *t do not match, or *s is end of string
		if (*s == '\0')
			return 0;
	return *s - *t;  // subtract chars at first position where s and t disagree
}

// compare s1 and s2 numerically
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

#include <ctype.h>

// convert string s to double
double atof(char s[]) {
	double val, power;
	int i, sign;

	for (i=0; isspace(s[i]); i++)  // skip white space
		;
	sign = (s[i] == '-' ? -1 : 1);
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	return sign * val / power;
}

// read input lines (page 109)
#define MAXLEN 1000  // max length of any input line

int getaline(char *, int);
char *alloc(int);

int readlines(char *lineptr[], int maxlines) {
	int len, nlines;
	char *p, line[MAXLEN];

	nlines = 0;
	while ((len = getaline(line, MAXLEN)) > 0) 
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0';  // delete newline
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

// return pointer to n characters (page 101)
#define ALLOCSIZE 10000  // size of available space

static char allocbuf[ALLOCSIZE];  // storage for alloc
static char *allocp = allocbuf;   // next free position

char *alloc(int n) {
	if (allocbuf + ALLOCSIZE - allocp >= n) {  // it fits
		allocp += n;
		return allocp - n;  // old p
	} else			// not enough room
		return 0;
}

// (page 109)
void writelines(char *lineptr[], int nlines) {
	printf("\nResult:\n");
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

// get line into s, return its length (page 69)
int getaline(char s[], int lim) {
	int c, i;

	i = 0;
	while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}