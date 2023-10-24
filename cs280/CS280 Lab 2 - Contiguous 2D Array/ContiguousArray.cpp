/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: ContiguousArray.cpp
Project: Lab 2 - Contiguous 2D Array
Author: 
Creation date:
******************************************************************/
#include <iostream>

class Cell {
public:
	Cell(int x, int y) : x(x), y(y) {}

	friend std::ostream& operator << (std::ostream& out, const Cell& c);
private:
	int x;
	int y;
};

std::ostream& operator << (std::ostream& out, const Cell& c) {
	out << "(0x" << c.x << ", 0x" << c.y << ")";
	return out;
}

template<typename T>
T** CreateContiguous2DArray(int width, int height) {
}

template<typename T>
void SetDataAs2D(T** data, int width, int height) {
}

template<typename T>
void SetDataAs1D(T* data, int width, int height) {
}

template<>
void SetDataAs2D<Cell>(Cell** data, int width, int height) {
}

template<>
void SetDataAs1D<Cell>(Cell* data, int width, int height) {
}

template<typename T>
void PrintAs2D(T** data, int width, int height) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width-1; x++) {
			std::cout << "0x" << /*add code here*/ << '\t';
		}
		std::cout << "0x" << /*add code here*/ << std::endl;
	}
}

template<typename T>
void PrintAs1D(T* data, int width, int height) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width-1; x++) {
			std::cout << "0x" << /*add code here*/ << '\t';
		}
		std::cout << "0x" << /*add code here*/ << std::endl;
	}
}

template<>
void PrintAs2D(Cell** data, int width, int height) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width-1; x++) {
			std::cout << /*add code here*/ << '\t';
		}
		std::cout << /*add code here*/ << std::endl;
	}
}

template<>
void PrintAs1D(Cell* data, int width, int height) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width-1; x++) {
			std::cout <</*add code here*/ << '\t';
		}
		std::cout << /*add code here*/ << std::endl;
	}
}

void Test1() {
	int width = 5, height = 5;
	int** array = CreateContiguous2DArray<int>(width, height);
	SetDataAs1D(array[0], width, height);
	PrintAs1D(array[0], width, height);
	delete[] array;
}

void Test2() {
	int width = 12, height = 12;
	unsigned int** array = CreateContiguous2DArray<unsigned int>(width, height);
	SetDataAs2D(array, width, height);
	PrintAs2D(array, width, height);
	delete[] array;
}

void Test3() {
	int width = 8, height = 12;
	short** array = CreateContiguous2DArray<short>(width, height);
	SetDataAs1D(array[0], width, height);
	PrintAs2D(array, width, height);
	delete[] array;
}

void Test4() {
	int width = 12, height = 8;
	unsigned short** array = CreateContiguous2DArray<unsigned short>(width, height);
	SetDataAs2D(array, width, height);
	PrintAs1D(array[0], width, height);
	delete[] array;
}

void Test5() {
	int width = 8, height = 12;
	Cell** array = CreateContiguous2DArray<Cell>(width, height);
	SetDataAs1D(array[0], width, height);
	PrintAs2D(array, width, height);
	delete[] array;
}

void Test6() {
	int width = 12, height = 8;
	Cell** array = CreateContiguous2DArray<Cell>(width, height);
	SetDataAs2D(array, width, height);
	PrintAs1D(array[0], width, height);
	delete[] array;
}

int main() {
	std::cout << std::hex << std::fixed;

	int test_num = -1;
#ifndef _MSC_VER
	std::cin >> test_num;
#endif

	typedef void(*Test)(void);
	Test Tests[] = { Test1,	Test2,  Test3,	Test4, Test5, Test6 };
	int numTests = static_cast<int>(sizeof(Tests) / sizeof(*Tests));

	if (test_num > 0 && test_num <= numTests) {
		Tests[test_num - 1]();
	} else {
		for (int i = 1; i <= numTests; i++) {
			Tests[i - 1]();
			std::cout << std::endl << std::endl;
		}
	}

	return 0;
}