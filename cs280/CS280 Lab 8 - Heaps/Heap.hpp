/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Heap.hpp
Project: Lab 8 - Heaps
Author: 
Creation date: 
******************************************************************/

#pragma once

#include <iomanip>
#include <iostream>
#include <string>
#include "Heap.h"

template<class T>
std::ostream & operator<<(std::ostream & out, Heap<T> & heap) {
	if (heap.data.empty() == false) {
		for (int i = 0; i < static_cast<int>(heap.data.size()) - 1; i++) {
			out << std::setw(3) << heap.data[i] << ",  ";
		}
		out << std::setw(3) << heap.data.back();
	}
	return out;
}

template<>
std::ostream & operator<<(std::ostream & out, Heap<std::string> & heap) {
	for (unsigned int i = 0; i < heap.data.size() - 1; i++) {
		out << heap.data[i] << ",  ";
	}
	out << heap.data.back();
	return out;
}