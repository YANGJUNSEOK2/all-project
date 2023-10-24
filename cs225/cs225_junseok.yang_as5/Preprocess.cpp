/* Start Header --------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Preprocess.cpp
Purpose: Assignment 5 Localize for Preprocess
Project: Localize
Author: yang junseok
Creation date: 2019-11-28
- End Header ----------------------------------------------------------------
*/
#include <fstream>
#include <string>
#include <map>

void readFile(std::string inFileName, std::string outFileName, std::map<int, std::string> map)
{
    std::ifstream inFile(inFileName);
    std::ofstream outFile(outFileName);
    std::string line;

    std::map<std::string, std::string> secondChar;
    int str_id = 0x10000;
    bool italy = false;
    if (inFile.is_open())
    {
        while (!inFile.eof())
        {
            std::getline(inFile, line);
            secondChar.insert(std::make_pair(line.substr(0, line.find('\t')), line.substr(line.find('\t') + 1)));
            str_id++;
        }

        for (auto it = map.begin(); it != map.end(); ++it)
        {
            for (auto compare = secondChar.begin(); compare != secondChar.end(); ++compare)
            {
                if (it->second == compare->first)
                {
                   
                    outFile << std::hex << it->first << "\t" << compare->second << std::endl;
                    italy = true;
                    break;
                }
                else
                {
                    italy = false;
                }
            }
            if(italy ==false)
            {
                outFile << it->first << "\t"<< it->second << std::endl;
                italy = true;
            }
        }
    }
    inFile.close();
    outFile.close();
    secondChar.clear();
}

int main(int argc, char *argv[])
{
    std::ifstream in_TXT_File("English.txt");
    std::ofstream out_H_File("Strings.h");
    std::string line;
    std::map<int, std::string> firstChar;

    int str_id = 0x10000;

    if (out_H_File.is_open())
    {
        out_H_File << "#pragma once" << std::endl;
    }

    if (in_TXT_File.is_open())
    {
        while (!in_TXT_File.eof())
        {
            std::getline(in_TXT_File, line);
            firstChar.insert(std::make_pair(str_id, line.substr(0, line.find('\t'))));

            if (out_H_File.is_open())
            {
                out_H_File << "#define\t" << firstChar[str_id] << "\t" << std::hex << "0x" << str_id << std::endl;
            }
            str_id++;
        }
    }
    in_TXT_File.close();
    out_H_File.close();
    readFile("English.txt", "English.dat", firstChar);
    readFile("Korean.txt", "Korean.dat", firstChar);
    readFile("French.txt", "French.dat", firstChar);
    readFile("Spanish.txt", "Spanish.dat", firstChar);
    readFile("Italian.txt", "Italian.dat", firstChar);
    firstChar.clear();
    return 0;
}