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
    iota(all(p), 0);

    // k = 0
    sort(all(p), [&](int i, int j) { return t[i] < t[j]; });
    c[p[0]] = 0;
    for(int i = 1; i < n; i++) {
        if(t[p[i]] == t[p[i - 1]]) {
            c[p[i]] = c[p[i - 1]];
        } else {
            c[p[i]] = c[p[i - 1]] + 1;
        }
    }

    vector<int> nc(n), np(n), cnt(n), pos(n);
    int k = 0;
    while(1 << k < n) {
        // radix sort
        {
            cnt.assign(n, 0);
            for(int i : p) {
                int second = c[(i + (1 << k)) % n];
                cnt[second]++;
            }
            pos[0] = 0;
            for(int i = 1; i < n; i++) {
                pos[i] = pos[i - 1] + cnt[i - 1];
            }
            for(int i : p) {
                int second = c[(i + (1 << k)) % n];
                np[pos[second]] = i;
                pos[second]++;
            }
            p.swap(np);
        }
        {
            cnt.assign(n, 0);
            for(int i : p) {
                int first = c[i];
                cnt[first]++;
            }
            pos[0] = 0;
            for(int i = 1; i < n; i++) {
                pos[i] = pos[i - 1] + cnt[i - 1];
            }
            for(int i : p) {
                int first = c[i];
                np[pos[first]] = i;
                pos[first]++;
            }
            p.swap(np);
        }

        nc[p[0]] = 0;
        for(int i = 1; i < n; i++) {
            int ci = p[i], pi = p[i - 1];
            int a1 = c[ci], a2 = c[(ci + (1 << k)) % n];
            int b1 = c[pi], b2 = c[(pi + (1 << k)) % n];
            if(a1 == b1 && a2 == b2) {
                nc[ci] = nc[pi];
            } else {
                nc[ci] = nc[pi] + 1;
            }
        }
        c.swap(nc);
        k += 1;
    }

    return p;
}
int main() {
    ios::sync_with_stdio(0), cin.tie(NULL), cout << setprecision(12) << fixed;

    string s;
    cin >> s;

    vector<int> p = suffixArray(s);

    for(int x : p) cout << x << " ";
    cout << '\n';

    return 0;
}
