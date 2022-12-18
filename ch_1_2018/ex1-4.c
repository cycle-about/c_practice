# include <stdio.h>

/* print Celsius-Fahrenheit table for 
 * Celsius = 0, 20, ..., 300 */

int main() {
	
	float celsius, fahr;
	int lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;

	celsius = lower;
	while (celsius <= upper) {
		fahr = (celsius / (5.0/9.0)) + 32;
		printf("%3.0f %6.1f\n", celsius, fahr);
		celsius += step;
	}
}
