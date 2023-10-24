/**
    \file        Array.c
    \author      junseok.yang
    \par         email: wnstjryang@gmail.com
    \par         course: CS120
    \par         assignment: 2
    \date        10/28/2018
    \brief
        This program calculates reverse array addarray strangy calculate arrays.
*/

#include<stdio.h>
#include<stdlib.h>

/* Given an array, reverse the order of the elements in the array. Do NOT create another array in the function.*/                                   
void ReverseArray(int a[], unsigned size)
{
	const int endOffset = 1;
	unsigned x,tmp;

	for(x=0;x<size/2;x++)
	{

		tmp=a[size-x-endOffset];
		a[size-x-endOffset]=a[x];
		a[x]=tmp;

	}
}

/* Given three arrays, add the elements of the first two arrays and put the sum in the third array.*/ 
void AddArrays(const int a[], const int b[], int c[], unsigned size)
{	

	unsigned i;

	for (i = 0; i < size; i++)
	{

		c[i] = a[i] + b[i];

	}
}

/* Given an array and a multiplier, multiply each element by the multiplier.*/ 
void ScalarMultiply(int a[], unsigned size, int multiplier) 
{

	unsigned i;

	for (i = 0; i < size; i++)
	{

		a[i] *= multiplier;

	}
}

/* Given two arrays, determine the dot product. Return the value.*/
int DotProduct(const int a[], const int b[], unsigned size)
{

	unsigned i, productVal=0;

	for (i = 0; i < size; i++)
	{

		productVal += (a[i] * b[i]) ;

	}

	return productVal;

}

/* Given three arrays, determine the cross product of the first two and put the result into the third array. Assume that  the size of the arrays is 3*/
void CrossProduct(const int a[], const int b[], int c[])
{
	const int array0Num = 0;
	const int array1Num = 1;
	const int array2Num = 2;

	c[array0Num] = a[array1Num] * b[array2Num] - a[array2Num] * b[array1Num];
	c[array1Num] = -(a[array0Num] * b[array2Num] - a[array2Num] * b[array0Num]);
	c[array2Num] = a[array0Num] * b[array1Num] - a[array1Num] * b[array0Num];

}
