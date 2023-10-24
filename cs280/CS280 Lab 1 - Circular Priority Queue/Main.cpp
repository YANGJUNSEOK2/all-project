/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Main.cpp
Project: Lab 1 - CirclePriQueue
Author: Kevin Wright
Creation date: 1/27/21
******************************************************************/

#include <iostream>

#include "CircularPriQueue.h"


void Test1() {
	std::cout << "============ Push/Pop ===============" << std::endl;
	CircularPriQueue<int, 10> queue;
	
	queue.Push(1);
	int rtrnResult = queue.Pop();
	std::cout << "Pop returned " << rtrnResult << std::endl;
	
	queue.Push(10);
	rtrnResult = queue.Pop();
	std::cout << "Pop returned " << rtrnResult << std::endl;
	
	queue.Push(-1);
	rtrnResult = queue.Pop();
	std::cout << "Pop returned " << rtrnResult << std::endl;
}


void Test2() {
	std::cout << "============ Push/Pop chars ===============" << std::endl;
	CircularPriQueue<char, 10> queue;
	
	queue.Push('a');
	char rtrnResult = queue.Pop();
	std::cout << "Pop returned " << rtrnResult << std::endl;
	
	queue.Push('b');
	rtrnResult = queue.Pop();
	std::cout << "Pop returned " << rtrnResult << std::endl;
	
	queue.Push('c');
	rtrnResult = queue.Pop();
	std::cout << "Pop returned " << rtrnResult << std::endl;
}


void Test3() {
	std::cout << "============ Push/Pop Strings ===============" << std::endl;
	CircularPriQueue<std::string, 10> queue;
	
	queue.Push("CS280 is");
	std::string rtrnResult = queue.Pop();
	std::cout << "Pop returned " << rtrnResult << std::endl;
	
	queue.Push("a fantastic");
	rtrnResult = queue.Pop();
	std::cout << "Pop returned " << rtrnResult << std::endl;
	
	queue.Push("class!");
	rtrnResult = queue.Pop();
	std::cout << "Pop returned " << rtrnResult << std::endl;
}


void Test4() {
	std::cout << "============ Pop empty queue ===============" << std::endl;
	CircularPriQueue<int, 10> queue;
	
	try {
		queue.Pop();
	} catch (CircularPriQueueException& exception) {
		std::cout << exception.what() << std::endl;
	}
}

void Test5() {
	std::cout << "============ Pop empty queue 2 ===============" << std::endl;
	CircularPriQueue<int, 10> queue;

	queue.Push(1);
	queue.Push(2);
	queue.Pop();
	queue.Pop();
	
	try {
		queue.Pop();
	} catch (CircularPriQueueException& exception) {
		std::cout << exception.what() << std::endl;
	}
}

void Test6() {
	std::cout << "============ Circular Array ===============" << std::endl;
	CircularPriQueue<int, 10> queue;

	queue.Push(1);
	queue.Push(2);
	queue.Push(3);
	queue.Push(4);
	queue.Push(5);
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Push(6);
	queue.Push(7);
	queue.Pop();
	queue.Pop();
	queue.Push(8);
	queue.Push(9);
	queue.Push(10);
	queue.Pop();
	queue.Pop();
	queue.Push(11);
	queue.Push(12);
	queue.Push(13);
	queue.Push(14);
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
}

void Test7() {
	std::cout << "============ Circular Array empty Pop ===============" << std::endl;
	CircularPriQueue<int, 10> queue;

	queue.Push(1);
	queue.Push(2);
	queue.Push(3);
	queue.Push(4);
	queue.Push(5);
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Push(6);
	queue.Push(7);
	queue.Push(8);
	queue.Push(9);
	queue.Push(10);
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Push(11);
	queue.Push(12);
	queue.Push(13);
	queue.Push(14);
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	
	try {
		queue.Pop();
	} catch (CircularPriQueueException& exception) {
		std::cout << exception.what() << std::endl;
	}
}

void Test8() {
	std::cout << "============ Circular Array full Push ===============" << std::endl;
	CircularPriQueue<int, 10> queue;

	queue.Push(1);
	queue.Push(2);
	queue.Push(3);
	queue.Push(4);
	queue.Push(5);
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Push(6);
	queue.Push(7);
	queue.Push(8);
	queue.Push(9);
	queue.Push(10);
	queue.Push(11);
	queue.Push(12);
	queue.Push(13);
	
	try {
		queue.Push(14);
	} catch (CircularPriQueueException& exception) {
		std::cout << exception.what() << std::endl;
	}
}

void Test9() {
	std::cout << "============ Circular Array with same priority ===============" << std::endl;
	CircularPriQueue<int, 10> queue;

	queue.Push(1, 1);
	queue.Push(2, 1);
	queue.Push(3, 1);
	queue.Push(4, 1);
	queue.Push(5, 1);
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Push(6, 1);
	queue.Push(7, 1);
	queue.Push(8, 1);
	queue.Push(9, 1);
	queue.Push(10, 1);
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Push(11, 1);
	queue.Push(12, 1);
	queue.Push(13, 1);
	queue.Push(14, 1);
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
}

void Test10() {
	std::cout << "============ Circular Array with sorted priority ===============" << std::endl;

	CircularPriQueue<int, 10> queue;

	queue.Push(1, 1);
	queue.Push(2, 2);
	queue.Push(3, 3);
	queue.Push(4, 4);
	queue.Push(5, 5);
	queue.Push(6, 6);
	queue.Push(7, 7);
	queue.Push(8, 8);
	queue.Push(9, 9);
	queue.Push(10, 10);
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Push(11, 12);
	queue.Push(12, 13);
	queue.Push(13, 14);
	queue.Push(14, 15);
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
}

void Test11() {
	std::cout << "============ Circular Array with reverse sorted priority ===============" << std::endl;
	CircularPriQueue<int, 10> queue;

	queue.Push(1, 14);
	queue.Push(2, 13);
	queue.Push(3, 12);
	queue.Push(4, 11);
	queue.Push(5, 10);
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Push(6, 9);
	queue.Push(7, 8);
	queue.Pop();
	queue.Pop();
	queue.Push(8, 7);
	queue.Push(9, 6);
	queue.Push(10, 5);
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Push(11, 4);
	queue.Push(12, 3);
	queue.Push(13, 2);
	queue.Push(14, 1);

	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
}

void Test12() {
	std::cout << "============ Circular Array with priority ===============" << std::endl;
	std::cout << "Random Priority values" << std::endl;
	CircularPriQueue<int, 10> queue;

	queue.Push(1, 10);
	queue.Push(2, 8);
	queue.Push(3, 9);
	queue.Push(4, 12);
	queue.Push(5, 10);
	queue.Pop();
	queue.Pop();
	queue.Push(6, 8);
	queue.Push(7, 10);
	queue.Push(8, 6);
	queue.Push(9, 7);
	queue.Push(10, 10);
	queue.Pop();
	queue.Pop();
	queue.Push(11, 12);
	queue.Push(12, 10);
	queue.Push(13, 5);
	queue.Push(14, 9);
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
	queue.Pop();
}

int main() {
	int test_num = -1;
#ifndef _MSC_VER
	std::cin >> test_num;
#endif

	void(*tests[])() = { Test1, Test2, Test3, Test4, Test5, Test6, Test7, Test8, Test9, Test10, Test11, Test12 };
	int numTests = static_cast<int>(sizeof(tests) / sizeof(*tests));
	
	if (test_num >= 0 && test_num <= numTests) {
		tests[test_num - 1]();
	} else {
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