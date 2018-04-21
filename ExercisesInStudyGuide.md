## Link List

1. **Copy the programs for inserting nodes at the head and at the tail. Also copy the PrintLL() into the same file, making one coherent program. In the main(), use the following sequence:**
```
int main(){
    AddNode2(A,1,1.11); 
    AddNode(A,2,2.22); 
    AddNode2(A,3,3.33);
    AddNode(A,4,4.44);
    AddNode2(A,5,5.55);
    AddNode(A,6,6.66);
    AddNode2(A,7,7.77);
    AddNode(A,8,8.88);
    AddNode2(A,9,9.99);
    PrintLL(A);
}
```
Solution:
    The sample code in the study guide doesn't encapsulate the linked-list. Here just follows this pattern to rewrite functions.
```
#include <iostream>
using namespace std;
struct Node{
    int accnumber; //the account number
    float balance; // the balance in the account
    Node *next;
};

// add a new node to the front of a linked-list.
void addNode(Node *&listpointer, int account, float bal);

//add a new node to the end of a linked-list.
void addNode2(Node *&listpointer, int account, float bal);

void printLL(Node *listpointer);

int main(){
    Node *A = nullptr;
    AddNode2(A,1,1.11); 
    AddNode(A,2,2.22); 
    AddNode2(A,3,3.33);
    AddNode(A,4,4.44);
    AddNode2(A,5,5.55);
    AddNode(A,6,6.66);
    AddNode2(A,7,7.77);
    AddNode(A,8,8.88);
    AddNode2(A,9,9.99);
    PrintLL(A);
    return 0;
}

void AddNode(Node *&listpointer, int account, float bal){
    Node *new_node = new Node;
    new_node->accnumber = account;
    new_node->balance = bal;
    new_node->next = listpointer;
    listpointer = new_node;
}

void AddNode2(Node *&listpointer, int account, float bal){
    Node *new_node = new Node;
    new_node->accnumber = account;
    new_node->balance = bal;
    new_node->next = nullptr;
    Node *temp = listpointer;
    if(temp == nullptr) {
        listpointer = new_node;
        return;
    }
    while(temp->next!=nullptr){
        temp = temp -> next;
    }
    temp->next = new_node; 
}

void PrintLL(Node *listpointer){
    Node* current = listpointer;
    while(current !=nullptr){
        cout<<"Account is "<<current->accnumber;
        cout<<" balance is "<<current->balance<<endl;
        current = current->next;
    }
    cout<<"End of the list "<<endl;
}
``` 

2. **Draw the linked-list manually and check in which sequence the nodes are arranged. Does it comply with what was printed?**

Solution:

A->[8, 8.88]->[6, 6.66]->[4, 4.44]->[2, 2.22]->[1, 1.11]->[3, 3.33]->[5, 5.55]->[7, 7.77]->[9, 9.99]->

The printed result of the Q1:

> Account is 8 balance is 8.88
Account is 6 balance is 6.66
Account is 4 balance is 4.44
Account is 2 balance is 2.22
Account is 1 balance is 1.11
Account is 3 balance is 3.33
Account is 5 balance is 5.55
Account is 7 balance is 7.77
Account is 9 balance is 9.99
End of the list

3. **Implement a function that returns the integer key of the Nth element of a linked-list. If the element does not exist, return -1;**

Solution:
```
/* return the position number of the node storing the key. If can't find a node with the key, return -1;
    the first node will be subscripted as 0.
*/
int IndexOf(Node *listpointer, int key){
    Node *current = listpointer;
    int subscript = 0;
    while(current!=nullptr){
        if(current->accnumber == key){
            return subscript;
        }
        ++subscript;
        current = current->next;
    }
    return -1;
} 
```

4. **Fix the Remove() (listing 2.9) function to work with the deletion of the first node. Fix it again for the case in which the key does not exist in the linked-list.**

Solution:
/*
 * Return true if the node was found and deleted else return false.
 */
```
bool Remove(Node *&listpointer, int key){
    Node *to_be_delete = listpointer;
    if(to_be_delete == nullptr) return false;
    //  Delete the first node if it meets the key.
    if(to_be_delete->accnumber == key){
        listpointer = listpointer ->next; //    reset listpointer
        delete to_be_delete;
        return true;
    }
    Node *prev = to_be_delete;
    to_be_delete = to_be_delete->next;
    while(to_be_delete != nullptr){
        if(to_be_delete->accnumber == key){
            prev->next = to_be_delete->next;
            delete to_be_delete;
            return true;
        }
        prev = to_be_delete;
        to_be_delete = to_be_delete->next;
    }
    return false;
}
```

5. **Modify the Remove() function to delete the Nth element. Remember to include the special cases for the removal, i.e., first node and the fact that the Nth node may not exist.**

Solution:

```
/*  return true if the index is valid and the corresponding node has been deleted successfully else return false.
 *  the first node is subscripted as 0.
 */
bool RemoveIndexOf(Node *&listpointer, int index){
    if(listpointer == nullptr) return false;
    int subscript = 0;
    Node *to_be_delete = listpointer;
    if(subscript == index){
        listpointer = listpointer->next;
        delete to_be_delete;
        return true;
    }
    Node *prev = to_be_delete;
    to_be_delete = to_be_delete->next;
    ++subscript;
    while(to_be_delete!=nullptr){
        if(subscript == index){
            prev->next = to_be_delete->next;
            delete to_be_delete;
            return true;
        }
        ++subscript;
        prev = to_be_delete;
        to_be_delete = to_be_delete->next;
    }
    return false;
}
```
6. **Write a function to delete an entire linked-list (to be used with method 1 of the reverse() functions.).
At the end of the function, listpointer should be NULL and every node should have been deallocated (use free() or delete).**

Solution:
```
void DeleteLinkList(Node *&listpointer){
    if(listpointer == nullptr) return;
    Node *to_be_delete = nullptr;
    while(listpointer !=nullptr){
        to_be_delete = listpointer;
        listpointer = listpointer->next;
        delete to_be_delete;
    }
}
```

7. **Write a program to insert a node in a linked-list after a certain key (i.e., search for the key and insert the new node after it).**

Solution:

```
/* @param listpointer the linked list to be inserted
 * @param key the position of the new node should be inserted after.
 * @param other  a single node to be inserted;
 * @return true if found the node with the key and insert the new node after it sucessfully otherwise return false.
 */
bool Insert(Node *&listpointer, int key, Node *&other){
    Node *current = listpointer;
    while(current!=nullptr){
        if(current->accnumber == key){
            other->next = current->next;
            current->next = other;
            return true;
        }
        current = current->next;
    }
    return false;
}
```

8. **Write a program to insert nodes to the head of a circular linked-list.**

9. **Write a program to insert nodes to the middle (after a certain key) of a circular linked-list.**

Solution for #8 and #9:
Implement a class to meet the operation of a circular linked-list.
```
#include<iostream>
using namespace std;

class CircularLinkList {
public:
    CircularLinkList();
    ~CircularLinkList();

    //  add a new node to the front of the list.
    void AddToFront(int data);

    //  add a new node to the end of the list.
    void AddToEnd(int data);

    /*  insert a single node with a given data after a certain key
    * @param search_key the key to be found.
    * @param data the data to be inserted to the list.
    * @return true if the node storing the key was found and a 
    *     new node was inserted after the found node successfully otherwise false.
    */
    bool Insert(int search_key, int data);
    friend ostream& operator<<(ostream& out, const CircularLinkList &linklist);
private:
    struct Node {
        int key;
        Node *next;
    };
    Node *listptr_;
};

ostream& operator<<(ostream& out, const CircularLinkList &linklist) {
    CircularLinkList::Node *current = linklist.listptr_;
    if (current == nullptr) return out;
    while (current->next != linklist.listptr_) {
        out << "|" << current->key << "|->";
        current = current->next;
    }
    out << "|" << current->key << "|->";
    return out;
}

CircularLinkList::CircularLinkList() :listptr_(nullptr) {}

CircularLinkList::~CircularLinkList() {
    if (listptr_ == nullptr) return;
    Node *current = listptr_;
    while (current->next != listptr_) {
        current = current->next;
    }
    current->next = nullptr;
    Node *to_be_delete = listptr_;
    while (listptr_ != nullptr) {
        to_be_delete = listptr_;
        listptr_ = listptr_->next;
        delete to_be_delete;
    }
}

void CircularLinkList::AddToFront(int data) {
    Node *new_node = new Node;
    new_node->key = data;
    if (listptr_ == nullptr) {
        listptr_ = new_node;
        new_node->next = listptr_;
        return;
    }
    new_node->next = listptr_;
    Node *temp = listptr_;
    while (temp->next != listptr_) {
        temp = temp->next;
    }
    temp->next = new_node;
    listptr_ = new_node;
}

void CircularLinkList::AddToEnd(int data) {
    Node *new_node = new Node;
    new_node->key = data;
    if (listptr_ == nullptr) {
        listptr_ = new_node;
    }
    else {
        Node *temp = listptr_;
        while (temp->next != listptr_) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
    new_node->next = listptr_;
}

bool CircularLinkList::Insert(int search_key, int data) {
    if (listptr_ == nullptr) return false;
    Node *current = listptr_;
    while (current->next != listptr_) {
        if (current->key == search_key) {
            Node *new_node = new Node;
            new_node->key = data;
            new_node->next = current->next;
            current->next = new_node;
            return true;
        }
        current = current->next;
    }
    //  current is at the end of the list
    if (current->key == search_key) {
        Node *new_node = new Node;
        new_node->key = data;
        new_node->next = current->next;
        current->next = new_node;
        return true;
    }
    return false;
}
```

10. **Using a doubly linked-list, write a printing function that traverses the list from the head to tail and then again from the tail to the head (this should be done within the same function).**

Solution:
Implement a doubly linked-list as a ADT
```
#include<iostream>
using namespace std;
class DoublelyLinkList {
public:
    DoublelyLinkList();
    ~DoublelyLinkList();
    void AddToFront(int data);
    void AddToEnd(int data);
    //  for Q10 overload output operator
    friend ostream& operator<<(ostream& out, const DoublelyLinkList &doublelylinklist);
private:
    struct Node {
        int key;
        Node *next;
        Node *previous;
    };
    Node *frontptr_;
    Node *endptr_;
};

DoublelyLinkList::DoublelyLinkList() :frontptr_(nullptr), endptr_(nullptr) {}

DoublelyLinkList::~DoublelyLinkList() {
    Node *to_be_del = nullptr;
    while (frontptr_ != nullptr) {
        to_be_del = frontptr_;
        frontptr_ = frontptr_->next;
        delete to_be_del;
    }
    endptr_ = nullptr;
}

void DoublelyLinkList::AddToFront(int data) {
    Node *new_node = new Node;
    new_node->key = data;
    new_node->previous = nullptr;
    new_node->next = frontptr_;
    if (frontptr_ == nullptr) {
        frontptr_ = endptr_ = new_node;
        return;
    }
    frontptr_->previous = new_node;
    frontptr_ = new_node;
}

void DoublelyLinkList::AddToEnd(int data) {
    Node *new_node = new Node;
    new_node->key = data;
    new_node->next = nullptr;
    new_node->previous = endptr_;
    if (frontptr_ == nullptr) {
        frontptr_ = endptr_ = new_node;
        return;
    }
    endptr_->next = new_node;
    endptr_ = new_node;
}

ostream& operator<< (ostream& out, const DoublelyLinkList &doublelylinklist) {
    DoublelyLinkList::Node *current = doublelylinklist.frontptr_;
    if (current == nullptr) return out << "Empty list";
    out << "Front to end: ";
    while (current != nullptr) {
        out << "|" << current->key << "|->";
        current = current->next;
    }
    out << "\n";
    out << "End to front: ";
    current = doublelylinklist.endptr_;
    while (current != nullptr) {
        out << "|" << current->key << "|->";
        current = current->previous;
    }
    return out;
}
```

----

## Stacks

1. **Modify the methods of the class Stack using an array to make sure that overflow and underflow errors do not happen.**

Solution:

Implement a complete stack class with a static array container.

```
const size_t MAX_ELEMENT = 10;
const size_t DEFAULT_INDEX = -1;
class Stack {
public:
    Stack();
    ~Stack();
    //  return true if the data push to the stack successfully otherwise false(No enough accommodation in the stack).
    bool Push(float data);
    //  clear the data on the top of the stack.return false if the stack is empty otherwise return true.
    bool Pop();
    bool IsEmpty();
    float Top() const;
private:
    float container_[MAX_ELEMENT];
    int front_;
};

Stack::Stack() :container_(), front_(DEFAULT_INDEX) {}

Stack::~Stack() {}

bool Stack::Push(float data) {
    ++front_;
    if (front_ == MAX_ELEMENT) {
        --front_;
        return false;
    }
    container_[front_] = data;
    return true;
}

bool Stack::Pop() {
    if (front_ == DEFAULT_INDEX) return false;
    container_[front_] = 0;
    --front_;
    return true;
}

bool Stack::IsEmpty() {
    return front_ == -1;
}

float Stack::Top()const {
    if (front_ == DEFAULT_INDEX) return 0;
    return container_[front_];
}
```

2. **Write an extra method for the class Stack called Copy(Stack B) that copies a Stack onto another. You need to traverse the entire linked-list and copy it. Be careful with the order of the elements.**

3. **Write an extra method bool Compare(Stack B) that traverses all the elements of both Stacks and compare them. If there is a difference, return false, otherwise return true.**

Solution for #2 and #3:
Implement a stack class with a doubly linked list.
```
class Stack {
public:
    Stack();
    ~Stack();
    Stack(const Stack& stack);
    Stack(Stack &&stack);
    //overloading copy assignment operator for Q2
    Stack& operator=(const Stack& stack);
    Stack& operator=(Stack &&stack);
    /* overloading equivalent operator for Q3 "compare" function
     * @param return true if two stacks have the same number of elements as well as keys are equivalent otherwise return false
     *        return false if both stacks are empty.
     */
    bool operator==(const Stack& stack);
    bool operator!=(const Stack& stack);
    void Push(float data);
    void Pop();
    float Top() const;
    bool IsEmpty() const;
private:
    struct Node {
        float key;
        Node *next;
        Node *previous;
    };
    Node *frontptr_;
    Node *endptr_;
};

Stack::Stack() :frontptr_(nullptr), endptr_(nullptr) {}

Stack::~Stack() {
    Node *to_be_del = nullptr;
    while (frontptr_ != nullptr) {
        to_be_del = frontptr_;
        frontptr_ = frontptr_->next;
        delete to_be_del;
    }
    endptr_ = nullptr;
}

Stack::Stack(const Stack& stack) :frontptr_(nullptr), endptr_(nullptr) {
    Node *temp = stack.endptr_;
    while (temp != nullptr) {
        Push(temp->key);
        temp = temp->previous;
    }
}

Stack::Stack(Stack && stack) :frontptr_(stack.frontptr_), endptr_(stack.endptr_) {
    stack.frontptr_ = nullptr;
    stack.endptr_ = nullptr;
}

Stack& Stack::operator=(const Stack& stack) {
    if (this->frontptr_ != stack.frontptr_) {
        this->~Stack();
        Node *temp = stack.endptr_;
        while (temp != nullptr) {
            Push(temp->key);
            temp = temp->previous;
        }
    }
    return *this;
}

Stack& Stack::operator=(Stack &&stack) {
    if (this->frontptr_ != stack.frontptr_) {
        this->~Stack();
        frontptr_ = stack.frontptr_;
        endptr_ = stack.endptr_;
        stack.frontptr_ = stack.endptr_ = nullptr;
    }
    return *this;
}

bool Stack::operator==(const Stack& stack) {
    Node *temp1 = frontptr_;
    Node *temp2 = stack.frontptr_;
    if (temp1 == nullptr && temp2 == nullptr) return false;
    while (temp1 != nullptr) {
        if (temp2 == nullptr) return false;
        if (temp1->key != temp2->key) return false;
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    if (temp2 != nullptr) return false;
    return true;
}

bool Stack::operator!=(const Stack& stack) {
    if (*this == stack) return false;
    return true;
}

void Stack::Push(float data) {
    Node *new_node = new Node;
    new_node->key = data;
    new_node->previous = nullptr;
    new_node->next = frontptr_;
    if (frontptr_ != nullptr) frontptr_->previous = new_node;
    if (endptr_ == nullptr) endptr_ = new_node;
    frontptr_ = new_node;
}

void Stack::Pop() {
    if (frontptr_ == nullptr) return;
    if (frontptr_->next == nullptr) {
        delete frontptr_;
        frontptr_ = endptr_ = nullptr;
        return;
    }
    Node *to_be_del = frontptr_;
    frontptr_ = frontptr_->next;
    frontptr_->previous = nullptr;
    delete to_be_del;
}

float Stack::Top() const {
    if (frontptr_ == nullptr) return -1;
    return frontptr_->key;
}

bool Stack::IsEmpty() const {
    return frontptr_ == nullptr;
}
```

## Binary Trees

1. **Re-write the binary tree class, including the functions for the traversals. Test your code by building different trees (manually) and traversing them (printing the keys). Use complete and non- complete binary trees.**
 
Solution: 
+ Implement a binary tree with recursive depth-first traversal.
+ Provide functions creating non-complete, full, complete but not perfect and perfect binary trees.
 ```
#include <iostream>
using namespace std;
 
class BinaryTree{
public:
    BinaryTree(int data, BinaryTree* leftptr, BinaryTree* rightptr): data_(data), leftptr_(leftptr), rightptr_(rightptr) { }
    ~BinaryTree(){ };
    int getData() const { return data_;}
    void preOrder() const;
    void inOrder() const;
    void postOrder() const;
private:
    int data_;
    BinaryTree *leftptr_;
    BinaryTree *rightptr_;
 };
 
 void BinaryTree::preOrder() const{
    if(this == nullptr) return;
    cout<<data_<<" ";
    leftptr_->preOrder();
    rightptr_->preOrder();
 }
 
 void BinaryTree::inOrder() const{
    if(this == nullptr) return;
    leftptr_->inOrder();
    cout<<data_<<" ";
    rightptr_->inOrder();
 }
 
 void BinaryTree::postOrder() const{
    if(this == nullptr) return;
    leftptr_->postOrder();
    rightptr_->postOrder();
    cout<<data_<<" ";
 }

BinaryTree* perfectTree();
 
BinaryTree* fullTree();
 
BinaryTree* nonComplete();

BinaryTree* completeNotPerfect();
 
/*
          1
        /   \
       2     3
      / \    / \
    4   5  6  7
*/
BinaryTree* perfectTree(){
    BinaryTree *t1 = new BinaryTree(4,nullptr,nullptr);
    BinaryTree *t2 = new BinaryTree(5,nullptr,nullptr);
    BinaryTree *t3 = new BinaryTree(2,t1,t2);
    BinaryTree *t4 = new BinaryTree(6,nullptr,nullptr);
    BinaryTree *t5 = new BinaryTree(7,nullptr,nullptr);
    BinaryTree *t6 = new BinaryTree(3,t4,t5);
    BinaryTree *tree = new BinaryTree(1,t3,t6);
    return tree;
}
/*
        1
       /  \
     2     3
    / \    / \
  4   5  6   7
           / \
          8   9     
 */
BinaryTree* fullTree(){
    BinaryTree *t1 = new BinaryTree(4,nullptr,nullptr);
    BinaryTree *t2 = new BinaryTree(5,nullptr,nullptr);
    BinaryTree *t3 = new BinaryTree(2,t1,t2);
    BinaryTree *t4 = new BinaryTree(8,nullptr,nullptr);
    BinaryTree *t5 = new BinaryTree(9,nullptr,nullptr);
    BinaryTree *t6 = new BinaryTree(6,t4,t5);
    BinaryTree *t7 = new BinaryTree(7,nullptr,nullptr);
    BinaryTree *t8 = new BinaryTree(3,t6,t7);
    BinaryTree *tree = new BinaryTree(1,t3,t8);
    return tree;
}
 
 /*
                1
                /\
             2     3
            /         \
         4             5
       /   \         /    \
    6       7      8      9
               \            /
                10     11
                    \
                    12
*/
BinaryTree* nonComplete(){
    BinaryTree *t1 = new BinaryTree(12,nullptr,nullptr);
    BinaryTree *t2 = new BinaryTree(10,nullptr,t1);
    BinaryTree *t3 = new BinaryTree(7,nullptr,t2);
    BinaryTree *t4 = new BinaryTree(6,nullptr,nullptr);
    BinaryTree *t5 = new BinaryTree(4,t4,t3);
    BinaryTree *t6 = new BinaryTree(2,t5,nullptr);
    BinaryTree *t7 = new BinaryTree(11,nullptr,nullptr);
    BinaryTree *t8 = new BinaryTree(9,t7,nullptr);
    BinaryTree *t9 = new BinaryTree(8,nullptr,nullptr);
    BinaryTree *t10 = new BinaryTree(5,t9,t8);
    BinaryTree *t11 = new BinaryTree(3,nullptr,t10);
    BinaryTree *tree = new BinaryTree(1,t6,t11);
    return tree;
 }

/*
            1
          /   \
        2       3
     /    \     /  \
    4     5   6   7
  /  \    /
8    9  10
 */
BinaryTree* completeNotPerfect(){
    BinaryTree *t1 = new BinaryTree(8,nullptr,nullptr);
    BinaryTree *t2 = new BinaryTree(9,nullptr,nullptr);
    BinaryTree *t3 = new BinaryTree(4,t1,t2);
    BinaryTree *t4 = new BinaryTree(10,nullptr,nullptr);
    BinaryTree *t5 = new BinaryTree(5,t4,nullptr);
    BinaryTree *t6 = new BinaryTree(2,t3,t5);
    BinaryTree *t7 = new BinaryTree(6,nullptr,nullptr);
    BinaryTree *t8 = new BinaryTree(7,nullptr,nullptr);
    BinaryTree *t9 = new BinaryTree(3,t7,t8);
    BinaryTree *tree = new BinaryTree(1,t6,t9);
    return tree;
}
 ```

2. **Write the pre-order non-recursive function and test it to see whether it yields the same result of the recursive one. Remember to use a Stack.**
 
Solution:
 + Add the method to the previous class as a public member using STL `stack`.
 
 ```
 /*
    Concise algorithm:
    1. If current tree is empty then return;
    2. Set a pointer *current points to the root, then push this pointer into the stack.
    3. Execute the below steps in a loop until the stack is empty.
        a. Get the first node then print it by top then pop it from stack. This node is either a sub-root or a leaf in the tree.
        b. If the previous printed node(pointed by *current) has a right child, `push` it to the stack.
        c. If the previous printed node has a left child, `push` it to the stack. This push order can ensure the left child will be picked before the right child in each sub-tree.
 */
  #include <stack>
 void BinaryTree::preOrderWithStack() {
    if(this == nullptr) return; 
    stack<BinaryTree*> s;
    BinaryTree* current = this;
    s.push(current);
    while(!s.empty()){
        current = s.top();
        s.pop();
        cout<<current->data_<<" ";
        if(current->rightptr_!=nullptr){
            s.push(current->rightptr_);
        }
        if(current->leftptr_!=nullptr){
            s.push(current->leftptr_);
        }
    }
 }
 ```
 
 3. **Repeat the previous exercise for the other two iterative traversals, in-order and post-order.**
 
Solution:
 + Add a member method of In order traversal with a stack to the previous class.
 ```
 /*
    Consice algorithm:
    1. Push the leftmost nodes into the stack until the leftmost leaf was pushed. This step ensures the left child will be visited in priority.
    2. Get(top and pop) a node from the stack and print it. Since the leftmost nodes were pushed into stack in a bottom to up order(step #1 or step #3.a), it can ensure
        the node we got is always either a leaf or a sub-root.
    3. Check whether the current printed node has a right child. If so, that refers this node is a sub-root, then set the current pointer to its right child as to
        traversal its left children.
        3.a In #3 condition, push the leftmost children into stack until the leftmost leaf was pushed.
    4. Repeat step #2 then step #3 until the stack is empty.
 */
 #include <stack>
 void BinaryTree::inOrderWithStack(){
    stack<BinaryTree*> s;
    BinaryTree* current = this;
    while(current!=nullptr){  
        s.push(current);
        current = current->leftptr_;
    }
    while(!s.empty()){
        current = s.top();
        s.pop();
        cout<<current->data_<<" ";
        if(current != nullptr){
            current = current ->rightptr_;
            while(current!=nullptr){
                s.push(current);
                current = current->leftptr_;
            }
        }
    }
 }
 ```
 
+ Add a member method of post order traversal with a stack to the previous class.
 
 ```
 /*
    Consice algorithm:
    1. Set two pointers to track nodes.
    2. Push the leftmost nodes into the stack if they have left children. After finishing the loop the "current" pointer will point to the leftmost leaf.
    3. Check if the current node has a right child or the right child has already been visited. If so, execute the below loop:
        3.a In #3 condition, print the current node and assign a pointer(previous_visited) to mark this node.Since this node might be a right child with respect to the next node in the stack.
        3.b If the stack is not empty, get the next element in the stack (top and pop).
        3.c Repeat to check if the node got in #3.b has a right child or the right child has been visited.
    4. If the current node has a right child and this right child has been visited, then the algorithm doesn't execute step #3 loop, just push the current node into the stack then
        set the current pointer to the right child.
    5. Repeat steps #2 to #4 to get the leftmost leaf of the current sub-root then verify whether it has no right child or the right child has been visited.
        
 */
void BinaryTree::postOrderWithStack(){
    stack<BinaryTree*> s;
    BinaryTree* current = this,  *previous_visited = this;
    //outer loop to deal with a right child
    while(current!=nullptr){
        //get the leftmost leaf of the current sub-root (locate the left node.)
        while(current->leftptr_ != nullptr){
            s.push(current);
            current = current ->leftptr_;
        }
        //deal with the sub-root in case it could be visited. If it has a right child that hasn't been visited, pass by this node then jump to deal with its right child.
        while(current->rightptr_ == nullptr || current->rightptr_ == previous_visited){
            cout<< current->data_<<" ";
            previous_visited= current;
            if(s.empty()) return; ///< quit the function
            current = s.top();
            s.pop();
        }
        //push back the sub-root which has a right child and it hasn't been visited.
        s.push(current);
        //locate the right child.
        current = current->rightptr_;
    }
 }
 ```
 
4. **Implement breath-first traversal in C++ using the Tree class defined before. Note that you need to change the queue type to a Tree (use either the STL queue or modify our Queue class).**

Solution:
+ Add a member to the previous class with a STL queue.

```
/*
    Concise algorithm:
    Push the left child then the right  child to a queue in each level. FIFO property of a queue can guarantee the node will be visited from left child to right child.
*/

#include <queue>
void BinaryTree::breathTraversal(){
    if(this == nullptr) return;
    queue<BinaryTree*> q;
    BinaryTree* current = this;
    q.push(current);
    while(!s.empty()){
        current = s.front();
        s.pop();
        cout<<current->data_<<" ";
        if(current->leftptr_ != nullptr){
            s.push(current->leftptr_);
        }
        if(current->rightptr_ != nullptr){
            s.push(current->rightptr_);
        }
    }
}
```