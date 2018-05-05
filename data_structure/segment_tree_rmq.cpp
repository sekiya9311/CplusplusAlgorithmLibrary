// 最大最小,セグメントツリー
// template指定なしで最小

template<typename type = int,
typename ctype = std::less<type>,
type LIM = (std::is_same<ctype, std::less<type>>::value ?
std::numeric_limits<type>::max() :
std::numeric_limits<type>::min())>
class segment_tree_rmq {
private:
    const int n;
    std::vector<type> st;
    ctype comp;
    type query(int l, int r, int k, int L, int R) {
        if (R <= l || r <= L) return LIM;
        if (l <= L && R <= r) return st[k];
        type res = LIM;
        int h = (L + R) >> 1;
        if (l < h) res = std::min(res, query(l, r, (k << 1) + 1, L, h), comp);
        if (h < r) res = std::min(res, query(l, r, (k << 1) + 2, h, R), comp);
        return res;
    }
    void update(int id, type el, int k, int L, int R) {
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
        st[k] = std::min(st[(k << 1) + 2], st[(k << 1) + 1], comp);
    }
public:
    segment_tree_rmq() : n(-1) {}
    segment_tree_rmq(int _n, type initval = LIM) : n(_n), st(_n << 2, initval){}
    //範囲 [l, r) !!!!!
    type query(int l, int r) {
        assert(this->n != -1 && 0 <= l && r <= this->n && l <= r);
        return query(l, r, 0, 0, n);
    }
    void update(int id, type el) {
        assert(this->n != -1 && id < this->n);
        update(id, el, 0, 0, n);
    }
};
