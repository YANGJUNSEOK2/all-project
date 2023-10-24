/**
    \file        List.h
    \author      junseok.yang
    \par         email: wnstjryang@gmail.com
    \par         course: CS170
    \par         lab: 5
    \date        spring 2019/04/08
    \brief
        make nodes link list
*/
#pragma once
namespace CS170
{
    namespace Lab5
    {
        class List {
        private:
            struct Node {
                Node(int value) : value(value), pNext(nullptr) { }

                Node(int value, Node *next) : value(value), pNext(next) { }

                int value;
                Node *pNext;
               
            };

            Node *pHead;
            Node *pTail;
            
        
        public:
            List() : pHead(nullptr), pTail(nullptr) { }

            ~List()
            {
                Node *toBeDeleted;
                while (pHead != nullptr) {
                    toBeDeleted = pHead;
                    pHead = pHead->pNext;
                    delete toBeDeleted;
                }
            }

            void Print();
            int Count();
            void HasValue(int value);
            int Sum();

            void PushBack(int value);
            void PushFront(int value);
            void Insert(int value, int index);

            void Move(List &source);
            void Copy(const List &source);
            int GetHeadValue();
            int GetTailValue();

        };
    }
}

