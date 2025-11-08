#include <bits/stdc++.h>
#include <limits>
#include "Segtree_packs.hpp"
#include "Segtree_basic.hpp"
#include "Segtree_lazy.hpp"

using namespace std;

typedef long long ll;

#ifdef SARTHAK_LOCAL
#include "/Users/sarthakkumar/work/Cpp/Templates/CP_Templates/debug.cpp"
#else
#define debug(...) 69
#endif

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
// mt19937_64 rng(69);

template <typename Node, typename Tag> using Lazy = LazySegtreeImpl<Node, Tag>;

class Random {
    typedef long double ld;

  public:
    Random(const mt19937_64 &_rng) : m_rng(_rng) {}

  public:
    template <typename T>
    T next(T min, T max) {
        if constexpr(std::is_integral_v<T>) {
            return std::uniform_int_distribution<T>(min, max)(rng);
        } else {
            return std::uniform_real_distribution<T>(min, max)(rng);
        }
    }
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

template <typename T>
struct Brute {
    const T MAX = numeric_limits<T>::max();
    const T MIN = numeric_limits<T>::lowest();

    vector<T> a;
    Brute(int n = 0) : a(n) {}
    Brute(const vector<T> &v) : a(v) {}
    int size() const { return (int)a.size(); }

    const vector<T> &get() const { return a; }

    ll sum(int l, int r) const {
        ll s = 0;
        for(int i = l; i < r; i++) s += a[i];
        return s;
    }
    T mx(int l, int r) const {
        T m = MIN;
        for(int i = l; i < r; i++) m = max(m, a[i]);
        return (l < r ? m : MIN);
    }
    T mn(int l, int r) const {
        T m = MAX;
        for(int i = l; i < r; i++) m = min(m, a[i]);
        return (l < r ? m : MAX);
    }
    pair<ll, int> min_count(int l, int r) const {
        if(l >= r) return {MAX, 0};
        ll m = MAX;
        int c = 0;
        for(int i = l; i < r; i++) {
            if(a[i] < m) {
                m = a[i];
                c = 1;
            } else if(a[i] == m)
                c++;
        }
        return {m, c};
    }
    void point_set(int i, T v) { a[i] = v; }
    void range_add(int l, int r, T x) {
        for(int i = l; i < r; i++) a[i] += x;
    }
    void range_assign(int l, int r, T x) {
        for(int i = l; i < r; i++) a[i] = x;
    }
};

template <typename T>
std::string slice_str(const std::vector<T> &a, int l = 0, int r = -1, int limit = 25) {
    const int n = static_cast<int>(a.size());
    if(r < 0) r = n;
    // clamp
    l = std::max(0, std::min(l, n));
    r = std::max(0, std::min(r, n));

    std::ostringstream os;
    os << "arr[" << l << ".." << r << ") size=" << n << " ";

    os << "[";
    const int len = r - l;
    for(int i = 0; i < len && i < limit; ++i) {
        if(i) os << ",";
        os << a[l + i];
    }
    if(len > limit) os << ",...(" << len << ")";
    os << "]";
    return os.str();
}

// ---------- randomized tests (use Brute; return bool) ----------

bool stress_sum_add(int tests = 300, int N = 1000, int Q = 30000) {
    using Node = packs::SumNode<long long>;
    using Tag = packs::AddTag<long long>;

    cout << YELLOW << "\r[SUM+ADD TEST]\n"
         << RESET;

    const ll max_v = 1e8;
    for(int it = 1; it <= tests; ++it) {
        int n = Rng.next(1, N);
        vector<long long> a = Rng.next_vector<long long>(n, -max_v, max_v);
        Brute brute(a);
        Lazy<Node, Tag> seg(a);

        for(int q = 0; q < Q; ++q) {
            int type = Rng.next(0, 4);
            if(type == 0) { // set
                int i = Rng.next(0, n - 1);
                long long v = Rng.next<long long>(-max_v, max_v);
                brute.point_set(i, v);
                seg.set(i, Node(v));

            } else if(type == 1) { // get(i)
                int i = Rng.next(0, n - 1);
                long long got = seg.get(i).sum;
                long long exp = brute.sum(i, i + 1);
                if(got != exp) {
                    cerr << "\n"
                         << RED << "[get(i)] FAIL test=" << it
                         << " q=" << q << " i=" << i
                         << " got=" << got << " exp=" << exp
                         << " arr=" << slice_str(a) << RESET << endl;
                    return false;
                }

            } else if(type == 2) { // get()
                long long got = seg.get().sum;
                long long exp = brute.sum(0, n);
                if(got != exp) {
                    cerr << "\n"
                         << RED << "[get()] FAIL test=" << it
                         << " q=" << q << " got=" << got << " exp=" << exp
                         << " arr=" << slice_str(a) << RESET << endl;
                    return false;
                }

            } else if(type == 3) { // calc(l, r)
                int l = Rng.next(0, n);
                int r = Rng.next(0, n);
                if(l > r) swap(l, r);
                long long got = seg.calc(l, r).sum;
                long long exp = brute.sum(l, r);
                if(got != exp) {
                    cerr << "\n"
                         << RED << "[calc(l,r)] FAIL test=" << it
                         << " q=" << q << " l=" << l << " r=" << r
                         << " got=" << got << " exp=" << exp
                         << " arr=" << slice_str(a) << RESET << endl;
                    return false;
                }

            } else if(type == 4) { // range add
                int l = Rng.next(0, n - 1);
                int r = Rng.next(0, n);
                if(l > r) swap(l, r);
                long long delta = Rng.next(-max_v, max_v);

                seg.apply(l, r, delta);
                brute.range_add(l, r, delta);
            }
        }

        // final sanity check
        long long gotFinal = seg.get().sum;
        long long expFinal = brute.sum(0, n);
        if(gotFinal != expFinal) {
            cerr << "\n"
                 << RED << "[FINAL CHECK FAIL] test=" << it
                 << " got=" << gotFinal << " exp=" << expFinal
                 << " arr=" << slice_str(a) << RESET << endl;
            return false;
        }

        cerr << GREEN << "\r[progress] " << setw(3) << it << "/" << tests
             << " tests passed ✅" << RESET << flush;
    }

    cerr << GREEN << "\n✅ stress_sum: all " << tests << " tests passed ("
         << N << " max size, " << Q << " ops each)\n"
         << RESET;
    return true;
}

bool stress_max_min_add(int tests = 200, int N = 1000, int Q = 30000) {
    using NodeMax = packs::MaxNode<long long>;
    using NodeMin = packs::MinNode<long long>;
    using Tag = packs::AddTag<long long>;

    const ll max_v = 1e9;

    cerr << YELLOW << "[MAX/MIN TEST]" << '\n'
         << RESET;

    for(int it = 1; it <= tests; ++it) {
        int n = Rng.next(1, N);
        vector<ll> a = Rng.next_vector<ll>(n, -max_v, max_v);

        Brute brute(a);
        Lazy<NodeMax, Tag> segMax(a);
        Lazy<NodeMin, Tag> segMin(a);

        for(int q = 0; q < Q; ++q) {
            int type = Rng.next(0, 2); // set or query
            if(type == 0) {            // set
                int i = Rng.next(0, n - 1);
                int v = Rng.next(-1'000'000, 1'000'000);
                brute.point_set(i, v);
                segMax.set(i, NodeMax(v));
                segMin.set(i, NodeMin(v));
            }
            if(type == 2) { // add to range
                int l = Rng.next(0, n);
                int r = Rng.next(0, n);
                if(l > r) swap(l, r);
                ll delta = Rng.next(-max_v, max_v);

                segMax.apply(l, r, delta);
                segMin.apply(l, r, delta);

            } else { // query
                int l = Rng.next(0, n);
                int r = Rng.next(0, n);
                if(l > r) swap(l, r);

                int gmax = segMax.calc(l, r).mx;
                int gmin = segMin.calc(l, r).mn;

                int bmax = brute.mx(l, r);
                int bmin = brute.mn(l, r);

                if(gmax != bmax || gmin != bmin) {
                    cerr << "\n"
                         << RED << "[max/min FAIL] test=" << it
                         << " q=" << q
                         << " l=" << l << " r=" << r
                         << " got_max=" << gmax << " exp_max=" << bmax
                         << " got_min=" << gmin << " exp_min=" << bmin
                         << " arr=" << slice_str(a) << RESET << endl;
                    return false;
                }
            }
        }

        cerr << GREEN << "\r[progress] " << setw(3) << it << "/" << tests
             << " tests passed ✅" << RESET << flush;
    }

    cerr << GREEN << "\n✅ stress_max_min: all " << tests
         << " tests passed (" << N << " max size, " << Q << " ops each)\n"
         << RESET;
    return true;
}

bool stress_maxRight_minLeft(int tests = 200, int N = 5000, int Q = 30000) {
    using Node = packs::SumNode<long long>;

    cerr << YELLOW << "[MAXRIGHT/MINLEFT TEST]" << '\n'
         << RESET;

    for(int it = 1; it <= tests; ++it) {
        int n = Rng.next(1, N);
        vector<long long> a = Rng.next_vector<long long>(n, 0, 1'000'000);
        SegtreeImpl<Node> seg(a);

        for(int q = 0; q < Q; ++q) {
            int type = Rng.next(0, 1); // 0=maxRight, 1=minLeft
            long long K = Rng.next<long long>(0, 1'000'000);

            if(type == 0) {
                // --- maxRight ---
                int l = Rng.next(0, n - 1);
                auto pred = [&](const Node &x) { return x.sum <= K; };
                int r_seg = seg.maxRight(l, pred);

                long long s = 0;
                int r_brute = l;
                for(int i = l; i < n; ++i) {
                    if(s + a[i] <= K)
                        s += a[i], r_brute = i + 1;
                    else
                        break;
                }

                if(r_seg != r_brute) {
                    cerr << "\n"
                         << RED << "[maxRight FAIL] test=" << it
                         << " q=" << q
                         << " l=" << l
                         << " K=" << K
                         << " got=" << r_seg
                         << " exp=" << r_brute
                         << " arr=" << slice_str(a)
                         << RESET << endl;
                    return false;
                }
            } else {
                // --- minLeft ---
                int r = Rng.next(0, n);
                auto pred = [&](const Node &x) { return x.sum <= K; };
                int l_seg = seg.minLeft(r, pred);

                long long s = 0;
                int l_brute = r;
                for(int i = r - 1; i >= 0; --i) {
                    if(s + a[i] <= K)
                        s += a[i], l_brute = i;
                    else
                        break;
                }

                if(l_seg != l_brute) {
                    cerr << "\n"
                         << RED << "[minLeft FAIL] test=" << it
                         << " q=" << q
                         << " r=" << r
                         << " K=" << K
                         << " got=" << l_seg
                         << " exp=" << l_brute
                         << " arr=" << slice_str(a)
                         << RESET << endl;
                    return false;
                }
            }
        }

        cerr << GREEN << "\r[progress] " << setw(3) << it << "/" << tests
             << " tests passed ✅" << RESET << flush;
    }
    cerr << GREEN << "\n✅ stress_maxRight_minLeft: all " << tests
         << " tests passed (" << N << " max size, " << Q << " ops each)\n"
         << RESET;
    return true;
}

bool stress_min_count(int tests = 300, int N = 1000, int Q = 30000) {
    using Node = packs::MinCountNode<int>;

    cerr << YELLOW << "[MIN COUNT TEST]" << '\n'
         << RESET;

    for(int it = 1; it <= tests; ++it) {
        int n = Rng.next(1, N);
        vector<int> a = Rng.next_vector<int>(n, -1'000'000, 1'000'000);
        Brute brute(a);
        SegtreeImpl<Node> seg(a);

        for(int q = 0; q < Q; ++q) {
            int type = Rng.next(0, 1); // set or query
            if(type == 0) {
                // point set
                int i = Rng.next(0, n - 1);
                int v = Rng.next(-1'000'000, 1'000'000);
                brute.point_set(i, v);
                seg.set(i, Node(v));

            } else {
                // range query
                int l = Rng.next(0, n);
                int r = Rng.next(0, n);
                if(l > r) swap(l, r);

                Node got = seg.calc(l, r);
                auto [mn, cnt] = brute.min_count(l, r);

                // valid edge case: empty range
                bool ok = (l == r && got.cnt == 0 && got.mn == std::numeric_limits<int>::max()) ||
                          (got.mn == mn && got.cnt == cnt);

                if(!ok) {
                    cerr << "\n"
                         << RED << "[MinCount FAIL] test=" << it
                         << " q=" << q
                         << " l=" << l << " r=" << r
                         << " got.mn=" << got.mn << " got.cnt=" << got.cnt
                         << " exp.mn=" << mn << " exp.cnt=" << cnt
                         << " arr=" << slice_str(a, 0, n)
                         << RESET << endl;
                    return false;
                }
            }
        }

        cerr << GREEN << "[progress] " << setw(3) << it << "/" << tests
             << " tests passed ✅" << RESET << "\r";
    }
    cerr << GREEN << "\n✅ stress_min_count: all " << tests
         << " tests passed (" << N << " max size, " << Q << " ops each)\n"
         << RESET;
    return true;
}

int main() {

    bool ok = true;

    ok &= stress_sum_add(300, 1000, 50000);
    ok &= stress_sum_add(5000, 10, 50000);
    ok &= stress_max_min_add(300, 1000, 50000);
    ok &= stress_max_min_add(5000, 10, 50000);
    ok &= stress_maxRight_minLeft(300, 1000, 50000);
    ok &= stress_maxRight_minLeft(5000, 10, 50000);
    ok &= stress_min_count(300, 1000, 50000);
    ok &= stress_min_count(5000, 10, 50000);

    if(ok) {
        cout << "ALL TESTS PASSED ✅\n";
        return 0;
    } else {
        cout << "TESTS FAILED ❌ (see stderr for details)\n";
        return 1;
    }
    return 0;
}
