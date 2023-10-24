/**
\file        excercise3.c
\author      junseok.yang
\par         email: wnstjr4043@naver.com
\par         course: CS120
\par         lab: 2
\date        6/25/2018
\brief
This program calculates the plus divide squre cube numbers.
*/
#include<stdio.h>
#include<math.h>

int main(void)
{
	float input1, input2, input3, input4, input5;
	printf("Please enter a floating point number: ");
	scanf("%f", &input1);
	input2 = input1 + 10;
	input3 = input1 * input1;
	input4 = input1 * input1*input1;
	input5 = input1 / 2;
	printf("%f\n", input2);
	printf("%f\n", input3);
	printf("%f\n", input4);
	printf("%f\n", input5);
	return 0;
}