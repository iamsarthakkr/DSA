#include "LinkedList.hpp"
#include <vector>

void Test_init() {
    std::vector<int> v = {1, 2, 3, 4};
    LinkedList<int> ll(v);

    ll.print();
    std::cout << '\n';
}

void Test_insertions() {
    LinkedList<int> ll;

    ll.push_back(1);
    ll.push_back(4);

    ll.print();

    ll.push_front(5);
    ll.print();
}

void Test_deletions() {
    std::vector<int> v = {1, 2, 3, 4};
    LinkedList<int> ll(v);

    ll.pop_back();
    ll.print();
    ll.pop_front();
    ll.print();

    ll.push_back(5);
    ll.push_back(6);
    ll.push_back(7);
    ll.pop(3);

    ll.print();
}

int main() {
    // Test_init();
    // Test_insertions();
    Test_deletions();
}
