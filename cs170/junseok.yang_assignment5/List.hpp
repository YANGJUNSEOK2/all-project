/*------------------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: List.hpp
Purpose: make template the node and list
Project: Assignment5
Author: Junseok.yang
Created: 2019/06/09
------------------------------------------------------------------------*/
#include "List.h"
#include <iostream>

namespace CS170
{
    namespace Assignment5
    {
        template<class T>
        std::ostream& operator<<(std::ostream& out, List<T>& list)
        {
            for (typename List<T>::Iterator it = list.Begin(); it != list.End(); it++)
            {
                std::cout.width(5);
                std::cout << *it;
            }
            return out;
        }
  
        std::ostream&operator << (std::ostream &out, List<double>& list)
        {
            for (typename List<double>::Iterator it = list.Begin(); it != list.End(); it++)
            {
                std::cout.precision(4);
                std::cout.width(8);
                std::cout << *it;
            }
            return out;
        }
      
        std::ostream&operator << (std::ostream &out, List<float>& list)
        {
            for (typename List<float>::Iterator it = list.Begin(); it != list.End(); it++)
            {
                std::cout.precision(4);
                std::cout.width(8);
                std::cout << *it;
            }
            return out;
        }

        template <class T>
        typename List<T>::Iterator& List<T>::Iterator::operator++()
        {
            node = node->pNext;
            return *this;
        }

        template <class T>
        typename List<T>::Iterator List<T>::Iterator::operator++(int)
        {
            Node* oldValue = node;
            node = node->pNext;
            return Iterator(oldValue);
        }

        template <class T>
        bool List<T>::Iterator::operator!=(const typename CS170::Assignment5::List<T>::Iterator& rhs)
        {
            return node != rhs.node;
        }

        template <class T>
        bool List<T>::Iterator::operator==(const typename CS170::Assignment5::List<T>::Iterator& rhs)
        {
            return node == rhs.node;
        }

        template <class T>
        T& List<T>::Iterator::operator*()
        {
            return node->value;
        }

        template <class T>
        typename List<T>::Node* List<T>::Iterator::operator->()
        {
            return node;
        }

        template <class T>
        List<T>::List()
        {
            pHead = nullptr;
        }

        template <class T>
        List<T>::~List()
        {
            Node *isdeleted;
            while (pHead != nullptr)
            {
                isdeleted = pHead;
                pHead = pHead->pNext;
                delete isdeleted;
            }
        }

        template <class T>
        int List<T>::Count() const
        {
            int nodeCount = 0;
            for (Iterator it = Begin(); it != End(); it++)
            {
                if (*it)
                {
                    nodeCount++;
                }
            }
            return nodeCount;
        }

        template <class T>
        T List<T>::Sum() const
        {
            int sumNode = 0;
            for (Iterator it = Begin(); it != End(); it++)
            {
                sumNode += it->value;
            }
            return sumNode;
        }

        template <class T>
        typename List<T>::Iterator List<T>::Find(T value) const
        {
            for (Iterator it = Begin(); it != End(); ++it)
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

        template <class T>
        void List<T>::PushBack(T value)
        {
            Node* temp = new Node(value);
            Node *pTail = pHead;

            if (pHead == nullptr)
            {
                pHead = temp;
            }
            else
            {
                while (pTail->pNext != nullptr)
                {
                    pTail = pTail->pNext;
                }
                pTail->pNext = temp;
            }
        }

        template <class T>
        void List<T>::PushFront(T value)
        {
            if (pHead != nullptr)
            {
                pHead = new Node(value, pHead);
            }
            else
            {
                pHead = new Node(value);
                Last() = pHead;
            }
        }

        template <class T>
        void List<T>::Insert(T value, int index)
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

        template <class T>
        void List<T>::Move(List& source)
        {
            Node *pList = source.pHead;

            Last()->pNext = pList;

            Last() = source.Last();

            source.pHead = nullptr;
            source.Last() = nullptr;
        }

        template <class T>
        void List<T>::Copy(const List& source)
        {
            Node *pList = source.pHead;

            while (pList != nullptr)
            {
                PushBack(pList->value);
                pList = pList->pNext;
            }
        }

        template <class T>
        bool List<T>::IsEmpty() const
        {
            return Begin() == nullptr;
        }

        template <class T>
        typename List<T>::Iterator List<T>::Begin() const
        {
            return Iterator(pHead);
        }

        template <class T>
        typename List<T>::Iterator List<T>::End() const
        {
            return Iterator(nullptr);
        }

        template <class T>
        typename List<T>::Iterator List<T>::Last() const
        {
            Node *pTail = pHead;
            if (pHead != nullptr)
            {
                while (pTail->pNext != nullptr)
                {
                    pTail = pTail->pNext;
                }
            }
            return Iterator(pTail);
        }

        template <class T>
        void List<T>::Splice(Iterator where, List& source)
        {
            if (where == End())
                return;

            source.Last()->pNext = where->pNext;
            where->pNext = source.pHead;

            if (where == Last())
            {
                Last() = source.Last();
            }

            source.pHead = nullptr;
            source.Last() = nullptr;
        }

        template <class T>
        void List<T>::Remove(Iterator which)
        {
            Node *pList = NULL;
            Node *remove = pHead;

            Node *pList2 = pHead;
            if (which == pHead)
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
                    Last() = pList2;
                    pList2 = pList2->pNext;
                }

            }
        }

        template <class T>
        List<T>::Node::Node(const T& value)
        {
            Node::value = value;
            Node::pNext = nullptr;
        }

        template <class T>
        List<T>::Node::Node(const T& value, Node* pNode)
        {
            Node::value = value;
            pNext = pNode;
        }

        template <class T>
        List<T>::Node::Node(const Node& source)
        {
            value = source.value;
            pNext = source.pNext;
        }
    }
}

