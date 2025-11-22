#include <bits/stdc++.h>
using namespace std;

template <typename T> inline bool cmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template <typename T> inline bool cmax(T &a, const T &b) { return b > a ? a = b, true : false; }

#ifdef SARTHAK_LOCAL
#include "/Users/sarthakkumar/work/Cpp/Templates/Common/debug.hpp"
#else
#define debug(...) ((void)0)
#endif

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
        if(m_left != nullptr) m_subtreeSize += m_left->size();
        if(m_right != nullptr) m_subtreeSize += m_right->size();
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

void print(Node<int> *root) {
    if(!root) return;
    print(root->left());
    cout << root->data() << " ";
    print(root->right());
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout << setprecision(12) << fixed;

    int n;
    cin >> n;

    Node<int> *root = nullptr;

    for(int i = 1; i <= n; i++) {
        root = Node<int>::merge(root, new Node<int>(i));
    }

    for(int i = 0; i < n; i++) {
        int a, b;
        cin >> a >> b;
        if(a >= b) continue;

        auto [l, r] = Node<int>::split(root, a - 1);
        int split = min(n - b + 1, b - a);
        auto [ap, bp] = Node<int>::split(r, b - a);
        auto [a1, a2] = Node<int>::split(ap, split);
        auto [b1, b2] = Node<int>::split(bp, split);

        root = Node<int>::merge(l, b1);
        root = Node<int>::merge(root, a2);
        root = Node<int>::merge(root, a1);
        root = Node<int>::merge(root, b2);
    }

    print(root);
    cout << '\n';

    return 0;
}
