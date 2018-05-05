// gcd,lcm,最大公約数,最小公倍数
// O(log max(a,b))

long long gcd(long long a, long long b) {
    if(a < b) {
        std::swap(a, b);
    }
    long long ret = 1;
    while (b) {
        ret = b;
        b = a % b;
        a = ret;
    }
    return ret;
}

long long lcm(long long a, long long b) {
    return (a * b) / gcd(a, b);
}
