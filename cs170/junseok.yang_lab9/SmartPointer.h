/*------------------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: SmartPointer.h
Purpose: make unique pointre and shared pointer
Project: Lab9
Author: Junseok.yang
Created: 2019/06/09
------------------------------------------------------------------------*/
#pragma once
#include <Memory>
template <class T>  class UniquePtr
{
    T *ptr;  // Actual pointer 
public:
    // Constructor 
    explicit UniquePtr(T *p) { ptr = p; }

    // Destructor 
    ~UniquePtr() { delete(ptr); }

    T & operator * () { return *ptr; }

    T * operator -> () { return ptr; }

    void operator = (T *p)
    {
        delete ptr;
        ptr = p;
    }
};

template <class T> class SharedPtr
{
public:
    // Constructor 
    explicit  SharedPtr(T *p)
    {
        count = new int;
        *count = 1;
        ptr = p;
    }
    SharedPtr()
    {
        count = new int;
    }
    SharedPtr(SharedPtr& p)
    {
        (*(p.count))++;
        ptr = p.ptr;
        count = p.count;
    }

    // Destructor 
    ~SharedPtr()
    {
        Reset();
    }

    T & operator * () { return *ptr; }

    T * operator -> () { return ptr; }

    void operator = (T *p)
    {
        Reset();
        ptr = p;
        delete p;
    }

    void operator=(SharedPtr& p)
    {
        Reset();
        ptr = p.ptr;
        *(p.count) = *(p.count) + 1;
        count = p.count;
    }

    void Reset()
    {
        (*count)--;
        if (*count == 0)
        {
            delete count;
            delete ptr;
        }
    }

    T* getValue() { return ptr; }

private:
    T *ptr;
    int *count = nullptr;
};