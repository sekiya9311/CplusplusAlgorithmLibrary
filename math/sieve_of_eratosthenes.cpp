// エラトステネスの篩,素数列挙
// O(N log log N)
std::vector<int> sieve_of_eratosthenes(const int n) {
    std::vector<bool> is(n + 1, true);
    std::vector<int> res;
    is[0] = false;
    is[1] = false;
    for (int i = 2; i <= n; i++) {
        if (is[i]) {
            res.emplace_back(i);
            for (int j = i * 2; j <= n; j += i) {
                is[j] = false;
            }
        }
    }
    return res;
}
