#include <bits/stdc++.h>
#include "hash.hpp"

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
#include "/Users/sarthakkumar/work/Cpp/Templates/Common/debug.hpp"
#else
#define debug(...) 69
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
