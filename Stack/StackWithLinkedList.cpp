#include <iostream>

using namespace std;
struct Node
{
    float my_fData;
    Node *next;
    Node(float _fdata):my_fData(_fdata) {}
    Node() {}
};

class Stack
{
public:
    Stack();
    virtual ~Stack();
    void push(float _f);
    void pop();
    float top();
    bool isEmpty();
    bool operator==(const Stack&);
    Stack& operator=(const Stack&);
protected:

private:
    Node *my_pListpointer;
};

Stack::Stack()
{
    my_pListpointer = nullptr;
}

Stack::~Stack() {}

void Stack::push(float _f)
{
    Node *pTempNewNode = new Node(_f);
    pTempNewNode->next = my_pListpointer;
    my_pListpointer = pTempNewNode;
}

void Stack::pop()
{
    Node *pTemp = my_pListpointer;
    if(my_pListpointer!=nullptr)
    {
        my_pListpointer = my_pListpointer->next;
        delete pTemp;
    }

}

float Stack::top()
{
    if(my_pListpointer!=nullptr)
    {
        return my_pListpointer->my_fData;
    }

}

bool Stack::isEmpty()
{
    return my_pListpointer == nullptr;
}

bool Stack::operator == (const Stack &_stack)
{
    Node *pTemp1 = my_pListpointer;
    Node *pTemp2 = _stack.my_pListpointer;
    while(pTemp1!=nullptr && pTemp2!=nullptr)
    {
        if(pTemp1->my_fData == pTemp2->my_fData)
        {
            pTemp1 = pTemp1->next;
            pTemp2 = pTemp2->next;
        }
        else
        {
            return false;
        }
    }
    if(pTemp1 == nullptr && pTemp2 == nullptr)
    {
        return true;
    }
    return false;
}


int main()
{
    //test push,pop,top,isEmpty
    Stack s;
    cout<<s.isEmpty()<<endl;
    s.pop();
    cout<<s.top()<<endl;
    s.push(5.55);
    s.push(4.44);
    s.push(3.33);
    s.push(2.22);
    s.push(1.11);
    cout<<s.top()<<endl;
    s.pop();
    cout<<s.top()<<endl;
    //test comparison operator
    Stack s1;
    Stack s2;
    s1.push(9.99);
    s1.push(8.88);
    s2.push(9.99);
    cout<<(s1==s2)<<endl;
    return 0;
}
