/**
    \file        pi.c
    \author      junseok.yang
    \par         email: wnstjr4043@naver.com
    \par         course: CS120
    \par         assignment: 1
    \date        7/11/2018
    \brief
        This program calculates infinite width divide and sum.
*/
#include<stdio.h>
#include<math.h>

double CirclePI(int rectangles)
{
	double x = 2.0;
	double area = 0.0;
	double radius = 2.0;
	double width = radius / (double)rectangles;
	double midpoint = 0;
	double height = 0.0;
	int i;
	for (i = 0; i < rectangles; i++)
	{
			midpoint = (width/2) + width*(double)i;
		height = sqrt(radius*radius - midpoint * midpoint);
		area += height * width;
	}
	return area;
}
double LeibnizPI(int iterations)
{
	double denominator;
	double sum = 0.0;
	int i;
	for (i = 0; i < iterations; i++)
	{
		denominator = 2 * i + 1;
		if (i % 2 == 0)
			sum += 1 / denominator;
		else
			sum += -(1 / denominator);
	}
	return sum*4;
}