/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: ListArray.hpp
Project: Assignment 1 - ListArray
Author: 
Creation date: 
******************************************************************/

#include <iostream>
#include "ListArray.h"

template <typename T, int ArraySize>
std::ostream& operator<<(std::ostream& os, ListArray<T, ArraySize> const& list) {
	for (typename ListArray<T, ArraySize>::Node* curr = list.head; curr != nullptr; curr = curr->pNext) {
		os << '[';
		int i = 0;
		for (; i < curr->count - 1; i++) {
			os << curr->values[i] << ", ";
		}
		os << curr->values[i];
		os << ']' << std::endl;
	}
	return os;
}


template<typename T, int ArraySize>
void ListArray<T, ArraySize>::dumpStats() {
	int numNodes = 0;
	size_t items = size();

	for (Node* curr = pHead; curr != nullptr; curr = curr->pNext) {
		numNodes++;
	}

	double ipn;
	if (numNodes) {
		ipn = static_cast<double>(items) / static_cast<double>(numNodes);
	}
	else {
		ipn = 0;
	}
	double util = ipn / static_cast<double>(ArraySize) * 100;

	std::cout << "Array Size: " << ArraySize << std::endl;
	std::cout << "Items: " << items << std::endl;
	std::cout << "Nodes: " << std::boolalpha << numNodes << std::endl;
	std::cout << "Sorted: " << isSorted() << std::endl;
	std::cout << "Average items per node: " << ipn << std::endl;
	std::cout << "Node utilization: " << std::setprecision(3) << util << "%" << std::endl;
}