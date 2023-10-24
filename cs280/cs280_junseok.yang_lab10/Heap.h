/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Heap.h
Project: Lab 8 - Heaps
Author: junseok yang
Creation date: 5/17 2021
******************************************************************/

#pragma once

#include <vector>
#include <algorithm>

template<class T>
class Heap {
public:
	Heap(bool(*compareFunc)(const T& a, const T& b));
	Heap(T* items, int numOfItems, bool(*compareFunc)(const T& a, const T& b));

	void greaterHeapify(T* items, int numOfItems, int pos);
	void lessHeapify(int pos);
	void Heapify(T* data, int numOfItems);

	void Push(T newItem);
	T Pop();

	bool IsEmpty();

	bool found(T c);

	void Sort();
	typename std::vector<T>::iterator Find(const T& val) { return std::find(data.begin(), data.end(), val); }
	void Update(typename std::vector<T>::iterator);

	//template<class U>
	//friend std::ostream& operator<<(std::ostream& out, Heap<U>& heap);
private:
	// Add your own private functions

	bool(*compareFunc)(const T& a, const T& b);
	std::vector<T> data;
};

#include "Heap.hpp"