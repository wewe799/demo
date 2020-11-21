#include<stdio.h>
	struct date 
	{
		int month;
		int day;
		int year;
	} today;
int main()
{

//	struct data today;
	today.month=07;
	today.day=31;
	today.year=2019;
	printf("Today's date is %d-%02d-%d.\n",today.year,today.month,today.day);
	return 0;
}
