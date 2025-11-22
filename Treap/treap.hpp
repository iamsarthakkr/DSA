#pragma once
#include <random>
#include <utility>
#include <cassert>

namespace treap {
template <typename T>
class Node {
    using NodeRef = Node *;

  public:
    inline static int sizeOf(NodeRef root) { return root ? root->size() : 0; }

    // split first cnt nodes
    static std::pair<NodeRef, NodeRef> split(NodeRef root, int cnt) {
        assert(0 <= cnt && cnt <= sizeOf(root));
        if(root == nullptr) return {nullptr, nullptr};
        if(sizeOf(root->left()) >= cnt) { // left
            auto ret = split(root->left(), cnt);
            root->setLeft(ret.second);
            ret.second = root;

            return ret;
        }
        // to right
        auto ret = split(root->right(), cnt - sizeOf(root->left()) - 1);
        root->setRight(ret.first);
        ret.first = root;

        return ret;
    }

    // merge two nodes (a must come before b)
    static NodeRef merge(NodeRef a, NodeRef b) {
        if(!a) return b;
        if(!b) return a;

        if(a->priority() > b->priority()) {
            // a is root
            a->setRight(merge(a->right(), b));
            return a;
        }
        // b is root
        b->setLeft(merge(a, b->left()));
        return b;
    }

  public:
    Node() = default;
    Node(const T &d) : m_data(d), m_priority(rng()), m_subtreeSize(1) {}

    T &data() { return m_data; }
    const T &data() const { return m_data; }
    NodeRef left() const { return m_left; }
    NodeRef right() const { return m_right; }
    int priority() const { return m_priority; }
    int size() const { return m_subtreeSize; }

    void setData(const T &data) { m_data = data; }
    void setLeft(NodeRef left) { m_left = left, recalc(); }
    void setRight(NodeRef right) { m_right = right, recalc(); }

    void recalc() {
        m_subtreeSize = 1;
        if(m_left != nullptr) m_subtreeSize += m_left->m_subtreeSize;
        if(m_right != nullptr) m_subtreeSize += m_right->m_subtreeSize;
    }

  private:
    T m_data{};
    int m_priority{}, m_subtreeSize{};
    Node *m_left = nullptr, *m_right = nullptr;

  private:
    static int rng() {
        static std::mt19937 gen(42);
        return std::uniform_int_distribution<int>()(gen);
    }
};

template <typename T>
class Treap {
    using NodeType = Node<T>;
    using NodeRef = NodeType *;

  public:
    Treap() = default;

    void insert(const T &val) { insertImpl(val, m_size); }
    void insert(const T &val, int pos) { insertImpl(val, pos); }
    T erase() { return eraseImpl(m_size - 1); }
    T erase(int pos) { return eraseImpl(pos); }

  private:
    void insertImpl(const T &val, int pos) {
        assert(0 <= pos && pos <= m_size);
        NodeRef node = new NodeType(val);
        m_root = insert(m_root, node, pos);
        m_size++;
    }

    T eraseImpl(int pos) {
        assert(0 <= pos && pos < m_size);
        T data;
        m_root = erase(m_root, pos, data);
        m_size--;
        return data;
    }

    NodeRef insert(NodeRef root, NodeRef node, int pos) {
        if(root == nullptr) return node;
        if(node == nullptr) return root;

        if(node->priority() > root->priority()) { // new node is parent
            auto p = NodeType::split(root, pos);
            node->setLeft(p.first);
            node->setRight(p.second);
            return node;
        }
        int left_size = NodeType::sizeOf(root->left());
        if(left_size >= pos) {
            root->setLeft(insert(root->left(), node, pos));
        } else {
            root->setRight(insert(root->right(), node, pos - 1 - left_size));
        }
        return root;
    }

    NodeRef erase(NodeRef root, int pos, T &erased) {
        if(root == nullptr) return root;
        int left_size = NodeType::sizeOf(root->left());

        if(left_size == pos) {
            // delete root
            auto ret = NodeType::merge(root->left(), root->right());
            erased = root->data();
            delete root;
            return ret;
        }
        if(left_size > pos) {
            root->setLeft(erase(root->left(), pos, erased));
        } else {
            root->setRight(erase(root->right(), pos - 1 - left_size, erased));
        }
        return root;
    }

  private:
    // member variables
    NodeRef m_root = nullptr;
    int m_size = 0;
};

} // namespace treap
