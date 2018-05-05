// 剰余計算,MOD計算,順列・組み合わせ,Permutation・Combination

template<int mod>
class mod_calc {
private:
    const int defnum = -1;
public:
    mod_calc() { }
    const inline int add(int a, const int b) const {
        a += b;
        while (a < 0) a += mod;
        while (a >= mod) a -= mod;
        return a;
    }
    const inline int mul(const int a, const int b) const {
        return (long long)a * b % mod;
    }
    const inline void add_ref(int &a, const int b) const {
        a = this->add(a, b);
    }
    const inline void mul_ref(int &a, const int b) const {
        a = this->mul(a, b);
    }
    const inline void add_ref(long long &a, const int b) const {
        a = this->add(a, b);
    }
    const inline void mul_ref(long long &a, const int b) const {
        a = this->mul(a, b);
    }
    const inline int pow(int a, int p) const {
        int res = 1;
        while (p > 0) {
            if (p & 1) res = this->mul(res, a);
            a = this->mul(a, a);
            p >>= 1;
        }
        return res;
    }
    const inline int inverse(int a) const {
        return this->pow(a, mod - 2);
    }
};

mod_calc<MOD> mc;
int memoFact[MAX], memoInvFact[MAX];

inline int fact(int n) {
    if (memoFact[n] != -1) return memoFact[n];
    return memoFact[n] = (n == 0 ? 1 : mc.mul(n, fact(n - 1)));
}

inline int invFact(int n) {
    if (memoInvFact[n] != -1) return memoInvFact[n];
    return memoInvFact[n] = mc.inverse(fact(n));
}

inline long long Perm(int n, int r) {
    return mc.mul(fact(n), invFact(n - r));
}

inline long long comb(int n, int r) {
    return mc.mul(mc.mul(fact(n), invFact(r)), invFact(n - r));
}

// M個の物をN人で分ける
inline long long combWithRepetition(int M, int N) {
    return comb(M + N - 1, N - 1);
}

//最初に呼んで♪ O(MAX)
inline void init() {
    memset(memoFact, -1, sizeof(memoFact));
    memset(memoInvFact, -1, sizeof(memoInvFact));
    for (int i = 0; i < MAX; i++) {
        fact(i);
        invFact(i);
    }
}
