/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vector.hpp
Author: junseok.yang
Creation Date:FALL/10/05/2019
    Header file vector link,  cs225 assignment2, template class file
******************************************************************************/
#pragma once
#include "Vector.h"//link vector header
#include <iostream>//std::cout,std::endl

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator++()
{
    vecBuffer++;
    return(*this);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int)
{
    Iterator count(*this);
    vecBuffer++;
    return count;
}

template <typename T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator--()
{
    vecBuffer--;
    return(*this);
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator--(int)
{
    Iterator count(*this);
    vecBuffer--;
    return count;
}

template <typename T>
T& Vector<T>::Iterator::operator*()
{
    return *vecBuffer;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator+(int offset)
{
    return vecBuffer + offset;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator-(int offset)
{
    return vecBuffer - offset;
}

template <typename T>
Vector<T>::Vector() : vecCount(0), vecCapacity(0), vecCapacityInit(8), vecMalloc((T *)malloc(vecCapacity * sizeof(T)))
{
    if (vecMalloc == nullptr)
    {
        throw std::out_of_range("CTOR Malloc is not been executed!!");
    }
}

template <typename T>
Vector<T>::~Vector()
{
    free(vecMalloc);
}

template <typename T>
bool Vector<T>::Iterator::operator>(const Iterator& rhs) const
{
    return this->vecBuffer > rhs.vecBuffer;
}

template <typename T>
bool Vector<T>::Iterator::operator<(const Iterator& rhs) const
{
    return this->vecBuffer < rhs.vecBuffer;
}

template <typename T>
bool Vector<T>::Iterator::operator>=(const Iterator& rhs) const
{
    return this->vecBuffer >= rhs.vecBuffer;
}

template <typename T>
bool Vector<T>::Iterator::operator<=(const Iterator& rhs) const
{
    return this->vecBuffer <= rhs.vecBuffer;
}

template <typename T>
bool Vector<T>::Iterator::operator==(const Iterator& rhs) const
{
    return this->vecBuffer == rhs.vecBuffer;
}

template <typename T>
bool Vector<T>::Iterator::operator!=(const Iterator& rhs) const
{
    return this->vecBuffer != rhs.vecBuffer;
}

template <typename T>
void Vector<T>::PushBack(const T& value)
{
    try
    {
        Insert(End() - 1, value);
        if (value < 0)
        {
            throw value;
            throw std::out_of_range("Exception error");
        }
    }
    catch (T& value)
    {
        std::cout << "Exception PushBack!! : " << " push the minus value!! (" << value << ")" << std::endl;
    }
}

template <typename T>
void Vector<T>::Remove(Iterator location)
{
    try
    {
        T index = static_cast<T>(location.vecBuffer - vecMalloc);

        for (int n = index + 1; n < vecCount; n++)
        {
            vecMalloc[n - 1] = vecMalloc[n];
        }
        vecCount--;
        if (index >= vecCount)
        {
            throw std::out_of_range("Exception with invalid index!!");
        }
    }
    catch (std::out_of_range& e)
    {
        std::cout << "Exception Remove!! : " << e.what() << std::endl;
    }
}

template <typename T>
void Vector<T>::Insert(Iterator location, const T& value)
{
    int vecLocation = static_cast<int>(location.vecBuffer - vecMalloc);
    if (vecCount == vecCapacity)
    {
        vecCapacity = vecCapacityInit;
        vecCapacityInit = vecCapacityInit * 2;
        vecMalloc = (T *)realloc(vecMalloc, sizeof(T) * vecCapacityInit);
    }
    for (int n = vecCount; n > vecLocation + 1; n--)
    {
        vecMalloc[n] = vecMalloc[n - 1];
    }
    (vecMalloc[vecLocation + 1]) = (value);
    vecCount++;
    if (location == nullptr && value < 0)
    {
        throw std::out_of_range("Out of range vecCount!!");
    }

}

template <typename T>
T& Vector<T>::operator[](int index)
{
    try
    {
        if (index < vecCount && index >= 0)
        {
            return vecMalloc[index];
        }
        if (index >= vecCount)
        {
            throw std::out_of_range("Used an invalid index!!");
        }
        if (index < 0)
        {
            throw std::out_of_range("Used an invalid index!!");
        }
    }
    catch (std::out_of_range& e)
    {
        std::cout << "Exception operator[]!! : " << e.what();
    }
    return vecMalloc[0];
}

template <typename T>
int Vector<T>::Count() const
{
    return vecCount;
}

template <typename T>
int Vector<T>::Capacity() const
{
    return vecCapacity;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::End() const
{
    return vecMalloc + vecCount;
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Find(const T& value)
{
    typename Vector<T>::Iterator it = NULL;
    for (it = Begin(); it != End(); it++)
    {
        if (*it == value)
        {
            return it;
        }
    }
    if (*it != value)
    {
        throw std::out_of_range("Used an invalid index!!");
    }
    return End();
}

template <typename T>
typename Vector<T>::Iterator Vector<T>::Begin() const
{
    return vecMalloc;
}

template<class T>
std::ostream& operator<<(std::ostream& out, Vector<T>& vector)
{
    for (typename Vector<T>::Iterator it = vector.Begin(); it != vector.End(); it++)
    {
        std::cout << *it << "  ";
    }
    return out;
}
