/**
	\file        sieve.c
	\author      junseok.yang
	\par         email: wnstjryang@gmail.com
	\par         course: CS120
	\par         lab: 6
	\date        10/16/2018
	\brief
	   This program calculates the bool ture and false, determine the prime number.
*/


#include<stdio.h>
#include "sieve.h"

#define NUMERATOR 1.0

/*******************************************************************************
   Function: Sieve

Description: Use two roop statements to express the prime number as 0,1.

     Inputs: array size- ex)101, 1001, 10001

    Outputs: prime numbers and prime numbers count in array count.
*******************************************************************************/

void Sieve(bool array[], unsigned length)
{
	unsigned iterate_i = 2, iterate_j;

	array[0] = 0;
	array[1] = 0;

	while (iterate_i < length)
	{

		for (iterate_j = 2; iterate_j <= iterate_i; iterate_j++)
		{

			if (iterate_i%iterate_j == 0)
			{
				array[iterate_i] = 0;
				break;
			}
		}

		if (iterate_i == iterate_j)
			array[iterate_i] = 1;

		iterate_i++;

	}
}

/*******************************************************************************
   Function: TwinPrimes

Description: The prime number expressed as a function of bull is expressed 
             in a twin prime.

     Inputs: prime number expressed 0,1. 

    Outputs: Twin prime and twin prime count.
*******************************************************************************/

unsigned TwinPrimes(const bool primes[], unsigned length)

{
	unsigned twin_prime = 0, count = 0;

	while (twin_prime < length)
	{

		if (primes[twin_prime] == 1 && primes[twin_prime - 2] == 1)
		{

			count++;

			printf("Twin Prime #%4u: %4u and %4u\n", count, twin_prime - 2, twin_prime);

		}

		twin_prime++;

	}

	return count;

}

/*******************************************************************************
   Function: BrunConstant

Description: Constant with 205 Twin Primes is 1.616893557432.

     Inputs: prime number expressed 0,1. 

    Outputs: The reverse number sum of 205 Twin Primes. 
*******************************************************************************/

double BrunConstant(const bool primes[], unsigned length)

{

	unsigned num;
	double bruns = 0;

	for (num = 0; num < length; num++)

	{
		if (primes[num] == 1 && primes[num - 2] == 1)
		{
			bruns += (double)(NUMERATOR / (num - 2) + NUMERATOR / (num));
		}

	}

	return bruns;

}