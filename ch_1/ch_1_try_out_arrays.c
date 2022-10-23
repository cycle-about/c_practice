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

/*
6. try using copy() method on p29 to handle the transfer to temp
 this works in some ways
	
strange finding with this setup 
	before copy: 97 97 97 97 97 97 97 97 97 97
	temp array: 97 97 97 97 97 97 97 97 97 97 98 98 98 98 98 98 98 98 98 98
	after copy: 97 97 97 97 97 97 97 97 97 97 0 58 30 46 82 125 -100 -93 1 0

Assessment of what happened here: not erroring out, but not doing as expected

#include <stdio.h>
#define SMALL 10
#define BIG 12

int copy(char from[], int len);

int main() {

	int i, cur_len;
	char sdigit[SMALL];

	// populate array with zeros, with size check
	cur_len = SMALL;
	for (i = 0; i < SMALL; i++) {
		sdigit[i] = 'a';
	}

	cur_len = copy(sdigit, SMALL);

	printf("\nafter copy:");
	for (i = 0; i < cur_len; i++) {
		printf(" %d", sdigit[i]);
	}
}


int copy(char from[], int len) {
	int i;
	int new_len;

	// print all values in array
	printf("before copy:");
	for (i = 0; i < len; i++) {
		printf(" %d", from[i]);
	}

	new_len = len * 2;
	char temp[new_len];

	for (i = 0; i < new_len; i++)
		if (i < len)
			temp[i] = from[i];
		else
			temp[i] = 'b';

	printf("\ntemp array:");
	for (i = 0; i < new_len; i++) {
		printf(" %d", temp[i]);
	}

	from = temp;
	return new_len;
}

*/

/* 7. Experiments with what happens when array modified by method, other than resize
Conclusion: yes, if just reassign elements in method, orig array changes

Additional conclusion: seems that yes the original array is only the originally defined size

Can arrays be reassigned (same size) with a '='? ****NO****

#include <stdio.h>
#define SMALL 10
#define BIG 12

int copy(char from[], int len);

int main() {

	int i, cur_len;
	char sdigit[SMALL];

	// populate array with zeros, with size check
	cur_len = SMALL;
	for (i = 0; i < SMALL; i++) {
		sdigit[i] = 'a';
	}

	// print all values in array
	printf("before method call:");
	for (i = 0; i < SMALL; i++) {
		printf(" %d", sdigit[i]);
	}

	cur_len = copy(sdigit, SMALL);

	printf("\nafter method call:");
	for (i = 0; i < SMALL; i++) {
		printf(" %d", sdigit[i]);
	}
}


int copy(char from[], int len) {
	int i;
	int new_len;

	new_len = len * 2;
	char temp[len];

	for (i = 0; i < len; i++) {
		temp[i] = 'c';
	}

	//for (i = 0; i < new_len; i++)
	//	if (i < len)
	//		temp[i] = from[i];
	//	else
	//		temp[i] = 'b';

	printf("\ntemp array:");
	for (i = 0; i < new_len; i++) {
		printf(" %d", temp[i]);
	}

	from = temp;
	return len;
}
*/

/*
end conclusions: did google 'c how to resize arrays.' Can't. Methods to work around this are calloc, char*, realloc
reread what the question is looking for. unclear if should be using malloc etc already
*/

/*
///////////////////////// additional check 10/23/22 /////////////////////////
confirm impression from yesterday
	can READ outside of array bounds without error (though is junk),
	but errors out if try to write out of bounds


#include <stdio.h>
#define SMALL 4
#define BIG 6

int main() {

	int i;
	char sdigit[SMALL];

	// populate array up to allowed bounds
	for (i = 0; i < SMALL; i++) {
		sdigit[i] = '9';
	}

	// prints as expected
	printf("Print to allowed bounds (length %d):\n\t", SMALL);
	for (i = 0; i < SMALL; i++) {
		printf(" %d", sdigit[i]);
	}

	// works but values outside of assigned are garbage
	printf("\nPrint OUTSIDE of allowed bounds (length %d):\n\t", BIG);
	for (i = 0; i < BIG; i++) {
		printf(" %d", sdigit[i]);
	}

	printf("\nTry to assign OUTSIDE of allowed bounds:\n");
	// ERRORS OUT BEFORE EXECUTING FIRST PRINT STATEMENT OF THIS LOOP
	for (i = 0; i < BIG; i++) {
		printf("\tAbout to assign to index %d", i);
		sdigit[i] = '2';
	}
}
*/


/* additional test: printing char[] elements and whole array

when initialized with 'c'
	Elements as digits
		 99 99 99 99 99 99
	Array as string
		cccccc
--------

# when initialized with '2'
	Elements as digits
		 50 50 50 50 50 50
	Array as string
		222222

%d for a char prints the ASCII decimal value
%s prints the digit

*/

#include <stdio.h>
#define SIZE 6
int main() {

	int i;
	char sdigit[SIZE];

	// populate array allowed bounds
	for (i = 0; i < SIZE; i++) {
		sdigit[i] = '2';
	}

	// print each element as digit
	printf("Elements as digits\n\t");
	for (i = 0; i < SIZE; i++) {
		printf(" %d", sdigit[i]);
	}

	// print each element as string
	// ERRORS OUT: 'Segmentation fault (core dumped)'
	//printf("\nElements as string\n\t");
	//for (i = 0; i < SIZE; i++) {
	//	printf(" %s", sdigit[i]);
	//}

	// print whole array as string
	printf("\nArray as string\n\t");
	printf("%s", sdigit);
}