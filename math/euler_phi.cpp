// オイラーの関数 (1 から N までの自然数のうち N と互いに素なものの個数)
std::vector<int> euler_phi(int N) {
    N++; std::vector<int> ret(N);
    std::iota(std::begin(ret), std::end(ret), 0);
    for (int i = 2; i < N; i++) {
        if (ret[i] == i) {
            for (int j = i; j < N; j += i) {
                ret[j] /= i;
                ret[j] *= (i - 1);
            }
        }
    }
    return ret;
}
