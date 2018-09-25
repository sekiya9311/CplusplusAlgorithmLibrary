//トポロジカルソート
// O(|V|+|E|)

class topological_sort {
private:
    std::vector<bool> is;
    std::vector<std::vector<int>> g;
    std::vector<int> t_sort;
    std::vector<int> in_cnt;
    void dfs(int now) {
        if (is[now]) return;
        is[now] = true;
        for (auto &&el : g[now]) {
            dfs(el);
        }
        t_sort.emplace_back(now);
    }
public:
    topological_sort() {}
    topological_sort(const int N) {
        is.resize(N);
        g.resize(N);
        in_cnt.resize(N);
    }
    std::vector<int> dfs_tsort() {
        for (int i = 0; i < (int) g.size(); i++) {
            dfs(i);
        }
        std::reverse(std::begin(t_sort), std::end(t_sort));
        return t_sort;
    }
    void add_edge(int src, int dst) {
        g[src].emplace_back(dst);
        in_cnt[dst]++;
    }
    std::vector<int> bfs_tsort() {
        std::queue<int> q;
        for (int i = 0; i < (int) in_cnt.size(); i++) {
            if (in_cnt[i] == 0) {
                q.push(i);
            }
        }
        while (!q.empty()) {
            auto now = q.front(); q.pop();
            t_sort.emplace_back(now);
            for (auto &&el : g[now]) {
                if (--in_cnt[el] == 0) {
                    q.push(el);
                }
            }
        }

        if (std::any_of(std::begin(in_cnt),
                        std::end(in_cnt),
                        [](int i) {return i > 0;})) {
            return std::vector<int>();
        }
        return t_sort;
    }
};
