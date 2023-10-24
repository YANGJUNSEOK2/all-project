/******************************************************************
CopypRightTree (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: AVLTree.hpp
Project: Assignment 4 - BST & AVL
Author: Kevin WpRightTree
Creation date: 2/4/21
******************************************************************/

#include <string>
#include <list>
#include <iomanip>

#include "BSTree.h"

template<typename T>
void BSTree<T>::DebugPrint(bool showCounts) const {

	if (pRootNode != nullptr) {
		std::queue<BinTreeNode*> printQueue = CreatePrintQueue();
		std::queue<BinTreeNode*> showCountQueue;
		if (showCounts) {
			showCountQueue = printQueue;
		}

		std::cout << "height: " << pRootNode->Height();
		std::cout << ", nodes: " << pRootNode->size << std::endl;

		int nodeRowCount = 0;
		int nodeRowTarget = 1;
		int coutWidth = 2 << pRootNode->Height();
		while (printQueue.empty() == false) {
			if (nodeRowCount == 0) {
				std::cout.width(coutWidth / 2); // first node of each row should have a 1/2 width offset
			} else {
				std::cout.width(coutWidth - 1);	// set the width for the next element
			}

			if (printQueue.front() != nullptr) {
				std::cout << printQueue.front()->data;
			} else {
				std::cout << "X";
			}

			// check if we are done with the current row
			if (++nodeRowCount == nodeRowTarget) {
				std::cout << std::endl;
				nodeRowTarget *= 2;
				coutWidth /= 2;
				nodeRowCount = 0;
			} else {
				std::cout << ' ';
			}
			printQueue.pop();
		}
		if (showCounts) {
			while (showCountQueue.empty() == false) {
				if (showCountQueue.front() != nullptr) {
					std::cout << showCountQueue.front()->data << "(" << showCountQueue.front()->size << ")  ";
				}
				showCountQueue.pop();
			}
			std::cout << std::endl;
		}
	} else {
		std::cout << "Tree is Empty" << std::endl;
	}
	std::cout << std::endl;
}