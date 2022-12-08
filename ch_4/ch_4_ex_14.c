// gcc -o ch_4_ex_14 ch_4_ex_14.c && ./ch_4_ex_14

/******************************************************************************** 
4-14 Define a macro swap(t,x,y) that interchanges two arguments of type t.
(Block structure will help.)

*/

#include <stdio.h>

#define max(A, B)    ((A) > (B) ? (A) : (B))
#define swap(t,x,y)    t temp; temp = x; x = y; y = temp;

int main() {
	// printf("%d\n", max(5, 6));
	
	int x = 1;
	int y = 7;

	printf("%d %d\n", x, y);
	swap(int, x, y);
	printf("%d %d\n", x, y);
}

