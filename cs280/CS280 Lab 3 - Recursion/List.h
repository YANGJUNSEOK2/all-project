/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: List.h
Project: Lab 3 - Recurssion
Author: 
Creation date: 
******************************************************************/
#pragma once
#include <iostream>


template<typename T>
class List {
private:
	struct Node {
		T data;
		Node* pNext;
		int index;

		Node(T& data, Node* pNext, int index) : data(data), pNext(pNext), index(index) {
			std::cout << "Creating Node " << index << ": " << data << std::endl;
		}
		~Node() {
			delete pNext;
			std::cout << "Deleting Node " << index << ": " << data << std::endl;
		}
	};
public:
	List( T* data, int numNode);
	~List() {
    	delete pHead;
    	pHead = nullptr;
    }
	void PrintList() const;
	void PrintListBackwards() const;
	void Reverse();
private:
	// Create your own private functions 
	
	Node* pHead;
	int nextNodeIndex;
};