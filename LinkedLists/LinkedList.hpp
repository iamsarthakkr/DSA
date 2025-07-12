#pragma once

#include <iostream>
#include <vector>
template <typename T>
struct Node {
    T val;
    Node *next = nullptr;

    Node() {}
    Node(T val) { this->val = val; }
};

template <typename T>
class LinkedList {
  public:
    LinkedList() {}
    LinkedList(const std::vector<T> &v) {
        for(auto const &val : v) {
            this->insert(val);
        }
    }

    size_t size() const { return m_size; }

    void insert(const T &val) {
        m_size += 1;
        Node<T> *node = new Node(val);

        if(m_head == nullptr) {
            m_head = node;
            return;
        }
        auto curr = m_head;
        while(curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = node;
    }

    void print() {
        auto node = m_head;
        while(node != nullptr) {
            std::cout << node->val << " ";
            node = node->next;
        }
    }

  private:
    Node<T> *m_head = nullptr;
    size_t m_size = 0;
};
