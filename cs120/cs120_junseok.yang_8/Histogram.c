/**
    \file        Histogram.c
    \author      junseok.yang
    \par         email: wnstjryang@gmail.com
    \par         course: CS120
    \par         lab: 8
    \date        11/22/2018
    \brief
        This program calculates sentance array numbers.
        Count the number of letters, spaces, and other characters.
*/

#include "Histogram.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>


int GetCounts(const char sentence[], int length, int letters[], int* spaces, int* other)
{

	int count = 0, spacesBox = 0, otherBox = 0;

	for (int j = 0; j < NUM_LETTERS; j++)
	{
		letters[j] = 0;
	}

	for (int i = 0; i < length; i++)
	{

		if (isalpha(sentence[i]))
		{
			letters[toupper(sentence[i]) - 'A']++;
			count++;
		}

		else if (isspace(sentence[i]))
		{
			spacesBox++;
		}

		else if (ispunct(sentence[i]))
		{
			otherBox++;
		}

		else if (isascii(sentence[i]))
		{
			otherBox++;
		}
		
		
	}

	*spaces = spacesBox;
	*other = otherBox;

	return count;
}


void PrintHistogram(const int letters[])
{
	
	char alphabet = 'A';

	for (int i = 0; i < NUM_LETTERS; i++)
	{

		printf("%c:", alphabet+i);

			for (int j = 0; j < letters[i]; j++)

			{
				printf("*");
			}

			printf("\n");
	}
}


void GetStatistics(const int letters[], double* average, char* maxLetter, int* maxLetterCount)
{

	double sum = 0;
	char letterChoice = 0;
	int letterCount = 0;

	for (int i = 0; i < NUM_LETTERS; i++)
	{

			sum += (i + 1) * letters[i];	

			for (int j = 0; j < letters[i]; j++)
			{

				if (letterCount < letters[i])

				{
					letterCount = letters[i];
					letterChoice = i + 'A';
				}
				
			}

	}

	*average = (sum / (double)NUM_LETTERS);
	*maxLetter = letterChoice;
	*maxLetterCount = letterCount;

}