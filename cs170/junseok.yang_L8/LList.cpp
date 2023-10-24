/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:   Driver.cpp
Author: junseok.yang
Creation Date:SPRING/5/29/2019
    Source file for the Linked List for Lab8
******************************************************************************/
#include <ostream>
#include"LList.h"

List::~List()
{
    while (pHead != nullptr)
    {
        Node* my_delete = pHead;
        pHead = pHead->pNext;
        delete my_delete;
    }
}

void List::Reverse()
{
    Node *curr = pHead;
    Node *next = nullptr;
    Node *prev = nullptr;

    while (curr != nullptr) {
        next = curr->pNext;
        curr->pNext = prev;
        prev = curr;
        curr = next;
    }
    pHead = prev;
}

bool List::IsCircularAndFix()
{
    Node *next = pHead->pNext;
    Node *nextDouble = pHead->pNext->pNext;
    while (next != nextDouble)
    {
        if (next->pNext == nullptr)
        {
            return false;
        }
        if(nextDouble->pNext == nullptr)
        {
            return false;
        }
        if(nextDouble->pNext->pNext == nullptr)
        {
            return false;
        }
        next = next->pNext;
        nextDouble = nextDouble->pNext->pNext;
    }
    RemoveLoop(next);
    return true;
}

bool List::DoesIntersectsAndFix(List &list2)
{
    Node *firstList = pHead;
    Node *secondList = list2.pHead;
    int firstCount = 0, secondCount = 0, count = 0;

    if (firstList == secondList)
    {
        list2.pHead = nullptr;
        pHead = firstList;
        return true;
    }
    while (firstList->pNext != nullptr) {
        firstCount++;
        firstList = firstList->pNext;
    }
    while (secondList->pNext != nullptr) {
        secondCount++;
        secondList = secondList->pNext;
    }
    firstList = pHead;
    secondList = list2.pHead;
    if (firstCount < secondCount)
    {
        for (int i = 0; i < secondCount - firstCount; i++)
        {
            secondList = secondList->pNext;
        }
    }
    if (firstCount > secondCount)
    {
        for (int i = 0; i < firstCount - secondCount; i++)
        {
            firstList = firstList->pNext;
        }
    }
    while (firstList != secondList)
    {
        if (firstList->pNext == nullptr)
        {
            return false;
        }
        if(secondList->pNext == nullptr)
        {
            return false;
        }
        firstList = firstList->pNext;
        secondList = secondList->pNext;
        count++;
    }
    secondList = list2.pHead;
    if (firstCount < secondCount)
    {
        for (int i = 0; i < count + secondCount - firstCount - 1; i++)
        {
            secondList = secondList->pNext;
        }
    }
    else
    {
        for (int i = 0; i < count - 1; i++)
        {
            secondList = secondList->pNext;
        }
    }
    if (count == 0)
    {
        list2.pHead = nullptr;
    }
    secondList->pNext = nullptr;
    return true;
}

std::ostream &operator << (std::ostream &outstream, List &list)
{
    List::Node *node = list.pHead;
    while (node != nullptr)
    {
        outstream << node->value << " ";
        node = node->pNext;
    }
    return outstream;
}

List::Node* List::operator[](int index)
{
    Node *node = pHead;
    for (int i = 0; i < index; i++)
    {
        node = node->pNext;
    }
    return node;
}

void List::RemoveLoop(List::Node *loopNode)
{
    Node *curr = loopNode->pNext;
    int count = 1;
    while (curr != loopNode)
    {
        curr = curr->pNext;
        count++;
    }
    loopNode = pHead;
    curr = pHead;
    for (int i = 0; i < count; i++)
    {
        curr = curr->pNext;
    }
    while (loopNode != curr)
    {
        loopNode = loopNode->pNext;
        curr = curr->pNext;
    }
    loopNode = pHead;
    while (loopNode != curr)
    {
        loopNode = loopNode->pNext;
    }
    int *arr = new int[count];
    for (int i = 0; i < count; i++)
    {
        arr[i] = curr->value;
        curr = curr->pNext;
    }
    for (int i = 1; i < count; i++)
    {
        loopNode->pNext = new Node(arr[i]);
        loopNode = loopNode->pNext;
    }
    loopNode->pNext = nullptr;
    delete[] arr;
}