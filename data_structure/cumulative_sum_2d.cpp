template<typename T = int>
class cumulative_sum_2d {
private:
    std::vector<std::vector<T>> vec;
    std::vector<std::vector<T>> sum;
    bool invalid;
    int H, W;
public:
    cumulative_sum_2d() {invalid = true;}
    cumulative_sum_2d(const std::vector<std::vector<T>> &v) {
        init(v);
    }
    void init() {
        vec.clear();
        sum.clear();
        H = W = -1;
        invalid = true;
    }
    void init(const std::vector<std::vector<T>> &v) {
        init();
        invalid = false;
        H = v.size();
        W = v.front().size();
        std::copy(v.begin(), v.end(), std::back_inserter(vec));
        sum.resize(H + 1, std::vector<T>(W + 1, 0));
    }
    bool calc_sum() {
        if (invalid) {
            return false;
        }
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W; j++) {
                sum[i + 1][j + 1] = vec[i][j];
            }
        }
        for (int i = 0; i < H + 1; i++) {
            for (int j = 0; j < W; j++) {
                sum[i][j + 1] += sum[i][j];
            }
        }
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < W + 1; j++) {
                sum[i + 1][j] += sum[i][j];
            }
        }
        return true;
    }
    // [p1, p2)
    T get_sum(std::pair<int, int> p1, std::pair<int, int> p2) {
        if (invalid) return 0;
        int h1, w1, h2, w2;
        std::tie(h1, w1) = p1; std::tie(h2, w2) = p2;
        h2--; w2--;
        return sum[h2 + 1][w2 + 1] - sum[h2 + 1][w1] - sum[h1][w2 + 1] + sum[h1][w1];
    }
    T get_sum(int x1, int y1, int x2, int y2) {
        return this->get_sum(std::make_pair(x1, y1), std::make_pair(x2, y2));
    }
    std::vector<std::vector<T>> get_sum_vec() {return sum;}
};
