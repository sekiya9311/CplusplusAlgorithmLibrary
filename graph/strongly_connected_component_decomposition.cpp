// 強連結成分分解,SCC
// O(|V|+|E|)
class strongly_connected_component_decomposition {
private:
    std::vector<bool> used;
    std::vector<std::vector<int>> graph, revgraph;
    std::vector<int> comp;
    std::vector<int> sortNode;

    void dfs(int now) {
        this->used[now] = true;
        for (const int e : this->graph[now]) {
            if (!this->used[e]) {
                dfs(e);
            }
        }
        this->sortNode.emplace_back(now);
        return;
    }
    void dfs2(int now, int cnt) {
        this->used[now] = true;
        for (const int e : this->revgraph[now]) {
            if (!this->used[e]) {
                dfs2(e, cnt);
            }
        }
        this->comp[now] = cnt;
        return;
    }
public:
    strongly_connected_component_decomposition() {}
    strongly_connected_component_decomposition(const int n)
        : used(n, false), graph(n), revgraph(n), comp(n, 0) {}
    void resize(const int n) {
         this->used.resize(n, false);
         this->graph.resize(n);
         this->revgraph.resize(n);
         this->comp.resize(n, 0);
    }
    void add_edge(const int from, const int to) {
        this->graph[from].emplace_back(to);
        this->revgraph[to].emplace_back(from);
        return;
    }
    int solve() {
        std::fill(std::begin(this->used), std::end(this->used), false);
        for (int i = 0; i < (int)this->used.size(); i++) {
            if (!used[i]) {
                dfs(i);
            }
        }
        std::fill(std::begin(this->used), std::end(this->used), false);
        std::reverse(std::begin(this->sortNode), std::end(this->sortNode));
        int res = 0;
        for (const int n : this->sortNode) {
            if (!this->used[n]) {
                dfs2(n, res++);
            }
        }
        return res;
    }
    std::vector<int> get_comp() {
        return this->comp;
    }
    bool same(const int a, const int b) {
        return this->comp[a] == this->comp[b];
    }
    int operator[](const int n) {
        return comp[n];
    }
};
