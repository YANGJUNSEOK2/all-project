/*
    \file        Jumble.c
    \author      junseok.yang
    \par         email: wnstjryang@gmail.com
    \par         course: CS120
    \par         assignment: 3
    \date        12/4/2018
    \brief       making code to encode a string using a password.
    				Encoding process in memory that lasts until 
    					the original length of the string ends.
*/
#include "Jumble.h"


int MyStrlen(const unsigned char* string)
{

  int cnt = 0;
 
  for(;*string != 0;++string)
  {

  	cnt++;

  }

  return cnt;
}

void Jumble(unsigned char* string, const unsigned char* password, Method method, int passes)
{
	
	int i=0;
	int char_count = MyStrlen(string);
	int lengh = MyStrlen(password);
	
	if (method == CM_ENCODE)
	{

		while(passes > 0)
		{

			for(i=0;i < char_count;i++)
			{

				*(string + i) += *(password + (i % lengh));

			}

			passes --;

		}
	}

	else if(method == CM_DECODE)
	{

		while(passes > 0)
		{

			for(i=0; i < char_count;i++)
			{

				*(string + i) -= *(password + (i % lengh));

			}

			passes --;

		}
	}
}