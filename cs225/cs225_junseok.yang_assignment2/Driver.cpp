/******************************************************************************
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Driver.cpp
Author: junseok.yang
Creation Date:FALL/10/05/2019
    driver file,  cs225 assignment2, fixed try catch Exception Throw
******************************************************************************/
#include <iostream> //std::cout, std::endl
#include "Vector.h"//link vector header

void test1() {
    try
    {
        Vector<int> vec;

        for (int i = 1; i <= 20; i++) {
            vec.PushBack(i);
            std::cout << "Current Size: " << vec.Count() << "   Capacity: " << vec.Capacity() << std::endl;
        }

        std::cout << vec << std::endl;
    }
    catch (std::out_of_range& e)
    {
        std::cout << "Exception Vector()!! : " << e.what() << std::endl;
    }
}

void test2() {
    try
    {
        Vector<int> vec;

        for (int i = 1; i <= 20; i++) {
            vec.PushBack(i);
        }

        std::cout << vec[0] << "  " << vec[4] << "  " << vec[9] << "  " << vec[14] << "  " << vec[19] << std::endl;
    }
    catch (std::out_of_range& e)
    {
        std::cout << "Exception operator[]!! : " << e.what();
    }
}

void test3() {
    try
    {
        Vector<int> vec;

        for (int i = 1; i <= 20; i++) {
            vec.PushBack(i);
        }

        std::cout << *vec.Find(5) << "  " << *vec.Find(15) << std::endl;
    }
    catch (std::out_of_range& e)
    {
        std::cout << "Exception Find!! : " << e.what() << std::endl;
    }
}

void test4() {
    try
    {
        Vector<int> vec;

        for (int i = 1; i <= 20; i++) {
            vec.PushBack(i);
        }

        vec.Remove(vec.Find(5));
        vec.Remove(vec.Find(15));
        vec.Remove(vec.Find(12));
        vec.Remove(vec.Find(19));
        vec.Remove(vec.Find(7));
        vec.Remove(vec.Find(2));
        std::cout << vec << std::endl;
    }
    catch (std::out_of_range& e)
    {
        std::cout << "Exception Remove!! : " << e.what() << std::endl;
    }
}

void test5() {
    try
    {
        Vector<int> vec;

        for (int i = 1; i <= 10; i++) {
            vec.PushBack(i);
        }

        vec.Insert(vec.Find(5), 11);
        vec.Insert(vec.Find(2), 12);
        vec.Insert(vec.Find(7), 13);
        vec.Insert(vec.Find(9), 14);
        vec.Insert(vec.Find(1), 15);
        vec.Insert(vec.Find(5), 16);
        std::cout << vec << std::endl;
    }
    catch (std::out_of_range& e)
    {
        std::cout << "Exception Insert!! : " << e.what() << std::endl;
    }
}

void test6() {
    try
    {
        Vector<char> charVec;
        for (char i = 'a'; i <= 'z'; i++) {
            charVec.PushBack(i);
        }
        std::cout << charVec << std::endl;

        Vector<double> doubleVec;
        for (int i = 1; i <= 10; i++) {
            doubleVec.PushBack(i / 10.0);
        }
        std::cout << doubleVec << std::endl;
    }
    catch (std::out_of_range& e)
    {
        std::cout << "Exception PushBack!! : " << e.what() << std::endl;
    }
}

void test7CTOR()
{
    try
    {
        std::cout << "[test7CTOR] " << std::endl;
        Vector<int> ctor;
    }
    catch (std::out_of_range& e)
    {
        std::cout << "Exception Vector()!! : " << e.what() << std::endl;
    }
}

void test8PUSH_BACK()
{
    std::cout << "[test8PUSH_BACK] " << std::endl;
    Vector<int> push_Back;
    push_Back.PushBack(-1);
}

void test9REMOVE()
{
    std::cout << "[test9REMOVE] " << std::endl;
    Vector<int> remove;
    remove.PushBack(1);
    remove.Remove(remove.Find(1));
}

void test10INSERT()
{
    try {
        std::cout << "[test10INSERT] " << std::endl;
        Vector<int> insert;
        insert.PushBack(1);
        insert.Insert(insert.Find(0), -1);

    }
    catch (std::out_of_range& e)
    {
        std::cout << "Exception Insert!! : " << e.what() << std::endl;
    }
}

void test11OPERATOR()
{
    std::cout << "[test11OPERATOR] " << std::endl;
    Vector<int> oper;
    oper.PushBack(1);
    std::cout << " : Test out put : (" << oper[-1] << ")" << std::endl;
}

void test12FIND()
{
    try
    {
        std::cout << "[test12FIND] " << std::endl;
        Vector<int> find;
        find.PushBack(1);
        std::cout << " : Test out put : (" << *find.Find(-1) << ")" << std::endl;
    }
    catch (std::out_of_range& e)
    {
        std::cout << "Exception Find!! : " << e.what() << std::endl;
    }
}


int main(int argc, char **argv) {
    int testNum = 12;
    if (argc > 1) {
        testNum = atoi(argv[1]);
    }

    if (testNum == -1) {
        test1();
        test2();
        test3();
        test4();
        test5();
        test6();
        //test7CTOR();
        //test8PUSH_BACK();
        //test9REMOVE();
        //test10INSERT();
        //test11OPERATOR();
        //test12FIND();
    }
    else {
        typedef void(*Test)(void);
        Test Tests[] = {
            test1, test2, test3, test4, test5, test6 , test7CTOR, test8PUSH_BACK, test9REMOVE, test10INSERT, test11OPERATOR, test12FIND
        };

        Tests[testNum - 1]();
    }
}