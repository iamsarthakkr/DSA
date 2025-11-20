#include <bits/stdc++.h>
#include "nt.hpp"

using namespace std;

template <typename T> inline bool cmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template <typename T> inline bool cmax(T &a, const T &b) { return b > a ? a = b, true : false; }

#ifdef SARTHAK_LOCAL
#include "/Users/sarthakkumar/work/Cpp/Templates/Common/debug.hpp"
#else
#define debug(...) ((void)0)
#endif

class Timer {
  public:
    Timer(const string &label = "") noexcept : m_label(label) { m_start = std::chrono::steady_clock::now(); }
    ~Timer() noexcept {
        const auto end = std::chrono::steady_clock::now();
        const auto diff = std::chrono::duration<double, std::milli>(end - m_start).count();
        std::clog << "[Timer] " << (m_label.empty() ? "" : m_label + " ") << "took: " << diff << " ms.\n";
    }

  private:
    using Clock = std::chrono::steady_clock;
    Clock::time_point m_start;
    string m_label;
};

using namespace nt;

// ------------ helpers for brute checks ------------

bool brute_is_prime(int64_t n) {
    if(n < 2) return false;
    for(int64_t d = 2; d * d <= n; ++d)
        if(n % d == 0) return false;
    return true;
}

vector<int64_t> brute_divisors(int64_t n) {
    vector<int64_t> divs;
    for(int64_t d = 1; d * d <= n; ++d) {
        if(n % d == 0) {
            divs.push_back(d);
            if(d * d != n) divs.push_back(n / d);
        }
    }
    sort(divs.begin(), divs.end());
    return divs;
}

// ------------ tests ------------

const int MAX = 500000;

void testSieveBasic() {
    Timer t("testSieveBasic");
    Sieve::init();

    // a few sanity checks
    assert(Sieve::is_prime(2));
    assert(Sieve::is_prime(3));
    assert(Sieve::is_prime(37));
    assert(Sieve::is_prime(47));

    assert(!Sieve::is_prime(0));
    assert(!Sieve::is_prime(1));
    assert(!Sieve::is_prime(51));
    assert(!Sieve::is_prime(100));

    cerr << "testSieveBasic passed.\n";
}

void testSieveVsBrute() {
    Timer t("testSieveVsBrute");

    for(int n = 0; n <= MAX; ++n) {
        bool a = Sieve::is_prime(n);
        bool b = brute_is_prime(n);
        if(a != b) {
            cerr << "Mismatch at n = " << n << ": sieve=" << a << " brute=" << b << "\n";
            assert(false);
        }
    }
    cerr << "testSieveVsBrute passed up to " << MAX << ".\n";
}

void testFactors() {
    Timer t("testFactors");

    for(int n = 2; n <= MAX; ++n) {
        auto facts = Sieve::factors(n);

        long long prod = 1;
        for(auto [p, e] : facts) {
            // p must be prime
            assert(Sieve::is_prime((int)p));
            for(int i = 0; i < e; ++i) {
                prod *= p;
            }
        }
        if(prod != n) {
            cerr << "Factorization product mismatch for n=" << n
                 << ", prod=" << prod << "\n";
            assert(false);
        }
    }
    cerr << "testFactors passed up to " << MAX << ".\n";
}

void testDivisors() {
    Timer t("testDivisors");

    for(int n = 1; n <= MAX; ++n) {
        auto dv1 = Sieve::divisors(n);
        auto dv2 = brute_divisors(n);

        if(dv1 != dv2) {
            cerr << "Divisors mismatch for n=" << n << "\n";
            cerr << "Sieve::divisors: ";
            for(auto x : dv1) cerr << x << " ";
            cerr << "\n";
            cerr << "brute_divisors: ";
            for(auto x : dv2) cerr << x << " ";
            cerr << "\n";
            assert(false);
        }
    }
    cerr << "testDivisors passed up to " << MAX << ".\n";
}

void testMillerRabinSmall() {
    Timer t("testMillerRabinSmall");

    // Use sieve as ground truth for small range

    for(int n = 0; n <= MAX; ++n) {
        bool a = MillerRabin::is_prime(n);
        bool b = Sieve::is_prime(n);
        if(a != b) {
            cerr << "MillerRabin mismatch at n=" << n
                 << ": MR=" << a << " sieve=" << b << "\n";
            assert(false);
        }
    }
    cerr << "testMillerRabinSmall passed up to " << MAX << ".\n";
}

void testMillerRabinKnown() {
    Timer t("testMillerRabinKnown");

    // Some known primes
    vector<long long> primes = {
        2LL, 3LL, 5LL, 7LL,
        97LL, 9973LL,
        1000000007LL,
        1000000009LL,
        998244353LL,
        9223372036854775783LL // a 63-bit prime (example)
    };

    for(auto p : primes) {
        assert(MillerRabin::is_prime(p));
    }

    // Some known composites
    vector<long long> comps = {
        0LL, 1LL, 4LL, 6LL, 8LL, 9LL, 15LL,
        1000000000LL,
        1000000007LL * 9, // definitely composite
        1000000009LL * 7, // composite
    };

    for(auto c : comps) {
        assert(!MillerRabin::is_prime(c));
    }

    cerr << "testMillerRabinKnown passed.\n";
}

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr), cout << setprecision(12) << fixed;

    Sieve::init(MAX);

    // Basic sieve correctness
    testSieveBasic();
    // Cross-check sieve with brute primality
    testSieveVsBrute();
    // Factorization tests
    testFactors();
    // Divisors tests
    testDivisors();
    // Miller-Rabin vs sieve on small range
    testMillerRabinSmall();
    // Miller-Rabin on known big primes / composites
    testMillerRabinKnown();

    return 0;
}
