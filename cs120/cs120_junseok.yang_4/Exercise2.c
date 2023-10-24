/**
	\file        Exercise2.c
	\author      junseok.yang
	\par         email: wnstjryang@gmail.com
	\par         course: CS120
	\par         lab: 4
	\date        10/11/2018
	\brief
		This program calculates the count number and infinite loop.
		It is the key to calculate number and usernumber together.
*/
#include<stdio.h>

int main(void)
{
	int userNumber = 1, smallest = 0, largest = 0, lagestcount = 1, smallestcount = 0, count_i = 0, count_j = 0, sum = 0, number = 1;
	double Average;
	//Initialize variables
	printf("Enter a series of positive or negative numbers\n");
	printf("Use 0 to end the list: \n");

	scanf("%d", &number);

	while (number != 0)
	{
		scanf("%d", &userNumber);

		if (userNumber == 0)
		{
			break;
		}
		//Stop at 0
		if (largest < userNumber&&number)
		{
			largest = userNumber;
			lagestcount = 1;
		}
		else if (largest == userNumber && number)
		{
			lagestcount++;
		}
		//Maximum value and count calculation
		if (smallest > userNumber&&number)
		{
			smallest = userNumber;
			smallestcount = 1;
		}
		else if (smallest == userNumber && number)
		{
			smallestcount++;
		}
		//Minimum value and count Compute
		if (userNumber != 0)
		{
			count_i = count_i + userNumber;
			sum++;
		}

		count_j = count_i + number;
		//Total number and total sum
		if (sum == 1)
		{
			printf("%d: %d\n", number, lagestcount);
			printf("%d: %d\n", userNumber, lagestcount);
		}
		else
			printf("%d: %d\n", userNumber, lagestcount);
	}

	if (number != 0)
	{
		Average = (double)count_j / (double)(sum + 1);
		//Calculate total number average
		printf("Numbers Entered:%12d\n", sum + 1);
		printf("Average is:%17.2f\n", Average);
		printf("Largest number:%13d\n", largest);

		if (largest == number)
			printf("Largest count:%14d\n", lagestcount + 1);
		else
			printf("Largest count:%14d\n", lagestcount);

		printf("Smallest number:%12d\n", smallest);

		if (smallest == number)
			printf("Smallest Count:%13d\n", smallestcount + 1);
		else
			printf("Smallest Count:%13d\n", smallestcount);
	}

	return 0;
}



