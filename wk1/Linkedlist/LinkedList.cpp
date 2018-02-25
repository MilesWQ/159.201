/**
* @file LinkedList.cpp
* @brief An exercise for implementing a linked-list
* @author MW
*/
#include<iostream>

using namespace std;

template <class T>
class LinkedList
{
private:
    struct Node
    {
        int my_id;
        T my_Data;
        Node *my_pNext;
        Node(int _id,T _data):my_id(_id),my_Data(_data),my_pNext(nullptr) {}
        Node() {}
    };
    Node *my_pListPointer;

public:
    LinkedList();
    ~LinkedList();
    void AddNode(int,const T&);
    //adding a node at the tail of the list
    void AddNodeT(int,const T&);
    void FindById(int);
    void RemoveById(int);
    void Concatenate(LinkedList<T>);
    void Reverse();
    void Print();
};

template<class T>
LinkedList<T>::LinkedList():my_pListPointer(nullptr) {}

template<class T>
LinkedList<T>::~LinkedList() {}

template<class T>
void LinkedList<T>::AddNode(int _id,const T& _data)
{
    Node *pNew = new Node(_id,_data);
    pNew->my_pNext = my_pListPointer;
    my_pListPointer = pNew;
}

template<class T>
void LinkedList<T>::Print()
{
    Node *pCurrent = my_pListPointer;
    while(pCurrent!=nullptr)
    {
        cout<<"["<<pCurrent->my_id<<"]:"<<pCurrent->my_Data<<" ";
        pCurrent = pCurrent->my_pNext;
    }
    cout<<"\nEnd of the list";
}

template<class T>
void LinkedList<T>::AddNodeT(int _id,const T& _data)
{
    Node *pCurrent = my_pListPointer;
    Node *pNew = new Node(_id,_data);
    if(pCurrent!=nullptr)
    {
        while(pCurrent->my_pNext!=nullptr)
        {
            pCurrent = pCurrent->my_pNext;
        }
        pCurrent->my_pNext = pNew;
    }
    else
    {
        my_pListPointer = pNew;
    }
}

template<class T>
void LinkedList<T>::FindById(int _id)
{
    Node *pCurrent = my_pListPointer;
    while(pCurrent!=nullptr && pCurrent->my_id != _id)
    {
        pCurrent = pCurrent->my_pNext;
    }
    if(pCurrent!=nullptr)
    {
        cout<<"["<<pCurrent->my_id<<"]:"<<pCurrent->my_Data;
    }
    else
    {
        cout<<"id:"<<_id<<" not found";
    }
}

template<class T>
void LinkedList<T>::RemoveById(int _id)
{
    Node *pCurrent = my_pListPointer;
    Node *pPrevious = nullptr;
    while(pCurrent !=nullptr)
    {
        if(pCurrent->my_id != _id)
        {
            pPrevious = pCurrent;
            pCurrent = pCurrent->my_pNext;
        }
        else if(pPrevious !=nullptr) //found the matched node and check if it's the first element;
        {
            pCurrent->my_pNext = pPrevious->my_pNext;
            delete pCurrent;
            return;
        }
        else //the matched node is the first element.
        {
            my_pListPointer = pCurrent->my_pNext;
            return;
        }
    }
    cout<<"id:"<<_id<<" not found";
}

template<class T>
void LinkedList<T>::Concatenate(LinkedList<T> _linklist)
{
    if(my_pListPointer != nullptr)
    {
        Node *pCurrent = my_pListPointer;
        while(pCurrent->my_pNext!=nullptr)
        {
            pCurrent = pCurrent->my_pNext;
        }
        pCurrent->my_pNext = _linklist.my_pListPointer;
    }
    else
    {
        my_pListPointer = _linklist.my_pListPointer;
    }
}

template<class T>
void LinkedList<T>::Reverse()
{
    if(my_pListPointer!=nullptr)
    {
        Node *pNext = my_pListPointer->my_pNext;
        Node *pPrevious = nullptr;
        while(pNext!=nullptr)
        {
            my_pListPointer->my_pNext = pPrevious;
            pPrevious = my_pListPointer;
            my_pListPointer = pNext;
            pNext = pNext->my_pNext;
        }
        my_pListPointer->my_pNext = pPrevious;
    }


}
int main()
{
    LinkedList<double> linkedlist1;
    linkedlist1.AddNodeT(1,1.11);
    linkedlist1.Print();
    cout<<endl;
    linkedlist1.RemoveById(1);
    cout<<endl;
    linkedlist1.Print();
    return 0;
}
