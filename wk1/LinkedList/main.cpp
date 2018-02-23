#include "LinkedList.h"
#include "CirularLinkedList.h"
int main()
{
    LinkedList *l =new LinkedList();
    CirularLinkedList *cl = new CirularLinkedList();
    cl->print();
    l->addNode(1,2.22);
    l->print();
    return 0;
}
