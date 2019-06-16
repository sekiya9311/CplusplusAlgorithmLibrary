/**
* Binary_Indexed_Tree(BIT) 2d by mod
* Fenwick Tree
* 0-indexed!!!
* O((log N)(log M))
*/
template<int mod>
class binary_indexed_tree_2d_by_mod {
private:
    int N;
    int M;
    std::vector<std::vector<int>> bit;

    void add(int &a, int b) {
        if (b < 0) b += mod;
        a += b;
        if (a >= mod) a -= mod;
    }

    int sum(int x, int y) {
        int res = 0;

        for (int i = x; i > 0; i -= i & (-i)) {
            for (int j = y; j > 0; j -= j & (-j)) {
                this->add(res, this->bit[i - 1][j - 1]);
            }
        }
        return res;
    }

public:
    binary_indexed_tree_2d_by_mod() {}
    binary_indexed_tree_2d_by_mod(int n, int m)
        : N(n + 1), M(m + 1), bit(n + 1, std::vector<int>(m + 1)) {}

    void add(int x, int y, long long val) {
        // for mod calc
        val %= mod;
        // for 0-indexed
        x++; y++;

        for (int i = x; i - 1 < N; i += i & (-i)) {
            for (int j = y; j - 1 < M; j += j & (-j)) {
                this->add(this->bit[i - 1][j - 1], val);
            }
        }
    }

    // [ (x1, y1), (x2, y2) )
    int sum(int x1, int y1, int x2, int y2) {

        int res = this->sum(x2, y2);
        add(res, -sum(x1, y2));
        add(res, -sum(x2, y1));
        add(res, sum(x1, y1));

        return res;
    }
};
