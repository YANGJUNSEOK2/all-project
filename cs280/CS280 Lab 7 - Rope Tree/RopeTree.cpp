/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: RopeTree.cpp
Project: Lab 7 - Rope Tree
Author: 
Creation date: 
******************************************************************/

std::ostream& operator << (std::ostream& out, RopeTree& tree) {
	out << tree.root;
	return out;
}

std::ostream& operator << (std::ostream& out, RopeTree::RopeNode* node) {
	if (node->GetNodeType() == RopeTree::RopeNode::RopeNodeType::Interier) {
		out << static_cast<RopeTree::RopeNodeInterior*>(node);
	}
	if (node->GetNodeType() == RopeTree::RopeNode::RopeNodeType::Leaf) {
		out << static_cast<RopeTree::RopeNodeLeaf*>(node);
	}
	return out;
}

std::ostream& operator << (std::ostream& out, RopeTree::RopeNodeInterior* node) {
	if (node->lChild != nullptr) {
		out << node->lChild;
	}
	if (node->rChild != nullptr) {
		out << node->rChild;
	}
	return out;
}

std::ostream& operator << (std::ostream& out, RopeTree::RopeNodeLeaf* node) {
	out << node->text;
	return out;
}


void RopeTree::CreatePrintQueueByDepth(RopeTree::RopeNode* subtreeRoot, std::queue<RopeTree::RopeNode*>& printQueue, int depth) const {
	if (depth == 0) {
		printQueue.push(subtreeRoot);
	} else if (subtreeRoot == nullptr) {
		CreatePrintQueueByDepth(nullptr, printQueue, depth - 1);
		CreatePrintQueueByDepth(nullptr, printQueue, depth - 1);
	} else {
		if (subtreeRoot->GetNodeType() == RopeNode::RopeNodeType::Interier) {
			CreatePrintQueueByDepth(static_cast<RopeNodeInterior*>(subtreeRoot)->lChild, printQueue, depth - 1);
			CreatePrintQueueByDepth(static_cast<RopeNodeInterior*>(subtreeRoot)->rChild, printQueue, depth - 1);
		} else {
			CreatePrintQueueByDepth(nullptr, printQueue, depth - 1);
			CreatePrintQueueByDepth(nullptr, printQueue, depth - 1);
		}
	}
}

std::queue<RopeTree::RopeNode*> RopeTree::CreatePrintQueue() const {
	if (root == nullptr) {
		return std::queue<RopeNode*>();
	}

	std::queue<RopeNode*> result;
	const int height = static_cast<RopeNodeInterior*>(root)->Height();
	for (int depth = 0; depth <= height; depth++) {
		CreatePrintQueueByDepth(root, result, depth);
	}

	return result;
}

void RopeTree::DebugPrint() const {
	std::queue<RopeNodeLeaf*> outputStrings;
	if (root != nullptr) {
		std::queue<RopeNode*> printQueue = CreatePrintQueue();

		std::cout << "height: " << static_cast<RopeNodeInterior*>(root)->Height() << std::endl;

		int nodeRowCount = 0;
		int nodeRowTarget = 1;
		int coutWidth = 2 << static_cast<RopeNodeInterior*>(root)->Height();
		while (printQueue.empty() == false) {
			if (nodeRowCount == 0) {
				std::cout.width(coutWidth / 2); // first node of each row should have a 1/2 width offset
			} else {
				std::cout.width(coutWidth - 1);	// set the width for the next element
			}

			if (printQueue.front() != nullptr) {
				std::cout << printQueue.front()->GetWeight();
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
	} else {
		std::cout << "Tree is Empty" << std::endl;
	}
	DebugPrintNodes(root);

	std::cout << std::endl;
}

void RopeTree::DebugPrintNodes(RopeNode* subtreeRoot) const {
	if (subtreeRoot->GetNodeType() == RopeTree::RopeNode::RopeNodeType::Interier) {
		RopeTree::RopeNodeInterior* nodePtr = static_cast<RopeTree::RopeNodeInterior*>(subtreeRoot);
		if (nodePtr->lChild != nullptr) {
			DebugPrintNodes(nodePtr->lChild);
		}
		if (nodePtr->rChild != nullptr) {
			DebugPrintNodes(nodePtr->rChild);
		}
	} else {
		std::cout << '[' << static_cast<RopeTree::RopeNodeLeaf*>(subtreeRoot) << ']';
	}
}