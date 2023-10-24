/**
    \file        Array.c
    \author      junseok.yang
    \par         email: wnstjr4043@naver.com
    \par         course: CS120
    \par         assignment: 2
    \date        7/08/2018
    \brief
        This program calculates reverse array addarray strangy calculate arrays.
*/
#include<stdio.h>
#include <stdlib.h>
void ReverseArray(int a[], unsigned size)
{
	unsigned x, tmp;
	
	for (x = 0; x < size / 2; x++)
	{
		tmp = a[x];
		a[x] = a[size - x-1];
		a[size - x - 1] = tmp;
	}
}
void AddArrays(const int a[], const int b[], int c[], unsigned size)
{	
	unsigned i;
	for (i = 0; i < size; i++)
	{
		c[i] = a[i] + b[i];
	}
}
void ScalarMultiply(int a[], unsigned size, int multiplier)
{
	unsigned i;
	for (i = 0; i < size; i++)
	{
		a[i] *= multiplier;
	}
}
int DotProduct(const int a[], const int b[], unsigned size)
{
	unsigned i, n=0;
	for (i = 0; i < size; i++)
	{
		n += (a[i] * b[i]) ;
	}
	return n;
}
void CrossProduct(const int a[], const int b[], int c[])
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = -(a[0] * b[2] - a[2] * b[0]);
	c[2] = a[0] * b[1] - a[1] * b[0];
}
