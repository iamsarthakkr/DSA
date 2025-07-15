#include <bits/stdc++.h>

/*
#include <cstdlib>
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

template <typename T>
struct Comparator {
    constexpr bool operator()(const T &a, const T &b) const;
};

template <typename T>
vector<int> next(vector<T> a, const std::function<bool(int, int)> &comp = greater<T>()) {
    int n = a.size();
    vector<int> res(n, n);

    vector<int> s;
    for(int i = n - 1; i >= 0; --i) {
        while(!s.empty() && !comp(a[s.back()], a[i])) s.pop_back();
        if(!s.empty()) res[i] = s.back();
        s.push_back(i);
    }
    return res;
}

template <typename T>
vector<int> prev(vector<T> a, const std::function<bool(int, int)> &comp = greater<T>()) {
    int n = a.size();
    vector<int> res(n, -1);

    vector<int> s;
    for(int i = 0; i < n; i++) {
        while(!s.empty() && !comp(a[s.back()], a[i])) s.pop_back();
        if(!s.empty()) res[i] = s.back();
        s.push_back(i);
    }
    return res;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(69);

class Random {
    typedef long double ld;

  public:
    Random(const mt19937_64 &_rng) : m_rng(_rng) {}

  public:
    template <typename T> T next(T min, T max) { return static_cast<T>(uniform_real_distribution<ld>(static_cast<ld>(min), static_cast<ld>(max))(rng)); }
    template <typename T> T next(T max = numeric_limits<T>::max()) { return next(static_cast<T>(0), max); }
    template <typename T> vector<T> next_vector(int n, T max = numeric_limits<T>::max()) {
        vector<T> ret(n);
        for(auto &v : ret) v = next(max);
        return ret;
    }
    template <typename T> vector<T> next_vector(int n, T min, T max) {
        vector<T> ret(n);
        for(auto &v : ret) v = next(min, max);
        return ret;
    }

  private:
    mt19937_64 m_rng;
};
Random Rng(rng);

void Test_next() {
    int tests = 1000;
    while(tests--) {
        int n = Rng.next<int>(5000);
        vector<int> v = Rng.next_vector<int>(n, 1e5);

        auto res = next(v);
        forn(i, n) {
            int j = i + 1;
            while(j < n && v[j] <= v[i]) j++;
            assert(res[i] == j);
        }
    }

    tests = 1000;
    while(tests--) {
        int n = Rng.next<int>(5000);
        vector<int> v = Rng.next_vector<int>(n, 1e5);

        auto res = next(v, less_equal<int>());
        forn(i, n) {
            int j = i + 1;
            while(j < n && v[j] > v[i]) j++;
            assert(res[i] == j);
        }
    }
    cout << "Passed next tests" << '\n';
}

void Test_prev() {
    int tests = 1000;
    while(tests--) {
        int n = Rng.next<int>(5000);
        vector<int> v = Rng.next_vector<int>(n, 1e5);

        auto res = prev(v);
        forn(i, n) {
            int j = i - 1;
            while(j >= 0 && v[j] <= v[i]) j--;
            assert(res[i] == j);
        }
    }

    tests = 1000;
    while(tests--) {
        int n = Rng.next<int>(5000);
        vector<int> v = Rng.next_vector<int>(n, 1e5);

        auto res = prev(v, less_equal<int>());
        forn(i, n) {
            int j = i - 1;
            while(j >= 0 && v[j] > v[i]) j--;
            assert(res[i] == j);
        }
    }
    cout << "Passed prev tests" << '\n';
}

void Main(int tc) {
    Test_next();
    Test_prev();
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
