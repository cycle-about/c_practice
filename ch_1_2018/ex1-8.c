#include <stdio.h>

// count blanks, tabs, newlines
int main() {

	int c, nl, tb, bl;

	nl = tb = bl = 0;
	while ((c = getchar()) != EOF) {
		if (c == '\n')
			++nl;
		else if (c == '\t')
			++tb;
		else if (c == ' ')
			++bl;
	}
	printf("%d%d%d\n", nl, tb, bl);
}
