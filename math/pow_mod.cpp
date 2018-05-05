// powmod 累乗
// O(log b)
long long pow_mod(long long a, long long b, long long mod) {
    long long ret = 1;
    while (b) {
        if (b & 1) ret = (a * ret) % mod;
        a = (a * a) % mod;
        b /= 2;
    }
    return ret;
}
