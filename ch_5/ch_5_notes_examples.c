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
