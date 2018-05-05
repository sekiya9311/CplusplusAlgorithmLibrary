// 部分永続UnionFind 各操作 O(log N)

class partial_persistence_union_find {
private:
    std::vector<std::map<int, int>> uni;
    int cnt;
public:
    partial_persistence_union_find() : cnt(-1) {}
    partial_persistence_union_find(const int N)
                            : uni(N), cnt(-1) {
        for (int i = 0; i < N; i++) {
            uni[i][-1] = i;
        }
    }
    // O(log N)
    int find(const int u, const int t) {
        auto itr = this->uni[u].upper_bound(t);
        itr--;
        return itr->second == u ? itr->second
                                : this->find(itr->second, t);
    }
    bool same(const int a, const int b, const int t) {
        return this->find(a, t) == this->find(b, t);
    }
    // O(log N)
    bool unite(int a, int b) {
        cnt++;
        a = this->find(a, cnt);
        b = this->find(b, cnt);
        if (a == b) {
            return false;
        }
        if (a > b) {
            std::swap(a, b);
        }
        this->uni[b][cnt] = a;
        return true;
    }
};
