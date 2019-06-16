/**
* Binary_Indexed_Tree(BIT) 2d
* Fenwick Tree
* 0-indexed!!!
* O((log N)(log M))
*/
template<typename T = int>
class binary_indexed_tree_2d {
private:
    int N;
    int M;
    std::vector<std::vector<T>> bit;

    T sum(int x, int y) {
        T res = 0;

        for (int i = x; i > 0; i -= i & (-i)) {
            for (int j = y; j > 0; j -= j & (-j)) {
                res += this->bit[i - 1][j - 1];
            }
        }
        return res;
    }

public:
    binary_indexed_tree_2d() {}
    binary_indexed_tree_2d(int n, int m)
        : N(n + 1), M(m + 1), bit(n + 1, std::vector<T>(m + 1)) {}

    void add(int x, int y, T val) {
        // for 0-indexed
        x++; y++;

        for (int i = x; i - 1 < N; i += i & (-i)) {
            for (int j = y; j - 1 < M; j += j & (-j)) {
                this->bit[i - 1][j - 1] += val;
            }
        }
    }

    // [ (x1, y1), (x2, y2) )
    T sum(int x1, int y1, int x2, int y2) {

        T res = this->sum(x2, y2);
        res -= sum(x1, y2);
        res -= sum(x2, y1);
        res += sum(x1, y1);

        return res;
    }
};
