/**
* Binary_Indexed_Tree(BIT)
* Fenwick Tree
* 0-indexed!!!
* O(log N)
*/
template<typename T = int>
class binary_indexed_tree {
private:
    const int N;
    std::vector<T> bit;
public:
    binary_indexed_tree() : N(-1) {}
    binary_indexed_tree(int n) : N(n), bit(n, 0) {}
    // bit[point]にnum追加
    void add(int point, T val) {
        point++;

        for (int i = point; i - 1 < N; i += i & (-i)) {
            bit[i - 1] += val;
        }
    }
    // [0, point)
    T sum(int point) {
        T res = 0;
        for (int i = point; i > 0; i -= i & (-i)) {
            res += bit[i - 1];
        }

        return res;
    }
    // [left, right)
    T sum(int left, int right) {
        return this->sum(right) - this->sum(left);
    }
};
