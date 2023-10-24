/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: array.cpp
Author: junseok.yang
Creation Date:FALL/10/30/2019
    Source file Array,  cs225 assignment3, Make the ~Array() and  operator=.
******************************************************************************/
#include "array.h" // link array header

CS225::Array::Array(int * array,
    unsigned int _size,
    const ElementFactory* _pElementFactory
)
    : data(new AbstractElement*[_size]), size(_size),
    pElementFactory(_pElementFactory), m_Shared(new int)
{
    for (unsigned int i = 0; i < size; ++i) {
        //create Element with id = 1 (that is Element1 )
        data[i] = pElementFactory->MakeElement(1, array[i]);
    }
    *this->m_Shared = 1;
}

CS225::Array::Array(const Array & rhs) : data(rhs.data), size(rhs.size),
pElementFactory(rhs.pElementFactory), m_Shared(rhs.m_Shared)
{
    ++(*this->m_Shared);
}

CS225::Array::~Array()
{
    DeleteData();
}

int CS225::Array::Get(unsigned int pos) const
{
    return this->data[pos]->Get();
}

void CS225::Array::Set(int id, int pos, int value) {
    //setter will delete the old and create new 
    //slightly inefficient if new and old have the same type

    DeepCopy();
    delete this->data[pos];
    this->data[pos] = this->pElementFactory->MakeElement(id, value);
}

void CS225::Array::Print() const {
    for (unsigned int i = 0; i < this->size; ++i) this->data[i]->Print();
    std::cout << std::endl;
}

CS225::Array& CS225::Array::operator=(const Array& rhs)
{
    if (this != &rhs)
    {
        if (this->m_Shared != nullptr)
        {
            DeleteData();
        }
        this->size = rhs.size;
        this->data = rhs.data;
        this->m_Shared = rhs.m_Shared;
        ++(*this->m_Shared);
    }
    return *this;
}

void CS225::Array::DeleteData()
{
    --(*this->m_Shared);
    if (*this->m_Shared == 0)
    {
        for (unsigned int i = 0; i < this->size; i++)
        {
            delete this->data[i];
        }
        delete this->m_Shared;
        delete[] this->data;
    }
}

void CS225::Array::DeepCopy()
{
    if (*this->m_Shared > 1)
    {
        AbstractElement** tmp_Data(new AbstractElement*[this->size]);
        for (unsigned int i = 0; i < this->size; ++i)
        {
            tmp_Data[i] = this->data[i]->clone();
        }
        this->data = tmp_Data;

        --(*this->m_Shared);
        this->m_Shared = new int(1);
    }
}