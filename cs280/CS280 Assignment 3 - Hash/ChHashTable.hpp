/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: ChHashTable.hpp
Project: CS280 Assignment 3
Author: 
Created: 
******************************************************************/
#pragma once

#include "ChHashTable.h"

template <typename T>
void ChHashTable<T>::DumpTable() {
	std::cout << "Initial size: " << initialTableSize << std::endl;
	std::cout << "Max load factor: " << maxLoadFactor << std::endl;
	std::cout << "Growth factor: " << growthFactor << std::endl;

	for (unsigned int i = 0; i < stats.tableSize; i++) {
		std::cout << "Slot: " << std::setw(3) << i;
		
        /*Loop You hash table going through each node of the chain*/
        {
			std::cout << " --> " << /*Output the hash key*/;
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

template <typename T>
void ChHashTable<T>::DumpStats() {
	std::cout << "Number of probes: " << stats.probes << std::endl;
	std::cout << "Number of expansions: " << stats.expansions << std::endl;
	std::cout << "Items: " << stats.count << ", TableSize: " << stats.tableSize << std::endl;
	std::cout << "Load factor: " << std::setprecision(3) << (double)stats.count / (double)stats.tableSize << std::endl;
	std::cout << "Nodes created: " << stats.allocations << std::endl;
	std::cout << std::endl;
}