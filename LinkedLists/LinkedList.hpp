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
            this->insert_end(val);
        }
    }

    bool empty() const { return m_size == 0; }
    size_t size() const { return m_size; }

    void push_back(const T &val) { insert_end(val); }
    void push_front(const T &val) { insert_start(val); }
    void pop_front() { delete_node(0); }
    void pop_back() {
        if(empty()) {
            return;
        }
        delete_node(m_size - 1);
    }
    void pop(size_t k) { delete_node(k); }

    void print() {
        auto node = m_head;
        while(node != nullptr) {
            std::cout << node->val << " ";
            node = node->next;
        }
        std::cout << '\n';
    }

  private:
    void insert_end(const T &val) {
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

    void insert_start(const T &val) {
        m_size += 1;
        Node<T> *node = new Node(val);

        node->next = m_head;
        m_head = node;
    }
    void delete_node(size_t pos) {
        if(m_size == 0 || pos >= m_size) {
            return;
        }

        m_size -= 1;
        if(pos == 0) {
            auto temp = m_head;
            m_head = m_head->next;
            delete temp;

            return;
        }

        auto curr = m_head;
        for(int i = 0; i < pos - 1; i++) {
            curr = curr->next;
        }

        auto next = curr->next;
        curr->next = next->next;
        delete next;
    }

  private:
    Node<T> *m_head = nullptr;
    size_t m_size = 0;
};
