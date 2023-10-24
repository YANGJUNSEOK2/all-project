/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: MemManager.h
Project: Assignment 2 - Memory Manager
Author: Kevin Wright
Creation date: 2/2/21
******************************************************************/
#pragma once
#include <map>
#include <exception>

class MemoryException : public std::runtime_error {
public:
	MemoryException(std::string message) : std::runtime_error(message.c_str()) { }
};

class MemManager {
public:
	MemManager(int pages);
	~MemManager();

	void* Alloc(std::size_t size, const std::string tag);
	void Free(void* ptr);

	void WriteMemoryInfo();
	static const int PageSize = (sizeof(void*) == 8) ? 272 : 256;

private:
	struct Node {
		static const int INDICATOR = 0xDEADBEEF;
		static int GetHeaderSize() { return sizeof(Node) - sizeof(placeholder); }

		Node(size_t size);
		Node(size_t size, Node* pPrev, Node* pNext);
		void WriteNodeInfo();

		bool BoundsCheck();
		void Free();
		void *GetUserData();
		int *GetPostIndicatorPtr();

		size_t usableSize;
		bool isAvailable;
		Node* pPrev;
		Node* pNext;
		int preIndicator;
		int placeholder;	// This is just here so sizeof(Node) returns the correct size, this should NOT be used directly!
	};

	struct Page {
		Page(int pageSize);
		void WritePageInfo();
		Node* GetFirstNode();

		Page* pNextPage;
	};
	 
	Page* pPageHead = nullptr;
	std::map<void*, std::string> allocationToSource;
};

void* operator new[](std::size_t size, const std::string fileName, int lineNum);
void *operator new(std::size_t size, const std::string fileName, int lineNum);
void operator delete(void* ptr) noexcept;
void operator delete[](void* ptr) noexcept;

#define new new(__FILE__,__LINE__)