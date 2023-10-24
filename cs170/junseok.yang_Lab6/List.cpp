/*------------------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:List.cpp
Purpose:make nodes link list
Project:lab: 6
Author: junseok.yang
Created:spring 2019/06/17
------------------------------------------------------------------------*/

#include<iostream>  //use std::
#include "List.h"   //link list header
#include <iomanip>  //use std::setw(value)

namespace CS170
{
    namespace Lab6
    {
        std::ostream& operator<<(std::ostream& out, List& list)
        {

            for (List::iterator it = list.Begin(); it != list.End(); it++)
            {
                std::cout.width(5);
                std::cout << *it;
            }
            return out;
        }

        int List::Count() const
        {
            int nodeCount = 0;
            for (List::iterator it = Begin(); it != End(); it++)
            {
                    nodeCount++;
            }
            return nodeCount;
        }

        List::iterator List::Find(int value) const
        {
            for (iterator it = Begin(); it != End(); ++it)
            {
                if (*it == value)
                {
                    std::cout << value << " was found in the list" << std::endl;
                    return it;
                }
            }
            std::cout << value << " was not found in the list" << std::endl;
            return End();
        }

        bool List::IsEmpty() const
        {
            return Begin() == nullptr;
        }

        int List::Sum()
        {
            int sumNode = 0;
            for (List::iterator it = Begin(); it != End(); it++)
            {
                sumNode += it->value;
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
            if (index <= 0)
            {
                PushFront(value);
            }
            else if (index > Count() - 1)
            {
                PushBack(value);
            }
            else
            {
                Node *temp = pHead;
                Node *temp2 = pHead->pNext;
                for (int i = 0; i < index - 1; i++)
                {

                    temp = temp->pNext;
                    temp2 = temp2->pNext;
                }

                temp2 = new Node(value, temp2);
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

        void List::Splice(iterator where, List& source)
        {
            if (where == End())
                return;

            source.pTail->pNext = where->pNext;
            where->pNext = source.pHead;

            if(where==Last())
            {
                pTail = source.pTail;
            }

            source.pHead = nullptr;
            source.pTail = nullptr;
        }

        void List::Remove(iterator which)
        {
            Node *pList = NULL;
            Node *remove = pHead;

            Node *pList2 = pHead;
           if(which==pHead)
           {
               pList = pHead;
               pHead = which->pNext;

               delete pList;
           }
           else
           {
               while (remove->pNext->value != which->value)
               {
                   remove = remove->pNext;
               }

               pList = remove->pNext;
               remove->pNext = remove->pNext->pNext;

               delete pList;

               while (pList2 != nullptr)
               {
                   pTail = pList2;
                   pList2 = pList2->pNext;
               }

           }
        }

        List::iterator List::Begin() const
        {
            return iterator(pHead);
        }

        List::iterator List::Last() const
        {
            return iterator(pTail);
        }

        List::iterator List::End() const
        {
            return iterator(nullptr);
        }

        List::iterator& List::iterator::operator++()
        {
            node = node->pNext;
            return *this;
        }

        List::iterator List::iterator::operator++(int)
        {
            Node* oldValue = node;
            node = node->pNext;
            return iterator(oldValue);
        }

        bool List::iterator::operator!=(List::iterator rhs)
        {
            return node != rhs.node;
        }

        bool List::iterator::operator==(iterator rhs)
        {
            return node == rhs.node;
        }


        int& List::iterator::operator*()
        {
            return node->value;
        }

        List::iterator& List::iterator::operator=(int value)
        {
            node->value = value;
            return *this;
        }

        List::Node* List::iterator::operator->()
        {
            return node;
        }

    }
}
