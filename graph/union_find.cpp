// UnionFind,素集合データ構造,DisjointSet

template<typename weight_type = int>
class union_find {
    static_assert(
        std::is_arithmetic<weight_type>::value,
        "Invalid weight type");
private:
    const std::function<void(int, int)> noop = [](int aa, int bb){};

    std::vector<int> uni;
    std::vector<int> edge_count_;
    std::vector<weight_type> weights;
    int size_;
    const void check(const int n) const {
        if (this->group_size() < 0) {
            assert(false);
        }
        if (!(0 <= n && n < this->all_size())) {
            assert(false);
        }
    }
public:
    union_find() : uni(0), edge_count_(0), weights(0), size_(-1) {}
    union_find(const int n)
        : uni(n, -1), edge_count_(n), weights(n), size_(n) {
        this->check(n - 1);
    }
    union_find(const std::vector<weight_type> &_weights)
        : uni(_weights.size(), -1), edge_count_(_weights.size()),
        weights(_weights), size_(_weights.size()) {
        this->check((int)_weights.size() - 1);
    }
    bool same(const int a, const int b) {
        this->check(a);
        this->check(b);
        return this->find(a) == this->find(b);
    }
    int find(const int a) {
        this->check(a);
        return this->uni[a] < 0 ?
                a :
            this->uni[a] = this->find(this->uni[a]);
    }
    bool unite(int a, int b) {
        return unite(a, b, noop);
    }
    bool unite(int a, int b, const std::function<void(int, int)> &f) {
        a = this->find(a);
        b = this->find(b);
        this->edge_count_[a]++;
        if (a == b) {
            return false;
        }
        this->size_--;
        if (this->uni[a] > this->uni[b]) {
            std::swap(a, b);
        }
        f(a, b);
        this->uni[a] += this->uni[b];
        this->weights[a] += this->weights[b];
        this->edge_count_[a] += this->edge_count_[b];
        this->uni[b] = a;
        return true;
    }
    const int group_size() const {
        return this->size_;
    }
    const int all_size() const {
        return this->uni.size();
    }
    const int size(const int a) {
        this->check(a);
        return -this->uni[this->find(a)];
    }
    const int edge_count(const int a) {
        this->check(a);
        return this->edge_count_[this->find(a)];
    }
    const weight_type weight(const int a) {
        this->check(a);
        return this->weights[this->find(a)];
    }
};
