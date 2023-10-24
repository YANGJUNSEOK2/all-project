/*------------------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
Project:lab1
CourseNumber:cs230
Author:junseok.yang
Created:Spring 2019/3/22
------------------------------------------------------------------------*/

// mathexe.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdio>
#include "Math.h"


int main()
{
	using namespace std;

	float a = 123.090565f;
	float b = 3.12344213124f;


	printf("a == %f\t b == %f\n\n", a, b);
	printf("a + b == %f\n", add(a, b));
	printf("a - b == %f\n", subtract(a, b));
	printf("a * b == %f\n", multiply(a, b));
	printf("a / b == %f\n", divide(a, b));

	/*cout << "a == " << a << "\n";
	cout << "b == " << b << "\n\n";

	cout << "a+b == " << add(a, b) << "\n";
	cout << "a-b == " << subtract(a, b) << "\n";
	cout << "a*b == " << multiply(a, b) << "\n";
	cout << "a/b == " << divide(a, b) << "\n";*/


	return 0;
}
