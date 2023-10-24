/************************************************************************
*    File name : dyn_array.cpp
*    Project name : apple
*   Author        Primary author : Junseok Yang
*                secondary author : Seungguk Jang
*    File description : dyn_array
*    2021 summer Semester cs225 class project
*************************************************************************/

#include "dyn_array.hpp"

dyn_array::dyn_array(const int a_length) : length(a_length)
{
    heap = new bool[length];
    int size = static_cast<int>(length);
    for (int i = 0; i < size; i++)
    {
        heap[i] = false;
    }
}

size_t dyn_array::size()
{
    return length;
}

bool& dyn_array::operator[](int i)
{
    return heap[i];
}