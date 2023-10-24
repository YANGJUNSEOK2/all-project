/* Start Header --------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: LocalizeText.cpp
Purpose: Assignment 5 Localize for LocalizeText
Project: Localize
Author: yang junseok
Creation date: 2019-11-28
- End Header ----------------------------------------------------------------
*/
#include "LocalizeText.h"

LocalizedText::LocalizedText() : m_Letter()
{
}

LocalizedText::LocalizedText(std::string letter) : m_Letter(letter)
{
}

LocalizedText::~LocalizedText()
{
}

std::string LocalizedText::ToString(int index)
{
    std::string line;
    std::ifstream inFile(m_Letter);
    std::map<int, std::string> map;
    int str_id = 0x10000;
    if (inFile.is_open())
    {
        while (!inFile.eof())
        {
            if (std::getline(inFile, line))
                map[str_id] = line.substr(line.find("\t") + 1, line.find("\n"));
            str_id++;
        }
        return map[index];
    }
    inFile.close();
    map.clear();
    return {};
}