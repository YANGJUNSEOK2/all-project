/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: ListArray.h
Project: Assignment 1 - ListArray
Author: 
Creation date: 
******************************************************************/
#pragma once

#include <vector>
#include <stdexcept>

class ListArrayException : public std::runtime_error {
public:
	ListArrayException(const std::string& Message) : std::runtime_error(Message.c_str()) {};
};

// forward declaration for 1-1 operator<< 
template<typename T, int ArraySize>
class ListArray;

template<typename T, int ArraySize>
std::ostream& operator<< (std::ostream& os, ListArray<T, ArraySize> const& rhs);

template <typename T, int ArraySize>
class ListArray {
private:
	struct Node {
	    // Feel free to make add any functions & any data members you like
		Node* pNext;
		T values[ArraySize + 1];
	};

public:
	ListArray();	// default constructor
	~ListArray();	// destructor

	// add data
	void insert(const T& value); // this adds data sorted
	void push_back(const T& value);
	void push_front(const T& value);
	void pop_back();
	void pop_front();

	// and some more
	size_t size(void) const;   // total number of items (not nodes)
	unsigned int find(const T& value) const;       // returns index, size (one past last) if not found

	friend std::ostream& operator<< <T, ArraySize>(std::ostream& os, ListArray<T, ArraySize> const& list);
	void dumpStats();

private:
	bool isSorted() const { return sorted; }
	
	// Feel free to make add any functions you like
	
	Node* pHead;
	bool sorted;
};

#include "ListArray.hpp"
