/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: CircularPriQueue.h
Project: Lab 1 - CirclePriQueue
Author: Kevin Wright
Creation date: 1/27/21
******************************************************************/

#pragma once
#include <stdexcept>
#include <string>

class CircularPriQueueException : public std::runtime_error {
public:
	CircularPriQueueException(std::string message) : std::runtime_error(message) {	}
};

template<typename T, int SIZE>
class CircularPriQueue {
public:
	CircularPriQueue();
	T Pop();
	void Push(T newItem, int pri = 0);

private:
	struct PriValue {
		T value;
		int pri;
	};
	
	// You may add additional helper functions where you need

	int back, front;
	PriValue data[SIZE];
};

#include "CircularPriQueue.hpp"