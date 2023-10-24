#include "file_IO.h"

void FileIO::OpenReadFile(const std::string& filename)
{
    m_ifstream.open(filename.c_str(), std::ios::in);
}	

void FileIO::OpenWriteFile(const std::string& filename)
{
    m_ofstream.open(filename.c_str(), std::ios::out);
}

void FileIO::Load()
{
    int stage, enemy, character, gameWeapon1, gameWeapon2, gameItem;

    m_ifstream >> stage;
    m_ifstream >> enemy;
    m_ifstream >> character;
    m_ifstream >> player_current_health;
    m_ifstream >> player_current_special_guage;
    m_ifstream >> gameWeapon1;
    m_ifstream >> gameWeapon2;
    m_ifstream >> gameItem;

    Stages = static_cast<Stage>(stage);
    enem_type = static_cast<Enemies>(enemy);
    char_type = static_cast<CharacterType>(character);
    game_weapon[1] = static_cast<Weapons>(gameWeapon1);
    game_weapon[2] = static_cast<Weapons>(gameWeapon2);
    game_item[0] = static_cast<Items>(gameItem);
}

void FileIO::Save()
{
    m_ofstream << Stages << std::endl;
    m_ofstream << enem_type << std::endl;
    m_ofstream << char_type << std::endl;
    m_ofstream << player_current_health << std::endl;
    m_ofstream << player_current_special_guage << std::endl;
    m_ofstream << game_weapon[1] << std::endl;
    m_ofstream << game_weapon[2] << std::endl;
    m_ofstream << game_item[0] << std::endl;
}

void FileIO::GetInt(int* fInt)
{
    std::string s;
    *fInt = atoi(s.c_str());
}

void FileIO::PutInt(int fInt)
{
    m_ofstream << fInt << std::endl;
}

void FileIO::GetFloat(float* fFloat)
{
    m_ifstream >> (*fFloat);
}

void FileIO::PutFloat(float fFloat)
{
    m_ofstream << fFloat << std::endl;
}

void FileIO::GetString(std::string* fString)
{
    char buf[64];
    while (true)
    {
        if (EndOfFile())
        {
            return;
        }

        m_ifstream.getline(buf, 64);
        *fString = buf;

        if (fString->size() > 0 && (*fString)[0] == '#')
        {
            continue;
        }
        if (!fString->empty())
        {
            return;
        }
    }
}

void FileIO::PutString(std::string fString)
{
    m_ofstream << fString << std::endl;
}

void FileIO::GetColor(Color* color)
{
    int R;
    int G;
    int B;
    int A;

    m_ifstream >> R;
    m_ifstream >> G;
    m_ifstream >> B;
    m_ifstream >> A;

    *color = { (GLubyte)R,(GLubyte)G,(GLubyte)B,(GLubyte)A };
}

void FileIO::PutColor(Color color)
{
    m_ofstream << (int)color.r << " "
               << (int)color.g << " "
               << (int)color.b << " "
               << (int)color.a << std::endl;
}

void FileIO::GetBool(bool* fbool)
{
    m_ifstream >> *fbool;
}

void FileIO::PutBool(bool fbool)
{
    m_ofstream << (int)fbool;
}

bool FileIO::EndOfFile()
{
    return m_ifstream.eof() || !m_ifstream.good();
}

void FileIO::CloseReadFile()
{
    m_ifstream.close();
}

void FileIO::CloseWriteFile()
{
    m_ofstream.close();
}
