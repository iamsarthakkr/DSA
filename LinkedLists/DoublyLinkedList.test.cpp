#include "DoublyLinkedList.hpp"
#include <vector>

void Test_init() {
    std::vector<int> v = {1, 2, 3, 4};
    DoublyLinkedList<int> dll(v);
    dll.print();
}

void Test_insertions() {
    DoublyLinkedList<int> dll;

    dll.push(0, 1);
    dll.push(0, 2);
    dll.push(2, 4);
    dll.print();

    dll.clear();

    dll.push_back(1);
    dll.push_front(10);
    dll.print();
}

void Test_deletions() {
    std::vector<int> v = {1, 2, 3, 4};
    DoublyLinkedList<int> dll(v);

    dll.print();
    dll.pop_back();
    dll.pop_front();
    dll.print();

    dll.push(2, 10);
    dll.push(2, 12);

    dll.print();

    dll.pop(1);
    dll.print();

    dll.pop(2);
    dll.print();

    dll.pop(1);
    dll.print();

    dll.pop(0);
    dll.print();
}

int main() {
    // Test_init();
    // Test_insertions();
    Test_deletions();
}
