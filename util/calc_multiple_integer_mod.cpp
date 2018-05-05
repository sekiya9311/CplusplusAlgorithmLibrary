//剰余計算,mod計算,string値

// O(length)
long long calc_multiple_integer_mod(const std::string &s, const long long &mod) {
    long long res = 0;
    for (auto &&e : s) {
        ((res *= 10) += (e - '0')) %= mod;
    }
    return res;
}
