#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <stdlib.h>

using std::cout;
using std::endl;

class LinkedList
{
public:
    LinkedList();
    virtual ~LinkedList();
/*Add a new node at the head of a linked-list.Creat a node if there's no node in the list.*/
    void addNodeH(const int&,const double&);
/*Add a new node at the tail of the current list.Creat a node if there's no node in the list.*/
    void addNodeT(const int&,const double&);
/*Return true if the node containing the id was found otherwise return false.*/
    bool isIdInList(const int&);
/*Return true if find the node and delete it successfully otherwise return false. O(N)*/
    bool removeNodeById(const int&);
/*Concatenate another linklist to the end of calling list.
* Parameter: a linklist that will be joined.
*/
    void concatenate(LinkedList *const&);
    void print();
protected:

private:
    struct Node
    {
        int id;
        double balance;
        Node *next;
        Node(const int &id,const double &balance)
        {
            this->id = id;
            this->balance = balance;
            next = 0;
        }
        Node() {next = 0;}
    };
    Node *listPointer;
};

#endif // LINKEDLIST_H
