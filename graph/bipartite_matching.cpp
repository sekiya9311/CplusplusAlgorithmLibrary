// 二部グラフの最大マッチング

class bipartite_matching {
private:
    std::vector<std::vector<int>> G;
    std::vector<int> match;
    std::vector<bool> visited;
    bool dfs(const int now) {
        this->visited[now] = true;
        for (const int &nxt : this->G[now]) {
            const int nxt_match = this->match[nxt];
            if (nxt_match < 0 || (!this->visited[nxt_match]
                                && this->dfs(nxt_match))) {
                this->match[now] = nxt;
                this->match[nxt] = now;
                return true;
            }
        }
        return false;
    }
public:
    bipartite_matching() {}
    bipartite_matching(const int N)
        : G(N),
          match(N, -1),
          visited(N, false) {}
    void add_edge(const int from, const int to) {
        this->G[from].emplace_back(to);
        this->G[to].emplace_back(from);
    }
    int calc_maximum_match() {
        int ret = 0;
        for (int i = 0; i < (int) this->G.size(); i++) {
            if (this->match[i] < 0) {
                std::fill(
                    std::begin(this->visited),
                    std::end(this->visited),
                    false
                );
                ret += this->dfs(i);
            }
        }
        return ret;
    }
    int operator[](const int idx) const {
        return this->match[idx];
    }
};
