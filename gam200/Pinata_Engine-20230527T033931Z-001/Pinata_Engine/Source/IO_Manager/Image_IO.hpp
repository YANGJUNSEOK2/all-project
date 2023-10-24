/************************************************************************
*	File name : Image_IO.hpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester
*************************************************************************/
#pragma once
#include <vector>
#include <string>

    class IOManager
    {
    public:
        //file read function
        static bool ReadFile(std::string p_FilePath, std::vector<unsigned char>& p_Buffer);
        static bool ReadFile(std::string p_FilePath, std::string& p_Buffer);
    };
