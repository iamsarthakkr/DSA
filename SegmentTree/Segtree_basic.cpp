#include <bits/stdc++.h>
using namespace std;

/******************** Segtree ********************/

template <typename Node>
class SegtreeImpl {
  public:
    explicit SegtreeImpl(int n) { init(n); }
    explicit SegtreeImpl(const vector<Node> &info) : SegtreeImpl((int)info.size()) { build(1, 0, m_size, info); }
    template <typename T>
    explicit SegtreeImpl(const vector<T> &info) : SegtreeImpl((int)info.size()) { build(1, 0, m_size, info); }

    const int size() const { return m_origSize; }

    void set(int i, const Node &v) { setImpl(1, 0, m_size, i, v); }
    Node calc(int l, int r) { return calcImpl(1, 0, m_size, l, r); }
    template <typename F> int maxRight(int l, F pred) {
        Node acc;
        assert(pred(acc));
        auto res = maxRightImpl(1, 0, m_size, l, pred, acc);
        return std::min(m_origSize, res);
    };
    template <typename F> int minLeft(int r, F pred) {
        Node acc;
        assert(pred(acc));
        auto res = minLeftImpl(1, 0, m_size, r, pred, acc);
        return std::max(0, res);
    };

  private:
    void setImpl(int node, int lx, int rx, int i, const Node &v) {
        if(rx - lx == 1) {
            m_tree[node] = v;
            return;
        }
        int m = (lx + rx) >> 1;
        if(i < m)
            setImpl(node << 1, lx, m, i, v);
        else
            setImpl(node << 1 | 1, m, rx, i, v);

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

    template <typename F> int maxRightImpl(int node, int lx, int rx, int l, F &pred, Node &acc) {
        if(rx <= l) return l;
        if(l <= lx) {
            Node res = Node::merge(acc, m_tree[node]);
            if(pred(res)) {
                acc = std::move(res);
                return rx;
            }
            if(rx - lx == 1) return lx;
        }
        if(rx - lx == 1) return l;

        int m = (lx + rx) >> 1;

        int r1 = maxRightImpl(node << 1, lx, m, l, pred, acc);
        if(r1 < m) return r1;
        return maxRightImpl(node << 1 | 1, m, rx, l, pred, acc);
    }
    template <typename F> int minLeftImpl(int node, int lx, int rx, int r, F &pred, Node &acc) {
        if(r <= lx) return r;
        if(rx <= r) {
            Node res = Node::merge(m_tree[node], acc);
            if(pred(res)) {
                acc = std::move(res);
                return lx;
            }
            if(rx - lx == 1) return rx;
        }
        if(rx - lx == 1) return r;

        int m = (lx + rx) >> 1;

        int l1 = minLeftImpl(node << 1 | 1, m, rx, r, pred, acc);
        if(l1 > m) return l1;
        return minLeftImpl(node << 1, lx, m, r, pred, acc);
    }

  private:
    void recalc(int node, int lx, int rx) {
        if(rx - lx == 1) return;
        m_tree[node] = Node::merge(m_tree[node << 1], m_tree[node << 1 | 1]);
    }

    void init(int n) {
        m_origSize = n;
        m_size = 1;
        while(m_size < n) m_size <<= 1;
        m_tree.resize(2 * m_size, Node());
    }

    template <typename T>
    void build(int node, int lx, int rx, const vector<T> &arr) {
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
    int m_origSize;
    vector<Node> m_tree;
};
struct Node {

    Node() {}

    static Node merge(const Node &a, const Node &b) {
        Node res;

        return res;
    }
};
using Segtree = SegtreeImpl<Node>;

/******************** Common Nodes ********************/

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

template <typename T>
struct MaxNode {
    T val;
    MaxNode() : val(std::numeric_limits<T>::min()) {}
    MaxNode(const T &v) : val(v) {}

    static MaxNode merge(const MaxNode &a, const MaxNode &b) {
        MaxNode res;
        res.val = std::max(a.val, b.val);
        return res;
    }
};
// template <typename T> using Segtree = SegtreeImpl<MaxNode<T>>;

template <typename T>
struct MinNode {
    T val;
    MinNode() : val(std::numeric_limits<T>::max()) {}
    MinNode(const T &v) : val(v) {}

    static MinNode merge(const MinNode &a, const MinNode &b) {
        MinNode res;
        res.val = std::min(a.val, b.val);
        return res;
    }
};
// template <typename T> using Segtree = SegtreeImpl<MinNode<T>>;

template <typename T>
struct MinCountNode {
    T mn;
    int cnt;
    MinCountNode() : mn(std::numeric_limits<T>::max()), cnt(0) {}
    MinCountNode(T v, int c = 1) : mn(v), cnt(c) {}

    static MinCountNode merge(const MinCountNode &a, const MinCountNode &b) {
        if(a.mn < b.mn) return a;
        if(b.mn < a.mn) return b;
        return {a.mn, a.cnt + b.cnt};
    }
};
// template <typename T> using Segtree = SegtreeImpl<MinCountNode<T>>;

/******************** Test Utilities ********************/
template <typename T>
T rangeSumBruteForce(const vector<T> &a, int l, int r) {
    l = max(l, 0);
    r = min(r, (int)a.size());
    T s = 0;
    for(int i = l; i < r; ++i) s += a[i];
    return s;
}
template <typename T>
T rangeMaxBruteForce(const vector<T> &a, int l, int r) {
    l = max(l, 0);
    r = min(r, (int)a.size());
    T m = std::numeric_limits<T>::lowest();
    for(int i = l; i < r; ++i) m = max(m, a[i]);
    return m;
}
template <typename T>
T rangeMinBruteForce(const vector<T> &a, int l, int r) {
    l = max(l, 0);
    r = min(r, (int)a.size());
    T m = std::numeric_limits<T>::max();
    for(int i = l; i < r; ++i) m = min(m, a[i]);
    return m;
}
template <typename T>
pair<T, int> rangeMinCountBruteForce(const vector<T> &a, int l, int r) {
    l = max(l, 0);
    r = min(r, (int)a.size());
    T mn = std::numeric_limits<T>::max();
    int c = 0;
    for(int i = l; i < r; ++i) {
        if(a[i] < mn) {
            mn = a[i];
            c = 1;
        } else if(a[i] == mn)
            ++c;
    }
    if(l >= r) { return {std::numeric_limits<T>::max(), 0}; }
    return {mn, c};
}

/******************** Tests ********************/

void test_sum_deterministic() {
    vector<long long> a = {1, 2, 3, 4, 5};
    SegtreeImpl<SumNode<long long>> seg(a);
    assert(seg.calc(0, 5).val == 15);
    assert(seg.calc(1, 4).val == 9);
    seg.set(2, 10); // a = [1,2,10,4,5]
    assert(seg.calc(0, 5).val == 22);
    assert(seg.calc(2, 3).val == 10);
}

void test_max_deterministic() {
    vector<int> a = {-5, 7, 1, 7, -2};
    SegtreeImpl<MaxNode<int>> seg(a);
    assert(seg.calc(0, 5).val == 7);
    assert(seg.calc(1, 3).val == 7);
    seg.set(1, MaxNode<int>(-10));
    assert(seg.calc(0, 5).val == 7);
    seg.set(3, MaxNode<int>(8));
    assert(seg.calc(0, 5).val == 8);
}

void test_min_deterministic() {
    vector<int> a = {4, 2, 6, 2, 9};
    SegtreeImpl<MinNode<int>> seg(a);
    assert(seg.calc(0, 5).val == 2);
    assert(seg.calc(2, 5).val == 2);
    seg.set(1, MinNode<int>(-3));
    assert(seg.calc(0, 5).val == -3);
}

void test_mincount_deterministic() {
    vector<int> a = {3, 1, 2, 1, 1, 5};
    SegtreeImpl<MinCountNode<int>> seg(a);
    auto res = seg.calc(0, 6);
    assert(res.mn == 1 && res.cnt == 3);
    res = seg.calc(2, 5);
    // [2,1,1] -> mn = 1, cnt = 2
    assert(res.mn == 1 && res.cnt == 2);
    seg.set(3, MinCountNode<int>(-7));
    res = seg.calc(0, 6);
    assert(res.mn == -7 && res.cnt == 1);
}

void test_maxRight_minLeft_sum_predicate() {
    // Find the longest prefix starting at l such that prefix sum <= K
    vector<int> a = {2, -1, 3, 4, -2, 1};
    SegtreeImpl<SumNode<long long>> seg(a);
    long long K = 4;
    auto pred = [&](const SumNode<long long> &x) { return x.val <= K; };

    int l = 0;
    int r = seg.maxRight(l, pred); // expect sum[0..r) <= 4 maximally
    // brute
    long long s = 0;
    int rb = l;
    for(int i = l; i < (int)a.size(); ++i) {
        if(s + a[i] <= K) {
            s += a[i];
            rb = i + 1;
        } else
            break;
    }
    assert(r == rb);

    // minLeft: given r, find minimal l s.t. sum[l..r) <= K maximally pushed left
    r = (int)a.size();
    auto pred2 = [&](const SumNode<long long> &x) { return x.val <= K; };
    int lb = r;
    s = 0;
    for(int i = r - 1; i >= 0; --i) {
        if(a[i] + s <= K) {
            s += a[i];
            lb = i;
        } else
            break;
    }
    int l2 = seg.minLeft(r, pred2);
    assert(l2 == lb);
}

void randomized_crosscheck_sum(int N = 200, int Q = 200) {
    std::mt19937 rng(123);
    for(int it = 0; it < 50; ++it) {
        int n = rng() % N + 1;
        vector<long long> a(n);
        for(int i = 0; i < n; ++i) a[i] = (rng() % 200) - 100;

        SegtreeImpl<SumNode<long long>> seg(a);

        for(int q = 0; q < Q; ++q) {
            int type = rng() % 3;
            if(type == 0) { // set
                int i = rng() % n;
                long long v = (rng() % 200) - 100;
                seg.set(i, SumNode<long long>(v));
                a[i] = v;
            } else if(type == 1) { // calc
                int l = rng() % (n + 1);
                int r = rng() % (n + 1);
                if(l > r) swap(l, r);
                auto got = seg.calc(l, r).val;
                auto bf = rangeSumBruteForce(a, l, r);
                if(got != bf) {
                    cerr << "Sum mismatch: got=" << got << " bf=" << bf << " l=" << l << " r=" << r << "\n";
                    assert(false);
                }
            } else { // maxRight with K
                int l = rng() % n;
                long long K = (rng() % 400) - 100;
                auto pred = [&](const SumNode<long long> &x) { return x.val <= K; };
                int r = seg.maxRight(l, pred);

                long long s = 0;
                int rb = l;
                for(int i = l; i < n; ++i) {
                    if(s + a[i] <= K) {
                        s += a[i];
                        rb = i + 1;
                    } else
                        break;
                }
                if(r != rb) {
                    cerr << "maxRight mismatch: got=" << r << " bf=" << rb << " l=" << l << " K=" << K << "\n";
                    assert(false);
                }
            }
        }
    }
}

void randomized_crosscheck_max_min(int N = 200, int Q = 200) {
    std::mt19937 rng(321);
    for(int it = 0; it < 40; ++it) {
        int n = rng() % N + 1;
        vector<int> a(n);
        for(int i = 0; i < n; ++i) a[i] = (rng() % 200) - 100;

        SegtreeImpl<MaxNode<int>> segMax(a);
        SegtreeImpl<MinNode<int>> segMin(a);

        for(int q = 0; q < Q; ++q) {
            int type = rng() % 3;
            if(type == 0) {
                int i = rng() % n;
                int v = (rng() % 200) - 100;
                segMax.set(i, MaxNode<int>(v));
                segMin.set(i, MinNode<int>(v));
                a[i] = v;
            } else {
                int l = rng() % (n + 1);
                int r = rng() % (n + 1);
                if(l > r) swap(l, r);
                auto gmax = segMax.calc(l, r).val;
                auto gmin = segMin.calc(l, r).val;
                auto bmax = rangeMaxBruteForce(a, l, r);
                auto bmin = rangeMinBruteForce(a, l, r);
                if(gmax != bmax || gmin != bmin) {
                    cerr << "Max/Min mismatch\n";
                    assert(false);
                }
            }
        }
    }
}

void randomized_crosscheck_mincount(int N = 200, int Q = 200) {
    std::mt19937 rng(777);
    for(int it = 0; it < 30; ++it) {
        int n = rng() % N + 1;
        vector<int> a(n);
        for(int i = 0; i < n; ++i) a[i] = (rng() % 50) - 25;

        SegtreeImpl<MinCountNode<int>> seg(a);

        for(int q = 0; q < Q; ++q) {
            int type = rng() % 2;
            if(type == 0) {
                int i = rng() % n;
                int v = (rng() % 50) - 25;
                seg.set(i, MinCountNode<int>(v));
                a[i] = v;
            } else {
                int l = rng() % (n + 1);
                int r = rng() % (n + 1);
                if(l > r) swap(l, r);
                auto got = seg.calc(l, r);
                auto bf = rangeMinCountBruteForce(a, l, r);
                if(!((got.mn == bf.first && got.cnt == bf.second) ||
                     (l == r && got.cnt == 0 && got.mn == std::numeric_limits<int>::max()))) {
                    cerr << "MinCount mismatch\n";
                    assert(false);
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Deterministic sanity
    test_sum_deterministic();
    test_max_deterministic();
    test_min_deterministic();
    test_mincount_deterministic();
    test_maxRight_minLeft_sum_predicate();

    // Randomized cross-checks vs brute force
    randomized_crosscheck_sum();
    randomized_crosscheck_max_min();
    randomized_crosscheck_mincount();

    cout << "All tests passed!\n";
    return 0;
}
