// 最小共通祖先

class lowest_common_ancester {
private:
    using cost_type = int;
    std::vector<std::vector<std::pair<int, cost_type>>> graph;
    std::vector<std::vector<int>> parent;
    std::vector<int> depth;
    std::vector<cost_type> cost;
    static const int MAX_LOG = 20;
    bool valid = false;
    void dfs(const int now, const int par, const int nowDepth, const cost_type nowCost) {
        depth[now] = nowDepth;
        parent[0][now] = par;
        cost[now] = nowCost;
        for (auto &&e : graph[now]) {
            if (e.first != par) {
                dfs(e.first, now, nowDepth + 1, nowCost + e.second);
            }
        }
    }
public:
    lowest_common_ancester() {}
    lowest_common_ancester(const std::vector<std::vector<std::pair<int, int>>> &graph_)
    : graph(graph_), parent(this->MAX_LOG, std::vector<int>(graph_.size(), 0)),
    depth(graph_.size(), 0), cost(graph_.size(), 0) {this->valid = false;}
    lowest_common_ancester(const std::vector<std::pair<int, int>> *graph_, int size_)
    : parent(this->MAX_LOG, std::vector<int>(size_, 0)), depth(size_, 0), cost(size_, 0) {
        graph.resize(size_);
        for (int i = 0; i < size_; ++i) {
            this->graph[i] = graph_[i];
        }
        this->valid = false;
    }
    lowest_common_ancester(const int n)
    : graph(n), parent(this->MAX_LOG, std::vector<int>(n, 0)), depth(n, 0), cost(n, 0) {this->valid = false;}

    void add_edge(const int a, const int b, const cost_type c) {
        this->graph[a].emplace_back(std::make_pair(b, c));
        this->graph[b].emplace_back(std::make_pair(a, c));
        this->valid = false;
    }
    void calc_init() {
        dfs(0, -1, 0, 0);
        for (int k = 0; k + 1 < this->MAX_LOG; ++k) {
            for (int v = 0; v < (int) graph.size(); ++v) {
                if (this-> parent[k][v] == -1) {
                    this->parent[k + 1][v] = -1;
                } else {
                    this->parent[k + 1][v] = this->parent[k][this->parent[k][v]];
                }
            }
        }
        this->valid = true;
    }
    int lca(int u, int v) {
        if (this->depth[u] > this->depth[v]) {
            std::swap(u, v);
        }
        // uとvの深さを合わせる
        for (int k = 0; k < this->MAX_LOG; ++k) {
            if (((this->depth[v] - this->depth[u]) >> k) & 1) {
                v = this->parent[k][v];
            }
        }
        if (u == v) {
            return u;
        }
        // 二分探索でぶつかる所までもっていく
        for (int k = this->MAX_LOG - 1; k >= 0; --k) {
            if (parent[k][u] != parent[k][v]) {
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }
};
