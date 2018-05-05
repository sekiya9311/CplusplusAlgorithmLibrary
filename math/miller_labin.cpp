// ミラーラビン素数判定法
// pow_mod関数，rnd(乱数生成)オブジェクト必須
bool miller_labin(long long n, int loopNum = 100) {
    if (n == 2) {
        return true;
    }
    if (n < 2 || (!(n & 1))) {
        return false;
    }
    long long d = n - 1;
    while (!(d & 1)) {
        d >>= 1;
    }
    while (loopNum--) {
        long long a = rnd() % (n - 2) + 1;
        long long t = d;
        long long y = pow_mod(a, t, n);
        while (t != n - 1 && y != 1 && y != n - 1) {
            y = (y * y) % n;
            t <<= 1;
        }
        if (y != n - 1 && (!(t & 1))) {
            return false;
        }
    }
    return true;
}
