/**
    \file        List.h
    \author      junseok.yang
    \par         email: wnstjryang@gmail.com
    \par         course: CS170
    \par         lab: 7
    \date        spring 2019/04/10
    \brief
        make nodes link list
*/
#pragma once
namespace CS170
{
    namespace Lab7
    {
        class List {
        private:
            struct Node {
                Node(int value) : value(value), pNext(nullptr) ,pPrev(nullptr){ }

                Node(int value, Node *next) : value(value), pNext(next) ,pPrev(nullptr){ }

                int value;
                Node *pNext;
                Node *pPrev;

            };

        public:

            class Reverseiterator
            {
                friend std::ostream& operator<<(std::ostream &out, List::Reverseiterator list);
                //friend class List;
            public:
                Reverseiterator &operator ++();
                Reverseiterator operator ++(int);
                bool operator !=(Reverseiterator rhs);
                bool operator==(Reverseiterator rhs);
                Reverseiterator &operator=(int value);
                int& operator*();
                Node *operator->();
                Reverseiterator(Node* node) :node(node) {}

            private:
                Node* node;

            };

            class iterator
            {
                friend  std::ostream& operator<<(std::ostream &out, List::iterator list);
              
            public:
                iterator &operator ++();
                iterator operator ++(int);
                bool operator !=(iterator rhs);
                bool operator==(iterator rhs);
                iterator &operator=(int value);
                int& operator*();
                Node *operator->();
                iterator(Node* node) :node(node) {}
           
                
            private:
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

            Reverseiterator ReverseBegin()const;
            Reverseiterator ReverseEnd()const;
            Reverseiterator ReverseLast()const;

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

        private:
       
            Node *pHead;
            Node *pTail;\

        };
    }
}

