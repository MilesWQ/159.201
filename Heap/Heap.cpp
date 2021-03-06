/**
 * Implement a heap with a vector as the underlying container
 * Provide a heapsort function with the heap.
 * @author Wan Qian
 */

#include<vector>
#include<utility>
#include<iostream>
#include<stdexcept>

using namespace std;
class Heap {
public:
    Heap();
    ~Heap() {}
    void Insert(int item);
    int DeleteRoot();
    size_t Size() const;
    const int operator[](size_t i)const;

private:
    vector<int> heap_;
};

Heap::Heap() {}

void Heap::Insert(int item) {
    heap_.push_back(item);
    int last = heap_.size() - 1;
    if (last == 0) return;
    int child = last;
    int parent = (child - 1) / 2;
    bool swapping = true;
    while (swapping == true) {
        swapping = false;
        if (parent >= 0) {
            if (heap_[child] > heap_[parent]) {
                swap(heap_[child], heap_[parent]);
                swapping = true;
                child = parent;
                if (child % 2 == 0) {//right child,when index =1, parent should be -1
                    parent = child / 2 - 1;
                }
                else {
                    parent = child / 2;
                }
            }
        }
    }
}

int Heap::DeleteRoot() {
    if (heap_.size() == 0) {
        throw out_of_range("No item to delete");
    }
    int del = heap_[0];
    int last = heap_.size() - 1;
    swap(heap_[0], heap_[last]);
    heap_.pop_back();
    last = heap_.size() - 1;
    //1 item
    if (last < 1) return del;
    //2 item
    if (last < 2) {
        if (heap_[0] < heap_[last]) {
            swap(heap_[0], heap_[last]);
        }
        return del;
    }
    int parent = 0;
    int left_child = 2 * parent + 1;
    int right_child = 2 * parent + 2;
    while (heap_[parent] < heap_[left_child] || heap_[parent] < heap_[right_child]) {
        if (heap_[left_child] > heap_[right_child]) {
            swap(heap_[parent], heap_[left_child]);
            parent = left_child;
        }
        else {
            swap(heap_[parent], heap_[right_child]);
            parent = right_child;
        }
        left_child = 2 * parent + 1;
        right_child = 2 * parent + 2;
        //parent is a leaf
        if (left_child > last) break;
        //parent has a left leaf
        if (right_child > last) {
            if (heap_[parent] < heap_[left_child]) {
                swap(heap_[parent], heap_[left_child]);
            }
            break;
        }
    }
    return del;
}

size_t Heap::Size() const {
    return heap_.size();
}

const int Heap::operator[](size_t i) const {
    return heap_[i];
}

ostream& operator<<(ostream& out, const Heap &heap) {
    size_t size = heap.Size();
    for (size_t i = 0; i != size; ++i) {
        out << heap[i] << " ";
    }
    return out;
}

void Heapsort(int *array, int size) {
    Heap h;
    for (int i = 0; i != size; ++i) {
        h.Insert(array[i]);
    }
    for (int i = size - 1; i >= 0; --i) {
        array[i] = h.DeleteRoot();
    }
}

void Heapsort(vector<int> &a) {
    Heap h;
    int size = a.size();
    for (int i = 0; i != size; ++i) {
        h.Insert(a[i]);
    }
    for (int i = size - 1; i >= 0; --i) {
        a[i] = h.DeleteRoot();
    }
}

int main()
{
    vector<int> v1 = { 5,9,1,7,16,15,0,3,4,20,14,54,34 };
    int array[] = { 5,9,1,7,16,15,0,3,4,20,14,54,34 };
    vector<int> v2 = { 10,9,8,7,6,5,4,3,2,1 };
    int size = sizeof(array) / sizeof(int);
    Heapsort(v1);
    Heapsort(array,size);
    Heapsort(v2);
    cout << "After sorting: " << endl;
    cout << "v1: ";
    for (auto i : v1) {
        cout << i << " ";
    }
    cout << endl;
    cout << "array: ";
    for (auto i : array) {
        cout << i << " ";
    }
    cout << endl;
    cout << "v2: ";
    for (auto i : v2) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}