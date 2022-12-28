// gcc -o ch_5_ex_8.o ch_5_ex_8.c && ./ch_5_ex_8.o

/********************************************************************************
page 111. Original setup for 5-8

#include <stdio.h>

// type char because these are all small integers
static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main() {

	// get day of year from: year, month, day
	// printf("day of year: %d\n", day_of_year(2022, 2, 10));

	// get month and day from day of year
	int month;
	int day;
	pass the ADDRESSES of vars to be used as pointers; function can modify those locations
	month_day(2022, 41, &month, &day);
	printf("Month: %d, Day: %d\n", month, day);
}

// set month and day from day of year
void month_day(int year, int yearday, int *pmonth, int *pday) {
	int i, leap;

	// leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	leap = 0;
	for (i = 1; yearday > daytab[leap][i]; i++) {
		yearday -= daytab[leap][i];
	}
	*pmonth = i;
	*pday = yearday;
}

// set day of year from month and day
int day_of_year(int year, int month, int day) {
	int i, leap;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	for (i = 1; i < month; i++) {
		day += daytab[leap][i];
	}
	return day;
}
*/

/********************************************************************************
5-8 There is no error checking in day_of_year. Remedy this defect.
*/

#include <stdio.h>

// type char because these are all small integers
static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main() {

	// get day of year from: year, month, day
	printf("day of year: %d\n", day_of_year(2022, 6, 30));

	// get month and day from day of year
	// int month;
	// int day;
	// pass the ADDRESSES of vars to be used as pointers; function can modify those locations
	// month_day(2022, 41, &month, &day);
	// printf("Month: %d, Day: %d\n", month, day);
}

// set day of year from month and day
int day_of_year(int year, int month, int day) {
	int i, leap;

	if (month < 0 || month > 12) {
		printf("invalid month\n");
		return -1;
	}
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	if (day > daytab[leap][month]) {
		printf("invalid day in month\n");
		return -1;
	}
	for (i = 1; i < month; i++) {
		day += daytab[leap][i];
	}
	return day;
}

// set month and day from day of year
void month_day(int year, int yearday, int *pmonth, int *pday) {
	int i, leap;

	// leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	leap = 0;
	for (i = 1; yearday > daytab[leap][i]; i++) {
		yearday -= daytab[leap][i];
	}
	*pmonth = i;
	*pday = yearday;
}