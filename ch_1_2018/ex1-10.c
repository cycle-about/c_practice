#include <stdio.h>

/* copy input to output, replacing space characters with
 * their string value
 */

int main() {

	int c;

	while((c = getchar()) != 'q') {
		if (c == '\t')
			printf("\t");
		else if (c == '\b')
			printf("\b");
		else if (c == '\\')
			printf("\\");
		else
			putchar(c);
	}
}
