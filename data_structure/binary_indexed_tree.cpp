/**
* Binary_Indexed_Tree(BIT)
* Fenwick Tree
* 1-indexed!!!
* O(log N)
*/
template<typename T = int>
class binary_indexed_tree {
private:
    std::vector<T> bit;
    const int N;
public:
    binary_indexed_tree() : N(-1) {}
    binary_indexed_tree(int n) : N(n), bit(n + 1, 0) {}
    //bit[point]にnum追加
    void add(int point, T num) {
        assert(N != -1 && 0 <= point && point <= N);
        while (point <= N) {
            bit[point] += num;
            point += point & -point;
        }
    }
    //pointまでの値の和を返す
    T sum(int point) {
        assert(N != -1 && 0 <= point && point <= N);
        T res = 0;
        while (point > 0) {
            res += bit[point];
            point -= point & -point;
        }
        return res;
    }
    //left から right の区間和
    T sum(int left, int right) {
        return this->sum(right) - this->sum(left - 1);
    }
};
