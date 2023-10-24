/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Main.cpp
Project: Lab 5 - Sort
Author: Kevin Wright
Creation date: 1/25/21
******************************************************************/

#include <iostream>
#include <random>
#include <chrono>
#include "Sort.h"

void PrintArray(int *data, size_t size) {
	std::cout << "[";
	for (size_t i = 0; i < size - 1; i++) {
		std::cout << data[i] << ", ";
	}
	std::cout << data[size - 1] << "]" << std::endl;

}
int* GenerateExampleNumbers(const int) {
	int *data = new int[9] { 1, 19, 15, 18, 10, 1, 7, 12, 0 };
	return data;
}

int *GenerateRandNumbers(const int arraySize) {
	std::mt19937 rand(0);
	std::uniform_int_distribution<int> dist(0, 100);

	int *data = new int[arraySize];

	for (int i = 0; i < arraySize; i++) {
		data[i] = dist(rand);
	}
	return data;
}
int *GenerateSortedNumbers(const int arraySize) {
	int *data = new int[arraySize];
	for (int i = 0; i < arraySize; i++) {
		data[i] = i+1;
	}
	return data;
}
int *GenerateReverseSortedNumbers(const int arraySize) {
	int *data = new int[arraySize];
	for (int i = 0; i < arraySize; i++) {
		data[i] = arraySize - i;
	}
	return data;
}

std::string GetFuncName(void* funcPtr) {
	if(funcPtr == (void*)&GenerateExampleNumbers) {
		return "Example Numbers";
	}
	if (funcPtr == (void*)&GenerateRandNumbers) {
		return "Random Numbers";
	}
	if (funcPtr == (void*)&GenerateSortedNumbers) {
		return "Sorted Numbers";
	}
	if (funcPtr == (void*)&GenerateReverseSortedNumbers) {
		return "Reverse Sorted Numbers";
	}
	if (funcPtr == (void*)&BubbleSort) {
		return "Bubble Sort";
	}
	if (funcPtr == (void*)&SelectionSort) {
		return "Selection Sort";
	}
	if (funcPtr == (void*)&MergeSort) {
		return "Merge Sort";
	}
	return "";
}

void TestSort(int size, int* (*genDataFunc)(int size), void(*sortFunc)(int*, size_t, int&, int&)) {
	std::cout << GetFuncName(reinterpret_cast<void*>(sortFunc)) << " with " << size 
			<< " " << GetFuncName(reinterpret_cast<void*>(genDataFunc)) << std::endl;

	int swaps = 0, compares = 0;
	int *data = genDataFunc(size);

	std::cout << "Before Sort = ";
	PrintArray(data, size);
	sortFunc(data, size, swaps, compares);
	std::cout << "After Sort = ";
	PrintArray(data, size);
	std::cout << "Swaps = " << swaps << " Compares = " << compares << std::endl << std::endl;
	delete[] data;
}

long long TimedTest(void(*sortFunc)(int*, size_t, int&, int&)) {
	int size = 40000;
	std::cout << GetFuncName(reinterpret_cast<void*>(sortFunc)) << " Timed test with " << size << " Random Numbers" << std::endl;

	int *data = GenerateRandNumbers(size);
	int swaps = 0, compares = 0;
	auto start = std::chrono::high_resolution_clock::now();
	sortFunc(data, size, swaps, compares);
	auto end = std::chrono::high_resolution_clock::now();
	delete[] data;
	return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

void TestBubbleTimed() {
	long long time = TimedTest(BubbleSort);
#ifdef _MSC_VER
	std::cout << "Bubble Sort took " << time << " ms" << std::endl << std::endl;
#else
	if (time >= 8600 || time <= 9600) {
		std::cout << "Bubble sort time was close to the expected time (around 9 seconds)";
	} else {
		std::cout << "Bubble sort should be around 9100ms when running on the moodle server";
	}
#endif
}

void TestSlectionTimed() {
	long long time = TimedTest(SelectionSort);
#ifdef _MSC_VER
	std::cout << "Selection Sort took " << time << " ms" << std::endl << std::endl;
#else
	if (time >= 2000 || time <= 3000) {
		std::cout << "Selection sort took the expected time (around 2.5 seconds)";
	} else {
		std::cout << "Selection sort should be around 2500ms when running on the moodle server";
	}
#endif
}

void TestMergeTimed() {
	long long time = TimedTest(MergeSort);
#ifdef _MSC_VER
	std::cout << "Merge Sort took " << time << " ms" << std::endl << std::endl;
#else
	if (time >= 3 || time <= 12) {
		std::cout << "Merge sort took the expected time (around 8ms)";
	} else {
		std::cout << "Merge sort should be around 8ms when running on the moodle server";
	}
#endif
}



int main() {
	int test_num = -1;
#ifndef _MSC_VER
	std::cin >> test_num;
#endif
	constexpr int numGenFuncs = 7;
	int* (*genDataFunc[numGenFuncs])(int size) = { GenerateExampleNumbers, GenerateRandNumbers, GenerateRandNumbers,
						GenerateSortedNumbers, GenerateReverseSortedNumbers, GenerateReverseSortedNumbers, GenerateRandNumbers };
	int dataSize[numGenFuncs] = { 9, 20, 40, 20, 20, 40, 1 };

	void(*sortFunc[])(int*, size_t, int&, int&) = { BubbleSort, SelectionSort, MergeSort };
	constexpr int sortAlgos = sizeof(sortFunc)/sizeof(*sortFunc);

	constexpr int numTestsFunctional = numGenFuncs * sortAlgos;

	if (test_num >= 0 && test_num < numTestsFunctional) {
		int numGenFuncIndex = test_num % numGenFuncs;
		int sortFuncIndex = test_num / numGenFuncs;
		TestSort(dataSize[numGenFuncIndex], genDataFunc[numGenFuncIndex], sortFunc[sortFuncIndex]);
	} else if (test_num >= numTestsFunctional && test_num < numTestsFunctional + sortAlgos) {
		switch (test_num - numTestsFunctional) {
		case 0:
			TestBubbleTimed();
			break;
		case 1:
			TestSlectionTimed();
			break;
		case 2:
			TestMergeTimed();
			break;
		}
	}
	else {
		for (int i = 0; i < numTestsFunctional; i++) {
			TestSort(dataSize[i % numGenFuncs], genDataFunc[i % numGenFuncs], sortFunc[i / numGenFuncs]);
		}
		TestBubbleTimed();
		TestSlectionTimed();
		TestMergeTimed();
	}


#ifdef _MSC_VER
	system("pause");
#endif
}