#include "LinkedList.h"

LinkedList::LinkedList()
{
    listPointer = 0;
}

LinkedList::~LinkedList()
{

}

//Add a new node at the head of a linked-list.Creat a node if there's no node in the list.
void LinkedList::addNodeH(const int &id,const double &balance)
{
    Node *temporaryNewNode = new Node(id,balance);
    temporaryNewNode->next = listPointer;
    listPointer = temporaryNewNode;
}

//Add a new node at the tail of current list.Creat a node if there's no node in the list.
void LinkedList::addNodeT(const int &id,const double &balance)
{
    Node *currentNode = listPointer;
    Node *temporaryNewNode = new Node(id,balance);
    if(currentNode == 0)
    {
        listPointer = temporaryNewNode;
    }
    else
    {
        while(currentNode->next!=0)
        {
            currentNode = currentNode->next;
        }
        currentNode->next = temporaryNewNode;
    }
}

void LinkedList::print()
{
    Node *currentNode = listPointer;
    while(currentNode!=0)
    {
        cout<<"id:"<<currentNode->id<<" Balance is "<<currentNode->balance<<endl;
        currentNode = currentNode->next;
    }
    cout<<"End of the list"<<endl;
}
//Return true if the node containing the id was found otherwise return false.
bool LinkedList::isIdInList(const int &id)
{
    Node *currentNode = listPointer;
    while(currentNode!=0 && currentNode->id != id)
    {
        currentNode = currentNode->next;
    }
    if(currentNode == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

//Return true if find the node and delete it successfully otherwise return false. O(N)
bool LinkedList::removeNodeById(const int &id)
{
    Node *previousOfToBeRemoved = NULL;
    Node *toBeRemoved = listPointer;
    if(isIdInList(id))
    {
        //check whether the node that will be removed is the first element.
        if(toBeRemoved->id == id)
        {
            listPointer = toBeRemoved->next;
            delete toBeRemoved;
        }
        else
        {
            do
            {
                previousOfToBeRemoved = toBeRemoved;
                toBeRemoved = toBeRemoved->next;
            }
            while(toBeRemoved->id!=id);
            previousOfToBeRemoved->next = toBeRemoved->next;
            delete toBeRemoved;
        }
        return true;
    }
    else
    {
        return false;
    }
}
/*Concatenate another linklist to the end of calling list.
* Parameter: a linklist that will be joined.
*/
void LinkedList::concatenate(LinkedList *const &linklist2)
{
    if(linklist2->listPointer!=0)
    {
        Node *findLastElement = listPointer;
        //check wheter the calling list contains any node.
        if(listPointer != 0 )
        {
            while(findLastElement->next!=0)
            {
                findLastElement = findLastElement->next;
            }
            findLastElement->next = linklist2->listPointer;
        }
        else
        {
            listPointer = linklist2->listPointer;
        }
    }
}
