#include "LinkedList.h"

LinkedList::LinkedList()
{
    listPointer = 0;
}

LinkedList::~LinkedList()
{

}

//Add a new node at the head of a linked-list.Creat a node if there's no node in the list.
void LinkedList::addNode(int id,double balance)
{
    Node *temporaryNewNode = new Node(id,balance);
    temporaryNewNode->next = listPointer;
    listPointer = temporaryNewNode;
}

//Add a new node at the tail of current list.Creat a node if there's no node in the list.
void LinkedList::addNodeTail(int id,double balance)
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
bool LinkedList::isIdInList(int id)
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
bool LinkedList::removeNodeById(int id)
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
void LinkedList::concatenate(LinkedList *const linklist2)
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

void LinkedList::reverse1()
{
    if(listPointer!=0)
    {
        LinkedList *temporaryList = new LinkedList();
        Node *currentNode = listPointer;
        while(currentNode!=0)
        {
            temporaryList->addNode(currentNode->id,currentNode->balance);
            currentNode = currentNode->next;
        }
        delete listPointer;
        listPointer = temporaryList->listPointer;
    }
}

void LinkedList::reverse2()
{
    if(listPointer!=0)
    {
        Node *oldListPointer = listPointer;
        Node *previousNode = listPointer;
        Node *NextNode = listPointer->next;
        while(NextNode !=0)
        {
            listPointer = NextNode;
            NextNode = listPointer->next;
            listPointer->next = previousNode;
            previousNode = listPointer;
        }
        oldListPointer->next = 0;
    }
}

bool LinkedList::split(LinkedList *&newlist,int id)
{
    if(newlist->listPointer!=0)
    {
        cout<<"The new list has already got nodes."<<endl;
        return false;
    }
    Node *current = listPointer;
    while(current!=0 && current->id != id)
    {
        current = current->next;
    }
    if(current!=0)
    {
        newlist->listPointer = current->next;
        current->next = 0;
        return true;
    }
    else
    {
        cout<<"id not found"<<endl;
        return false;
    }
}
