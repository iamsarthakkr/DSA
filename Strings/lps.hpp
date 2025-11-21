#pragma once
#include <vector>

template <typename T>
std::vector<int> lps(const T &s) {
    int n = (int)s.size();
    std::vector<int> p(n);
    if(n == 0) return p;

    for(int i = 1; i < n; i++) {
        int k = p[i - 1];
        while(k > 0 && s[k] != s[i]) k = p[k - 1];
        p[i] = k + (s[k] == s[i]);
    }
    return p;
}
