/* Start Header --------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: bitciper.cpp
Purpose: Assignment 4 Bit Cipher with Proxy
Project: Bit Cipher
Author: junseok yang
Creation date: 2019/11/13
- End Header ----------------------------------------------------------------
 */

#include <iostream> // add the std func
#include <vector>   // add the vector
#include "cipher.h" // include cipher header file

std::string data = { " etaoinshrdlcumwfgypbvkjxqz" };

class BitStream :public std::vector<char>
{
private:
    struct BitData;
public:
    BitStream() : m_BitIndex(-1), m_ByteIndex(-1) { }
    BitStream(std::vector<char>& compressed) : m_BitIndex(7), m_ByteIndex(0)
    {
        m_BitStream = std::move(compressed);
    }

    BitData operator[](const size_t index)
    {
        return BitData(*this, index);
    }

private:
    int m_Value = 0;
    int m_BitIndex;
    int m_ByteIndex;
    std::vector<char> m_BitStream;

    struct BitData
    {
        BitStream& m_Stream;
        size_t m_Position;
        int m_Bitsize = 7;
        const int m_VecSize = 8;

        BitData();
        BitData(BitStream& p_BitStream, size_t p_Position) :m_Stream(p_BitStream), m_Position(p_Position) {}

        bool EndOfData() const
        {
            return (m_Position + 2) / m_VecSize >= static_cast<int>(m_Stream.m_BitStream.size());
        }

        BitStream& operator=(const char p_Value)
        {
            if (m_Position % m_VecSize == 0)
            {
                m_Stream.push_back(0);
                m_Stream.m_Value = 0;
            }
            m_Stream.at(m_Position / m_VecSize) |= p_Value << m_Bitsize - m_Stream.m_Value;
            m_Stream.m_Value++;
            return m_Stream;
        }

        int operator<<(const int& p_Value)
        {
            return static_cast<bool>(m_Stream.m_BitStream.at(m_Position / m_VecSize) & 1 << m_Bitsize - (m_Position % m_VecSize)) << p_Value;
        }
    };
};

int ReadBits(BitStream& stream, int& index, int numBits) {
    int value = 0;
    for (int i = numBits - 1; i >= 0; --i) {
        value |= stream[index++] << i;
    }
    return value;
}

void SetBits(BitStream& stream, int& index, int value, int numBits) {
    for (int i = numBits - 1; i >= 0; --i) {
        stream[index++] = static_cast<bool>(value & (1 << i));
    }
}

// Counts the number of bits needed to store the given value 
int numBits(int value) {
    int requiredBits = 1;
    while (value >>= 1) {
        requiredBits++;
    }
    return requiredBits;
}

int GetNumGroups() {
    int groupCount = 0;
    int size = data.size();
    while (size > 1 << (groupCount + 1)) {
        groupCount++;
        size -= 1 << (groupCount + 1);
    }
    return groupCount + 1;
}

bool GetGroupAndIndex(char letter, int& groupIndex, int& charIndex) {
    charIndex = data.find(letter);
    if (charIndex == std::string::npos) {
        return false;
    }
    groupIndex = 0;
    while (charIndex >= 1 << (groupIndex + 1)) {
        charIndex -= 1 << (groupIndex + 1);
        groupIndex++;
    }
    return true;
}

char GetLetter(int groupIndex, int charIndex) {
    int charIndexFromGroup = 0;
    while (groupIndex > 0) {
        charIndexFromGroup += 1 << groupIndex;
        groupIndex--;
    }
    return data[charIndexFromGroup + charIndex];
}


std::string decode(std::vector<char> compressed) {
    BitStream stream(compressed);
    int index = 0;
    std::string uncompressed;
    int bitsPerGroup = numBits(GetNumGroups() - 1);

    while (stream[index].EndOfData() == false) {
        int groupIndex = ReadBits(stream, index, bitsPerGroup);
        int charIndex = ReadBits(stream, index, groupIndex + 1);	// charIndex uses groupIndex + 1 bits to store it
        uncompressed += GetLetter(groupIndex, charIndex);
    }
    return uncompressed;
}

std::vector<char> encode(std::string uncompressed) {
    BitStream stream;
    int index = 0;
    int groupIndex, charIndex;
    int bitsPerGroup = numBits(GetNumGroups() - 1);

    for (char c : uncompressed) {
        if (GetGroupAndIndex(c, groupIndex, charIndex) == true) {
            SetBits(stream, index, groupIndex, bitsPerGroup);
            SetBits(stream, index, charIndex, groupIndex + 1); // charIndex uses groupIndex + 1 bits to store it
        }
    }
    return stream;
}