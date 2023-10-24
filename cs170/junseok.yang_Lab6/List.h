/*------------------------------------------------------------------------
Copyright (C) 2019 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name:List.h
Purpose:make nodes link list
Project:lab: 6
Author: junseok.yang
Created:spring 2019/06/17
------------------------------------------------------------------------*/
#pragma once
namespace CS170
{
    namespace Lab6
    {
        class List {
        private:
            struct Node {
                Node(int value) : value(value), pNext(nullptr) { }

                Node(int value, Node *next) : value(value), pNext(next) { }

                int value;
                Node *pNext;

            };

        public:

            class iterator
            {
                friend class List;
            public:
                iterator &operator ++();
                iterator operator ++(int);
                bool operator !=(iterator rhs);
                bool operator==(iterator rhs);
                iterator &operator=(int value);
                int& operator*();
                
            private:
                iterator(Node* node) :node(node) {}
                Node *operator->();
                Node* node;
            };

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

            iterator Begin()const;
            iterator Last()const;
            iterator End()const;

            int Count()const;
            iterator Find(int value)const;
            int Sum();
            bool IsEmpty()const;

            void PushBack(int value);
            void PushFront(int value);
            void Insert(int value, int index);

            void Move(List &source);
            void Copy(const List &source);
            void Splice(iterator where, List &source);
            void Remove(iterator which);

            friend  std::ostream& operator<<(std::ostream &out, List &list);


        private:
       
            Node *pHead;
            Node *pTail;

        };
    }
}

