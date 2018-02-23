#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <stdlib.h>

using std::cout;
using std::endl;

struct Node
{
    int id;
    double balance;
    Node *next;
    Node(int id,double balance)
    {
        this->id = id;
        this->balance = balance;
        next = 0;
    }
    Node():next(0){}
    ~Node() {}
};

class LinkedList
{
public:
    LinkedList();
    virtual ~LinkedList();
    /*Add a new node at the head of a linked-list.Creat a node if there's no node in the list.*/
    virtual void addNode(int,double);
    /*Add a new node at the tail of the current list.Creat a node if there's no node in the list.*/
    void addNodeTail(int,double);
    /*Return true if the node containing the id was found otherwise return false.*/
    bool isIdInList(int);
    /*Return true if find the node and delete it successfully otherwise return false. O(N)*/
    bool removeNodeById(int);
    /*Concatenate another linklist to the end of calling list.
    * Parameter: a linklist that will be joined.
    */
    void concatenate(LinkedList *const);
    void reverse1();
    void reverse2();
    bool split(LinkedList*&,int);
    void print();

private:
    Node *listPointer;
};

#endif // LINKEDLIST_H
