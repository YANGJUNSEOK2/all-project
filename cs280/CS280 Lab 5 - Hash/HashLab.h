/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: HashLab.h
Project: Lab 4 - Hash
Author: Kevin Wright
Creation date: 1/26/2021
******************************************************************/
#pragma once


// Count the number of characters in the given string (only count lowercase, other characters should be ignored)
// output should be written.  Write the char then ": " then the count
void ShowCharCount(std::string text);

constexpr int SudokuBoardSize = 9;
// Test if all the rows are valid
// Test if all the columns are valid
// Test if all the 3x3s are valid
// Output the errors (Test6), if no errors output 
//    if complete: "Puzzle solved correctly" (Test4) or 
//       incomplete: "Puzzle doesn't have any errors at the moment" (Test5)
void TestSudoku(char board[SudokuBoardSize][SudokuBoardSize]);

// Prove the Birthday paradox by running it 10000 times
// use std::mt19937 and MAKE SURE use 0 as the seed or you won't match my results
float BirthdayParadox();

// Union means to set 2 nodes to be connected
// data is our data
// numNodes is the number of nodes in our data set
// nodeA and nodeB are indices to connect
class QuickFind {
public:
	QuickFind(int numNodes);
	~QuickFind();
	void Union(int nodeA, int nodeB);
	bool IsConnected(int nodeA, int nodeB);
private:
	int Hash(int nodeIndex);

	int size;
	int* data;
};