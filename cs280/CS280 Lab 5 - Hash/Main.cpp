/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Main.cpp
Project: Lab 4 - Hash
Author: Kevin Wright
Creation date: 1/26/2021
******************************************************************/

#include <iostream>
#include <string>

#include "HashLab.h"


void Test1() {
	std::cout << "============ char count for abc ===============" << std::endl;
	ShowCharCount("abc");
}

void Test2() {
	std::cout << "============ only count lowercase letters ===============" << std::endl;
	ShowCharCount("aAa");
}

void Test3() {
	std::cout << "============ count something more interesting ===============" << std::endl;
	std::string text = "\
Arirang, Arirang, Arariyo...\n\
Arirang gogaero neomeoganda.\n\
Nareul beorigo gasineun nimeun\n\
Sibrido mosgaseo balbyeongnanda.\n\
Cheongcheonhaneuren janbyeoldo manko,\n\
Urine gaseumen huimangdo manda.\n\
Jeogi jeo sani Baekdusaniraji,\n\
Dongji seotdaredo kkotman pinda.";
	ShowCharCount(text);
}

void Test4() {
	std::cout << "============ Complete Sodoku ===============" << std::endl;
	char sudoku[SudokuBoardSize][SudokuBoardSize] = { { 3, 5, 1,   9, 2, 4,   7, 6, 8},
													  { 2, 8, 4,   6, 1, 7,   9, 3, 5},
													  { 9, 7, 6,   5, 3, 8,   4, 2, 1},

													  { 7, 4, 5,   3, 8, 2,   1, 9, 6},
													  { 6, 2, 8,   1, 9, 5,   3, 7, 4},
													  { 1, 9, 3,   4, 7, 6,   8, 5, 2},

													  { 4, 6, 9,   8, 5, 3,   2, 1, 7},
													  { 5, 1, 2,   7, 4, 9,   6, 8, 3},
													  { 8, 3, 7,   2, 6, 1,   5, 4, 9}, };
	TestSudoku(sudoku);
}

void Test5() {
	std::cout << "============ Incomplete Sodoku ===============" << std::endl;
	char sudoku[SudokuBoardSize][SudokuBoardSize] = { { -1,  5, -1,    9,  2, -1,    7, -1,  8},
													  {  2,  8, -1,   -1,  1, -1,   -1, -1, -1},
													  {  9,  7, -1,   -1,  3,  8,   -1,  2,  1},

													  { -1, -1,  5,   -1,  8,  2,    1,  9,  6},
													  { -1, -1,  8,    1,  9,  5,    3, -1, -1},
													  {  1,  9, -1,    4,  7, -1,    8, -1, -1},

													  {  4,  6, -1,    8,  5, -1,   -1,  1,  7},
													  {  5,  1, -1,   -1,  4, -1,   -1,  8,  3},
													  {  8, -1,  7,   -1, -1,  1,    5, -1, -1} };

	TestSudoku(sudoku);
}

void Test6() {
	std::cout << "============ Sodoku with Errors ===============" << std::endl;
	char sudoku[SudokuBoardSize][SudokuBoardSize] = { { 4, 5, 1,   9, 2, 4,   7, 6, 8},
													  { 2, 3, 4,   6, 1, 7,   9, 3, 5},
													  { 9, 7, 6,   5, 3, 8,   4, 2, -1},

													  { 7, 4, 5,   3, 8, 1,   -1, 9, 6},
													  { 6, 2, 8,   -1, 9, 5,   3, 7, 4},
													  { 1, 9, 3,   4, 7, 6,   8, 5, 2},

													  { 4, 6, 9,   8, 5, 3,   2, 1, 7},
													  { 5, 1, 2,   7, 4, 9,   1, 8, 3},
													  { 8, 3, 7,   2, 6, 1,   5, 4, 9}, };

	TestSudoku(sudoku);
}

void Test7() {
	std::cout << "============ Birthday Paradox ===============" << std::endl;

	std::cout << "The average number of people needed to have a matching birthday is " << BirthdayParadox() << std::endl;
}

void Test8() {
	std::cout << "============ Quick Find ===============" << std::endl;
	QuickFind quickFind(10);

	quickFind.Union(0, 5);
	quickFind.Union(0, 6);
	quickFind.Union(1, 2);
	quickFind.Union(2, 7);
	quickFind.Union(3, 4);
	quickFind.Union(3, 8);
	quickFind.Union(9, 4);

	// Visually this now looks like this
	// 0    1 -- 2    3 -- 4 
	// |		 |    |    |
	// 5 -- 6	 7    8    9
	std::cout << std::boolalpha;

	
	std::cout << "Is 1 connected to 6 :" << quickFind.IsConnected(1, 6) << std::endl;
	std::cout << "Is 1 connected to 7 :" << quickFind.IsConnected(1, 7) << std::endl;
	std::cout << "Is 8 connected to 7 :" << quickFind.IsConnected(8, 7) << std::endl;

	quickFind.Union(2, 4);
		// Visually this now looks like this
        //           ___________
        //           |         |
        // 0    1 -- 2    3 -- 4 
        // |         |    |    |
        // 5 -- 6    7    8    9
	std::cout << "After connecting 2 & 4, Is 8 connected to 7 :" << quickFind.IsConnected(8, 7) << std::endl;
}


int main(int argc, char** argv) {
	int test_num = 0;
#ifndef _MSC_VER
	std::cin >> test_num;
#endif

	void(*tests[])() { Test1, Test2, Test3, Test4, Test5, Test6, Test7, Test8 };

	int numTests = static_cast<int>(sizeof(tests) / sizeof(*tests));
	if (argc > 1) {
		test_num = std::atoi(argv[1]);
	}

	if (test_num > 0 && test_num <= numTests) {
		tests[test_num - 1]();
	} else {
		for (int i = 0; i < numTests; i++) {
			tests[i]();
			std::cout << std::endl << std::endl;
		}
	}
}