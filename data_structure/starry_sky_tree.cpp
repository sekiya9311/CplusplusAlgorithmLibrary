// StarrySkyTree, (区間加算，区間最小値or最大値)
// O(log N)
class starry_sky_tree {
private:
    const static long long inf = 1e18;
    const int N;
    std::vector<long long> addVec, minVec;
    std::function<bool(long long, long long)> comp;
    void add(int l, int r, long long val, int k, int L, int R) {
        if (R <= l || r <= L) {
            return;
        }
        if (l <= L && R <= r) {
            this->addVec[k] += val;
            return;
        }
        this->add(l, r, val, k * 2 + 1, L, (L + R) / 2);
        this->add(l, r, val, k * 2 + 2, (L + R) / 2, R);
        this->minVec[k] = std::min(addVec[k * 2 + 1] + minVec[k * 2 + 1],
                                   addVec[k * 2 + 2] + minVec[k * 2 + 2], comp);
    }
    long long get(int l, int r, int k, int L, int R) {
        if (R <= l || r <= L) {
            return inf;
        }
        if (l <= L && R <= r) {
            return addVec[k] + minVec[k];
        }
        auto left = this->get(l, r, k * 2 + 1, L, (L + R) / 2);
        auto right = this->get(l, r, k * 2 + 2, (L + R) / 2, R);
        return std::min(left, right, comp) + addVec[k];
    }
public:
    starry_sky_tree(const int n, const long long def = inf,
                    const std::function<bool(long long, long long)> _comp = std::less<long long>())
        : N(n), addVec(n << 2, 0),
          minVec(n << 2, def), comp(_comp) {}
    void add(int l, int r, long long v) {
        this->add(l, r, v, 0, 0, N);
    }
    long long get(int l, int r) {
        return this->get(l, r, 0, 0, N);
    }
};
