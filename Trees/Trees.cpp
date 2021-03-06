#include "stdafx.h"
#include <iostream>

using namespace std;

template<class T>
class Tree {
private:
	T my_Key;
	Tree *my_ptrLeft;
	Tree *my_ptrRight;
public:
	Tree(const T&, Tree*, Tree*);
	~Tree();
	T GetLeft() { return my_ptrLeft; }
	T GetRight() { return my_ptrRight; }
	T GetRootKey() { return my_Key; }
	void PreOrder();
	void InOrder();
	void PostOrder();
};

template<class T>
Tree<T>::Tree(const T& _key, Tree *_left, Tree *_right) :my_Key(_key), my_ptrLeft(_left), my_ptrRight(_right) {}

template<class T>
Tree<T>::~Tree() {}

template<class T>
void Tree<T>::PreOrder() {
	if (this == nullptr) {
		return;
	}
	cout << my_Key << " ";
	my_ptrLeft->PreOrder();
	my_ptrRight->PreOrder();
}

template<class T>
void Tree<T>::InOrder() {
	if (this == nullptr) {
		return;
	}
	my_ptrLeft->InOrder();
	cout << my_Key << " ";
	my_ptrRight->InOrder();
}

template<class T>
void Tree<T>::PostOrder() {
	if (this == nullptr) {
		return;
	}
	my_ptrLeft->PostOrder();
	my_ptrRight->PostOrder();
	cout << my_Key << " ";
}
int main()
{
	Tree<char> *treeD = new Tree<char>('D', nullptr, nullptr);
	Tree<char> *treeE = new Tree<char>('E', nullptr, nullptr);
	Tree<char> *treeB = new Tree<char>('B', treeD, treeE);
	Tree<char> *treeF = new Tree<char>('F', nullptr, nullptr);
	Tree<char> *treeG = new Tree<char>('G', nullptr, nullptr);
	Tree<char> *treeC = new Tree<char>('C', treeF, treeG);
	Tree<char> *treeA = new Tree<char>('A', treeB, treeC);
	treeA->PostOrder();
	return 0;
}

