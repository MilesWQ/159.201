/**
* @file assignment1.cpp
* @brief 159201 assignment 1
* @author Wan Qian ID:17326163
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

/**
Definition of a node storing the value in a sparse matrix
e.g. For the below sparse matrix, 1 will be represented by row=0,col=0 ,value=1 in a node.
1 0 2
0 3 4
5 0 9
*/
struct Node {
    size_t row; /*> row in the sparse matrix.The value begins with 0. */
    size_t col; /*> column in the sparse matrix beginning with 0*/
    float value;/*> Stores the value. If the value is 0,the element will not be added into linked list*/
    Node *next;
    //constructor for a new node.
    Node(size_t _row, size_t _col, float _val) :row{ _row }, col{ _col }, value{ _val }, next(nullptr) {}
};
/**
Implement a sparse matrix with a linked list.
*/
class SparseMatrix {
public:
    /**
     * Default constructor for a new sparse matrix.Initialize a sparse matrix with empty linked list.
     */
    SparseMatrix() :headptr_(nullptr), tailptr_(nullptr) {}
    ~SparseMatrix();

    /**
     * Set the sparse matrix row.
     */
    void setRow(size_t row) { row_ = row; }

    /**
    * Set the sparse matrix col.
    */
    void setCol(size_t col) { col_ = col; }

    /**
    * Get the sparse matrix row.
    */
    size_t getRow() { return row_; }

    /**
    * Get the sparse matrix column.
    */
    size_t getCol() { return col_; }

    /**
    * Get the head pointer point to a linked list in the sparse matrix.
    */
    Node* getHeadPtr() { return headptr_; }

    /**
     * Add a node to the tail of a linked list stored by current sparse matrix.It will create a new node if current linked list is empty.
     * If the value is 0,the node will not be added.
     */
    void addNode(size_t, size_t, float);

    /*
     * Print out the values in the linked list of a sparse matrix and output the formatting matrix.
     * e.g.
     * 1 2 3 4 5  <- the values stores in the linked list.
     * 0 1 0 2    <- the matrix format for the above values.
     * 3 0 4 0
     * 0 5 0 0
     * It will not print the value if the sparse matrix is composed of 0.(the linked list is empty in this case),
     * and the matrix format is also printed by 0.
     *
     */
    void print();
    /**
     * Check if current sparse matrix is empty.
     */
    bool isEmpty();

private:
    Node * headptr_;
    Node * tailptr_;
    //Stores the total row and column of a matrix for printing use
    size_t row_;
    size_t col_;
};

SparseMatrix::~SparseMatrix() {
    Node* to_be_del = headptr_;
    while (headptr_ != nullptr) {
        to_be_del = headptr_;
        headptr_ = headptr_->next;
        delete to_be_del;
    }
    tailptr_ = nullptr;
    row_ = 0;
    col_ = 0;
}

/**
  * Check if Node A and Node B have the same rows and cols.
  */
bool isSameCoordinate(const Node*, const Node*);

/**
 *Check if node A is located before node B in a sparse matrix by comparing their rows and columns(coordinates)
 */
bool isBefore(const Node*, const Node*);

/**
 * Compares the location of each node between A B matrices,add the compared node to a new linked list as the result matrix.
 * The locations of elements in result linked list is in order and just contains the value except 0 since there's no 0 node in A B matrices.
 *
 * The comparison algorithm is like the merge method in merge sort which considers below situations:
 * 1.Sum the values in the two nodes when they have the same rows and cols then add a node with this value into result linked list.
 * After adding the new node move both pointers in A B to the next node for the next comparison round.
 * 2.If a node in A list is located before the corresponding node in B,then add a new node with the value in node
 * of A into the result list.Otherwise add the new node with the value in node of B into the result list.
 * After adding the new node just move the pointers in either A or B to its next node for the next comparison round.
 * 3.When finish evaluating in one of list A or B,add the remaining nodes contained either in A or B into the result linked list.
 */
void addMatrices(SparseMatrix* a, SparseMatrix* b, SparseMatrix &result);

/**
 * read file method as sample code.
 */
void read_matrix(SparseMatrix *a, const char *file_name);

/**
 * The entrance of the program.
 */
int main(int argc, char** argv) {
    if (argc != 3) { printf("needs two matrices \n"); exit(0); }
    SparseMatrix *A = new SparseMatrix();
    SparseMatrix *B = new SparseMatrix();
    SparseMatrix result;
    read_matrix(A, argv[1]);
    read_matrix(B, argv[2]);
    addMatrices(A, B, result);
    cout << "Matrix 1: ";
    A->print();
    cout << "Matrix 2: ";
    B->print();
    cout << "Matrix Result: ";
    result.print();
}

void SparseMatrix::addNode(size_t row, size_t col, float val) {
    if (val == 0) {
        return;
    }
    Node *pNewNode = new Node{ row, col, val };
    if (tailptr_ == nullptr) {
        headptr_ = tailptr_ = pNewNode;
    }
    else {
        tailptr_->next = pNewNode;
        tailptr_ = pNewNode;
    }
}

void SparseMatrix::print() {
    size_t row = getRow();
    size_t col = getCol();
    //print out the matrix format with 0 when the linked list is empty.
    if (isEmpty()) {
        cout << "\n";
        for (size_t i = 0; i != row; ++i) {
            for (size_t j = 0; j != col; ++j) {
                cout << "0 ";
            }
            cout << "\n";
        }
        return;
    }
    //print out the values stores in the linked list.
    Node *current = headptr_;
    while (current != nullptr) {
        cout << current->value << " ";
        current = current->next;
    }
    cout << "\n";
    //reset the pointer to current node to the head
    current = headptr_;
    //print out the matrix format.
    for (size_t i = 0; i != row; ++i) {
        for (size_t j = 0; j != col; ++j) {
            if (current != nullptr && current->row == i && current->col == j) {
                cout << current->value << " ";
                current = current->next;
            }
            else {
                cout << "0 ";
            }
        }
        cout << "\n";
    }
}


bool SparseMatrix::isEmpty() {
    return headptr_ == nullptr;
}

bool isSameCoordinate(const Node *a, const Node *b) {
    if (a == nullptr || b == nullptr) {
        return false;
    }
    if (a->row == b->row && a->col == b->col) {
        return true;
    }
    return false;
}

bool isBefore(const Node *a, const Node *b) {
    if (a == nullptr || b == nullptr) {
        return false;
    }
    if (a->row < b->row) {
        return true;
    }
    if (a->row == b->row && a->col < b->col) {
        return true;
    }
    return false;
}

void addMatrices(SparseMatrix *a, SparseMatrix *b, SparseMatrix &result) {
    //The passed result list argument should be empty as to add the new node.
    if (!result.isEmpty()) {
        return;
    }
    Node *currentA = a->getHeadPtr();
    Node *currentB = b->getHeadPtr();
    float sum = 0;
    //If two matrices have different rows and columns,set row and col of result sparse matrix with the larger one.
    a->getRow() >= b->getRow() ? result.setRow(a->getRow()) : result.setRow(b->getRow());
    a->getCol() >= b->getCol() ? result.setCol(a->getCol()) : result.setCol(b->getCol());
    while (currentA != nullptr && currentB != nullptr) {
        //Nodes in A and B have the same position
        if (isSameCoordinate(currentA, currentB)) {
            sum = currentA->value + currentB->value;
            result.addNode(currentA->row, currentA->col, sum);
            //move both pointers to the next nodes for next comparison
            currentA = currentA->next;
            currentB = currentB->next;
        }
        //location of the node in A list precedes that of B
        else if (isBefore(currentA, currentB)) {
            result.addNode(currentA->row, currentA->col, currentA->value);
            //just move the pointers in A list to next node for next comparison
            currentA = currentA->next;
        }
        //location of the node in B list precedes that of A
        else {
            result.addNode(currentB->row, currentB->col, currentB->value);
            //just move the pointers in B list to next node for next comparison
            currentB = currentB->next;
        }
    }
    // Add remaining nodes either in A or B to result sparse matrix.
    while (currentA != nullptr) {
        result.addNode(currentA->row, currentA->col, currentA->value);
        currentA = currentA->next;
    }
    while (currentB != nullptr) {
        result.addNode(currentB->row, currentB->col, currentB->value);
        currentB = currentB->next;
    }
}

void read_matrix(SparseMatrix *a, const char *file_name) {
    //reads a sparse matrix from a file
    int row = 0, col = 0;
    float value = 0;
    ifstream input;
    input.open(file_name);
    if (!input.good()) {
        cout << "Cannot open file " << file_name << endl;
        exit(0);
    }
    string line;
    //reads the first line to get dimensions
    if (input.good()) {
        getline(input, line);
        stringstream sline(line);
        sline >> row >> col;
        //Add these two statements to set the sparse matrix row and col in the current instance.
        a->setRow(row);
        a->setCol(col);
        /*cout << "SparseMatrix dimensions " << row << " " << col << endl;*/
    }
    //read SparseMatrix 
    for (int i = 0; i < row; ++i) {
        if (input.good()) {
            getline(input, line);
            stringstream sline(line);
            for (int j = 0; j < col; ++j) {
                sline >> value;
                if (value == 0) continue;
                //
                //Include your own add_node(a, i, j, value); function here
                //
                a->addNode(i, j, value);
                //The next line is for debbuging, it can be commented later

                /*cout << "Element at (" << i << " " << j << ") is different than zero and it is: " << value << " ";*/
            }
            //the next line is for debbuging purposes, it can be commented out later
            /*cout << endl;*/
        }
    }
    input.close();
}
