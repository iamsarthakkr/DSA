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

    ll.insert(1);
    ll.insert(4);
    ll.insert(8);
    ll.insert(12);
    ll.print();
    std::cout << '\n';
}
int main() {
    Test_init();
    Test_insertions();
}
