/**
    \file        numbers.c
    \author      junseok.yang
    \par         email: wnstjr4043@naver.com
    \par         course: CS120
    \par         lab: 1
    \date        10/4/2018
    \brief
        this program is triangle math calculate program.
*/
#include<stdio.h>
#include<math.h>

int main(void)
{
	float input1, input2, input3;
	
	scanf("%f%f%f",&input1,&input2,&input3);
	
	printf("Enter 3 numbers between 0 and 9.999: \n");
	printf("Number      sin      cos      tan      atan\n");
	printf("-------------------------------------------\n");

	printf("%6.5f%9.3f%9.3f%9.3f%9.3f\n",input1, sin(input1), cos(input1), tan(input1), atan(input1));
	printf("%6.5f%9.3f%9.3f%9.3f%9.3f\n",input2, sin(input2), cos(input2), tan(input2), atan(input2));
	printf("%6.5f%9.3f%9.3f%9.3f%9.3f\n",input3, sin(input3), cos(input3), tan(input3), atan(input3));
	
	return 0;
}