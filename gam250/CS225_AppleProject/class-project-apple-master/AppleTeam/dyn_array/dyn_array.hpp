/************************************************************************
*    File name : dyn_array.hpp
*    Project name : apple
*   Author        Primary author : Junseok Yang
*                secondary author : Seungguk Jang
*    File description : dyn_array
*    2021 summer Semester cs225 class project
*************************************************************************/
#pragma once
struct dyn_array
{
    dyn_array(const int a_length);
    bool& operator[](int i);

    size_t size();

    bool* heap;
    size_t length = 0;
};