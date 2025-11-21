#include <bits/stdc++.h>
#include "suffix_array.hpp"
using namespace std;

#ifdef SARTHAK_LOCAL
#include "/Users/sarthakkumar/work/Cpp/Templates/Common/debug.hpp"
#else
#define debug(...) 69
#endif

vector<int> build_suffix_array_naive(const string &s) {
    int n = (int)s.size();
    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    sort(p.begin(), p.end(), [&](int i, int j) {
        while(i < (int)s.size() && j < (int)s.size()) {
            if(s[i] < s[j]) return true;
            if(s[i] > s[j]) return false;
            ++i;
            ++j;
        }
        return i == (int)s.size() && j != (int)s.size();
    });
    return p;
}

void check_suffix_array(const string &s) {
    suffix_array sa_obj(s);
    const auto &sa = sa_obj.sa();

    int n = (int)s.size();

    assert((int)sa.size() == n);

    for(int idx : sa) {
        assert(0 <= idx && idx < n);
    }

    for(int i = 1; i < n; ++i) {
        assert(sa[i - 1] != sa[i]);
    }

    auto naive = build_suffix_array_naive(s);
    assert(sa == naive);

    for(int k = 1; k < n; ++k) {
        int i = sa[k - 1];
        int j = sa[k];
        int x = i, y = j;
        while(x < n && y < n && s[x] == s[y]) {
            ++x;
            ++y;
        }
        bool ok = (y < n && x < n && s[x] < s[y]) || (x == n && y != n);
        assert(ok);
    }
}

void test_small_fixed() {
    {
        string s = "";
        suffix_array sa_obj(s);
        const auto &sa = sa_obj.sa();
        assert(sa.empty());
    }

    {
        string s = "a";
        suffix_array sa_obj(s);
        const auto &sa = sa_obj.sa();
        assert(sa.size() == 1);
        assert(sa[0] == 0);
    }

    {
        string s = "banana";
        suffix_array sa_obj(s);
        const auto &sa = sa_obj.sa();

        // Known correct SA for "banana":
        // suffixes:
        // 0: banana
        // 1: anana
        // 2: nana
        // 3: ana
        // 4: na
        // 5: a
        // Sorted: [5:"a", 3:"ana", 1:"anana", 0:"banana", 4:"na", 2:"nana"]
        vector<int> expected = {5, 3, 1, 0, 4, 2};
        assert(sa == expected);
    }

    {
        string s = "aaaaa";
        suffix_array sa_obj(s);
        const auto &sa = sa_obj.sa();

        // All suffixes: 0:"aaaaa",1:"aaaa",2:"aaa",3:"aa",4:"a"
        // Sorted: [4,3,2,1,0]
        vector<int> expected = {4, 3, 2, 1, 0};
        assert(sa == expected);
    }

    {
        string s = "ababa";
        suffix_array sa_obj(s);
        const auto &sa = sa_obj.sa();

        // suffixes:
        // 0: ababa
        // 1: baba
        // 2: aba
        // 3: ba
        // 4: a
        // Sorted: [4:"a",2:"aba",0:"ababa",3:"ba",1:"baba"]
        vector<int> expected = {4, 2, 0, 3, 1};
        assert(sa == expected);
    }

    {
        string s = "abcd";
        suffix_array sa_obj(s);
        const auto &sa = sa_obj.sa();
        // suffixes already in order
        vector<int> expected = {0, 1, 2, 3};
        assert(sa == expected);
    }

    {
        string s = "dcba";
        suffix_array sa_obj(s);
        const auto &sa = sa_obj.sa();
        // suffixes:
        // 0: dcba
        // 1: cba
        // 2: ba
        // 3: a
        // Sorted: [3,2,1,0]
        vector<int> expected = {3, 2, 1, 0};
        assert(sa == expected);
    }
}

void test_random() {
    mt19937_64 rng(123456789);

    const int TESTS = 500;
    const int MAXN = 50;

    uniform_int_distribution<int> len_dist(0, MAXN);
    uniform_int_distribution<int> ch_dist(0, 25);

    for(int t = 0; t < TESTS; ++t) {
        int n = len_dist(rng);
        string s;
        s.reserve(n);
        for(int i = 0; i < n; ++i) {
            char c = char('a' + ch_dist(rng));
            s.push_back(c);
        }

        check_suffix_array(s);
    }
}

int main() {
    ios::sync_with_stdio(0), cin.tie(NULL), cout << setprecision(12) << fixed;

    test_small_fixed();
    test_random();

    cout << "All suffix_array tests passed\n";

    return 0;
}
