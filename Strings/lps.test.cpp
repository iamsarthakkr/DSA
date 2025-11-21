#include <bits/stdc++.h>
using namespace std;

#ifdef SARTHAK_LOCAL
#include "/Users/sarthakkumar/work/Cpp/Templates/CP_Templates/debug.cpp"
#else
#define debug(...) 69
#endif

template <typename T>
vector<int> lps(const T &s) {
    int n = (int)s.size();
    vector<int> p(n);

    for(int i = 1; i < n; i++) {
        int k = p[i - 1];
        while(k > 0 && s[k] != s[i]) k = p[k - 1];
        p[i] = k + (s[k] == s[i]);
    }

    return p;
}

template <typename T>
vector<int> lps_naive(const T &s) {
    int n = (int)s.size();
    vector<int> p(n);

    for(int i = 1; i < n; i++) {
        for(int j = 1; j <= i; j++) {
            int l = i - j + 1;
            if(s.substr(j, l) == s.substr(0, l)) {
                p[i] = max(p[i], l);
            }
        }
    }

    return p;
}

void testRandom(int tests = 100) {
    mt19937_64 rng(123456789);
    const int max = 500;
    for(int test = 0; test < tests; test++) {
        const int n = int(rng() & 0xFFFFF) % max + 1;
        string s;
        s.resize(n);
        for(int i = 0; i < n; ++i) s[i] = char(rng() & 0xFF);

        assert(lps(s) == lps_naive(s));
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(NULL), cout << setprecision(12) << fixed;

    testRandom();

    cout << "All tests passed" << '\n';

    return 0;
}
