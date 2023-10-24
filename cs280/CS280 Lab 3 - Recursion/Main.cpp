/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Main.cpp
Project: Lab 3 - Recurssion
Author: Kevin Wright
Creation date: 1/23/21
******************************************************************/

#include "List.h"
#include "LargestSubset.h"
#include "Queens.h"

int main() {
	int testNum;
	std::cin >> testNum;
	switch (testNum) {
    	case 1: {
    		int data[] = { 1, 2, 3, 4, 5 };
    		List<int> list(data, sizeof(data) / sizeof(*data));
    
    		list.PrintList();
    		list.PrintListBackwards();
    		list.Reverse();
    		list.PrintList();
    		list.PrintListBackwards();
    		break;
    	}
    	case 2: {
    		char data[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    		List<char> list(data, sizeof(data) / sizeof(*data));
    
    		list.PrintList();
    		list.PrintListBackwards();
    		list.Reverse();
    		list.PrintList();
    		list.PrintListBackwards();
    		break;
    	}
    	case 3: {
    		std::string data[] = { "Test", "String" };
    		List<std::string> list(data, sizeof(data) / sizeof(*data));
    
    		list.PrintList();
    		list.PrintListBackwards();
    		list.Reverse();
    		list.PrintList();
    		list.PrintListBackwards();
    		break;
    	}
    	case 4: {
    		List<int> list(nullptr, 0);
    
    		list.PrintList();
    		list.PrintListBackwards();
    		list.Reverse();
    		list.PrintList();
    		list.PrintListBackwards();
    		break;
    	}
    	case 5: {
    		int data[] = { 1 };
    		List<int> list(data, sizeof(data) / sizeof(*data));
    
    		list.PrintList();
    		list.PrintListBackwards();
    		list.Reverse();
    		list.PrintList();
    		list.PrintListBackwards();
    		break;
    	}
    	case 6: {
    		int data[] = { 8, 2, 5, 9, 12, 8 };
    
    		int largest = FindLargestSubset(data, sizeof(data) / sizeof(*data));
    		std::cout << "Largest Subset = " << largest << std::endl;
    		break;
    	}
    	case 7: {
    		int data[] = { -3 };
    
    		int largest = FindLargestSubset(data, sizeof(data) / sizeof(*data));
    		std::cout << "Largest Subset = " << largest << std::endl;
    		break;
    	}
    	case 8: {
    		int data[] = { -3, -8 };
    
    		int largest = FindLargestSubset(data, sizeof(data) / sizeof(*data));
    		std::cout << "Largest Subset = " << largest << std::endl;
    		break;
    	}
    	case 9: {
    		int data[] = { -3, 8, -4 };
    
    		int largest = FindLargestSubset(data, sizeof(data) / sizeof(*data));
    		std::cout << "Largest Subset = " << largest << std::endl;
    		break;
    	}
    	case 10: {
    		int data[] = { 12, -50, 8 };
    
    		int largest = FindLargestSubset(data, sizeof(data) / sizeof(*data));
    		std::cout << "Largest Subset = " << largest << std::endl;
    		break;
    	}
    	case 11: {
    		int data[] = { -3, 8, -4, 2, 5, -8 };
    
    		int largest = FindLargestSubset(data, sizeof(data) / sizeof(*data));
    		std::cout << "Largest Subset = " << largest << std::endl;
    		break;
    	}
    	case 12: {
    		int data[] = { -3, 8, -4, 2, 5, -8, -2, 9, 12, -50, 8 };
    
    		int largest = FindLargestSubset(data, sizeof(data) / sizeof(*data));
    		std::cout << "Largest Subset = " << largest << std::endl;
    		break;
    	}
    	case 13: {
    		Queens<4> board;
    		int solutions = board.FindSolutions();
    		std::cout << "There are " << solutions << " solutions" << std::endl;
    		break;
    	}
    	case 14: {
    		Queens<5> board;
    		int solutions = board.FindSolutions();
    		std::cout << "There are " << solutions << " solutions" << std::endl;
    		break;
    	}
    	case 15: {
    		Queens<3> board;
    		int solutions = board.FindSolutions();
    		std::cout << "There are " << solutions << " solutions" << std::endl;
    		break;
    	}
    	case 16: {
    		Queens<8> board;
    		int solutions = board.FindSolutions(false);
    		std::cout << "There are " << solutions << " solutions" << std::endl;
    		break;
    	}
    	case 17: {
    		Queens<5> board;
    		board.SetQueen(5, 0);
    		board.SetQueen(0, 5);
    		board.SetQueen(0, 0);
    		board.SetQueen(0, 1);
    		board.SetQueen(1, 0);
    		board.SetQueen(1, 1);
    		break;
    	}
    	case 18: {
    		Queens<5> board;
    		board.SetQueen(0, 0);
    		int solutions = board.FindSolutions();
    		std::cout << "There are " << solutions << " solutions" << std::endl;
    		break;
    	}
    	case 19: {
    		Queens<5> board;
    		board.SetQueen(3, 4);
    		int solutions = board.FindSolutions();
    		std::cout << "There are " << solutions << " solutions" << std::endl;
    		break;
    	}
    	case 20: {
    		Queens<5> board;
    		board.SetQueen(0, 0);
    		board.SetQueen(4, 1);
    		int solutions = board.FindSolutions();
    		std::cout << "There are " << solutions << " solutions" << std::endl;
    		break;
    	}
	}
}