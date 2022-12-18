# include <stdio.h>

/* print Celsius-Fahrenheit table for 
 * Fahrenheit = 300, 280, ..., 0 */

int main() {
	
	int fahr;

	for (fahr = 300; fahr >= 0; fahr -= 20) {
		printf("%3d %6.1f\n", fahr, (5.0/9.0)*(fahr-32));
	}	
}
