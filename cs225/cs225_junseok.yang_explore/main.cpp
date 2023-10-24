/* Start Header --------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: main.cpp
Purpose: I made a demo to make sure that std::endl was slow.
Project: Assignment - Explore C++
Author: junseok.yang
Creation date: 2019-12-05
- End Header ----------------------------------------------------------------*/
#include <iostream>
#include <chrono>

#define LINE_NUM 10000
#define STR      "OOOOOOOOOO XXXXXXXXXX OOOOOOOOOO XXXXXXXXXX OOOOOOOOOO XXXXXXXXXX OOOOOOOOOO XXXXXXXXXX" 

std::ostream& nl(std::ostream& out)
{
    return out << '\n';
}
void Test_endl()
{
    for (int i = 0; i < LINE_NUM; ++i)
    {
        std::cout << STR << std::endl;
    }
}
void Test_n()
{
    for (int i = 0; i < LINE_NUM; ++i)
    {
        std::cout << STR"\n";
    }
}
void Test_nl()
{
    for (int i = 0; i < LINE_NUM; ++i)
    {
        std::cout << STR << nl;
    }
}
void Test_printfn()
{
    for (int i = 0; i < LINE_NUM; ++i)
    {
        printf(STR"\n");
    }
}

int main(void)
{
    std::chrono::system_clock::time_point endl_start = std::chrono::system_clock::now();
    Test_endl();
    std::chrono::duration<double> endl_sec = std::chrono::system_clock::now() - endl_start;

    std::chrono::system_clock::time_point n_start = std::chrono::system_clock::now();
    Test_n();
    std::chrono::duration<double> n_sec = std::chrono::system_clock::now() - n_start;

    std::chrono::system_clock::time_point nl_start = std::chrono::system_clock::now();
    Test_nl();
    std::chrono::duration<double> nl_sec = std::chrono::system_clock::now() - nl_start;

    std::chrono::system_clock::time_point printfn_start = std::chrono::system_clock::now();
    Test_printfn();
    std::chrono::duration<double> printfn_sec = std::chrono::system_clock::now() - printfn_start;

    std::cout << "Test_endl()      : " << endl_sec.count() << " s" << std::endl;
    std::cout << "Test_n()         : " << n_sec.count() << " s\n";
    std::cout << "Test_nl()        : " << nl_sec.count() << " s" << nl;
    std::cout << "Test_printfn()   : " << printfn_sec.count() << " s\n";

    system("pause");
    return 0;
}