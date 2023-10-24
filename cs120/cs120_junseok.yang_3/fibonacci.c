/**
    \file        fibonacci.c
    \author      junseok.yang
    \par         email: wnstjryang@gmail.com
    \par         course: CS120
    \par         lab: 3
    \date        10/4/2018
    \brief
        This program calculates the fibonacci number and quotient.
        and The recursive function was too slow to change the code.
*/
#include<stdio.h>

int main(void)
{
	int putnum = 2, num1 = 0, num2 = 0;
	int in = 0, swap_a = 0, swap_b = 1, result;
	double quotient = 1;
	//Initialize the variable.
	putnum = putnum + 1;

	printf("Enter the Fibonacci number to calculate.\n");
	printf("The number must be an integer between 2 and 46. (Enter 1 to quit): \n");
	scanf("%d", &in);
	//1 ends because it does not belong to any range.
	if (in > 1 && in < 47)
	{
		printf("           Fibonacci        Fibonacci\n");
		printf(" N           number          quotient\n");
		printf("-------------------------------------\n");

		printf("%2d%14d                  N/A\n", putnum - 3, num1);
		printf("%2d%14d                  N/A\n", putnum - 2, num2 + 1);

		for (putnum = 2; putnum <= in; putnum++)
		{
			result = swap_a + swap_b;
			quotient = (double)result / (double)swap_b;
			//calculates quotient.
			printf("%2d%14d%21.16f\n", putnum, result, quotient);
			swap_a = swap_b;
			swap_b = result;
		}
	}
	//The Fibonacci function repeats with in the range.

	while (in < 1 || in >= 47)
	{
		printf("Enter the Fibonacci number to calculate.\n");
		printf("The number must be an integer between 2 and 46. (Enter 1 to quit): \n");
		scanf("%d", &in);
		//Repeat when not in the range of 2 ~ 46.

		if (in > 1 && in < 47)
		{
			printf("           Fibonacci        Fibonacci\n");
			printf(" N           number          quotient\n");
			printf("-------------------------------------\n");
			printf("%2d%14d                  N/A\n", putnum - 3, num1);
			printf("%2d%14d                  N/A\n", putnum - 2, num2 + 1);

			for (putnum = 2; putnum <= in; putnum++)
			{
				result = swap_a + swap_b;
				quotient = (double)result / (double)swap_b;
				printf("%2d%14d%21.16f\n", putnum, result, quotient);
				swap_a = swap_b;
				swap_b = result;
			}
			//If it is in the range of 2 ~ 46 again, Fibonacci value is output.
		}
	}
	return 0;
}