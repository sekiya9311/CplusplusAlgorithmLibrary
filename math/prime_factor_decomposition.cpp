// 素因数分解
// O(√N * std::map)
//res[i] = n : iがn個
std::map<long long, int> prime_factor_decomposition(long long N) {
    std::map<long long, int> res;
    for (long long i = 2; i * i <= N; i++) {
        int cnt = 0;
        while(N % i == 0) {
            cnt++;
            N /= i;
        }
        if (cnt) {
            res[i] = cnt;
        }
    }
    if (N != 1) {
        res[N] = 1;
    }
    return res;
}
