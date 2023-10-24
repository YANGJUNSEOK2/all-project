#pragma once
#include <string>
#include <fstream>

namespace JS_Engine {
    namespace Tools {
        class TextReader {
        public:
            static std::string ReadTextFile(const char *p_Directory) {
                FILE *InputFile = fopen(p_Directory, "rt");
                fseek(InputFile, 0, SEEK_END);
                unsigned long Length = ftell(InputFile);
                char *Data = new char[Length + 1];
                memset(Data, 0, Length + 1);
                fseek(InputFile, 0, SEEK_SET);
                fread(Data, 1, Length, InputFile);
                fclose(InputFile);
                std::string Result(Data);
                delete[] Data;
                return Result;
            }
        };
    }
}