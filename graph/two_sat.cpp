// 2-SAT
// 今日連結成分分解(SCC)必須
class two_sat {
private:
    strongly_connected_component_decomposition scc;
    int sz;
public:
    two_sat(const int n) : scc(n * 2), sz(n) {}
    two_sat() {}

    void add_logic(const int a, const bool ab, const int b, const bool bb) {
        this->scc.add_edge(a + (ab ? 0 : this->sz), b + (bb ? this->sz : 0));
        this->scc.add_edge(b + (bb ? 0 : this->sz), a + (ab ? this->sz : 0));
    }

    bool calc_satisfy() {
        this->scc.solve();
        for (int i = 0; i < this->sz; i++) {
            if (this->scc.same(i, i + this->sz)) {
                return false;
            }
        }
        return true;
    }
    bool operator[](const int n) {
        return this->scc[n] > this->scc[n + sz];
    }
};
