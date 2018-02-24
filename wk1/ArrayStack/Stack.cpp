/**
 *@file stack.cpp
 *@brief Practices for stack implementation
 *@author MW
 */
#include<iostream>

using namespace std;

class Stack
{
public:
    Stack();
    ~Stack();
    void push(float _f);
    void pop();
    float top();
    bool isEmpty();
private:
    float my_aData[10];
    int my_iIndex;
};

Stack::Stack()
{
    my_iIndex = -1;
}

Stack::~Stack() {}

void Stack::push(float _f)
{
    if(my_iIndex >9)
    {
        return;
    }
    ++my_iIndex;
    my_aData[my_iIndex] = _f;
}

void Stack::pop()
{
    if(my_iIndex>-1)
    {
        --my_iIndex;
    }
}

float Stack::top()
{

    if(my_iIndex>-1)
    {
        return my_aData[my_iIndex];
    }
}

bool Stack::isEmpty()
{
    if(my_iIndex < 0)
    {
        return true;
    }
    return false;
}

int main()
{
    Stack s;
    s.push(1.11);
    s.push(2.22);
    s.push(3.33);
    cout<<s.top()<<endl;
    return 0;
}
