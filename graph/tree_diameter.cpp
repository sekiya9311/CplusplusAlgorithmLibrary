// 木の直径
// O(|E|)

template<typename cost_type = int>
class tree_diameter {
private:
    std::vector<std::vector<std::pair<int, cost_type>>> Graph;
    std::vector<cost_type> dist;
    void make_tree_dfs(const std::vector<std::vector<int>> &G, int now, int prev) {
        for (auto &&e : G[now]) {
            if (e != prev) {
                Graph[now].emplace_back(std::make_pair(e, 1));
                Graph[e].emplace_back(std::make_pair(now, 1));
                make_tree_dfs(G, e, now);
            }
        }
    }
    void calc_tree_diameter_dfs(int now, int prev) {
        for (auto &&e : Graph[now]) if (e.first != prev) {
            dist[e.first] = dist[now] + e.second;
            calc_tree_diameter_dfs(e.first, now);
        }
    }
public:
    tree_diameter() {}
    tree_diameter(int n) {
        init(n);
    }
    void init(int n) {
        Graph.resize(n);
        dist.resize(n, 0);
    }
    tree_diameter(const std::vector<std::vector<std::pair<int, cost_type>>> &G) {
        Graph = G;
        dist.resize(G.size());
    }
    tree_diameter(const std::vector<std::vector<int>> &G) {
        Graph.resize(G.size());
        make_tree_dfs(G, 0, -1);
        dist.resize(G.size());
    }
    void add_edge(int u, int v, cost_type cost) {
        Graph[u].emplace_back(std::make_pair(v, cost));
        Graph[v].emplace_back(std::make_pair(u, cost));
    }
    int calc_tree_diameter() {
        calc_tree_diameter_dfs(0, -1);
        const int root = std::distance(std::begin(dist), std::max_element(std::begin(dist), std::end(dist)));
        dist[root] = 0;
        calc_tree_diameter_dfs(root, -1);
        return *std::max_element(std::begin(dist), std::end(dist));
    }
};
