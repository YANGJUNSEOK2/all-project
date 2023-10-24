/**
	\file        Exercise1.c
	\author      junseok.yang
	\par         email: wnstjryang@gmail.com
	\par         course: CS120
	\par         lab: 4
	\date        10/11/2018
	\brief
		This program calculates the factorial number and looping.
*/
#include<stdio.h>

int main(void)
{
	int num = -1, loop_i, loop_j, result = 1;
	//Initialize variables. The initial value of num must be in range.
	while (num < 0 || num > 12)
	{
		printf("Enter an integer between 0 and 12: \n");
		scanf("%d", &num);
	}
	//There is a range from 0 to 12.
	printf("%d factorial (%d!) is: \n\n", num, num);

	for (loop_i = 0; loop_i <= num; loop_i++)
	{
		for (loop_j = 0; loop_j <= loop_i; loop_j++)
		{
			printf("%d", num - loop_j);

			if (loop_i == loop_j)
				continue;

			else
				printf(" X ");
		}
		printf("!\n");
	}
	//Use two loops to make a triangle.
	for (loop_j = num; loop_j >= 1; loop_j--)
	{
		printf("%d", loop_j);
		printf(" X ");
	}
	printf("%d", result);
	printf("\n");
	//Make the next line
	for (loop_i = 0; loop_i < num; loop_i++)
	{
		result *= loop_i + 1;
		//It is a Factorial calculation.
		for (loop_j = num; loop_j >= loop_i + 2; loop_j--)
		{
			printf("%d", loop_j);
			printf(" X ");
		}

		printf("%d", result);
		printf("\n");
	}
	//Complete the final triangle
	return 0;
}