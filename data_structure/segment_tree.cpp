// セグメントツリー,SegmentTree,区分木,range
// O(log N)
template<typename value_type>
class segment_tree {
private:
    const int n;
    std::vector<value_type> st;
    std::function<value_type(value_type, value_type)> func;
    value_type initVal;
    value_type query(int l, int r, int k, int L, int R) {
        if (R <= l || r <= L) return initVal;
        if (l <= L && R <= r) return st[k];
        value_type res = initVal;
        int h = (L + R) >> 1;
        if (l < h) res = func(res, query(l, r, (k << 1) + 1, L, h));
        if (h < r) res = func(res, query(l, r, (k << 1) + 2, h, R));
        return res;
    }
    void update(int id, value_type el, int k, int L, int R) {
        if (id < L || R <= id) return;
        if (L + 1 == R && id == L) {
            st[k] = el;
            return;
        }
        int h = (L + R) >> 1;
        update(id, el, (k << 1) + 1, L, h);
        update(id, el, (k << 1) + 2, h, R);
        st[k] = func(st[(k << 1) + 1], st[(k << 1) + 2]);
    }
public:
    segment_tree() : n(-1) {}
    segment_tree(int _n,
                value_type _initVal,
                std::function<value_type(value_type, value_type)> _func)
        : n(_n), initVal(_initVal), st(_n << 2, _initVal), func(_func){}
    //範囲 [l, r) !!!!!
    value_type query(int l, int r) {
        assert(this->n != -1 && 0 <= l && r <= this->n && l <= r);
        return query(l, r, 0, 0, n);
    }
    void update(int id, value_type el) {
        assert(this->n != -1 && id < this->n);
        update(id, el, 0, 0, n);
    }
};
