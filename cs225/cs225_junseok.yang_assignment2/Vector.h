/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Vector.h
Author: junseok.yang
Creation Date:FALL/10/05/2019
    Header file vector, cs225 assignment2 ,template class file
******************************************************************************/
#pragma once

template<typename T>
class Vector
{
    int vecCount;
    int vecCapacity;
    int vecCapacityInit;
    T* vecMalloc;

public:

    class Iterator
    {
        T* vecBuffer;
        Iterator(T* vecBuffer) : vecBuffer(vecBuffer) {}
        friend class Vector;
    public:
        //~Iterator();
        Iterator &operator++(); // Pre increment
        Iterator operator++(int); // Post increment.  Note here, this returns a copy of the Iterator from before the value was incremented. The int param is unused and should be unnamed
        Iterator &operator--(); // Pre decrement 
        Iterator operator--(int); // Post decrement.  Note here, this returns a copy of the Iterator from before the value was incremented. The int param is unused and should unnamed
        bool operator !=(const Iterator &rhs) const;
        bool operator ==(const Iterator &rhs) const;
        bool operator <=(const Iterator &rhs) const;
        bool operator >=(const Iterator &rhs) const;
        bool operator <(const Iterator &rhs) const;
        bool operator >(const Iterator &rhs) const;
        T &operator *();
        Iterator operator +(int offset);
        Iterator operator -(int offset);
    private:
    };

    Vector();
    ~Vector();
    Vector(const Vector<T> &) = delete;
    Vector<T> operator =(const Vector<T> &) = delete;
    void PushBack(const T& value);//
    void Remove(Iterator location);
    void Insert(Iterator location, const T& value);
    T &operator[](int index);
    int Count() const;
    int Capacity() const;
    Iterator Begin() const;	//Iterator to the start of your data
    Iterator End() const;	//Iterator to the end of your data, this should not be a valid 
    Iterator Find(const T& value);
};

#include "Vector.hpp"//template class vector so, linked vector hpp file






