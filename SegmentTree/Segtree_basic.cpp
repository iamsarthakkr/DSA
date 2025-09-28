#include <bits/stdc++.h>
using namespace std;

template <typename Node>
class SegtreeImpl {
  public:
    explicit SegtreeImpl(int n) { init(n); }
    explicit SegtreeImpl(const vector<Node> &info) : SegtreeImpl((int)info.size()) { build(1, 0, m_size, info); }
    template <typename T>
    explicit SegtreeImpl(vector<T> &info) : SegtreeImpl((int)info.size()) { build(1, 0, m_size, info); }

    void set(int i, const Node &v) { setImpl(1, 0, m_size, i, v); }
    Node calc(int l, int r) { return calcImpl(1, 0, m_size, l, r); }

  private:
    void setImpl(int node, int lx, int rx, int i, const Node &v) {
        if(rx - lx == 1) {
            m_tree[node] = v;
            return;
        }
        int m = (lx + rx) >> 1;
        if(i < m) {
            setImpl(node << 1, lx, m, i, v);
        } else {
            setImpl(node << 1 | 1, m, rx, i, v);
        }
        recalc(node, lx, rx);
    }

    Node calcImpl(int node, int lx, int rx, int l, int r) {
        if(rx <= l || r <= lx) return Node();
        if(l <= lx && rx <= r) return m_tree[node];
        int m = (lx + rx) >> 1;
        auto s1 = calcImpl(node << 1, lx, m, l, r);
        auto s2 = calcImpl(node << 1 | 1, m, rx, l, r);
        return Node::merge(s1, s2);
    }

  private:
    void recalc(int node, int lx, int rx) {
        if(rx - lx == 1) return;
        m_tree[node] = Node::merge(m_tree[node << 1], m_tree[node << 1 | 1]);
    }

    void init(int n) {
        m_size = 1;
        while(m_size < n) m_size <<= 1;
        m_tree.resize(2 * m_size, Node());
    }

    template <typename T>
    void build(int node, int lx, int rx, vector<T> &arr) {
        if(rx - lx == 1) {
            if(lx < (int)arr.size()) m_tree[node] = arr[lx];
            return;
        }
        int m = (lx + rx) >> 1;
        build(node << 1, lx, m, arr);
        build(node << 1 | 1, m, rx, arr);

        recalc(node, lx, rx);
    }

  private:
    int m_size;
    vector<Node> m_tree;
};

template <typename T>
struct SumNode {
    T val;
    SumNode() : val(T(0)) {}
    SumNode(const T &v) : val(v) {}

    static SumNode merge(const SumNode &a, const SumNode &b) {
        SumNode res;
        res.val = a.val + b.val;
        return res;
    }
};

// template <typename T> using Segtree = SegtreeImpl<SumNode<T>>;
