#pragma once

#include <cassert>
#include <complex>
#include <iostream>
#include <vector>
template <typename T>
struct Node {
    T val;
    Node *next = nullptr;
    Node *prev = nullptr;

    Node() {}
    Node(T val) { this->val = val; }
};

template <typename T>
class DoublyLinkedList {
  public:
    DoublyLinkedList() {
        m_head = new Node(0);
        m_tail = new Node(0);
        m_head->next = m_tail;
        m_tail->prev = m_head;
    }

    DoublyLinkedList(const std::vector<T> &v) : DoublyLinkedList() {
        for(auto const &val : v) {
            this->insert_node(m_size, val);
        }
    }

    void clear() {
        for(auto node = m_head->next; node != m_tail;) {
            auto next = node->next;
            delete node;
            node = next;
        }
        m_size = 0;
        m_head->next = m_tail;
        m_tail->prev = m_head;
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
        for(auto node = m_head->next; node != m_tail; node = node->next) {
            std::cout << node->val << " ";
        }
        std::cout << '\n';
    }

    void reverse() {

        for(auto node = m_head; node != nullptr;) {
            std::swap(node->next, node->prev);
            node = node->prev;
        }
        std::swap(m_head, m_tail);
    }

  private:
    void insert_node(size_t pos, const T &val) {
        if(pos > m_size) {
            return;
        }

        Node<T> *curr = m_head;
        for(size_t i = 0; i < pos; i++) {
            curr = curr->next;
        }

        Node<T> *node = new Node(val);
        node->next = curr->next;
        node->prev = curr;

        curr->next->prev = node;
        curr->next = node;
        m_size += 1;
    }

    void delete_node(size_t pos) {
        if(m_size == 0 || pos >= m_size) {
            return;
        }

        Node<T> *curr = m_head;
        for(size_t i = 0; i <= pos; i++) {
            curr = curr->next;
        }

        Node<T> *prev = curr->prev, *next = curr->next;
        prev->next = next;
        next->prev = prev;
        delete curr;
        m_size -= 1;
    }

  private:
    Node<T> *m_head = nullptr;
    Node<T> *m_tail = nullptr;
    size_t m_size = 0;
};
