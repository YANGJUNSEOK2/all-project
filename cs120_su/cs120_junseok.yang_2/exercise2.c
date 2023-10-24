/**
\file        excercise2.c
\author      junseok.yang
\par         email: wnstjr4043@naver.com
\par         course: CS120
\par         lab: 2
\date        6/25/2018
\brief
This program calculates the reverse three numbers.
*/
#include<stdio.h>

int main(void)
{
	int input1;
	int input2;
	scanf("%d", &input1);
	input2 = input1 / 100;
	printf("Please enter a three digit, positive number:%2d%d%d\n", input1%10,(input1 % 100)/10, input2);
	return 0;
}