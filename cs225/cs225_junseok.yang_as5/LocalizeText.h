/* Start Header --------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: LocalizeText.h
Purpose: Assignment 5 Localize for LocalizeText
Project: Localize
Author: yang junseok
Creation date: 2019-11-28
- End Header ----------------------------------------------------------------
*/
#include <string>
#include <fstream>
#include <map>

class LocalizedText 
{
public:
    LocalizedText();
    LocalizedText(std::string letter);
    ~LocalizedText();
    std::string ToString(int index);
private:
    std::string m_Letter;
};



