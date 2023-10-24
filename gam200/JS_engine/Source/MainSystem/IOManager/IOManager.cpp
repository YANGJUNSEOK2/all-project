#include "IOManager.hpp"
#include <fstream>

namespace JS_Engine {
    namespace MainSystem {
        bool IOManager::readFileToBuffer(std::string p_FilePath, std::vector<unsigned char>& p_Buffer)
        {
            std::ifstream file(p_FilePath, std::ios::binary);
            if(file.fail())
            {
                perror(p_FilePath.c_str());
                return false;
            }

            //seek to the end
            file.seekg(0, std::ios::end);

            //get the file size
            int fileSize = file.tellg();
            file.seekg(0, std::ios::beg);

            //Reduce the file size by any header bytes that might be present
            fileSize -= file.tellg();

            p_Buffer.resize(fileSize);
            file.read((char*)&(p_Buffer[0]),fileSize);
            file.close();

            return true;
        }
    }
}