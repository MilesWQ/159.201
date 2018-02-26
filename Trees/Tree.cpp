#include<iostream>

using namespace std;

template<class T>
class Tree
{
public:
    Tree(const T&,Tree<T>*,Tree<T>*);
    ~Tree();
    T GetRootData()
    {
        return my_Data;
    }
    Tree* GetLeft()
    {
        return my_ptrLeft;
    }
    Tree* GetRight()
    {
        return my_ptrRight;
    }
private:
    T my_Data;
    Tree<T> *my_ptrLeft;
    Tree<T> *my_ptrRight;
};

template<class T>
Tree<T>::Tree(const T &_data,Tree<T>* _left,Tree<T>* _right):my_Data(_data),my_ptrLeft(_left),my_ptrRight(_right) {}

template<class T>
Tree<T>::~Tree() {}

template<class T>
void PreOrder(Tree<T> *_root)
{
    if(_root == nullptr)
    {
        return;
    }
    cout<<_root->GetRootData()<<" ";
    PreOrder(_root->GetLeft());
    PreOrder(_root->GetRight());
}

int main()
{
    Tree<char> *t1 = new Tree<char>('D',nullptr,nullptr);
    Tree<char> *t2 = new Tree<char>('E',nullptr,nullptr);
    Tree<char> *t3 = new Tree<char>('B',t1,t2);
    Tree<char> *t4 = new Tree<char>('F',nullptr,nullptr);
    Tree<char> *t5 = new Tree<char>('G',nullptr,nullptr);
    Tree<char> *t6 = new Tree<char>('C',t4,t5);
    Tree<char> *tree = new Tree<char>('A',t3,t6);
    PreOrder(tree);
    return 0;
}
