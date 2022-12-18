/*
A pointer is a variable that contains the address of a variable

		SYMBOL 		GETS
		&			address of variable
		*			value at pointer

variable has an address
address has a value
pointer is an address
*/

// Example 1 page 94
int x = 1, y = 2, z[10];
// 'ip' is a pointer to an int, aka contains address of an int
int *ip;
// ip contains address of x, aka ip points to x
ip = &x;
// y gets the value at address of x; result is y = x
y = *ip;
// value at address stored by ip (aka address of x) gets 0; result is x = 0
*ip = 0;
// ip contains address of z[0]; aka ip points to z[0]
ip = &z[0];


// dp points to a double; value at address dp is a double
// arg of atof() is pointer to a char
double *dp, atof(char *);

// increments value at ip by 10
*ip = *ip + 10;

// gets value at ip, adds 1, assigns result to y
y = *ip + 1;

// increment what ip points to
*ip += 1;
++*ip;
(*ip)++;  // need parens, or would iterate ip, ++ associate R to L

// pointers are themselves variables, can reassign without dereference
// eg if iq and ip are both pointers to ints
iq = ip;

/*
Pointers and function args, page 95-6
C passes args to functions only by value, so no direct way to alter var in calling function
The swap(a, b) used only swaps COPIES of a and b
Alternate approach is to interchange *px and *py
That allows function to access and change objects in function that called it

*/
void swap(int *px, int *py) {
	int temp;

	temp = *px;
	*px = *py;
	*py = temp;
}

/*
Part of getint() on page 97
Reads chars LEFT to RIGHT (larger to smaller) and puts into an int

eg string "38"
Reads 3, then reads 8

Loop 0
	*pn = 0
	c = char 3, dec 51
	(10 * 0) + (51 - 48))
	0 + 3 = 30
Loop 1
	*pn = 30
	c = char 8, dec 56
	(10 * 30) + (56 - 48))
	30 * 8 = 38

*/

//page 98
int a[10]; 	 // defines block of 10 consecutive objects, named a[0] to a[9]
int *pa;     // pa is a pointer to an int
pa = &a[0];	 // sets pa to point to a[0]
x = *pa; 	 // copies the contents of a[0] into x
*(pa+1) 	 // refers to contents of a[1]

// "adding to a pointer" means that pa+i points to element i elements after pa

// page 99
// the value of variable (or expression) of type array is address of its element 0

// equivalent expressions
pa = &a[0];  // pa points to address of a[0]
pa = a; 	 // pa poitns to array a, meaning address of its element a[0]

// equivalent expressions
a[i] 		// value at i-th element of array a
*(a+i) 		// value at i-th element of array a

// equivalent expressions
&[a+i] 		// address of i-th element of array a
a+i 		// element i elements after a[0]

// pointer is a variable, so these expressions are legal
pa = a 		// pointer pa points to element a[0]
pa++ 		// add 1 to the index of array element pa points to


// function using pointers that returns length of a string
// s is pointer to a char to the initial element of the array
// this pointer is unique to this function, no effect on calling function
// these are all valid ways to call the function
    strlen("hello, world"); 	// string constant
    strlen(array); 				// char array[100]
    strlen(ptr); 				// char *ptr (to first element of array)

int strlen(char *s) {
	int n;

	// s is a pointer, so incrementing it has no effect on string in calling function
	for (n = 0; *s != '\0'; s++)
		n++;
	return n;
}

// equivalent as formal params in function definition (page 99-100)
// notes latter is preferred, since explicit that param is a pointer
char s[];
char *s;

// when array name passed to function, 