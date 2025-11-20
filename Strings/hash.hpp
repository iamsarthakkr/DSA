#include <type_traits>
#include <cassert>
#include <vector>

template <typename T_Iterable, typename Mod>
class Hash {
  public:
    Hash() = delete;
    Hash(const T_Iterable &s, Mod base = Mod(31)) { build(s, base); }
    Mod operator()(int l, int r) const {
        assert(l >= 0 && l <= r && r <= m_size);
        Mod r_hash = m_hash[r], l_hash = m_hash[l];
        return r_hash - l_hash * m_power[r - l];
    }
    Mod operator()() const { return m_hash.back(); }
    Mod operator()(int i) const {
        assert(0 <= i && i <= m_size);
        return m_hash[i];
    }

    int size() const { return m_size; }
    Mod base() const { return m_base; }
    Mod concat(Mod hA, int lenB, Mod hB) const { return hA * m_power[lenB] + hB; }
    const std::vector<Mod> &powers() const { return m_power; }

  private:
    void build(const T_Iterable &s, Mod base) {
        m_size = (int)s.size();
        m_base = base;
        m_hash.assign(m_size + 1, Mod(0));
        m_power.resize(m_size + 1, Mod(1));

        for(int i = 1; i <= m_size; i++) m_power[i] = m_base * m_power[i - 1];

        for(int i = 0; i < m_size; i++) {
            Mod val = normalize(s[i]);
            m_hash[i + 1] = m_hash[i] * m_base + val;
        }
    }

  private:
    template <typename T>
    static Mod normalize(const T &x) {
        using U = std::decay_t<T>;
        if constexpr(std::is_integral_v<U> && sizeof(U) == 1) {
            return Mod(static_cast<unsigned int>(static_cast<unsigned char>(x))) + Mod(1);
        } else {
            return Mod(x) + Mod(1);
        }
    }

  private:
    std::vector<Mod> m_hash;
    std::vector<Mod> m_power;
    int m_size;
    Mod m_base;
};
