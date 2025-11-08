#include <bits/stdc++.h>
using namespace std;

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

template <typename T>
T inverse(T a, T m) {
    T u = 0, v = 1;
    while(a != 0) {
        T t = m / a;
        m -= t * a;
        swap(a, m);
        u -= t * v;
        swap(u, v);
    }
    assert(m == 1);
    return u;
}

template <typename VarMod>
class ModInt {
  public:
    using Type = typename decay<decltype(VarMod::value)>::type;

  public:
    ModInt() : v(0) {}

    template <typename T>
    ModInt(T v_) {
        v = normalize(v_);
    }

    static const Type mod() { return VarMod::value; }

    const Type &operator()() const { return v; }
    template <typename U> explicit operator U() const { return static_cast<U>(v); }

    ModInt &operator+=(const ModInt &other) {
        v = normalize((int64_t)v + (int64_t)other.v);
        return *this;
    }
    ModInt &operator-=(const ModInt &other) {
        v = normalize((int64_t)v - (int64_t)other.v);
        return *this;
    }
    ModInt &operator*=(const ModInt &other) {
        v = normalize((int64_t)v * (int64_t)other.v);
        return *this;
    }
    ModInt &operator/=(const ModInt &other) {
        *this *= ModInt(inverse(other.v, mod()));
        return *this;
    }

    template <typename U> ModInt &operator+=(const U &other) { return *this += ModInt(other); }
    template <typename U> ModInt &operator-=(const U &other) { return *this -= ModInt(other); }
    template <typename U> ModInt &operator*=(const U &other) { return *this *= ModInt(other); }
    template <typename U> ModInt &operator/=(const U &other) { return *this /= ModInt(other); }

    ModInt &operator++() { return *this += 1; }
    ModInt &operator--() { return *this -= 1; }

    ModInt operator++(int) {
        ModInt result(*this);
        *this += 1;
        return result;
    }
    ModInt operator--(int) {
        ModInt result(*this);
        *this -= 1;
        return result;
    }

    ModInt operator+() const { return ModInt(v); }
    ModInt operator-() const { return ModInt(-v); }

    friend ModInt operator+(const ModInt &a, const ModInt &b) { return ModInt(a) += b; }
    friend ModInt operator-(const ModInt &a, const ModInt &b) { return ModInt(a) -= b; }
    friend ModInt operator*(const ModInt &a, const ModInt &b) { return ModInt(a) *= b; }
    friend ModInt operator/(const ModInt &a, const ModInt &b) { return ModInt(a) /= b; }

    template <typename U> friend ModInt operator+(const ModInt &a, const U &b) { return ModInt(a) += b; }
    template <typename U> friend ModInt operator-(const ModInt &a, const U &b) { return ModInt(a) -= b; }
    template <typename U> friend ModInt operator*(const ModInt &a, const U &b) { return ModInt(a) *= b; }
    template <typename U> friend ModInt operator/(const ModInt &a, const U &b) { return ModInt(a) /= b; }

    template <typename U> friend ModInt operator+(const U &a, const ModInt &b) { return ModInt(a) += b; }
    template <typename U> friend ModInt operator-(const U &a, const ModInt &b) { return ModInt(a) -= b; }
    template <typename U> friend ModInt operator*(const U &a, const ModInt &b) { return ModInt(a) *= b; }
    template <typename U> friend ModInt operator/(const U &a, const ModInt &b) { return ModInt(a) /= b; }

    friend bool operator==(const ModInt &a, const ModInt &b) { return a.v == b.v; }
    friend bool operator!=(const ModInt &a, const ModInt &b) { return !(a == b); }

    template <typename U> friend bool operator==(const ModInt &a, const U &b) { return a.v == ModInt(b); }
    template <typename U> friend bool operator==(const U &a, const ModInt &b) { return ModInt(a) == b; }

    template <typename U> friend bool operator!=(const ModInt &a, const U &b) { return a.v != ModInt(b); }
    template <typename U> friend bool operator!=(const U &a, const ModInt &b) { return ModInt(a) != b; }

    friend bool operator<(const ModInt &a, const ModInt &b) { return a.v < b.v; }
    template <typename U> friend bool operator<(const ModInt &a, const U &b) { return a < ModInt(b); }
    template <typename U> friend bool operator<(const U &a, const ModInt &b) { return ModInt(a) < b; }

    friend bool operator<=(const ModInt &a, const ModInt &b) { return a.v <= b.v; }
    template <typename U> friend bool operator<=(const ModInt &a, const U &b) { return a <= ModInt(b); }
    template <typename U> friend bool operator<=(const U &a, const ModInt &b) { return ModInt(a) <= b; }

    friend bool operator>(const ModInt &a, const ModInt &b) { return a.v > b.v; }
    template <typename U> friend bool operator>(const ModInt &a, const U &b) { return a > ModInt(b); }
    template <typename U> friend bool operator>(const U &a, const ModInt &b) { return ModInt(a) > b; }

    friend bool operator>=(const ModInt &a, const ModInt &b) { return a.v >= b.v; }
    template <typename U> friend bool operator>=(const ModInt &a, const U &b) { return a >= ModInt(b); }
    template <typename U> friend bool operator>=(const U &a, const ModInt &b) { return ModInt(a) >= b; }

    friend std::ostream &operator<<(std::ostream &out, const ModInt &n) { return out << Type(n); }
    friend std::istream &operator>>(std::istream &in, ModInt &n) {
        int64_t v_;
        in >> v_;
        n = ModInt(v_);
        return in;
    }

  private:
    template <typename T>
    static Type normalize(T x) {
        Type v = static_cast<Type>(x % mod());

        if(v < 0) v += mod();
        return v;
    }

  private:
    Type v;
};

template <typename T, typename U>
T power(const T &base, const U &exp) {
    assert(exp >= 0);
    T x = base, res = 1;
    U p = exp;
    while(p > 0) {
        if(p & 1) res *= x;
        x *= x;
        p >>= 1;
    }
    return res;
}

template <typename T>
std::string to_string(const ModInt<T> &number) {
    return to_string(number());
}

/*
using ModType = int;
struct VarMod { static ModType value; };
ModType VarMod::value = 1000000007;
ModType& md = VarMod::value;

using Mint = ModInt<VarMod>;
*/

constexpr int md = 1000000007;
using Mint = ModInt<std::integral_constant<decay<decltype(md)>::type, md>>;

/*
std::vector<Mint> fact(1, 1);
std::vector<Mint> inv_fact(1, 1);

Mint C(int n, int k) {
    if (k < 0 || k > n) return 0;

    while((int)fact.size() < n + 1) {
        fact.push_back(fact.back() * (int)fact.size());
        inv_fact.push_back(1 / fact.back());
    }
    return fact[n] * inv_fact[k] * inv_fact[n - k];
}
*/

template <typename T_Iterable, typename Mod>
class Hash {
  public:
    Hash() = delete;
    Hash(const T_Iterable &s, Mod base = Mod(31)) { build(s, base); }
    Mod operator()(int l, int r) const {
        assert(l >= 0 && l <= r && r <= m_size);
        Mod r_hash = m_hash[r], l_hash = m_hash[l];
        return r_hash - l_hash * m_power[r - l];
    }
    Mod operator()(int i) const {
        assert(0 <= i && i <= m_size);
        return m_hash[i];
    }
    Mod operator()() const { return m_hash[m_size]; }

    int size() const { return m_size; }
    Mod base() const { return m_base; }
    Mod concat(Mod hA, int lenB, Mod hB) const { return hA * m_power[lenB] + hB; }
    const std::vector<Mod> &powers() const { return m_power; }

  private:
    void build(const T_Iterable &s, Mod base) {
        m_size = (int)s.size();
        m_base = base;
        m_hash.assign(m_size + 1, Mod(0));
        m_power.resize(m_size + 1, Mod(1));

        for(int i = 1; i <= m_size; i++) m_power[i] = m_base * m_power[i - 1];

        for(int i = 0; i < m_size; i++) {
            Mod val = normalize(s[i]);
            m_hash[i + 1] = m_hash[i] * m_base + val;
        }
    }

  private:
    template <typename T>
    static Mod normalize(const T &x) {
        using U = std::decay_t<T>;
        if constexpr(std::is_integral_v<U> && sizeof(U) == 1) {
            return Mod(static_cast<unsigned int>(static_cast<unsigned char>(x))) + Mod(1);
        } else {
            return Mod(x) + Mod(1);
        }
    }

  private:
    std::vector<Mod> m_hash;
    std::vector<Mod> m_power;
    Mod m_base;
    int m_size;
};

template <typename Mod>
Mod concat(Mod hA, const vector<Mod> &pow, int lenB, Mod hB) {
    return hA * pow[lenB] + hB;
}

template <typename Iterable, typename Mod>
Mod naive_hash(const Iterable &s, int l, int r, Mod base) {
    assert(0 <= l && l <= r && r <= (int)s.size());
    Mod h = Mod(0);
    for(int i = l; i < r; ++i) {
        using U = std::decay_t<decltype(s[i])>;
        Mod val;
        if constexpr(std::is_integral_v<U> && sizeof(U) == 1) {
            val = Mod(static_cast<unsigned int>(static_cast<unsigned char>(s[i]))) + Mod(1);
        } else {
            val = Mod(s[i]) + Mod(1);
        }
        h = h * base + val;
    }
    return h;
}

void testEmpty() {
    string s;
    Hash<string, Mint> H(s);
    assert(H.size() == 0);
    assert(H(0) == 0);
    assert(H(0, 0) == 0);
    assert(H() == 0);
}

void testCustom() {
    string s = string("\x00\x01\xff", 3); // includes 0 and 0xFF (signed char hazard)
    Hash<string, Mint> H(s);

    assert(H() == H((int)s.size()));

    for(int l = 0; l <= (int)s.size(); ++l) {
        for(int r = l; r <= (int)s.size(); ++r) {
            auto h1 = H(l, r);
            auto h2 = naive_hash(s, l, r, H.base());
            assert(h1 == h2);
        }
    }
}

void testRandomStrings() {
    mt19937_64 rng(123456789);
    const int N = 500;
    string s;
    s.resize(N);
    for(int i = 0; i < N; ++i) s[i] = char(rng() & 0xFF);

    Mint base = 146527ull;
    Hash<string, Mint> H(s, base);

    for(int t = 0; t < 2000; ++t) {
        int l = uniform_int_distribution<int>(0, N)(rng);
        int r = uniform_int_distribution<int>(l, N)(rng);
        auto h1 = H(l, r);
        auto h2 = naive_hash(s, l, r, base);
        assert(h1 == h2);
    }

    for(int k = 0; k <= N; ++k) {
        auto hA = H(0, k);
        auto hB = H(k, N);
        auto combined = concat(hA, H.powers(), N - k, hB);
        assert(combined == H());
    }
}

void testNumbers() {
    vector<int> a = {10, 0, -5, 1000000, 42};
    Mint base = 911382323ull;
    Hash<vector<int>, Mint> H(a, base);

    assert(H() == naive_hash(a, 0, (int)a.size(), base));

    for(int l = 0; l <= (int)a.size(); ++l) {
        for(int r = l; r <= (int)a.size(); ++r) {
            assert(H(l, r) == naive_hash(a, l, r, base));
        }
    }

    int k = 2;
    auto hA = H(0, k), hB = H(k, (int)a.size());
    auto combined = concat(hA, H.powers(), (int)a.size() - k, hB);
    assert(combined == H());
}

int main() {
    ios::sync_with_stdio(0), cin.tie(NULL), cout << setprecision(12) << fixed;

    testEmpty();
    testCustom();
    testRandomStrings();
    testNumbers();

    cout << "All tests passed" << '\n';

    return 0;
}
