// 一点変更,区間GCD,セグメントツリー

template<typename type = int>
class segment_tree_gcd {
private:
    const int n;
    std::vector<type> st;
    const type LIM = 0;
    inline type query(int l, int r, int k, int L, int R) {
        if (R <= l || r <= L) {
            return LIM;
        }
        if (l <= L && R <= r) {
            return st[k];
        }
        type res = LIM;
        type h = (L + R) >> 1;
        if (l < h) {
            res = query(l, r, (k << 1) + 1, L, h);
        }
        if (h < r) {
            type rRet = query(l, r, (k << 1) + 2, h, R);
            if (rRet != LIM) {
                if (res == LIM) {
                    res = rRet;
                } else {
                    res = __gcd(res, rRet);
                }
            }
        }
        return res;
    }
    inline bool valid_query(int l, int r, int k, int L, int R, int cond) {
        if (R <= l || r <= L) {
            return true;
        }
        if (l <= L && R <= r) {
            return st[k] % cond == 0;
        }
        bool res = true;
        int h = (L + R) >> 1;
        return valid_query(l, r, (k << 1) + 2, h, R, cond) && valid_query(l, r, (k << 1) + 1, L, h, cond);
    }
    inline void update(int id, type el, int k, int L, int R) {
        if (id < L || R <= id) {
            return;
        }
        if (L + 1 == R && id == L) {
            st[k] = el;
            return;
        }
        const int h = (L + R) >> 1;
        update(id, el, (k << 1) + 1, L, h);
        update(id, el, (k << 1) + 2, h, R);
        st[k] = __gcd(st[(k << 1) + 2], st[(k << 1) + 1]);
    }
public:
    segment_tree_gcd() : n(-1) {}
    segment_tree_gcd(int _n) : n(_n), st(_n << 2, LIM){}
    //範囲 [l, r) !!!!!
    inline type query(int l, int r) {
        return this->query(l, r, 0, 0, n);
    }
    // gcd が cond の倍数になるか
    inline type valid_query(int l, int r, int cond) {
        return this->valid_query(l, r, 0, 0, n, cond);
    }
    inline void update(int id, type el) {
        update(id, el, 0, 0, n);
    }
};
