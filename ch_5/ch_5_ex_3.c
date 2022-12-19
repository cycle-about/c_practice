// gcc -o ch_5_ex_3.o ch_5_ex_3.c && ./ch_5_ex_3.o

/******************************************************************************** 
5-3 Write a pointer version of the function 'strcat' that we showed in Chapter 2:
strcat(s,t) copies the string 't' to the end of 's' (page 107)

Surprising error message
	error: lvalue required as left operand of assignment
   			while ((s+i = t+j) != '\0') {
   	-> need to use the * to get 'value at'


#include <stdio.h>

void strcat_ch2(char s[], char t[]);
void strcatp(char s[], char t[]); // renamed since strcat is in <string.h>

int main() {
	char s[100] = "again hi"; // note: segfaults if string to long for declared size
	char t[100] = " world";
	strcatp(s, t);
	printf("%s\n", s);
}


void strcatp(char *s, char *t) {
	int i, j = 0;

	for (i = 0; *(s+i) != '\0'; i++) {
		//putchar(*(s+i));
	}

	while (( *(s+i) = *(t+j) ) != '\0') {
		i++;
		j++;
		//printf("j value: %d\n", j);
	}

	// starting at end of s, add letters in t
	//while ((s[i++] = t[j++]) != '\0') 	// append letters in t into s, 
	//
}

// related: page 99 (renamed since name already used in <string.h>)
int strleng(char *s) {
	int n;

	for (n = 0; *s != '\0'; s++)
		n++;
	return n;
}

// original strcat, page 48
void strcat_ch2(char s[], char t[]) {
	int i, j;

	i = j = 0;
	while (s[i] != '\0') 	// find end of s
		i++;
	// starting at end of s, add letters in t
	while ((s[i++] = t[j++]) != '\0') 	// append letters in t into s, 
		;
}
*/


/******************************************************************************** 
5-4 Write the function strend(s,t) which returns 1 if the string t occurs at the
end of string s, and zero otherwise

Approach
	/ Get lengths of both strings
	/ If t longer than s, return 0
	Otherwise, iterate in s up to position (length s - length t)
	For all remaining chars until '\0', compare s there, versus t from 0
	If any does not match, return 0
	Otherwise, return 1

#include <stdio.h>

int strend(char *s, char *t);
int strleng(char *s);

int main() {
	char *s = "again,hccicccc";
	char *t = "ccc";
	int r = strend(s, t);
	if (r == 1)
		printf("end matches\n");
	else
		printf("does not match\n");
}

// return 1 if s ends with t, otherwise 0
int strend(char *s, char *t) {
	int slen, tlen, i, j;

	slen = strleng(s);
	tlen = strleng(t);

	printf("lengths: %d, %d\n", slen, tlen);

	if (tlen > slen) {  // t could not be end of s
		printf("s shorter than t\n");
		return 0;
	}

	// compare chars in t with the tlen end chars of s

	// first version of iteration
	//for (i = slen-tlen, j = 0; i < slen; i++, j++) {
	//	if ( *(s+i) != *(t+j) ) {
	//		printf("mismatch at indices: %d, %d\n", i, j);
	//		return 0;
	//	}
	//}

	// alternate iteration - note, worked on first try :)
	i = slen-tlen;
	j = 0;
	while (*(s+i) != '\0') {
		if ( *(s+i++) != *(t+j++) ) {
			printf("mismatch at indices: %d, %d\n", i, j);
			return 0;
		}
	}

	return 1;
}

// related, page 103
// return length of string s
int strleng(char *s) {
	char *p = s;

	while (*p != '\0')
		p++;
	return p - s;
}
*/


/******************************************************************************** 
5-5 Write versions of the library functions strncpy, strncat, and strncmp, which
operate on at most the first n characters of their arg strings. For example,
strncpy(s,t,n) copies at most n chars of t to s. Full descriptions are in Appendix B

[Note: ex does not include arg names or desciption to use exact types like size_t, 
so use eg just int for n if helps get first version of this done]

Library function signatures and descriptions page 249

In all three descriptions, types are:
    s, t 	 	char *
    cs, ct 		const char *
    n 			size_t
    c 			int converted to char


// copy at most n char of ct to s
// return s; pad with '\0' if t has fewer than n chars
char *strncpy(s,ct,n);  

// concatenate at most n characters of string ct to string s
// terminate s with '\0'; return s
char *strncat(s,ct,n);

// compare at most n char of string cs to string ct
// return <0 if (cs > ct), 0 if (cs==ct), or >0 if (cs > ct)
int strncmp_ex(cs,ct,n); 

*/

#include <stdio.h>

char *strncat_ex(char *s, char *ct, int n);

int main() {
	char *s = "hello world";
	const char *ct = "!";
	printf("%s\n", s);
}


// concatenate at most n chars of string ct to string s
// terminate s with '\0'; return s
char *strncat_ex(char *s, char *ct, int n) {
	return s;
}