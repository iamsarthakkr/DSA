#pragma once
#include <cassert>
#include <numeric>
#include <vector>
#include <string>
#include <algorithm>

class suffix_array {
  public:
    suffix_array() = default;
    explicit suffix_array(const std::string &str) { buildImpl(str); }
    void build(const std::string &str) { buildImpl(str); }
    const std::vector<int> &sa() const { return m_sa; }

  private:
    void buildImpl(const std::string &str) {
        assert(str.find(S) == std::string::npos);
        std::string t = str + S;
        int n = (int)t.size();

        std::vector<int> p(n), c(n);
        std::iota(p.begin(), p.end(), 0);
        std::sort(p.begin(), p.end(), [&](int i, int j) { return t[i] < t[j]; });

        c[p[0]] = 0;
        for(int i = 1; i < n; i++) {
            if(t[p[i]] == t[p[i - 1]]) {
                c[p[i]] = c[p[i - 1]];
            } else {
                c[p[i]] = c[p[i - 1]] + 1;
            }
        }

        std::vector<int> nc(n), np(n), cnt(n), pos(n);

        auto count_sort = [&]() {
            std::fill(cnt.begin(), cnt.end(), 0);
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

        m_sa.assign(p.begin() + 1, p.end());
    }

  private:
    std::vector<int> m_sa;

  private:
    static constexpr char S = '\0';
};
