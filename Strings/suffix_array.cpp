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

vector<int> suffixArray(const string &s) {
    string t = s + "$";
    int n = (int)t.size();

    vector<int> p(n), c(n);
    iota(p.begin(), p.end(), 0);

    sort(p.begin(), p.end(), [&](int i, int j) { return t[i] < t[j]; });
    c[p[0]] = 0;
    for(int i = 1; i < n; i++) {
        if(t[p[i]] == t[p[i - 1]]) {
            c[p[i]] = c[p[i - 1]];
        } else {
            c[p[i]] = c[p[i - 1]] + 1;
        }
    }

    vector<int> nc(n), np(n), cnt(n), pos(n);

    auto count_sort = [&]() {
        fill(cnt.begin(), cnt.end(), 0);
        for(int i : p) {
            cnt[c[i]]++;
        }
        pos[0] = 0;
        for(int i = 1; i < n; i++) {
            pos[i] = pos[i - 1] + cnt[i - 1];
        }
        for(int i : p) {
            int id = c[i];
            np[pos[id]] = i;
            pos[id]++;
        }
        p.swap(np);
    };

    int k = 0;
    while(1 << k < n) {
        int shift = 1 << k;
        for(int i = 0; i < n; i++) {
            p[i] -= shift;
            if(p[i] < 0) p[i] += n;
        }

        count_sort();

        nc[p[0]] = 0;
        for(int i = 1; i < n; i++) {
            int ci1 = p[i], pi1 = p[i - 1];
            int ci2 = p[i] + shift, pi2 = p[i - 1] + shift;
            if(ci2 >= n) ci2 -= n;
            if(pi2 >= n) pi2 -= n;

            int a1 = c[ci1], a2 = c[ci2];
            int b1 = c[pi1], b2 = c[pi2];
            if(a1 == b1 && a2 == b2) {
                nc[ci1] = nc[pi1];
            } else {
                nc[ci1] = nc[pi1] + 1;
            }
        }
        c.swap(nc);
        k += 1;
        if(c[p.back()] == n - 1) break; // early break if all unique
    }

    return p;
}

int main() {
    ios::sync_with_stdio(0), cin.tie(NULL), cout << setprecision(12) << fixed;

    string s = "ababba";
    auto p = suffixArray(s);
    debug(p);

    return 0;
}
