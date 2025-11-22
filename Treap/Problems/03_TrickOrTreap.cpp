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
    inline static T sumOf(NodeRef root) { return root ? root->sum() : 0; }
    static NodeRef rootOf(NodeRef root) {
        while(root && root->parent()) root = root->parent();
        return root;
    }

    // split first cnt nodes
    static std::pair<NodeRef, NodeRef> split(NodeRef root, int cnt) {
        assert(0 <= cnt && cnt <= sizeOf(root));
        if(root == nullptr) return {nullptr, nullptr};
        if(sizeOf(root->left()) >= cnt) { // left
            auto ret = split(root->left(), cnt);
            if(ret.first) ret.first->setParent(nullptr);
            if(ret.second) ret.second->setParent(nullptr);
            root->setLeft(ret.second);
            ret.second = root;

            return ret;
        }
        // to right
        auto ret = split(root->right(), cnt - sizeOf(root->left()) - 1);
        if(ret.first) ret.first->setParent(nullptr);
        if(ret.second) ret.second->setParent(nullptr);
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
    Node(const T &d) : m_data(d), m_sum(d), m_priority(rng()), m_subtreeSize(1) {}

    T &data() { return m_data; }
    const T &data() const { return m_data; }
    T &sum() { return m_sum; }
    const T &sum() const { return m_sum; }
    NodeRef left() const { return m_left; }
    NodeRef right() const { return m_right; }
    NodeRef parent() const { return m_parent; }
    int priority() const { return m_priority; }
    int size() const { return m_subtreeSize; }

    void setData(const T &data) { m_data = data, recalc(); }
    void setLeft(NodeRef left) { m_left = left, recalc(); }
    void setRight(NodeRef right) { m_right = right, recalc(); }
    void setParent(NodeRef par) { m_parent = par, recalc(); }

    void recalc() {
        m_subtreeSize = 1 + sizeOf(m_left) + sizeOf(m_right);
        m_sum = m_data + sumOf(m_left) + sumOf(m_right);
        if(m_left) m_left->m_parent = this;
        if(m_right) m_right->m_parent = this;
    }

  private:
    T m_data{};
    T m_sum{};
    int m_priority{}, m_subtreeSize{};
    Node *m_left = nullptr, *m_right = nullptr, *m_parent = nullptr;

  private:
    static int rng() {
        static std::mt19937 gen(42);
        return std::uniform_int_distribution<int>()(gen);
    }
};

using node = Node<long long>;

const int N = 500010;
node *a[N] = {nullptr};

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout << setprecision(12) << fixed;

    int qq;
    cin >> qq;

    for(int q = 1; q <= qq; q++) {
        int type;
        cin >> type;

        debug(q, type);
        if(type == 1) {
            long long val;
            cin >> val;
            a[q] = new node(val);
        } else if(type == 2) {
            int y, z;
            cin >> y >> z;
            assert(a[y] && a[z]);
            auto root1 = node::rootOf(a[y]);
            auto root2 = node::rootOf(a[z]);

            if(root1 != root2) {
                node::merge(root1, root2);
            }
        } else if(type == 3) {
            int y, z;
            cin >> y >> z;
            assert(a[y]);
            auto root = node::rootOf(a[y]);
            if(node::sizeOf(root) > z) {
                node::split(root, z);
            }
        } else {
            int y;
            cin >> y;
            auto root = node::rootOf(a[y]);
            assert(root);
            cout << node::sumOf(root) << '\n';
        }
    }

    return 0;
}
