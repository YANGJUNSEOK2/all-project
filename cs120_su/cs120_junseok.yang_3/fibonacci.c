/**
\file        fibonacci.c
\author      junseok.yang
\par         email: wnstjr4043@naver.com
\par         course: CS120
\par         lab: 3
\date        6/25/2018
\brief
This program calculates the fibonacci numbers and quotient.
*/
#include<stdio.h>
double fibona(int x);

int main(void)
{
	int x = 0;
	int n1 = 0, n2 = 1, n3 = 0;
	int a;
	double quotient = 1;
	x = x + 1;
	printf("Enter the Fibonacci number to calculate.\n");
	printf("The number must be an integer between 2 and 46. (Enter 1 to quit): \n");
	printf("           Fibonacci        Fibonacci\n");
	printf(" N           number          quotient\n");
	printf("-------------------------------------\n");
	printf("%2d%14d                  N/A\n", x - 1, n1);
	printf("%2d%14d                  N/A\n", x, n2);
	printf("%2d%14d%21.16f\n", x + 1, n2, quotient);
	scanf("%d",&a);
	for (x = 3; x <= a; x++)
	{
		quotient = (double)fibona(x) / (double)fibona(x - 1);
		n3 = fibona(x);
		if(x!=a)
		printf("%2d%14d%21.16f\n", x, n3, quotient);
		else
		printf("%2d%14d%21.16f", x, n3, quotient);	
	}
	return 0;
}
double fibona(int x)
{
	if (x <= 2)
		return 1;
	else
		return(fibona(x - 2) + fibona(x - 1));
}