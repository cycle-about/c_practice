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
	Get lengths of both strings
	If t longer than s, return 0
	Otherwise, iterate in s up to position (length s - length t)
	For all remaining chars until '\0', compare s there, versus t from 0
	If any does not match, return 0
	Otherwise, return 1
*/

#include <stdio.h>

void strend(char *s, char *t);
int strleng(char *s);

int main() {
	char *s = "again hi";
	char *t = " world";
	strend(s, t);
	printf("%s\n", s);
}


void strend(char *s, char *t) {
	int slen, tlen;

	slen = strleng(s);
	tlen = strleng(t);

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

// related, page 103
// return length of string s
int strleng(char *s) {
	char *p = s;

	while (*p != '\0')
		p++;
	return p - s;
}