/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Main.cpp
Project: Lab 9 - Knights Tour
Author: Kevin Wright
Creation date: 1/29/21
******************************************************************/
#include <iostream>
#include "Board.h"

void Test1() {
	const int width = 8;
	const int height = 8;
	Board<width, height> board;

	board.SolveKnightsTour({ 0,0 }, { width - 1, height - 1 });
	board.PrintPath();
}

void Test2() {
	const int width = 8;
	const int height = 8;
	Board<width, height> board;

	board.SolveKnightsTour({ 1,0 }, { width - 2, height - 1 });
	board.PrintPath();
}

void Test3() {
	const int width = 3;
	const int height = 3;
	Board<width, height> board;

	board.SolveKnightsTour({ 0,0 }, { width - 1, height - 1 });
	board.PrintPath();
}

void Test4() {
	const int width = 10;
	const int height = 5;
	Board<width, height> board;

	board.SolveKnightsTour({ 0,0 }, { width - 1, height - 1 });
	board.PrintPath();
}

void Test5() {
	const int width = 5;
	const int height = 5;
	Board<width, height> board;

	board.SolveKnightsTour({ 1,1 }, { 3, 3 });
	board.PrintPath();
}

void Test6() {
	const int width = 2;
	const int height = 2;
	Board<width, height> board;

	board.SolveKnightsTour({ 0,0 }, { width - 1, height - 1 });
	board.PrintPath();
}

void Test7() {
	const int width = 8;
	const int height = 8;
	Board<width, height> board;

	board.PrintPath();
}

void Test8() {
	const int width = 8;
	const int height = 8;
	Board<width, height> board;

	board.SolveKnightsTour({ -1,-1 }, { width - 1, height - 1 });
	board.PrintPath();
}

void Test9() {
	const int width = 8;
	const int height = 8;
	Board<width, height> board;

	board.SolveKnightsTour({ 0,0 }, { width, height });
	board.PrintPath();
}

int main() {
	int test_num = -1;
#ifndef _MSC_VER
	std::cin >> test_num;
#endif
	void(*tests[])() = { Test1, Test2, Test3, Test4, Test5, Test6, Test7, Test8, Test9 };
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
}