/**
\file        Exercise2.c
\author      junseok.yang
\par         email: wnstjr4043@naver.com
\par         course: CS120
\par         lab: 4
\date        6/26/2018
\brief
This program calculates the find maxnum, minnum, maxcount, mincount, average, numcount and infinite roof tool.
*/
#include<stdio.h>

int main(void)
{
	int userNumber=1, smallestnumber=0, largestnumber=0;
	int count=1,a=1,s=0,sum=0;
	double Average;
	printf("Enter a series of positive or negative numbers\n");
	printf("Use 0 to end the list: \n");
	scanf("%d", &userNumber);
	while (1)
	{
		if (userNumber == 0)
			break;
		if (largestnumber < userNumber)
		{
			largestnumber = userNumber;
			count = 1;
		}
		else if (largestnumber == userNumber)
		{
			count++;
		}
		if (smallestnumber > userNumber)
		{
			smallestnumber = userNumber;
			a = 1;
		}
		else if (smallestnumber == userNumber)
		{
			a++;
		}
		if (userNumber != 0)
		{
			sum = sum + userNumber;
			s++;
		}
		printf("%d: %d\n", userNumber, count);
		scanf("%d", &userNumber);
	}
	Average = (double)sum /(double)s ;
	printf("Numbers Entered:%12d\n", s);
	printf("Average is:%17.2f\n", Average);
	printf("Largest number:%13d\n", largestnumber);
	printf("Largest count:%14d\n", count);
	printf("Smallest number:%12d\n", smallestnumber);
	printf("Smallest Count:%13d", a);
	return 0;
}