/**
* @file WanQian_17326163_assignment3.cpp
* @brief 159201 assignment 3 
* @details implement a Queue with a List container to simulate the packet process of a router.
* @author Wan Qian ID:17326163
*
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>
#include <string>
using namespace std;

/**
* A Linked-List acted as an underlying container in a queue.
*/
class List {
public:
    /**
    * Default constructor
    */
    List();

    /**
    * Destructor.Will delete every node in the list.
    */
    ~List();

    /**
    * Copy constructor.Implements deep copying.
    */
    List(const List &list);

    /**
    * Move constructor.
    */
    List(List &&list);

    /**
    * Overloading assignment operator.Ensure deep copying for the assigned list.
    */
    List& operator=(const List &other);

    /**
    * Overloading move assignment operator.
    */
    List& operator=(List &&other);

    /**
    * Add a node at the end of the list.It will create a node into the list when the list is empty.
    * @param[in] number an integer stored in the node.
    */
    void AddToEnd(int number);

    /**
    * Delete the first node.
    */
    void DeleteFirst();

    /**
    * Check whether the list is empty
    * @return false if the list contains elements.
    *         true if the list is empty.
    */
    bool IsEmpty() const;

    /**
    * Get the number stored in the first node of the list.
    * @param[out] data the number stored in the first node if return true
    * @return true if retrieve the element successfully
    *         false if the list is empty
    */
    bool GetFirst(int &data) const;

    /**
    * Overloading output operator.Print out the numbers stored in the list.
    */
    friend ostream& operator<<(ostream &out, const List &list);

private:
    struct Node {
        int data; ///< store the number data in a node
        Node *next; ///< point to the next node.
    };
    Node *front_ptr_; ///< point to the first node of a list as the list pointer.
    Node *rear_ptr_;///< point to the last node of a list.
};

List::List() :front_ptr_(nullptr), rear_ptr_(nullptr) {}

List::~List() {
    Node *to_be_del = front_ptr_;
    while (front_ptr_ != nullptr) {
        to_be_del = front_ptr_;
        front_ptr_ = front_ptr_->next;
        delete to_be_del;
    }
    rear_ptr_ = nullptr;
}

List::List(const List &list) : front_ptr_(nullptr), rear_ptr_(nullptr) {
    Node *current = list.front_ptr_;
    while (current != nullptr) {
        AddToEnd(current->data);
        current = current->next;
    }
}

List::List(List &&list) :front_ptr_(list.front_ptr_), rear_ptr_(list.rear_ptr_) {
    list.front_ptr_ = nullptr;
    list.front_ptr_ = nullptr;
}

List& List::operator=(const List &other) {
    if (this != &other) {
        this->~List();
        Node *current = other.front_ptr_;
        while (current != nullptr) {
            AddToEnd(current->data);
            current = current->next;
        }
    }
    return *this;
}

List& List::operator=(List &&other) {
    if (this != &other) {
        this->~List();
        front_ptr_ = other.front_ptr_;
        rear_ptr_ = other.rear_ptr_;
        other.front_ptr_ = nullptr;
        other.rear_ptr_ = nullptr;
    }
    return *this;
}

void List::AddToEnd(int number) {
    Node *new_node = new Node;
    new_node->data = number;
    new_node->next = nullptr;
    if (front_ptr_ == nullptr) {
        front_ptr_ = rear_ptr_ = new_node;
        return;
    }
    rear_ptr_->next = new_node;
    rear_ptr_ = new_node;
}

void List::DeleteFirst() {
    if (front_ptr_ == nullptr) return;
    Node *current = front_ptr_;
    front_ptr_ = current->next;
    if (front_ptr_ == nullptr) rear_ptr_ = nullptr;
    delete current;
}

bool List::IsEmpty() const {
    return front_ptr_ == nullptr;
}

bool List::GetFirst(int &data) const {
    if (front_ptr_ == nullptr) {
        return false;
    }
    data = front_ptr_->data;
    return true;
}

ostream& operator<<(ostream& out, const List &list) {
    List::Node *current = list.front_ptr_;
    while (current != nullptr) {
        out << "|" << current->data << "|->";
        current = current->next;
    }
    return out;
}

/* implement your Queue class here */

/**
* Implement a queue for storing port number with a list container.
*/
class Queue {
public:
    /**
    * Default constructor.
    */
    Queue();

    /**
    * Destructor.The underlying list will be destructed.
    */
    ~Queue();

    /**
    * Overloading assignment operator
    */
    Queue& operator=(const Queue &other);

    /**
    * Add the element into the queue.
    * @param[in] port_num The destination port number.
    */
    void Join(int port_num);

    /**
    * Delete the first element in the queue.
    */
    void Leave();

    /**
    * Get the port number of the first element in the queue.
    * @return the port number stored in the first element in the queue
    *         if the underlying list isn't empty.
    */
    int Front() const;

    /**
    * Check whether the queue is empty.
    * @return false if the queue contains elements.
    *         true if the queue is empty.
    */
    bool IsEmpty() const;

    /**
    * Get the size of the queue.
    * @return the number of the elements stored in the queue.
    */
    size_t Size() const;

    /**
    * Overloading output operator.
    */
    friend ostream& operator<<(ostream& out, const Queue &queue);
private:
    List list_; ///< the list container
    size_t length_; ///< record the number of elements of the queue.
};

Queue::Queue() :length_(0) {}

Queue::~Queue() {
    length_ = 0;
}

Queue& Queue::operator=(const Queue &other) {
    if (this != &other) {
        list_.~List();
        list_ = other.list_;
        length_ = other.length_;
    }
    return *this;
}

void Queue::Join(int port_num) {
    list_.AddToEnd(port_num);
    ++length_;
}

void Queue::Leave() {
    list_.DeleteFirst();
    if (list_.IsEmpty()) {
        length_ = 0;
        return;
    }
    --length_;
}

int Queue::Front() const {
    int result = -1;
    if (list_.GetFirst(result)) {
        return result;
    }
    return result;
}

bool Queue::IsEmpty() const {
    return list_.IsEmpty();
}

size_t Queue::Size() const {
    return length_;
}

ostream& operator<<(ostream& out, const Queue &queue) {
    out << queue.list_;
    return out;
}


////////////////////////////////////////////////////////////////////////

#define TIMEDELAY 3 //DO NOT CHANGE THIS VALUE!!!
#define N 128 //DO NOT CHANGE THIS VALUE!!!
int OutQueues_current[N];
int Congestion_Size[N];

/*include your array of queues declarations somewhere here, for example: */
Queue InputQueues[N];
Queue OutputQueues[N];

void init_simulation() {
    for (int a = 0; a < N; a++) {
        OutQueues_current[a] = 0;
        Congestion_Size[a] = 0;
    }
}

int sum_elements_array(int array[]) {
    int sum = 0;
    for (int a = 0; a < N; a++) {
        sum = sum + array[a];
    }
    return sum;
}

int number_of_ports = 0;

int main(int argc, char** argv) {//get arguments from command line, the name of the simulation text file
    //read the file, print the input ports contents
    int portnumber = 0;
    int destination = 0;
    string expression;
    string geninput;
    ifstream input_file;
    if (argc != 2) { cout << "Type a file name. " << endl << argv[1] << endl; exit(0); }
    input_file.open(argv[1]);
    if (input_file.is_open() == false) { cout << "Could not read file: " << endl << argv[1] << endl; exit(0); }
    string token;
    while (!input_file.eof()) {
        getline(input_file, expression);
        stringstream line(expression);
        if (input_file.eof()) break;
        if (expression[0] == '#') continue;//jump line, this is a line of comments
        if (expression[0] == 'P') {
            getline(line, token, ' ');
            getline(line, token, ' ');
            number_of_ports = atoi(token.c_str());
            continue;//got the number of ports
        }
        portnumber++;//get data for the next port
        while (getline(line, token, ' ')) {
            int destination;
            //destination = stoi(token);//only works with option -std=c++11
            destination = atoi(token.c_str());//use this one if your compiler is not C++11
            if (destination < 0 || destination > number_of_ports || number_of_ports < portnumber) {
                cout << "ERROR in the format of the text file" << endl; exit(0);
            }
            InputQueues[portnumber - 1].Join(destination);
        }
    }
    init_simulation();
    unsigned long int clock = 0;
    unsigned long int currentsum = 99999999;
    portnumber = 0;
    while (currentsum > 0) {
        //move 1 packet from current port to its destination port
        if (!InputQueues[portnumber].IsEmpty()) {
            destination = InputQueues[portnumber].Front();
            InputQueues[portnumber].Leave();
            OutputQueues[destination - 1].Join(destination);
            OutQueues_current[destination - 1] = OutputQueues[destination - 1].Size();
        }
        portnumber++;
        if (portnumber > (number_of_ports - 1)) portnumber = 0;
        clock++;
        if (clock % (TIMEDELAY*number_of_ports) == 0 && clock != 0) {
            for (int a = 0; a < number_of_ports; a++) {
                //Delete 1 packet from each queue and count number of packets again
                if (OutputQueues[a].IsEmpty()) continue;
                OutputQueues[a].Leave();
                OutQueues_current[a] = OutputQueues[a].Size();
            }
        }
        //clock++;
        currentsum = sum_elements_array(OutQueues_current);
        if (currentsum > sum_elements_array(Congestion_Size)) {
            for (int a = 0; a < number_of_ports; a++) {
                Congestion_Size[a] = OutQueues_current[a];
            }
        }
    }
    for (int a = 0; a < number_of_ports; a++) {
        cout << "output port " << a + 1 << ": " << Congestion_Size[a] << " packets" << endl;
    }
}
