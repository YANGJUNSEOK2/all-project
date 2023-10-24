/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Main.cpp
Project: Assignment 1 - ListArray
Author: Kevin Wright
Creation date: 7/8/21
******************************************************************/
#include <iostream>
#include <chrono>
#include <random>
#include <set>
#include <unordered_set>

#include "ListArray.h"


template <typename T, int ArraySize>
void test_findAndOutput(const ListArray<T, ArraySize>& data, int target) {
	unsigned int index = data.find(target);
	if (index == data.size())
		std::cout << "Item: " << target << " not found" << std::endl;
	else
		std::cout << "Found " << target << " at index " << index << std::endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
template <int ArraySize>
void testLetters() {
	std::cout << "==================== PushFront Test:  Size " << ArraySize << " ====================\n";
	ListArray<char, ArraySize> data;
	for (char i = 'a'; i <= 'z'; i++) {
		data.push_back(i);
	}
	std::cout << data << std::endl;
	data.dumpStats();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
template <int ArraySize>
void testPushFront() {
	std::cout << "==================== PushFront Test:  Size " << ArraySize << " ====================\n";
	ListArray<int, ArraySize> data;
	for (int i = 15; i > 0; i--) {
		data.push_front(i);
	}
	std::cout << data << std::endl;
	data.dumpStats();
}

template <int ArraySize>
void testPopFront() {
	std::cout << "==================== PopFront Test:  Size " << ArraySize << " ====================\n";
	ListArray<int, ArraySize> data;
	for (int i = 15; i > 0; i--) {
		data.push_front(i);
	}
	std::cout << '\n' << data << std::endl;
	data.dumpStats();
	data.pop_front();
	data.pop_front();
	data.pop_front();
	std::cout << '\n' << data << std::endl;
	data.dumpStats();
	data.pop_front();
	data.pop_front();
	data.pop_front();
	std::cout << '\n' << data << std::endl;
	data.dumpStats();
	data.pop_front();
	data.pop_front();
	data.pop_front();
	std::cout << '\n' << data << std::endl;
	data.dumpStats();
	data.pop_front();
	data.pop_front();
	data.pop_front();
	std::cout << '\n' << data << std::endl;
	data.dumpStats();
	data.pop_front();
	data.pop_front();
	data.pop_front();
	std::cout << '\n' << data << std::endl;
	data.dumpStats();
	std::cout << std::endl;
	
	try {
		data.pop_front();
	}
	catch (const ListArrayException& e) {
		std::cout << e.what();
	}
}

void testPushFrontIsSorted1() {
	std::cout << "==================== PushFront Test Is Sorted 1" << " ====================\n";
	ListArray<int, 1> data;
	std::cout << "Push front 10" << std::endl;
	data.push_front(10);
	std::cout << data << std::endl;
	data.dumpStats();
	std::cout << std::endl;

	std::cout << "Push front 15" << std::endl;
	data.push_front(15);
	std::cout << data << std::endl;
	data.dumpStats();
	std::cout << std::endl;

	std::cout << "Push front 2" << std::endl;
	data.push_front(2);
	std::cout << data << std::endl;
	data.dumpStats();
}

void testPushFrontIsSorted2() {
	std::cout << "==================== PushFront Test Is Sorted 2" << " ====================\n";
	ListArray<int, 1> data;
	data.push_front(80);
	data.push_front(70);
	data.push_front(60);
	data.push_front(50);
	data.push_front(40);

	std::cout << data << std::endl;
	data.dumpStats();
	std::cout << std::endl;

	std::cout << "Push front 45" << std::endl;
	data.push_front(45);
	std::cout << data << std::endl;
	data.dumpStats();
	std::cout << std::endl;

	std::cout << "Push front 30,20,10" << std::endl;
	data.push_front(30);
	data.push_front(20);
	data.push_front(10);
	std::cout << data << std::endl;
	data.dumpStats();
}

void testPushFrontIsSorted3() {
	std::cout << "==================== PushFront Test Is Sorted 3" << " ====================\n";
	ListArray<int, 2> data;
	data.push_front(80);
	data.push_front(70);
	data.push_front(60);
	data.push_front(50);
	data.push_front(40);

	std::cout << data << std::endl;
	data.dumpStats();
	std::cout << std::endl;

	std::cout << "Push front 45" << std::endl;
	data.push_front(45);
	std::cout << data << std::endl;
	data.dumpStats();
	std::cout << std::endl;

	std::cout << "Push front 30,20,10" << std::endl;
	data.push_front(30);
	data.push_front(20);
	data.push_front(10);
	std::cout << data << std::endl;
	data.dumpStats();
}

void testPushFrontIsSorted4() {
	std::cout << "==================== PushFront Test Is Sorted 4" << " ====================\n";
	ListArray<int, 2> data;
	data.push_front(80);
	data.push_front(70);
	data.push_front(60);
	data.push_front(40);

	std::cout << data << std::endl;
	data.dumpStats();
	std::cout << std::endl;

	std::cout << "Push front 45" << std::endl;
	data.push_front(45);
	std::cout << data << std::endl;
	data.dumpStats();
	std::cout << std::endl;

	std::cout << "Push front 30,20,10" << std::endl;
	data.push_front(30);
	data.push_front(20);
	data.push_front(10);
	std::cout << data << std::endl;
	data.dumpStats();
}

void testPushFrontIsSorted5() {
	std::cout << "==================== PushFront Test Is Sorted 5" << " ====================\n";
	ListArray<int, 4> data;
	data.push_front(80);
	data.push_front(70);
	data.push_front(60);
	data.push_front(50);
	data.push_front(40);

	std::cout << data << std::endl;
	data.dumpStats();
	std::cout << std::endl;

	std::cout << "Push front 45" << std::endl;
	data.push_front(45);
	std::cout << data << std::endl;
	data.dumpStats();
	std::cout << std::endl;

	std::cout << "Push front 30,20,10" << std::endl;
	data.push_front(30);
	data.push_front(20);
	data.push_front(10);
	std::cout << data << std::endl;
	data.dumpStats();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
template <int ArraySize>
void testPushBack() {
	std::cout << "==================== PushBack Test:  Size " << ArraySize << " ====================\n";
	ListArray<int, ArraySize> data;
	for (int i = 1; i <= 15; i++) {
		data.push_back(i);
	}
	std::cout << data << std::endl;
	data.dumpStats();
}

template <int ArraySize>
void testPopBack() {
	std::cout << "==================== PopBack Test:  Size " << ArraySize << " ====================\n";
	ListArray<int, ArraySize> data;
	for (int i = 1; i <= 15; i++) {
		data.push_back(i);
	}
	std::cout << '\n' << data << std::endl;
	data.dumpStats();
	data.pop_back();
	data.pop_back();
	data.pop_back();
	std::cout << '\n' << data << std::endl;
	data.dumpStats();
	data.pop_back();
	data.pop_back();
	data.pop_back();
	std::cout << '\n' << data << std::endl;
	data.dumpStats();
	data.pop_back();
	data.pop_back();
	data.pop_back();
	std::cout << '\n' << data << std::endl;
	data.dumpStats();
	data.pop_back();
	data.pop_back();
	data.pop_back();
	std::cout << '\n' << data << std::endl;
	data.dumpStats();
	data.pop_back();
	data.pop_back();
	data.pop_back();
	std::cout << '\n' << data << std::endl;
	data.dumpStats();
	std::cout << std::endl;
	
	try {
		data.pop_back();
	}
	catch (const ListArrayException& e) {
		std::cout << e.what();
	}
}

void testPushBackIsSorted1() {
	std::cout << "==================== PushBack Test Is Sorted 1" << " ====================\n";
	ListArray<int, 1> data;
	std::cout << "Push back 10" << std::endl;
	data.push_back(10);
	std::cout << data << std::endl;
	data.dumpStats();
	std::cout << std::endl;

	std::cout << "Push back 0" << std::endl;
	data.push_back(5);
	std::cout << data << std::endl;
	data.dumpStats();
	std::cout << std::endl;

	std::cout << "Push back 7" << std::endl;
	data.push_back(7);
	std::cout << data << std::endl;
	data.dumpStats();
}

void testPushBackIsSorted2() {
	std::cout << "==================== PushBack Test Is Sorted 2" << " ====================\n";
	ListArray<int, 1> data;
	data.push_back(10);
	data.push_back(20);
	data.push_back(30);
	data.push_back(40);
	data.push_back(50);

	std::cout << data << std::endl;
	data.dumpStats();
	std::cout << std::endl;

	std::cout << "Push back 45" << std::endl;
	data.push_back(45);
	std::cout << data << std::endl;
	data.dumpStats();
	std::cout << std::endl;

	std::cout << "Push back 60,70,80" << std::endl;
	data.push_back(60);
	data.push_back(70);
	data.push_back(80);
	std::cout << data << std::endl;
	data.dumpStats();
}

void testPushBackIsSorted3() {
	std::cout << "==================== PushBack Test Is Sorted 3" << " ====================\n";
	ListArray<int, 2> data;
	data.push_back(10);
	data.push_back(20);
	data.push_back(30);
	data.push_back(40);
	data.push_back(50);

	std::cout << data << std::endl;
	data.dumpStats();
	std::cout << std::endl;

	std::cout << "Push back 45" << std::endl;
	data.push_back(45);
	std::cout << data << std::endl;
	data.dumpStats();
	std::cout << std::endl;

	std::cout << "Push back 60,70,80" << std::endl;
	data.push_back(60);
	data.push_back(70);
	data.push_back(80);
	std::cout << data << std::endl;
	data.dumpStats();
}

void testPushBackIsSorted4() {
	std::cout << "==================== PushBack Test Is Sorted 4" << " ====================\n";
	ListArray<int, 2> data;
	data.push_back(20);
	data.push_back(30);
	data.push_back(40);
	data.push_back(50);

	std::cout << data << std::endl;
	data.dumpStats();
	std::cout << std::endl;

	std::cout << "Push back 45" << std::endl;
	data.push_back(45);
	std::cout << data << std::endl;
	data.dumpStats();
	std::cout << std::endl;

	std::cout << "Push back 60,70,80" << std::endl;
	data.push_back(60);
	data.push_back(70);
	data.push_back(80);
	std::cout << data << std::endl;
	data.dumpStats();
}

void testPushBackIsSorted5() {
	std::cout << "==================== PushBack Test Is Sorted 5" << " ====================\n";
	ListArray<int, 4> data;
	data.push_back(10);
	data.push_back(20);
	data.push_back(30);
	data.push_back(40);
	data.push_back(50);

	std::cout << data << std::endl;
	data.dumpStats();
	std::cout << std::endl;

	std::cout << "Push back 45" << std::endl;
	data.push_back(45);
	std::cout << data << std::endl;
	data.dumpStats();
	std::cout << std::endl;

	std::cout << "Push back 60,70,80" << std::endl;
	data.push_back(60);
	data.push_back(70);
	data.push_back(80);
	std::cout << data << std::endl;
	data.dumpStats();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
template <int ArraySize>
void testInsert() {
	std::cout << "==================== Insert Test:  Size " << ArraySize << " ====================\n";
	ListArray<int, ArraySize> data;

	std::mt19937 generator(0);
	std::uniform_int_distribution<> dist(10, 99);
	std::set<int> found;

	int size = 15;
	for (int i = 0; i < size; ) {
		int rand = dist(generator);
		if (found.find(rand) == found.end()) {
			found.insert(rand);
			data.insert(rand);
			std::cout << data << "*************************" << std::endl;
			i++;
		}
	}

	data.dumpStats();
}


///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
template <int ArraySize>
void testLinearSearch() {
	std::cout << "==================== Linear Search Test:  Size " << ArraySize << " ====================\n";
	ListArray<int, ArraySize> data;

	std::mt19937 generator(0);
	std::uniform_int_distribution<> dist(10, 99);
	std::set<int> found;
	found.insert(50);
	found.insert(75);
	found.insert(33);
	int size = 15;
	for (int i = 0; i < size; ) {
		int rand = dist(generator);
		if (found.find(rand) == found.end()) {
			found.insert(rand);
			data.push_back(rand);
			i++;
		}
	}

	std::cout << data << std::endl;

	for (const int& i : found) {
		test_findAndOutput(data, i);	// except for 50, 75 & 33 these should all be found
	}
	// these should not be found
	test_findAndOutput(data, 0);
	test_findAndOutput(data, 1);
	test_findAndOutput(data, -1);
	test_findAndOutput(data, 9);
	test_findAndOutput(data, 100);

	data.dumpStats();
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
template <int ArraySize>
void testBinarySearch() {
	std::cout << "==================== Binary Search Test:  Size " << ArraySize << " ====================\n";
	ListArray<int, ArraySize> data;

	std::mt19937 generator(0);
	std::uniform_int_distribution<> dist(10, 99);
	std::set<int> found;
	found.insert(50);
	found.insert(75);
	found.insert(33);
	int size = 15;
	for (int i = 0; i < size; ) {
		int rand = dist(generator);
		if (found.find(rand) == found.end()) {
			found.insert(rand);
			data.insert(rand);
			i++;
		}
	}

	std::cout << data << std::endl;

	for (const int& i : found) {
		test_findAndOutput(data, i);	// except for 50, 75 & 33 these should all be found
	}
	// these should not be found
	test_findAndOutput(data, 0);
	test_findAndOutput(data, 1);
	test_findAndOutput(data, -1);
	test_findAndOutput(data, 9);
	test_findAndOutput(data, 100);

	data.dumpStats();
}

template <int ArraySize, int NumItems, int NumFinds>
void TimedTest() {
	std::cout << "==================== Timed Test:  Size " << ArraySize << "  Items " << NumItems << "  Finds " << NumFinds << " ====================\n";

	std::mt19937 generator(0);
	std::uniform_int_distribution<> dist(0, NumItems * 1000);
	std::unordered_set<unsigned int> found;
	for (int i = 0; i < NumItems; ) {
		int rand = dist(generator);
		if (found.find(rand) == found.end()) {
			found.insert(rand);
			i++;
		}
	}

	ListArray<unsigned int, ArraySize> data;
	auto startAddData = std::chrono::high_resolution_clock::now();
	for (unsigned int i : found) {
		data.insert(i);
	}
	auto endAddData = std::chrono::high_resolution_clock::now();

	int count = 0;
	for (int i = 0; i < NumFinds; i++) {
		if (data.find(dist(generator)) != data.size()) {
			count++;
		}
	}
	auto endFindData = std::chrono::high_resolution_clock::now();

	long long addTime = std::chrono::duration_cast<std::chrono::milliseconds>(endAddData - startAddData).count();
	long long findTime = std::chrono::duration_cast<std::chrono::milliseconds>(endFindData - endAddData).count();
	std::cout << "Adding data took: " << addTime << " ms" << std::endl;
	std::cout << "Find data took: " << findTime << " ms" << std::endl;
	std::cout << "Find took an average of: " << findTime / (float)NumFinds << " ms" << std::endl;
}


int main() {
	int test_num = -1;
#ifndef _MSC_VER
	std::cin >> test_num;
#endif

	typedef void(*Test)(void);
	Test tests[] = {
					testPushBack<16>,					testPushBack<1>,					testPushBack<2>,				    testPushBack<5>,			        testPushBack<12>,			    //  1 - 5, push_back
					testPushBackIsSorted1,				testPushBackIsSorted2,				testPushBackIsSorted3,			    testPushBackIsSorted4,		        testPushBackIsSorted5,		    //  6 - 10, push_back sort test
					testPopBack<16>,					testPopBack<1>,						testPopBack<3>,					    testPopBack<7>,				        testPopBack<12>,				// 11 - 15, pop_back
					testPushFront<16>,					testPushFront<1>,					testPushFront<3>,				    testPushFront<7>,			        testPushFront<12>,			    // 16 - 20, push_front
					testPushFrontIsSorted1,				testPushFrontIsSorted2,				testPushFrontIsSorted3,			    testPushFrontIsSorted4,		        testPushFrontIsSorted5,		    // 21 - 25, push_front sort test
					testPopFront<16>,					testPopFront<1>,					testPopFront<3>,				    testPopFront<7>,			        testPopFront<12>,			    // 26 - 30, pop_front sort test
					testInsert<16>,						testInsert<1>,						testInsert<3>,					    testInsert<7>,				        testInsert<12>,				    // 31 - 35, insert
					testLinearSearch<16>,				testLinearSearch<1>,				testLinearSearch<3>,			    testLinearSearch<7>,		        testLinearSearch<12>,		    // 36 - 40, Linear Search
					testBinarySearch<16>,				testBinarySearch<1>,				testBinarySearch<3>,			    testBinarySearch<7>,		        testBinarySearch<12>,		    // 41 - 45, Binary Search
					testLetters<16>,					testLetters<1>,						testLetters<3>,					    testLetters<7>,				        testLetters<12>,				// 46 - 50, Testing the template
					TimedTest<64, 100000, 100000>,      TimedTest<128, 100000, 100000>,     TimedTest<256, 100000, 100000>,     TimedTest<512, 100000, 100000>,     TimedTest<1024, 100000, 100000>, // 55 - 60, Timed Tests     
	};
	int numTests = static_cast<int>(sizeof(tests) / sizeof(*tests));

	if (test_num >= 0 && test_num <= numTests) {
		tests[test_num - 1]();
	}
	else {
		for (int i = 0; i < numTests; i++) {
			tests[i]();
			std::cout << std::endl << std::endl;
		}
	}

#ifdef _MSC_VER
	system("pause");
#endif
	return 0;
}