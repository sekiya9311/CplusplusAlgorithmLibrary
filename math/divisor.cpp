// 約数列挙
//  (O√n)
std::vector<long long> divisor(const long long n, const bool to_sort) {
    std::vector<long long> ret;
    if (n > 1) for(long long i = 1; i * i <= n; i++) {
        if (n % i == 0) {
             ret.emplace_back(i);
             if (i != n / i && i != 1) {
                 ret.emplace_back(n / i);
             }
        }
    }

    if (to_sort) {
        std::sort(std::begin(ret), std::end(ret));
    }

    return ret;
}
