/* Start Header --------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: cipher.cpp
Purpose: make the encode and decode function.
This is the source file to be used for the bit cipher assignment,
change the encode and decode format. (re-submission)
Project: CS225.Assignment1 Bit Cipher
Author: junseok yang
Creation date: 2019/10/05
- End Header ----------------------------------------------------------------
*/

#include <string> // to use std::string
#include <vector> // to use std::vector
#include "cipher.h"// link header

namespace
{
    const int NUMGROUPS = 4;
    std::string groups[NUMGROUPS] = { " e", "taoi", "nshrdlcu", "mwfgypbvkjxqz" };
    const int BIT_SIZE_ZERO = 0;
    const int BIT_SIZE_ONE = 1;
    const int G_BIT = 2;
    const int BIT_SIZE = 3;
    const int BINARY_SIZE = 7;
}

std::vector<char> encode(std::string uncompressed)
{
    std::vector<char> group_Box{};
    std::vector<char> char_Box{};
    std::vector<char> binary_Box{};
    std::vector<char>binary_Vec{};
    std::vector<char>binary_Re{};

    int tmp = 0, character = 0, bit_Num = 7, characterCount = 0, group = 0, Character = 0,
    ChaNum = 0,prev_size = 0, binary_size = 0,current_size = 0;
    char decimal = 0;

    for (int i = 0; i < static_cast<int>(uncompressed.size()); i++)
    {
        for (int g = 0; g < NUMGROUPS; g++)
        {
            character = static_cast<unsigned int>(groups[g].find(uncompressed[i]));
            if (groups[g].find(uncompressed[i]) != std::string::npos)
            {
                group_Box.push_back(static_cast<char>(g)); //Group location push_back
                char_Box.push_back(static_cast<char>(character));//Char location push_back

                characterCount++;
            }
        }
    }

    for (int i = 0; i < characterCount; i++)
    {
        group = group_Box.at(i);
        Character = char_Box.at(i);
        ChaNum = group + 1;

        for (int j = 0; j < ChaNum; j++)
        {
            if ((Character & 0x01) == 1)
            {
                binary_Box.push_back(1);
            }
            else
            {
                binary_Box.push_back(0);
            }
            Character = Character >> 1;
        }

        for (int j = 0; j < G_BIT; j++)
        {
            if ((group & 0x01) == 1)
            {
                binary_Box.push_back(1);
            }
            else
            {
                binary_Box.push_back(0);
            }
            group = group >> 1;
        }

        prev_size = binary_size;
        binary_size = static_cast<unsigned int>(binary_Box.size());
        current_size = binary_size - prev_size;

        for (int z = 0; z < current_size; z++)
        {
            binary_Re.push_back(binary_Box[binary_size - z - 1]);
        }
    }
    int binary_Re_Size = static_cast<unsigned int>(binary_Re.size());
    for (int i = 0; i < binary_Re_Size; i++)
    {
        if (bit_Num == -1)//When the bit index is -1, it initializes to 7.
        {
            decimal = static_cast<char>(tmp);
            binary_Vec.push_back(decimal);//push back the decimal values in binary_Vec.
            bit_Num = BINARY_SIZE;
            decimal = 0;
            tmp = 0;
        }

        if (binary_Re[i] == 1)
        {
            tmp += (1 << bit_Num);
        }
        else
        {
            tmp += (0 << bit_Num);
        }//Store the information of 'binary_Box' in 'tmp'.

        bit_Num--;

        if (i == binary_Re_Size - 1)
        {
            decimal = static_cast<char>(tmp);
            binary_Vec.push_back(decimal);
        }
    }
    return binary_Vec;
}

std::string decode(std::vector<char> p_String)
{
    std::string decode_Box{};
    std::vector<char> bit_Arr{};
    int bit_Size = 0;
    int group_Location = 0, bitSize = 0, group_Temp = 0, index_Size = 0, index_Temp = 0, group_Next = 0;
    char character = 0;
    unsigned int index_Char = 0;

    for (char c : p_String) {
        for (int bitIndex = BINARY_SIZE; bitIndex >= 0; --bitIndex) {

            if (c & (1 << bitIndex)) {
                bit_Arr.push_back(BIT_SIZE_ONE);
            }
            else {
                bit_Arr.push_back(BIT_SIZE_ZERO);
            }
            bit_Size++;
        }
    }

    group_Location = 0;
    bitSize = bit_Size / BIT_SIZE;

    for (int i = 0; i < bitSize; i++)
    {
        unsigned int group = 0;
        int index = 0;
        for (int j = 0; j < G_BIT; j++)
        {
            if (group_Location < bit_Size - 1)
            {
                group = group<< 1;
                group |= bit_Arr[group_Location + j];
            }
        }
        group_Temp = group_Location;

        index = group + 1;
        index_Temp = group_Temp;

        if (group_Temp != bit_Size - 1)
        {
            index_Temp = group_Temp + G_BIT;
        }

        index_Char = 0;
        index_Size = 0;
        group_Next = group + BIT_SIZE;
        int index_Bit_Size = index_Temp + index_Size;
        for (int j = 0; j < index; j++)
        {
            if (index_Bit_Size < bit_Size)
            {
                index_Char = index_Char << 1;
                index_Char |= bit_Arr[index_Temp + index_Size];
            }
            index_Size++;
        }

        character = groups[group].at(index_Char);
        decode_Box.push_back(character);

        group_Location += group_Next;
    }
    return decode_Box;
}