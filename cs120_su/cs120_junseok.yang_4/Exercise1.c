/**
\file        Exercise1.c
\author      junseok.yang
\par         email: wnstjr4043@naver.com
\par         course: CS120
\par         lab: 4
\date        6/26/2018
\brief
This program calculates the Factorial number function and roof.
*/
#include<stdio.h>
int fac(int n);
int main(void)
{
	int num = -1, a, b, i, j;
	
	while (num < 0 || num > 12)
	{
		printf("Enter an integer between 0 and 12: \n");
		scanf("%d", &num);
	}
	printf("%d factorial (%d!) is: \n\n", num, num);

	for (a = 0; a <= num; a++)
	{
		for (b = 0; b <= a; b++)
		{
			printf("%d", num - b);
			if (a == b)
				continue;
			else
				printf(" X ");
		}
		printf("!\n");
	}
	
	for (i = 0; i <= num; i++)
	{
		for (j = num; j > i; j--)
		{
			printf("%d", j);
			printf(" X ");
		}
		printf("%d", fac(i));
		if(i!=num)
			printf("\n");
	}

	return 0;
}
int fac(int n)
{
	if (n <= 1)
		return 1;
	else
		return n * fac(n - 1);
}