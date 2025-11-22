#include <bits/stdc++.h>
#include <utility>
using namespace std;

template <typename T> inline bool cmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template <typename T> inline bool cmax(T &a, const T &b) { return b > a ? a = b, true : false; }
#ifdef SARTHAK_LOCAL
#include "/Users/sarthakkumar/work/Cpp/Templates/Common/debug.hpp"
#else
#define debug(...) ((void)0)
#endif

namespace mint {
template <typename T> T inverse(T a, T m) {
    T u = 0, v = 1;
    T mod = m;
    while(a != 0) {
        T t = m / a;
        m -= t * a;
        std::swap(a, m);
        u -= t * v;
        std::swap(u, v);
    }
    assert(m == 1);
    if(u < 0) u += mod;
    return u;
}

template <typename T, typename U> T power(T base, U exp) {
    assert(exp >= 0);
    T res = 1;
    while(exp > 0) {
        if(exp & 1) res *= base;
        base *= base;
        exp >>= 1;
    }
    return res;
}

template <typename VarMod>
class ModInt {
  public:
    using Type = typename std::decay<decltype(VarMod::value)>::type;

    ModInt() : val(0) {}
    template <typename T, typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
    ModInt(T x) : val(normalize(x)) {}

    static Type mod() { return VarMod::value; }

    const Type &operator()() const { return val; }
    template <typename U> explicit operator U() const { return static_cast<U>(val); }

    ModInt &operator+=(const ModInt &other) {
        val = normalize((int64_t)val + (int64_t)other.val);
        return *this;
    }
    ModInt &operator-=(const ModInt &other) {
        val = normalize((int64_t)val - (int64_t)other.val);
        return *this;
    }
    ModInt &operator*=(const ModInt &other) {
        val = normalize((int64_t)val * (int64_t)other.val);
        return *this;
    }
    ModInt &operator/=(const ModInt &other) {
        *this *= ModInt(inverse(other.val, mod()));
        return *this;
    }

    // compound ops with arithmetic types
    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    ModInt &operator+=(U other) { return *this += ModInt(other); }

    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    ModInt &operator-=(U other) { return *this -= ModInt(other); }

    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    ModInt &operator*=(U other) { return *this *= ModInt(other); }

    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    ModInt &operator/=(U other) { return *this /= ModInt(other); }

    ModInt &operator++() { return *this += 1; }
    ModInt &operator--() { return *this -= 1; }

    ModInt operator++(int) {
        ModInt res(*this);
        *this += 1;
        return res;
    }
    ModInt operator--(int) {
        ModInt res(*this);
        *this -= 1;
        return res;
    }

    ModInt operator+() const { return ModInt(val); }
    ModInt operator-() const { return ModInt(-val); }

    friend ModInt operator+(ModInt a, const ModInt &b) {
        a += b;
        return a;
    }
    friend ModInt operator-(ModInt a, const ModInt &b) {
        a -= b;
        return a;
    }
    friend ModInt operator*(ModInt a, const ModInt &b) {
        a *= b;
        return a;
    }
    friend ModInt operator/(ModInt a, const ModInt &b) {
        a /= b;
        return a;
    }

    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    friend ModInt operator+(ModInt a, U b) {
        a += b;
        return a;
    }

    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    friend ModInt operator-(ModInt a, U b) {
        a -= b;
        return a;
    }

    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    friend ModInt operator*(ModInt a, U b) {
        a *= b;
        return a;
    }

    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    friend ModInt operator/(ModInt a, U b) {
        a /= b;
        return a;
    }

    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    friend ModInt operator+(U a, ModInt b) {
        b += a;
        return b;
    }

    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    friend ModInt operator-(U a, ModInt b) {
        ModInt res(a);
        res -= b;
        return res;
    }

    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    friend ModInt operator*(U a, ModInt b) {
        b *= a;
        return b;
    }

    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    friend ModInt operator/(U a, ModInt b) {
        ModInt res(a);
        res /= b;
        return res;
    }

    friend bool operator==(const ModInt &a, const ModInt &b) { return a.val == b.val; }
    friend bool operator!=(const ModInt &a, const ModInt &b) { return a.val != b.val; }

    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    friend bool operator==(const ModInt &a, U b) { return a == ModInt(b); }

    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    friend bool operator==(U a, const ModInt &b) { return ModInt(a) == b; }

    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    friend bool operator!=(const ModInt &a, U b) { return !(a == b); }

    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    friend bool operator!=(U a, const ModInt &b) { return !(a == b); }

    friend bool operator<(const ModInt &a, const ModInt &b) { return a.val < b.val; }
    friend bool operator<=(const ModInt &a, const ModInt &b) { return a.val <= b.val; }
    friend bool operator>(const ModInt &a, const ModInt &b) { return a.val > b.val; }
    friend bool operator>=(const ModInt &a, const ModInt &b) { return a.val >= b.val; }

    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    friend bool operator<(const ModInt &a, U b) { return a < ModInt(b); }

    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    friend bool operator<(U a, const ModInt &b) { return ModInt(a) < b; }

    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    friend bool operator<=(const ModInt &a, U b) { return a <= ModInt(b); }

    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    friend bool operator<=(U a, const ModInt &b) { return ModInt(a) <= b; }

    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    friend bool operator>(const ModInt &a, U b) { return a > ModInt(b); }

    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    friend bool operator>(U a, const ModInt &b) { return ModInt(a) > b; }

    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    friend bool operator>=(const ModInt &a, U b) { return a >= ModInt(b); }

    template <typename U, typename std::enable_if<std::is_arithmetic<U>::value, int>::type = 0>
    friend bool operator>=(U a, const ModInt &b) { return ModInt(a) >= b; }

    friend std::ostream &operator<<(std::ostream &out, const ModInt &n) {
        return out << n.val;
    }

    friend std::istream &operator>>(std::istream &in, ModInt &n) {
        long long x;
        in >> x;
        n = ModInt(x);
        return in;
    }

  private:
    template <typename T>
    static Type normalize(T x) {
        Type m = mod();
        Type v = static_cast<Type>(x % m);
        if(v < 0) v += m;
        return v;
    }

    Type val;
};

template <typename VarMod>
std::string to_string(const ModInt<VarMod> &number) {
    return std::to_string(number());
}

/*
using ModType = int;
struct VarMod {
    static ModType value;
};
ModType VarMod::value = 1000000007;
ModType &md = VarMod::value;
using Mint = ModInt<VarMod>;
*/

constexpr int md = 1000000007;
using Mint = ModInt<std::integral_constant<int, md>>;

/*
static std::vector<Mint> fact(1, Mint(1));
static std::vector<Mint> inv_fact(1, Mint(1));
Mint C(int n, int k) {
    if(k < 0 || k > n) return Mint(0);
    while((int)fact.size() <= n) {
        int i = (int)fact.size();
        fact.emplace_back(fact.back() * i);
        inv_fact.emplace_back(Mint(1) / fact.back());
    }
    return fact[n] * inv_fact[k] * inv_fact[n - k];
}
*/

} // namespace mint
using namespace mint;

const int N = int(6e5) + 1;
template <typename T>
class Node {
    using NodeRef = Node *;

  public:
    inline static int sizeOf(NodeRef root) { return root ? root->size() : 0; }
    inline static const std::pair<Mint, Mint> &hashOf(NodeRef root) { return root ? root->hash() : emptyHash(); }
    inline static const std::pair<Mint, Mint> &reverseHashOf(NodeRef root) { return root ? root->reverseHash() : emptyHash(); }

    inline static void destroy(NodeRef root) {
        if(!root) return;
        destroy(root->left());
        destroy(root->right());
        delete root;
    }

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
    Node(const T &d) : m_data(d), m_priority(rng()), m_subtreeSize(1), m_hash({d, d}), m_reverseHash({d, d}) {}

    T &data() { return m_data; }
    const T &data() const { return m_data; }
    NodeRef left() const { return m_left; }
    NodeRef right() const { return m_right; }
    int priority() const { return m_priority; }
    int size() const { return m_subtreeSize; }
    const std::pair<Mint, Mint> &hash() const { return m_hash; }
    const std::pair<Mint, Mint> &reverseHash() const { return m_reverseHash; }

    void setData(const T &data) { m_data = data, recalc(); }
    void setLeft(NodeRef left) { m_left = left, recalc(); }
    void setRight(NodeRef right) { m_right = right, recalc(); }

    void recalc() {
        m_subtreeSize = 1 + sizeOf(m_left) + sizeOf(m_right);

        {
            // hash
            m_hash.first = hashOf(m_left).first;
            m_hash.first += power1()[sizeOf(m_left)] * m_data;
            m_hash.first += power1()[sizeOf(m_left) + 1] * hashOf(m_right).first;

            m_hash.second = hashOf(m_left).second;
            m_hash.second += power2()[sizeOf(m_left)] * m_data;
            m_hash.second += power2()[sizeOf(m_left) + 1] * hashOf(m_right).second;
        }
        {
            // reverse hash
            m_reverseHash.first = reverseHashOf(m_right).first;
            m_reverseHash.first += power1()[sizeOf(m_right)] * m_data;
            m_reverseHash.first += power1()[sizeOf(m_right) + 1] * reverseHashOf(m_left).first;

            m_reverseHash.second = reverseHashOf(m_right).second;
            m_reverseHash.second += power2()[sizeOf(m_right)] * m_data;
            m_reverseHash.second += power2()[sizeOf(m_right) + 1] * reverseHashOf(m_left).second;
        }
    }

  private:
    T m_data{};
    int m_priority{}, m_subtreeSize{};
    std::pair<Mint, Mint> m_hash{}, m_reverseHash{};
    Node *m_left = nullptr, *m_right = nullptr;

  private:
    static constexpr int base1 = 31;
    static constexpr int base2 = 137;
    static int rng() {
        static std::mt19937 gen(42);
        return std::uniform_int_distribution<int>()(gen);
    }
    static const std::pair<Mint, Mint> &emptyHash() {
        static const std::pair<Mint, Mint> s_emptyHash = {0, 0};
        return s_emptyHash;
    }
    static const std::vector<Mint> &power1() {
        static std::vector<Mint> powers(N);
        static bool init = false;
        if(!init) {
            powers[0] = 1;
            for(int i = 1; i < N; i++) {
                powers[i] = powers[i - 1] * base1;
            }
            init = true;
        }
        return powers;
    }
    static const std::vector<Mint> &power2() {
        static std::vector<Mint> powers(N);
        static bool init = false;
        if(!init) {
            powers[0] = 1;
            for(int i = 1; i < N; i++) {
                powers[i] = powers[i - 1] * base2;
            }
            init = true;
        }
        return powers;
    }
};

void print(Node<int> *root) {
    if(!root) return;
    print(root->left());
    cout << root->data() << " ";
    print(root->right());
}

using node = Node<int>;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout << setprecision(12) << fixed;

    int n, q;
    string s;
    cin >> n >> q >> s;

    Node<int> *root = nullptr;

    for(int i = 0; i < n; i++) {
        int val = s[i] - 'a' + 1;

        root = node::merge(root, new Node(val));
    }

    while(q--) {
        int type;
        cin >> type;
        if(type == 1) {
            int l, r;
            cin >> l >> r;

            auto [left, right] = node::split(root, l - 1);
            auto [toDelete, rem] = node::split(right, r - l + 1);
            root = node::merge(left, rem);

            node::destroy(toDelete);
        } else if(type == 2) {
            char c;
            int p;
            cin >> c >> p;
            int val = c - 'a' + 1;

            auto nn = new node(val);

            auto [left, right] = node::split(root, p - 1);

            root = node::merge(left, nn);
            root = node::merge(root, right);
        } else {
            int l, r;
            cin >> l >> r;

            auto [left, rem] = node::split(root, l - 1);
            auto [sub, right] = node::split(rem, r - l + 1);

            auto h = node::hashOf(sub), revH = node::reverseHashOf(sub);
            debug(l, r, h, revH);
            cout << (h == revH ? "yes" : "no") << '\n';

            root = node::merge(left, sub);
            root = node::merge(root, right);
        }
    }

    return 0;
}
