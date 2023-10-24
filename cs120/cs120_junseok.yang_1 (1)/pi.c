/**
	\file        pi.c
	\author      junseok.yang
	\par         email: wnstjryang@gmail.com
	\par         course: CS120
	\par         assignment: 1
	\date        10/11/2018
	\brief
	   This program calculates infinite width divide and sum.
*/
#include<stdio.h>
#include<math.h>

#define NUMERATOR 1
#define MIDPOINT 2
#define TIMES 2
#define MAKE_ODD 1
#define MAKE_LIBNIZ 4


/*******************************************************************************
   Function: CirclePI

Description: Calculates PI by summing the area of rectangles that fit into the
			 quarter of a cirlcle with radius 2.

	 Inputs: rectangles - The number of rectangles to fit into the quarter
			 circle.

	Outputs: The aproximate value of PI.
*******************************************************************************/
double CirclePI(int rectangles);

double CirclePI(int rectangles)
{
	double area = 0.0;
	double radius = 2.0;
	double width = radius / (double)rectangles;
	double mid = 0;
	double height = 0.0;


	for (int i = 0; i < rectangles; i++)
	{
		mid = (width / MIDPOINT) + width * (double)i;
		height = sqrt(radius*radius - mid * mid);
		area += height * width;
	}

	return area;

}

/*******************************************************************************
   Function: LeibnizPI

Description: Calculates pi using the libniz method pi/4 = 1 - 1/3 + 1/5 - 1/7...
			 This only approximates 1/4 pi, so we must multiply by 4 before
			 returning.

	 Inputs: iterations - The number of terms to use in the series.

	Outputs: The aproximated value of pi.
*******************************************************************************/
double LeibnizPI(int iterations);

double LeibnizPI(int iterations)
{
	double num, sum = 0.0;
	int i = 0;

	while (i < iterations)
	{
		num = TIMES * i + MAKE_ODD;

		if (i % 2 == 0)   //even num
			sum += NUMERATOR / num;
		else              //odd num
			sum += -(NUMERATOR / num);

		i++;
	}

	return sum * MAKE_LIBNIZ;
}