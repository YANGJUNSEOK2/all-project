/**
    \file        List.cpp
    \author      junseok.yang
    \par         email: wnstjryang@gmail.com
    \par         course: CS170
    \par         lab: 7
    \date        spring 2019/04/08
    \brief
        make nodes link list
*/
#include<iostream>  //use std::
#include "List.h"   //link list header
#include <iomanip>  //use std::setw(value)
#include <experimental/filesystem>

namespace CS170
{
    namespace Lab7
    {
         std::ostream& operator<<(std::ostream& out, List::iterator list)
        {

            for (List::iterator it = list; it != nullptr; it++)
            {
                std::cout.width(5);
                std::cout << *it;
            }
            return out;
        }

        std::ostream& operator<<(std::ostream & out, List::Reverseiterator list)
        {
            for (List::Reverseiterator it = list; it != nullptr; it++)
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
                if (*it)
                {
                    nodeCount++;
                }
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
            if (pHead)
            {
                return false;
            }
            else
                return true;
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
            Node *space = new Node(value);
            if (pHead == nullptr)
            {
                pHead = space;
                pTail = space;
            }
            else
            {
                pTail->pNext = space;
                space->pPrev = pTail;
                pTail = space;
            }
        }
        
        

        void List::PushFront(int value)
        {
            Node *space = new Node(value);
            if (pHead == nullptr)
            {
                pHead = space;
                pTail = space;
            }
            else
            {
                space->pNext = pHead;
                pHead->pPrev = space;
                pHead = space;
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
                temp2->pPrev = temp;
                temp->pNext = temp2;
                temp2->pNext->pPrev = temp2;
            }
        }

        void List::Move(List &source)
        {
            //test8
            Node *pList = source.pHead;

            pTail->pNext = pList;
            pList->pPrev = pTail;
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
            if (where->pNext != nullptr)
            {
                where->pNext->pPrev = source.pTail;
            }
            where->pNext = source.pHead;
            source.pHead->pPrev = where.operator->();

            

            if (where == Last())
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

            if (pHead->pNext == nullptr)
            {
                
                delete pHead;
                pHead = nullptr;
                pTail = nullptr;
                
                return;
            }

            if (which == pHead)
            {
                pList = pHead;
                pHead = which->pNext;
                pHead->pPrev = nullptr;
                
                delete pList;
            }
            else
            {
                if (remove->pNext != nullptr)
                {
                    while (remove->pNext->value != which->value)
                    {
                        remove = remove->pNext;
                    }


                    pList = remove->pNext;

                    remove->pNext = remove->pNext->pNext;
                }
                if (remove->pNext != nullptr)
                {
                    remove->pNext->pPrev = remove;
                }

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

        List::Reverseiterator & List::Reverseiterator::operator++()
        {
            node = node->pPrev;
            return *this;
        }

        List::Reverseiterator List::Reverseiterator::operator++(int)
        {
            Node* oldValue = node;
            node = node->pPrev;
            return Reverseiterator(oldValue);
        }

        bool List::Reverseiterator::operator !=(List::Reverseiterator rhs)
        {
            return node != rhs.node;
        }

        bool List::Reverseiterator::operator==(List::Reverseiterator rhs)
        {
            return node == rhs.node;
        }

        List::Reverseiterator & List::Reverseiterator::operator=(int value)
        {
            node->value = value;
            return *this;
        }

        int& List::Reverseiterator::operator*()
        {
            return node->value;
        }

        List::Node *List::Reverseiterator::operator->()
        {
            return node;
        }

        List::Reverseiterator List::ReverseBegin()const
        {
            return Reverseiterator(pTail);
        }
        List::Reverseiterator List::ReverseEnd()const
        {
            return Reverseiterator(nullptr);
        }
        List::Reverseiterator List::ReverseLast()const
        {
            return Reverseiterator(pHead);
        }
       
    }
}
