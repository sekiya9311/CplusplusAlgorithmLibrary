/**
* Binary_Indexed_Tree(BIT) by mod
* Fenwick Tree
* 0-indexed!!!
* O(log N)
*/
template<int mod>
class binary_indexed_tree_by_mod {
private:
    const int N;
    std::vector<int> bit;

    void add_by_mod(int &a, int b) {
        if (b < 0) b += mod;
        a += b;
        if (a >= mod) a -= mod;
    }

public:
    binary_indexed_tree_by_mod() : N(-1) {}
    binary_indexed_tree_by_mod(int n) : N(n), bit(n, 0) {}
    // bit[point]にnum追加
    void add(int point, long long val) {
        // for mod calc
        val %= mod;
        // for 0-indexed
        point++;

        for (int i = point; i - 1 < N; i += i & (-i)) {
            add_by_mod(bit[i - 1], val);
        }
    }
    // [0, point)
    int sum(int point) {
        int res = 0;
        for (int i = point; i > 0; i -= i & (-i)) {
            add_by_mod(res, bit[i - 1]);
        }

        return res;
    }
    // [left, right)
    int sum(int left, int right) {
        int res = this->sum(right);
        add_by_mod(res, -this->sum(left));

        return res;
    }
};
