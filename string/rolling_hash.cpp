// ローリングハッシュ,文字列比較
// これはクソ実装

class rolling_hash {
private:
    const long long mods[2] = {(long long)(1e9 + 7), (long long)(1e9 + 9)};
    std::vector<long long> hs[2], pm[2];
    std::vector<long long> x; //基数
    int len;
    std::string S;
public:
    //文字列, 基数1, 基数2
    // 基数はランダムで指定する(hack怖い)
    rolling_hash(const std::string& str, long long num1, long long num2) {
        x.resize(2);
        x[0] = num1; x[1] = num2;
        S = str;
        len = str.length();
        for (int i = 0; i < 2; i++) {
            pm[i].resize(1000000);
            pm[i][0] = 1;
            for (int j = 0; j < (int)pm[i].size(); j++) {
                pm[i][j + 1] = (pm[i][j] * x[i]) % mods[i];
            }
        }
        init(S);
    }
    void init(const std::string& str) {
        len = str.length();
        for (int i = 0; i < 2; i++) {
            hs[i].resize(len + 5);
            hs[i][0] = 0;
            for (int j  = 0; j < len; j++) {
                hs[i][j + 1] = ((hs[i][j] * x[i]) + str[j]) % mods[i];
            }
        }
    }
    //strのハッシュ値生成
    std::pair<long long, long long> make_hash(const std::string& str) {
        long long res[2];
        const int slen = str.length();
        for (int i = 0; i < 2; i++) {
            res[i] = 0;
            for (int j = 0; j < slen; j++) {
                res[i] = ((res[i] * x[i]) + str[j]) % mods[i];
            }
        }
        return std::make_pair(res[0], res[1]);
    }
    //S[l..r)のハッシュ値返す
    std::pair<long long, long long> get_hash(int l, int r) {
        r--;
        if (l > r) {
            throw std::invalid_argument("");
        }
        long long res[2];
        while ((int) pm[0].size() < r + 5) {
            for (int i = 0; i < 2; i++) {
                pm[i].emplace_back((pm[i].back() * x[i]) % mods[i]);
            }
        }
        for (int i = 0; i < 2; i++) {
            res[i] = (hs[i][r + 1] - (hs[i][l] * pm[i][r - l + 1] % mods[i]) + mods[i]) % mods[i];
        }
        return std::make_pair(res[0], res[1]);
    }
    //Sのハッシュ配列返す
    std::vector<std::vector<long long>> get_hash_array() {
        return std::vector<std::vector<long long>>{hs[0], hs[1]};
    }
    std::vector<long long> get_mod() {
        return std::vector<long long>{mods[0], mods[1]};
    }
    std::vector<long long> get_base_num() {
        return x;
    }
};
