/**
* Binary_Indexed_Tree(BIT)
* Fenwick Tree
* 0-indexed!!!
* O(log N)
*/
template<typename T = int>
class binary_indexed_tree {
private:
    std::vector<T> bit;
    const int N;
public:
    binary_indexed_tree() : N(-1) {}
    binary_indexed_tree(int n) : N(n), bit(n, 0) {}
    // bit[point]にnum追加
    void add(int point, T num) {
        point++;
        while (point - 1 < N) {
            bit[point - 1] += num;
            point += point & -point;
        }
    }
    // [0, point)
    T sum(int point) {
        T res = 0;
        while (point > 0) {
            res += bit[point - 1];
            point -= point & -point;
        }
        return res;
    }
    // [left, right)
    T sum(int left, int right) {
        return this->sum(right) - this->sum(left);
    }
};
