/**
\file        numbers.c
\author      junseok.yang
\par         email: wnstjr4043@naver.com
\par         course: CS120
\par         lab: 1
\date        6/25/2018
\brief
	This program calculates the Triangle function.
*/
#include<stdio.h>
#include<math.h>
int main(void)
{
	float input1;
	float input2;
	float input3;
	scanf("%f%f%f", &input1, &input2, &input3);
	printf("Enter 3 numbers between 0 and 9.999: \n");
	printf("Number      sin      cos      tan      atan\n");
	printf("-------------------------------------------\n");
	printf("%0.5f%9.3f%9.3f%9.3f%9.3f\n",input1, sin(input1), cos(input1), tan(input1), atan(input1));
	printf("%0.5f%9.3f%9.3f%9.3f%9.3f\n",input2, sin(input2), cos(input2), tan(input2), atan(input2));
	printf("%0.5f%9.3f%9.3f%9.3f%9.3f",input3, sin(input3), cos(input3), tan(input3), atan(input3));
	return 0;
}
