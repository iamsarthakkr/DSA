#include <bits/stdc++.h>
#include "fenwick.hpp"
using namespace std;

template <typename T> inline bool cmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template <typename T> inline bool cmax(T &a, const T &b) { return b > a ? a = b, true : false; }

#ifdef SARTHAK_LOCAL
#include "/Users/sarthakkumar/work/Cpp/Templates/Common/debug.hpp"
#else
#define debug(...) ((void)0)
#endif

namespace random_utils {
class Random {
    using Engine = std::mt19937_64;

  public:
    using result_type = Engine::result_type;

    Random() : m_rng(static_cast<result_type>(std::chrono::steady_clock::now().time_since_epoch().count())) {}

    explicit Random(result_type seed) : m_rng(seed) {}
    explicit Random(const Engine &eng) : m_rng(eng) {}

    template <typename T>
    T next(T min, T max) {
        static_assert(std::is_arithmetic_v<T>, "Random::next requires arithmetic type");

        if constexpr(std::is_same_v<T, bool>) {
            std::bernoulli_distribution dist(0.5);
            return dist(m_rng);
        } else if constexpr(std::is_integral_v<T>) {
            std::uniform_int_distribution<T> dist(min, max);
            return dist(m_rng);
        } else {
            std::uniform_real_distribution<T> dist(min, max);
            return dist(m_rng);
        }
    }

    // next in [0, max]
    template <typename T>
    T next(T max = std::numeric_limits<T>::max()) {
        if constexpr(std::is_same_v<T, bool>) {
            return next<bool>(false, true);
        } else {
            return next<T>(static_cast<T>(0), max);
        }
    }

    template <typename T>
    std::vector<T> next_vector(int n, T max = std::numeric_limits<T>::max()) {
        std::vector<T> ret(n);
        for(auto &v : ret) v = next<T>(max);
        return ret;
    }

    template <typename T>
    std::vector<T> next_vector(int n, T min, T max) {
        std::vector<T> ret(n);
        for(auto &v : ret) v = next<T>(min, max);
        return ret;
    }

  private:
    Engine m_rng;
};
} // namespace random_utils

random_utils::Random Rng;
// random_utils::Random Rng(42);

class Timer {
  public:
    Timer() noexcept { m_start = std::chrono::steady_clock::now(); }
    ~Timer() noexcept {
        const auto end = std::chrono::steady_clock::now();
        const auto diff = std::chrono::duration<double, std::milli>(end - m_start).count();
        std::clog << "\nTime taken: " << diff << " ms.\n";
    }

  private:
    using Clock = std::chrono::steady_clock;
    Clock::time_point m_start;
};

void Test() {
    Timer t;
    int n = 1000;
    vector<int> a = Rng.next_vector<int>(n, (int)1e5);

    fenwick<long long> fw(a);

    int TESTS = 1e6;
    for(int test = 0; test < TESTS; test++) {
        cout << "\rRunning test " << test + 1 << "..." << std::flush;
        bool add = Rng.next<bool>();
        if(add) {
            int i = Rng.next<int>(n - 1), v = Rng.next<int>((int)1e3);
            fw.update(i, v);
            a[i] += v;
        } else {
            int l, r;
            do {
                l = Rng.next(n - 1), r = Rng.next(n - 1);
            } while(l > r);

            auto s = fw.get(l, r);
            long long v = 0;
            for(int i = l; i <= r; i++) v += a[i];
            assert(s == v);
        }
    }
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout << setprecision(12) << fixed;

    Test();

    return 0;
}
