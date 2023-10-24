#pragma once
#include <fstream>
#include "../Game_Objects/Character_Extern.h"
#include "../Game_Objects/GameObjectExtern.h"
#include "../Game_Objects/Colors.h"

class FileIO
{
public:
    void OpenReadFile(const std::string& filename);
    void OpenWriteFile(const std::string& filename);
    void Load();
    void Save();

    void GetInt(int* fInt);
    void PutInt(int pInt);
    void GetFloat(float* fFloat);
    void PutFloat(float fFloat);
    void GetString(std::string* fString);
    void PutString(std::string fString);
    void GetColor(Color* color);
    void PutColor(Color color);
    void GetBool(bool* fbool);
    void PutBool(bool fbool);
    bool EndOfFile();
    void CloseReadFile();
    void CloseWriteFile();
private:
    std::ifstream m_ifstream;
    std::ofstream m_ofstream;
};