/**
\file        excercise1.c
\author      junseok.yang
\par         email: wnstjr4043@naver.com
\par         course: CS120
\par         lab: 2
\date        6/25/2018
\brief
This program calculates the reverse numbers.
*/
#include<stdio.h>

int main(void)
{
	int input1;
	int input2;
	scanf("%d", &input1);
	input2 = input1 / 10;
	printf("Please enter a two digit, positive number:%2d%d\n", input1 % 10, input2);
	return 0;
}