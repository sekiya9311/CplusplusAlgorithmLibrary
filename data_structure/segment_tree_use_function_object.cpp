// セグメントツリー,関数オブジェクト

template<typename T>
class segment_tree_use_function_object {
private:
    std::vector<T> data, lazy;
    std::vector<bool> lazyFlag;
    int size;
    const std::function<T(T, T)> op, change;
    const T initVal;
    void push(int l, int r, int k) {
        if (this->lazyFlag[k]) {
            this->data[k] = change(this->data[k], this->lazy[k]);
            if (k * 2 + 2 < this->size * 2 - 1) {
                this->lazyFlag[k * 2 + 1]
                = this->lazyFlag[k * 2 + 2]
                = true;
                this->lazy[k * 2 + 1]
                = this->lazy[k * 2 + 2]
                = this->lazy[k];
            }
            this->lazyFlag[k] = false;
        }
    }
    void update(int l, int r, int L, int R, int k, T val) {
        this->push(l, r, k);
        if (L <= l && r <= R) {
            this->lazy[k] = val;
            this->lazyFlag[k] = true;
            this->push(l, r, k);
        } else if (R <= l || r <= L) {
            return;
        } else if (r - l > 1) {
            const int mid = (l + r) / 2;
            this->update(l, mid, L, R, k * 2 + 1, val);
            this->update(mid, r, L, R, k * 2 + 2, val);
            data[k] = op(data[k * 2 + 1], data[k * 2 + 2]);
        }
    }
    T query(int l, int r, int L, int R, int k) {
        this->push(l, r, k);
        if (L <= l && r <= R) {
            return data[k];
        } else if (R <= l || r <= L) {
            return this->initVal;
        } else {
            const int mid = (l + r) / 2;
            const T left = this->query(l, mid, L, R, k * 2 + 1);
            const T right = this->query(mid, r, L, R, k * 2 + 2);
            return op(left, right);
        }
    }
public:
    // change : update時の関数
    // op : それ以外
    segment_tree_use_function_object(const int size_, T initVal_, std::function<T(T, T)> op_, std::function<T(T, T)> change_)
        : op(op_), change(change_), initVal(initVal_) {
        this->size = 1;
        while (this->size < size_) {
            this->size <<= 1;
        }
        data.resize(this->size * 2 - 1, this->initVal);
        lazy.resize(this->size * 2 - 1, this->initVal);
        lazyFlag.resize(this->size * 2 - 1, false);
    }
    void update(int l, int r, T val) {
        this->update(0, this->size, l, r, 0, val);
    }
    void update(int idx, T val) {
        this->update(0, this->size, idx, idx + 1, val);
    }
    T query(int l, int r) {
        return this->query(0, this->size, l, r, 0);
    }
};
