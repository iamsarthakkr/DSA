#pragma once

#include <cassert>
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
            this->insert_node(m_size, val);
        }
    }

    bool empty() const { return m_size == 0; }
    size_t size() const { return m_size; }

    void push_back(const T &val) { insert_node(m_size, val); }
    void push_front(const T &val) { insert_node(0, val); }
    void push(size_t k, const T &val) { insert_node(k, val); }
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
    void insert_node(size_t pos, const T &val) {
        if(empty()) {
            if(pos == 0) {
                m_size += 1;
                Node<T> *node = new Node(val);
                m_head = node;
            }
            return;
        }
        if(pos > m_size) {
            return;
        }
        m_size += 1;

        Node<T> *prev = nullptr, *curr = m_head;
        for(int i = 0; i < pos; i++) {
            prev = curr;
            curr = curr->next;
        }

        Node<T> *node = new Node(val);
        node->next = curr;
        if(!prev) {
            m_head = node;
        } else {
            prev->next = node;
        }
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
