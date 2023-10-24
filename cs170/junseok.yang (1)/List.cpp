/**
    \file        List.cpp
    \author      junseok.yang
    \par         email: wnstjryang@gmail.com
    \par         course: CS170
    \par         lab: 5
    \date        spring 2019/04/08
    \brief
        make nodes link list
*/
#include<iostream>
#include "List.h"
#include <iomanip>  //use std::setw(value)

namespace CS170
{
    namespace Lab5
    {
       
        void List::Print()
        {
            Node *pList = pHead;
            while (pList != nullptr) {
                std::cout<<std::setw(5) << pList->value;
                pList = pList->pNext;
            }
        }

        int List::Count()
        {
            Node *pList = pHead;
            int nodeCount = 0;
            while (pList != nullptr)
            {
                 pList = pList->pNext;
                 nodeCount++;
            }
         return nodeCount;
        }

        void List::HasValue(int value)
        {
            Node *pList = pHead;

            bool isValue = NULL;

            while (pList != nullptr) {

                if (value == pList->value)
                {
                    isValue = true;
                }
                pList = pList->pNext;
            }
            if (isValue == true)
            {
                //pList = pList->pNext;
                std::cout << value << " was found in the list" << std::endl;

            }
            else if (isValue == false)
            {
                //pList = pList->pNext;
                std::cout << value << " was not found in the list" << std::endl;

            }
        }

        int List::Sum()
        {
            Node *pList = pHead;
            int sumNode = 0;
            while (pList != nullptr)
            {
                sumNode += pList->value;
                pList = pList->pNext;

            }
            return sumNode;
        }

        void List::PushBack(int value)
        {
            if (pTail == nullptr)
            {
                pTail = new Node(value);
                pHead = pTail;
            }
            else
            {
                Node *temp = pTail;
                pTail = new Node(value);
                temp->pNext = pTail;
            }
            
        }

        void List::PushFront(int value)
        {
            if (pHead != nullptr)
            {
                pHead = new Node(value, pHead);
            }
            else
            {
                pHead = new Node(value);
                pTail = pHead;
            }
        }

        void List::Insert(int value, int index)
        {
            if(index<=0)
            {
                PushFront(value);
            }
            else if(index>Count()-1)
            {
                PushBack(value);
            }
            else
            {
                Node *temp = pHead;
                Node *temp2 = pHead->pNext;
                for(int i=0;i<index-1;i++)
                {
                    
                    temp = temp->pNext;
                    temp2 = temp2->pNext;
                }
                
                temp2 = new Node(value,temp2);
                temp->pNext = temp2;
            }
        }

        void List::Move(List &source)
        {
            //test8
            Node *pList = source.pHead;

            pTail->pNext = pList;
            
            pTail = source.pTail;
       
            source.pHead = nullptr;
            source.pTail = nullptr;            
        }

        void List::Copy(const List &source)
        {
            //test9
            Node *pList = source.pHead;

            while (pList != nullptr)
            {
                PushBack(pList->value);
                pList = pList->pNext;
            }
        }

        int List::GetHeadValue()
        {
            if(pHead==nullptr)
            {
                return 0;
            }
            else
            {
                int value = pHead->value;
                return value;
            }
        }
        int List::GetTailValue()
        {
            if(pTail==nullptr)
            {
                return 0;
            }
            else
            {
                int value = pTail->value;
                return value;
            }
        }

    }
}
