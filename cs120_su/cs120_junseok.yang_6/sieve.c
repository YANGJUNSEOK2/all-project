/**
\file        sieve.c
\author      junseok.yang
\par         email: wnstjr4043@naver.com
\par         course: CS120
\par         lab: 6
\date        7/1/2018
\brief
This program calculates the bool ture and false, determine the prime number.
*/
#include<stdio.h>
#include "sieve.h"

void Sieve(bool array[], unsigned length)
{
	unsigned a, b;
	array[0]=false;
	array[1]=false;
	for 
		(a = 2; a < length; a++)
	{
		for (b = 2; b <= a; b++)
		{
			if (a%b == 0)
			{
				array[a] = false;
				break;
			}
		}
		if (a == b)
		{
			array[a] = true;
		}

	}
}
unsigned TwinPrimes(const bool primes[], unsigned length)
{
	unsigned x, count = 0; 
	for (x = 0; x < length; x++)
	{
		if (primes[x] == true && primes[x - 2] == true)
		{
			count++;
			printf("Twin Prime #%4u: %4u and %4u\n", count, x - 2, x);
		}
	}
	return count;
}
double BrunConstant(const bool primes[], unsigned length)
{
	unsigned x;
	double result = 0;
	for (x = 0; x < length; x++)
	{
		if (primes[x] == true && primes[x - 2] == true)
		{
			result += (1.0 / ((double)x - 2) + 1.0 / ((double)x));
		}
	}
	return result;
}