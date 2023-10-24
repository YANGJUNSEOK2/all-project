/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: MemManager.cpp
Project: Assignment 2 - Memory Manager
Author: 
Creation date: 
******************************************************************/

#include <iostream>
#include <map>
#include <string>
#include <algorithm>
#include "MemManager.h"

#undef new

MemManager gMemManager(2);

void MemManager::WriteMemoryInfo() {
	int totalFree = 0;
	int totalAllocated = 0;

	for (Page* currPage = pPageHead; currPage != nullptr; currPage = currPage->pNextPage) {
		currPage->WritePageInfo();
		for (Node* currNode = currPage->GetFirstNode(); currNode != nullptr; currNode = currNode->pNext) {
		    /* Caclulate totalFree (total bytes which are unused) and total allocated (total byes which are used)*/
		}
	}
	std::cout << "========================= Allocated: " << totalAllocated << " bytes\tFree: " << totalFree << " bytes ==========================" << std::endl << std::endl;
}

void MemManager::Page::WritePageInfo() {
	std::cout.width(40);
	std::cout.fill('-');
	std::cout << std::dec;
	std::cout << "" << "Page (" << MemManager::PageSize << ")";
	std::cout.width(40);
	std::cout << "" << std::endl;
	for (MemManager::Node* currNode = GetFirstNode(); currNode != nullptr; currNode = currNode->pNext) {
		currNode->WriteNodeInfo();
	}
}

void MemManager::Node::WriteNodeInfo() {
	std::cout << std::boolalpha << std::dec;
	std::cout << "Useable Size = " << usableSize << "\t";
	std::cout << "Available = " << isAvailable << std::endl;
	std::cout.fill('0');
}

void *operator new[](std::size_t size, const std::string fileName, int lineNum) {
	unsigned int folderIndex = static_cast<unsigned int>(fileName.find_last_of('\\')) + 1;
	std::string trackName = fileName.substr(folderIndex, fileName.length() - folderIndex)
		+ ':' + std::to_string(lineNum);
	return gMemManager.Alloc(size, trackName);
}
void *operator new(std::size_t size, const std::string fileName, int lineNum) {
	unsigned int folderIndex = static_cast<unsigned int>(fileName.find_last_of('\\')) + 1;
	std::string trackName = fileName.substr(folderIndex, fileName.length() - folderIndex)
		+ ':' + std::to_string(lineNum);
	return gMemManager.Alloc(size, trackName);
}
void operator delete(void *ptr) noexcept {
	gMemManager.Free(ptr);
}
void operator delete[](void *ptr) noexcept {
	gMemManager.Free(ptr);
}