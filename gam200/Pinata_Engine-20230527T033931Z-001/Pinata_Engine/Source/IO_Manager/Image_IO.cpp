/************************************************************************
*	File name : Image_IO.cpp
*	Project name : Pinata
* Author	    Primary author : Junseok Yang
*			        Secondary author :
*			        Others :
*
*	File description :
*	SUMMER VACATION ~ 2019 Fall Semester
*************************************************************************/
#include <fstream>
#include "Image_IO.hpp"


bool IOManager::ReadFile(std::string p_FilePath, std::vector<unsigned char>& p_Buffer)
{
    std::ifstream file(p_FilePath, std::ios::binary);
    if (file.fail())
    {
        perror(p_FilePath.c_str());
        return false;
    }

    file.seekg(0, std::ios::end);

    int file_Size = static_cast<int>(file.tellg());
    file.seekg(0, std::ios::beg);
    file_Size -= static_cast<int>(file.tellg());

    p_Buffer.resize(file_Size);
    file.read((char*) & (p_Buffer[0]), file_Size);
    file.close();

    return true;
}

bool IOManager::ReadFile(std::string p_FilePath, std::string& p_Buffer)
{
    std::ifstream file(p_FilePath, std::ios::binary);
    if (file.fail()) {
        perror(p_FilePath.c_str());
        return false;
    }

    file.seekg(0, std::ios::end);

    unsigned int file_Size = (unsigned int)file.tellg();
    file.seekg(0, std::ios::beg);
    file_Size -= (unsigned int)file.tellg();

    p_Buffer.resize(file_Size);
    file.read((char*) & (p_Buffer[0]), file_Size);
    file.close();

    return true;
}
