#include <stdio.h>

#define IN	1	// has reached a blank
#define OUT	0	// not a blank

/* copy input to output, and replace any series of blanks
*  with a single blank */
int main() {

	int c;
	int state;

	state = OUT;

	while((c = getchar()) != EOF) {
		if ((state == OUT) & (c == ' ')) {
			state = IN;
			break;
		} else if ((state == IN) & (c != ' ')) {
			state = OUT;
			putchar(' ');
	       		putchar(c);
		} else		
			putchar(c);
	}
}
