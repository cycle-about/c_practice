#include <stdio.h>

int main() {

	// p is the prior character; c advances and is the current one
	int c, p = EOF;		// int value of EOF is -1

	// boolean expressions evaluate to 0 if false, 1 if true
	while ((c = getchar()) != EOF) {
		// if one or both expressions are false, sum is >0 
		if ((c != ' ') + (p != ' ') > 0)
			putchar(c);
		p = c;
	}
}
