#include <bits/stdc++.h>

/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>template
*/

using namespace std;
// using namespace __gnu_pbds;

// typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

typedef long long ll;
typedef unsigned long long ull;
typedef long double lld;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<vi> vvi;
typedef vector<vll> vvll;
typedef vector<pii> vpii;
typedef vector<pll> vpll;

#define pb push_back
#define fi first
#define se second
#define forn(i, n) for(int i = 0; i < n; i++)
#define forv(x, a) for(auto &x : a)
#define ford(i, n) for(int i = n - 1; i >= 0; i--)
#define for1(i, n) for(int i = 1; i <= n; i++)
#define forr(i, l, r) for(int i = l; i <= r; i++)
#define forrd(i, l, r) for(int i = r; i >= l; i--)
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define len(a) (int)(a).size()
#define sq(x) (x) * (x)

#ifdef SARTHAK_LOCAL
#include "/Users/sarthakkumar/work/Cpp/Templates/CP_Templates/debug.cpp"
#else
#define debug(...) 69
#endif

template <typename T> T gcd(T a, T b) {
    while(b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

bool islower(char c) { return c >= 'a' && c <= 'z'; }
bool isupper(char c) { return c >= 'A' && c <= 'Z'; }
void tolower(char &c) { c = isupper(c) ? c = 'a' + (c - 'A') : c; }
void toupper(char &c) { c = islower(c) ? c = 'A' + (c - 'a') : c; }
template <typename T> bool cmin(T &a, T b) { return b < a ? a = b, 1 : 0; }
template <typename T> bool cmax(T &a, T b) { return b > a ? a = b, 1 : 0; }

template <typename Node>
class SegtreeImpl {
  public:
    explicit SegtreeImpl(int n) { init(n); }
    explicit SegtreeImpl(const vector<Node> &info) : SegtreeImpl((int)info.size()) { build(1, 0, m_size, info); }
    template <typename T>
    explicit SegtreeImpl(vector<T> &info) : SegtreeImpl((int)info.size()) { build(1, 0, m_size, info); }

    void set(int i, const Node &v) { setImpl(1, 0, m_size, i, v); }
    Node calc(int l, int r) { return calcImpl(1, 0, m_size, l, r); }
    template <typename F> int maxRight(int l, F pred) {
        Node acc;
        return maxRightImpl(1, 0, m_size, l, pred, acc);
    };
    template <typename F> int minLeft(int r, F pred) {
        Node acc;
        return minLeftImpl(1, 0, m_size, r, pred, acc);
    };

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

template <typename T> using Segtree = SegtreeImpl<SumNode<T>>;

void Main(int tc) {
    int n, q;
    cin >> n >> q;
    vi a(n);
    forn(i, n) cin >> a[i];

    Segtree<int> st(a);

    while(q--) {
        int type;
        cin >> type;
        if(type == 1) {
            int i;
            cin >> i;
            a[i] ^= 1;
            st.set(i, a[i]);
        } else {
            int k;
            cin >> k;
            int ans = st.maxRight(0, [&](const SumNode<int> &node) {
                return node.val <= k;
            });
            cout << ans << '\n';
        }
    }
}

// #define MULTI // comment for single test

int main() {
    ios::sync_with_stdio(0), cin.tie(NULL), cout << setprecision(12) << fixed;

    int tt = 1;
#ifdef MULTI
    cin >> tt;
#endif

    for(int t = 1; t <= tt; t++) {
#ifdef SARTHAK_LOCAL
        cerr << "Test Case: #" << t << '\n';
        cerr << "---------------" << '\n';
#endif

        Main(t);

#ifdef SARTHAK_LOCAL
        cerr << "---------------" << '\n';
#endif
    }

#ifdef SARTHAK_LOCAL
    cerr << "Total Time: " << (double)clock() * 1e3 / CLOCKS_PER_SEC << "ms" << '\n';
#endif
    return 0;
}
