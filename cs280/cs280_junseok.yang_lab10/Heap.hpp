/******************************************************************
Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.

File Name: Heap.hpp
Project: Lab 8 - Heaps
Author: junseok yang
Creation date: 5/17 2021
******************************************************************/

#pragma once

#include <iomanip>
#include <iostream>
#include <string>
#include "Heap.h"

template<class T>
std::ostream& operator<<(std::ostream& out, Heap<T>& heap) {
    if (heap.data.empty() == false) {
        for (int i = 0; i < static_cast<int>(heap.data.size()) - 1; i++) {
            out << std::setw(3) << heap.data[i] << ",  ";
        }
        out << std::setw(3) << heap.data.back();
    }
    return out;
}

//template<>
//std::ostream& operator<<(std::ostream& out, Heap<std::string>& heap) {
//    for (unsigned int i = 0; i < heap.data.size() - 1; i++) {
//        out << heap.data[i] << ",  ";
//    }
//    out << heap.data.back();
//    return out;
//}
////////////////////////////////////////////////////////
template<class T>
inline Heap<T>::Heap(bool(*compareFunc)(const T& a, const T& b))
    : compareFunc(compareFunc)
{
    data.clear();
}

template<class T>
inline Heap<T>::Heap(T* items, int numOfItems, bool(*compareFunc)(const T& a, const T& b))
    :compareFunc(compareFunc)
{
    for (int i = 0; i < numOfItems; i++)
    {
        data.push_back(items[i]);
    }

    Heapify(&data[0], numOfItems);
}

template<class T>
inline void Heap<T>::greaterHeapify(T* items, int numOfItems, int pos)
{
    T* tmpItems = items;
    int largest = pos;
    int left = 2 * pos + 1;
    int right = 2 * pos + 2;

    if (right < numOfItems)
    {
        if (compareFunc(items[right], items[largest]))
        {
            largest = right;
        }
    }
    if (left < numOfItems)
    {
        if (compareFunc(items[left], items[largest]))
        {
            largest = left;
        }
    }
    if (largest != pos)
    {
        std::swap(items[pos], items[largest]);
        //std::cout << "Swap:\t" << *this << std::endl;
        greaterHeapify(&tmpItems[0], numOfItems, largest);
    }
}

template<class T>
inline void Heap<T>::lessHeapify(int pos)
{
    int parent = (pos - 1) / 2;

    if (compareFunc(data[pos], data[parent]))
    {
        std::swap(data[pos], data[parent]);
        //std::cout << "Swap:\t" << *this << std::endl;

        lessHeapify(parent);
    }
}


template<class T>
inline void Heap<T>::Heapify(T* items, int numOfItems)
{
    for (int i = numOfItems / 2; i >= 0; --i)
    {
        greaterHeapify(items, numOfItems, i);
    }
}

template<class T>
inline void Heap<T>::Push(T newItem)
{
    data.push_back(newItem);
    //std::cout << "Push:\t" << *this << std::endl;
    lessHeapify(static_cast<int>(data.size() - 1));
}

template<class T>
inline T Heap<T>::Pop()
{
    T tmp = data[0];
    std::swap(data[0], data[data.size() - 1]);
    data.pop_back();
    //std::cout << "Pop:\t" << *this << std::endl;
    if (data.size() != 0)
    {
        greaterHeapify(&data[0], static_cast<int>(data.size()), 0);
    }
    return tmp;

}

template<class T>
inline bool Heap<T>::IsEmpty()
{
    if (data.data() != nullptr)
        return (data.size() == 0);
    return false;
}

template<class T>
inline bool Heap<T>::found(T c)
{
    for (auto i = data.begin(); i != data.end(); i++)
    {
        if(*i == c)
        {
            return true;
        }
    }
    return false;
}

template<class T>
inline void Heap<T>::Sort()
{
    Heapify(&data[0], data.size() / 2);

    for (int count = 1; count <= data.size(); ++count)
    {
        Heapify(&data[count - 1], data.size() - count);
    }
}

template<class T>
inline void Heap<T>::Update(typename std::vector<T>::iterator i)
{
    for (i = data.begin(); i < data.end(); i++)
    {
        Heapify(&data[0], static_cast<int>(data.size() - 1));
    }
}