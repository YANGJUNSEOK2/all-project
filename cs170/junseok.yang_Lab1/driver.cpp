/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: driver.cpp
Author: junseok.yang
Creation Date:SPRING/4/25/2019
   Lab1
******************************************************************************/
#include <iostream> 
#include <cstdlib>

namespace Lab1 {
	void test1()
	{
		std::cout << "This is test 1" << std::endl;
	}

	void test2()
	{
		std::cout << "This is another test, test 2" << std::endl;
	}

	void test3()
	{
		std::cout << "Again this is a test, test 3" << std::endl;
	}

	void test4()
	{
		std::cout << "Another test (4)" << std::endl;
	}

	void test5()
	{
		std::cout << "Final Test, #5" << std::endl;
	}
}

int main(int argc, char *argv[])
{
	typedef void(*Test)(void); 
	Test tests[] = {Lab1::test1,
					Lab1::test2,
					Lab1::test3,
					Lab1::test4,
					Lab1::test5 };
	int numTests = static_cast<int>(sizeof(tests) / sizeof(*tests)); 

	int *ptr = new int[1];
	if (ptr != nullptr)
	{
		int callTest = 0;
		if (argc > 1)
		{
			callTest = std::atoi(argv[1]);
			if (callTest >= numTests || callTest < 0)
			{
				callTest = 0;
			}
		}
		tests[callTest]();
	}
	delete[] ptr;
	}