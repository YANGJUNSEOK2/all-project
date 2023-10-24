/*
junseok.yang
assignment8
cs230
spring 2019
*/
#include "Image.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "stb_image.h"

int main(int argc, char* argv[])
{
    if (argc == 1) {          // quit if no arguments
        std::cerr << "Usage: " << argv[0] << " filename[s]\n";
        exit(EXIT_FAILURE);
    }

    std::ifstream file;
    std::string   Read;
    int           count = 0;
    char          value;
    std::filesystem::path filePath = argv[1];
    std::string fileString = filePath.filename().string();
    std::string fileName = fileString.substr(0, fileString.size() - 4);
    std::string filetmp = fileName;
    std::string fileName2 = fileString.substr(0, fileString.size() - 4);
    std::string filetmp2 = fileName2;
    std::string fileIn_fnt = fileName.append("_fnt.inl");
    std::string fileIn_image = fileName2.append("_image.inl");
    std::ofstream file_Out(fileIn_fnt);

    for (int fileIndex = 1; fileIndex < argc; fileIndex++)
    {

        file.open(argv[fileIndex], std::ios_base::in | std::ios_base::binary);

        if (!file.is_open()) {

            std::cerr << "Could not open " << argv[fileIndex] << std::endl;
            std::exit(EXIT_FAILURE);

        }

        if (file.is_open())
        {

            file_Out << "const wchar_t " << filetmp <<"Font[] = {\n";

            while (file.get(value))
            {
                file_Out << "0x" << std::hex << int(value) << "," << std::endl;
                count++;
            }

            file_Out << "};" << std::endl << "const wchar_t " << filetmp <<"FontLength = " << std::dec << count << ";"<<"\n";
        }
        file.clear();
        file.close();
        file_Out.close();
    }

    std::filesystem::path temp = argv[1];
    std::string fontPath = temp.filename().string();
    std::ifstream fileOpen;
    fileOpen.open(fontPath);
    std::string imageFile(fileIn_image);
    std::ofstream file_Out2(imageFile.c_str());
    std::stringstream Linestream;
    std::vector<std::string> vectorPage;
    int pageCount = 0;

    file.open(fontPath, std::ios_base::in | std::ios_base::binary);

    if (file.is_open())
    {

        std::string       Line;
        std::string       Key, Value;
        std::size_t       i;
      
        while (!file.eof())
        {
            getline(file, Line);
            Linestream << Line;
            Linestream >> Read;

            if (Read == "page")
            {
                while (!Linestream.eof())
                {

                    Linestream >> Read;
                    i = Read.find('=');
                    Key = Read.substr(0, i);
                    Value = Read.substr(i + 1);

                    if (Key == "file")

                    {

                        vectorPage.push_back(Value);
                        vectorPage.back() = vectorPage.back().substr(1);
                        vectorPage.back().pop_back();

                    }
                }
            }

        }
    }

    for (auto PNG : vectorPage)
    {
        CS230::Image image;

        image.LoadFromPNG(PNG);

        if (pageCount == 0)
        {
            file_Out2 << "const int " << filetmp2 << "ImageWidth = " << image.GetWidth() << ";" << std::endl;
            file_Out2 << "const int " << filetmp2 << "ImageHeight = " << image.GetHeight() << ";" << std::endl;
        }

            file_Out2 << "const unsigned " << filetmp2  << "_" << pageCount << "[]" << " = {" << std::endl;

            const CS230::Color4ub* pixelPointer = image.GetPixelsPointer();

            for (int i = 0; i < image.GetPixelsBufferBytesSize(); i++)
            {

                int color = pixelPointer[i].alpha << 24 | pixelPointer[i].red << 16 | pixelPointer[i].green << 8 | pixelPointer[i].blue;
                file_Out2 << std::hex << "0x" << color << ",\n";

            }

            file_Out2 << "};" << "\n";
            pageCount++;
        
    }

    file.close();

    return 0;
}
