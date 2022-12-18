#include <stdio.h>

// print input one word per line

int main() {

	int c, p = EOF;

	while ((c = getchar()) != 'q') {
		if ((c != ' ') & (p != ' ')) // both not spaces
			putchar(c);
		else if ((c != ' ') & (p == ' ')) { // only prior a space
			putchar('\n');
			putchar(c);
		}
		p = c;
		// if both are spaces, or current is a space
		// do nothing
	}
}

/* makes multiple spaces into multiple new lines
int main() {

	int c, p = EOF;

	while ((c = getchar()) != 'q') {
		if (c == ' ')
			putchar('\n');
		else
			putchar(c);
	}
}
*/
