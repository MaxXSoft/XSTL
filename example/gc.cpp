#include <iostream>

#include "../gc/smart_gc.h"

using namespace std;

xstl::SmartGC gc;

class Node {
public:
    Node(int data) : data_(data) { cout << "constructed " << this << endl; }
    ~Node() { cout << "destructed " << this << endl; }

    void Print() const { cout << "content " << data_ << endl; }
    void Modify(int data) { data_ = data; }

    xstl::SmartPtr<Node> prev, next;

private:
    int data_;
};

xstl::SmartPtr<Node> Func1() {
    auto ptr = gc.make_smart<Node>(100);
    ptr->Print();
    return ptr;
}

void Func2(xstl::SmartPtr<Node> ptr) {
    cout << "unique? " << ptr.unique() << endl;
    cout << "pointer " << ptr.get() << endl;
    ptr->Modify(10);
    ptr->Print();
}

void Test1() {
    auto ptr = Func1();
    Func2(ptr);
    cout << "Test1 done" << endl;
}

void NewLinkedList(xstl::SmartPtr<Node> &head, int count) {
    auto temp = head, prev = head->prev;
    for (int i = 0; i < count; ++i) {
        temp->next = temp.make_smart<Node>(i);
        prev = temp;
        temp = temp->next;
        temp->prev = prev;
    }
}

void PrintLinkedList(xstl::SmartPtr<Node> &head) {
    auto temp = head;
    while (temp) {
        temp->Print();
        temp = temp->next;
    }
}

void Test2() {
    auto head = gc.make_smart<Node>(100);
    NewLinkedList(head, 10);
    PrintLinkedList(head);
    cout << "Test2 done" << endl;
}

int main(int argc, const char *argv[]) {
    Test1();
    Test2();
    gc.CollectGarbage();
    cout << "done! exiting 'main'..." << endl;
    return 0;
}
