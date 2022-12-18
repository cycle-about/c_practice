// gcc -o ch_5_ex_3.o ch_5_ex_3.c && ./ch_5_ex_3.o

/******************************************************************************** 
5-3 Write a pointer version of the function 'strcat' that we showed in Chapter 2:
strcat(s,t) copies the string 't' to the end of 's' (page 107)

Surprising error message
	error: lvalue required as left operand of assignment
   			while ((s+i = t+j) != '\0') {

*/

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