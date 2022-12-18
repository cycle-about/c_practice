#include <stdio.h>

// To use this program, enter any character in command line to be evaluated

int main() {

	int c;

	c = (getchar() != EOF);

	if (c == 1) 
		printf("expected, char does not equal EOF\n");
	else if (c == 0) 
		printf("problem, char *does* equal EOF\n");
	else
		printf("problem, expression is *not* a boolean\n");
}
