// 10/22/22
// trying out with arrays, for ideas about exercise 1-16

/*
Combined compile and run command
gcc -o ch_1_try_out_arrays ch_1_try_out_arrays.c && ./ch_1_try_out_arrays
*/


/*
// 0. base case: make array of a size, initialize all values, print them
#include <stdio.h>
#define MAXDIGITS 10

int main() {

	int i;
	int ndigit[MAXDIGITS];

	// populate array with zeros
	for (i=0; i<MAXDIGITS; i++) {
		ndigit[i] = 0;
	}

	// print all values in array
	printf("ndigits array: ");
	for (i=0; i<MAXDIGITS; i++) {
		printf(" %d", ndigit[i]);
	}
}
*/

/*
// 1. Test trying to populate more indices than exist
//     Result: *** stack smashing detected ***: terminated
#include <stdio.h>
#define MAXDIGITS 10

int main() {

	int i;
	int ndigit[MAXDIGITS];

	// populate array with zeros
	for (i=0; i<20; i++) {
		ndigit[i] = 0;
	}

	// print all values in array
	printf("ndigits array: ");
	for (i=0; i<MAXDIGITS; i++) {
		printf(" %d", ndigit[i]);
	}
}
*/

/*
// 2. Check and prevent if tries to assign over allowed digits
//     result: with break only prints 'trying' message once, and no unallowed assignments
#include <stdio.h>
#define MAXDIGITS 10

int main() {

	int i;
	int ndigit[MAXDIGITS];

	// populate array with zeros, with size check
	for (i=0; i<20; i++) {
		if (i >= MAXDIGITS) {
			printf("Trying to access nonexistant index\n");
			break;
		} else
			ndigit[i] = 0;
	}

	// print all values in array
	printf("ndigits array: ");
	for (i=0; i<MAXDIGITS; i++) {
		printf(" %d", ndigit[i]);
	}
}
*/

/*
// 3. first attempt to increase size of array
// make separate array temp[size*2], then copy in values
// result: every time 'stack smashing detected'
#include <stdio.h>

int resize(int cur_length, int ndigit[]) {

	int i;

	printf("start ndigit[]: ");
	for (i=0; i < cur_length; i++)
		printf(" %d", ndigit[i]);

	// initialize temp[] that is twice the size of current ndigit
	int temp_len = cur_length * 2;
	int temp[temp_len];

	// copy in intial values
	for (i=0; i < cur_length; i++) {
			temp[i] = ndigit[i];
	}

	printf("\ntemp[]: ");
	for (i=0; i < temp_len; i++)
		printf(" %d", temp[i]);

	// todo erroring out here
	// copy in all prior array values
	//for (i=0; i < cur_length; i++) 
	//	temp[i] = ndigit[i];

	//printf("\nafter temp[]: ");
	//for (i=0; i < temp_len; i++)
	//	printf(" %d", ndigit[i]);
	
	//ndigit = temp;
	//return cur_length *= 2;
	return 0;
}
*/

/*
// 4. try to resize array by just re-declaring it
// still get stack smashing errors
#include <stdio.h>
#define STARTLEN 10
#define ENDLEN 12

int resize(int ndigit[], int cur_len);

int main() {

	int i, cur_len;
	int ndigit[STARTLEN];

	cur_len = STARTLEN;

	// initialize array with ones
	for (i=0; i < ENDLEN; i++) {
		printf("\n %d", i);
		if (i >= cur_len) {
			printf("too long");
			cur_len = resize(ndigit, cur_len);
			//ndigit[i] = 1;
		} else
			ndigit[i] = 0;
	}

	// print all values in array
	printf("ndigits array:");
	for (i=0; i<cur_len; i++) {
		printf(" %d", ndigit[i]);
	}
}

int resize(int ndigit[], int cur_len) {
	int new_size = cur_len*2;
	ndigit = ndigit[new_size];
	return new_size;
}
*/

// 5. Idea from warning generated with re-assignment try
// warning: assignment to ‘int *’ from ‘int’ makes pointer from integer without a cast [-Wint-conversion]
//     ndigit = ndigit[new_size];
// make a pointer to be the variable 'in use' and just make new arrays for it to point to
// question though: pointers are not introduced until chapter 5, should there be a way to do this without them, shit


// 6. try using copy() method on p29 to handle the transfer to temp
#include <stdio.h>
#define SMALL 10
#define BIG 12

void copy(char to[], char from[], int len);

int main() {

	int i;
	char sdigit[SMALL];
	char bdigit[BIG];

	// populate array with zeros, with size check
	for (i=0; i<SMALL; i++) {
		sdigit[i] = 'a';
	}

	// print all values in array
	printf("sdigits array:");
	for (i=0; i<SMALL; i++) {
		printf(" %d", sdigit[i]);
	}

	copy(bdigit, sdigit, SMALL);

	// print all values in array
	printf("bdigits array:");
	for (i=0; i<BIG; i++) {
		printf(" %d", bdigit[i]);
	}
}

void copy(char to[], char from[], int len) {

	for (int i = 0; i < len; i++)
		to[i] = from[i];
}