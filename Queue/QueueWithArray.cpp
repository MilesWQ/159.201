/**
@file QueueWithArray.cpp

@author MW
*/

#include<iostream>
using namespace std;

const int g_Qmax = 10;

class Queue
{
public:
    Queue();
    ~Queue();
    void Join(float);
    void Leave();
    float Front();
    bool isEmpty();
private:
    float my_fData[g_Qmax];
    size_t my_first,my_last,my_count;
};

Queue::Queue()
{
    my_first =0;
    my_last = -1;
    my_count =0;
}

Queue::~Queue() {}

void Queue::Join(float _f)
{
    if(my_count<g_Qmax)
    {
        ++my_last;
        if(my_last>=g_Qmax)
        {
            my_last = 0;
        }
        my_fData[my_last] = _f;
        ++my_count;
    }
}

void Queue::Leave()
{
    if(my_count>0)
    {
        ++my_first;
        if(my_first>=g_Qmax)
        {
            my_first = 0;
        }
        --my_count;
    }
}

float Queue::Front()
{
    return my_fData[my_first];
}

bool Queue::isEmpty()
{
    return my_count == 0;
}

int main()
{
    Queue q;
    q.Join(5.5);
    q.Join(4.4);
    q.Join(3.3);
    q.Leave();
    q.Leave();
    q.Leave();
    q.Leave();
    q.Join(2.222);
    q.Join(3.333);
    q.Leave();
    if(!q.isEmpty()){
        cout<<q.Front();
    }else{
        cout<<"empty"<<endl;
    }
    return 0;
}
