/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Queens.h
Project: Lab 3 - Recurssion
Author: 
Creation date: 
******************************************************************/
#pragma once

template<int BOARDSIZE>
class Queens {
public:
	Queens();
	int FindSolutions(bool displaySolution = true);
	void SetQueen(int xPos, int yPos);
private:
	// Create any own private functions or private data memembers that you like
	
	int solutions;
	bool board[BOARDSIZE][BOARDSIZE];
};