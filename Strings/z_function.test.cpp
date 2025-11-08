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
vector<int> z_function(const T &s) {
    int n = (int)s.size();
    vector<int> z(n);

    for(int i = 1, l = 0, r = 0; i < n; i++) {
        if(i < r) {
            z[i] = max(0, min(r - i, z[i - l]));
        }
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if(i + z[i] > r) l = i, r = i + z[i];
    }

    return z;
}

template <typename T>
vector<int> z_function_naive(const T &s) {
    int n = (int)s.size();
    vector<int> z(n);

    for(int i = 1; i < n; i++) {
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
    }

    return z;
}

void testRandom(int tests = 100) {
    mt19937_64 rng(123456789);
    const int max = 5000;
    for(int test = 0; test < tests; test++) {
        const int n = int(rng() & 0xFFFFF) % max + 1;
        string s;
        s.resize(n);
        for(int i = 0; i < n; ++i) s[i] = char('a' + (rng() & 0xFF) % 26);

        assert(z_function(s) == z_function_naive(s));
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(NULL), cout << setprecision(12) << fixed;

    testRandom();

    cout << "All tests passed" << '\n';

    return 0;
}
