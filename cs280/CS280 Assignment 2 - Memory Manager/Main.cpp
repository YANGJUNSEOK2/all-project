/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Main.cpp
Project: Assignment 2 - Memory Manager
Author: Kevin Wright
Creation date: 2/2/21
******************************************************************/
#include <iostream>

#include "MemManager.h"

extern MemManager gMemManager;


void Test1() {
	std::cout << "Test initial setup" << std::endl;
	gMemManager.WriteMemoryInfo();
}

void Test2() {
	std::cout << "Test alloc, free, alloc, free" << std::endl;
	gMemManager.WriteMemoryInfo();
	int *int1 = new int(-1);
	gMemManager.WriteMemoryInfo();
	delete int1;
	gMemManager.WriteMemoryInfo();
	int1 = new int(0);
	gMemManager.WriteMemoryInfo();
	delete int1;
	gMemManager.WriteMemoryInfo();
}

void Test3( ) {
	std::cout << "Test multiple allocations (including array) and merge next" << std::endl;
	gMemManager.WriteMemoryInfo();
	int *int1 = new int(-1);
	gMemManager.WriteMemoryInfo();
	int *int2 = new int[2]{-1, -1};
	gMemManager.WriteMemoryInfo();
	int *int3 = new int[4]{-1, -1, -1, -1};
	gMemManager.WriteMemoryInfo();

	delete[] int3;
	gMemManager.WriteMemoryInfo();
	delete[] int2;
	gMemManager.WriteMemoryInfo();
	delete int1;
	gMemManager.WriteMemoryInfo();
}

void Test4( ) {
	std::cout << "Test multiple allocations (including array) and merge prev" << std::endl;
	int *int1 = new int(-1);
	int *int2 = new int[2]{-1, -1};
	int *int3 = new int[4]{-1, -1, -1, -1};
	gMemManager.WriteMemoryInfo();

	delete int1;
	gMemManager.WriteMemoryInfo();
	delete[] int2;
	gMemManager.WriteMemoryInfo();
	delete[] int3;
	gMemManager.WriteMemoryInfo();
}

void Test5( ) {
	std::cout << "Test multiple allocations (including array) and merge again" << std::endl;
	int *int1 = new int(-1);
	int *int2 = new int[2]{-1, -1};
	int *int3 = new int[4]{-1, -1, -1, -1};
	gMemManager.WriteMemoryInfo();

	delete[] int2;
	delete int1;
	delete[] int3;
	gMemManager.WriteMemoryInfo();
}

void Test6( ) {
	std::cout << "Test multiple allocations (including array) and merge again 2" << std::endl;
	int *int1 = new int(-1);
	int *int2 = new int[2]{-1, -1};
	int *int3 = new int[4]{-1, -1, -1, -1};
	gMemManager.WriteMemoryInfo();

	delete int1;
	delete[] int3;
	delete[] int2;
	gMemManager.WriteMemoryInfo();
}


void Test7() {
	std::cout << "Test repeated allocation/merge" << std::endl;

	int *int1 = new int(-1);
	int *int2 = new int[2]{ -1, -1 };
	int *int3 = new int[4]{ -1, -1, -1, -1 };
	delete[] int2;
	delete[] int3;
	delete int1;
	gMemManager.WriteMemoryInfo();

	int1 = new int(-1);
	int2 = new int[2]{ -1, -1 };
	int3 = new int[4]{ -1, -1, -1, -1 };
	delete[] int2;
	delete int1;
	delete[] int3;
	gMemManager.WriteMemoryInfo();

	int1 = new int(-1);
	int2 = new int[2]{ -1, -1 };
	int3 = new int[4]{ -1, -1, -1, -1 };

	delete int1;
	delete[] int3;
	delete[] int2;
	gMemManager.WriteMemoryInfo();
}

void Test8() {
	std::cout << "Test making 2 nodes out of a block of free data surrounded by used data.  If this fails double check all of your pPrev nodes, one maybe off" << std::endl;
	int *int1 = new int(-1);
	int *int2 = new int[2]{ -1, -1 };
	int *int3 = new int[4]{ -1, -1, -1, -1 };
	int* int4 = new int[4]{ -1, -1, -1, -1 };

	delete[] int2;
	delete[] int3;
	gMemManager.WriteMemoryInfo();
	int3 = new int[4]{ -1, -1, -1, -1 };
	gMemManager.WriteMemoryInfo();

	delete int1;
	gMemManager.WriteMemoryInfo();
	delete[] int4;
	gMemManager.WriteMemoryInfo();
	delete[] int3;
	gMemManager.WriteMemoryInfo();
}

void Test9( ) {
	std::cout << "Test basic allocation/free with 1 char" << std::endl;
	char *c = new char;
	gMemManager.WriteMemoryInfo();
	delete c;
	gMemManager.WriteMemoryInfo();
}

void Test10() {
	std::cout << "Test basic allocation/free with struct" << std::endl;
	struct testStruct{
		int x;
		int y;
	};
	testStruct* structPtr = new testStruct;
	gMemManager.WriteMemoryInfo();
	delete structPtr;
	gMemManager.WriteMemoryInfo();
}

void Test11() {
	std::cout << "Test alloc of very large size (small amount left over)" << std::endl;
	const int size = (sizeof(void*) == 8) ? 180 : 200;
	char *c1 = new char[size];
	gMemManager.WriteMemoryInfo();
	delete[] c1;
	gMemManager.WriteMemoryInfo();
}

void Test12() {
	const int maxNodes = (sizeof(void*) == 8) ? 12 : 18;
	std::cout << "Test " << maxNodes <<" allocations" << std::endl;
	int *intArray[maxNodes+1];
	for (int i = 0; i < maxNodes; i++) {
		intArray[i] = new int(-1);
	}
	gMemManager.WriteMemoryInfo();
	for (int i = 0; i < maxNodes; i++) {
		delete intArray[i];
	}
	gMemManager.WriteMemoryInfo();
}

void Test13( ) {
	std::cout << "Test too large of allocation (This should throw an exception)" << std::endl;
	try {
		const int size = MemManager::PageSize;
		char *c1 = new char[size];
		std::cout << "Allocation should have thrown an exception" << std::endl;
		delete[] c1;
	} catch (MemoryException &ex) {
		std::cout << ex.what() << std::endl;
	}
	gMemManager.WriteMemoryInfo();
}

void Test14() {
	std::cout << "Test 2 allocs of max size size" << std::endl;
	const int size = (sizeof(void*) == 8) ? 224 : 228;
	char *c1 = new char[size];
	char *c2 = new char[size];
	gMemManager.WriteMemoryInfo();
	delete[] c1;
	delete[] c2;
	gMemManager.WriteMemoryInfo();
}

void Test15() {
	std::cout << "Test 3 allocs which would need a 3rd page to work (This should throw an exception if you only have 2 pages)" << std::endl;
	std::cout << "Hint:  You might want to change your number of pages to 3 to make sure your code isn't special cased to only work with 2 pages" << std::endl;

	const int size = (sizeof(void*) == 8) ? 224 : 228;
	char* c1 = new char[size];
	char* c2 = new char[size];
	gMemManager.WriteMemoryInfo();
	try {
		char* c3 = new char[size];
		delete[] c3;
	} catch (MemoryException & ex) {
		std::cout << ex.what() << std::endl;
	}
	delete[] c1;
	delete[] c2;
	gMemManager.WriteMemoryInfo();
}

void Test16( ) {
	std::cout << "Test write out of array bounds" << std::endl;
	int *array = new int[4];
	array[0] = -1;
	array[1] = -1;
	array[2] = -1;
	array[3] = -1;
	array[4] = -1;
	delete[] array;
}

void Test17( ) {
	std::cout << "Test unfreed memory" << std::endl;
	int *int1 = new int;
	int *int2 = new int[2];
	int *int3 = new int[4];

	int1[0] = -1;
	int2[0] = -1;
	int2[1] = -1;
	int3[0] = -1;
	int3[1] = -1;
	int3[2] = -1;
	int3[3] = -1;
	
	gMemManager.WriteMemoryInfo();
}

int main() {
	int test_num = -1;

	typedef void(*Test)(void);
	Test Tests[] = {
		Test1,	Test2,	Test3,	Test4,	Test5,	Test6,	
		Test7,	Test8,	Test9,	Test10,	Test11,	Test12,
		Test13, Test14,	Test15,	Test16, Test17
	};
	int numTests = static_cast<int>(sizeof(Tests) / sizeof(*Tests));
#ifndef _MSC_VER
	std::cin >> test_num;
#endif
	
	if(test_num > 0 && test_num <= numTests) {
		Tests[test_num-1]( );
	} else {
		for(int i = 0; i < numTests; i++) {
			Tests[i]( );
#ifdef _MSC_VER
			std::cout << std::endl << std::endl;
#endif
		}
	}

 }