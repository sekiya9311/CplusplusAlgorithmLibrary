//トポロジカルソート
// O(|V|+|E|)

class topological_sort {
private:
    std::vector<bool> is;
    std::vector<std::vector<int>> g;
    std::vector<int> tsort;
    std::vector<int> inCnt;
    void dfs(int now) {
        if (is[now]) return;
        is[now] = true;
        for (auto &&el : g[now]) {
            dfs(el);
        }
        tsort.emplace_back(now);
    }
public:
    topological_sort() {}
    topological_sort(const int N) {
        is.resize(N);
        g.resize(N);
        inCnt.resize(N);
    }
    std::vector<int> dfs_tsort() {
        for (int i = 0; i < (int) g.size(); i++) {
            dfs(i);
        }
        std::reverse(std::begin(tsort), std::end(tsort));
        return tsort;
    }
    void add_edge(int src, int dst) {
        g[src].emplace_back(dst);
        inCnt[dst]++;
    }
    std::vector<int> bfs_tsort() {
        std::queue<int> q;
        for (int i = 0; i < (int) inCnt.size(); i++) {
            if (inCnt[i] == 0) {
                q.push(i);
            }
        }
        while (!q.empty()) {
            auto now = q.front(); q.pop();
            tsort.emplace_back(now);
            for (auto &&el : g[now]) {
                if (--inCnt[el] == 0) {
                    q.push(el);
                }
            }
        }

        if (std::any_of(std::begin(inCnt),
                        std::end(inCnt),
                        [](int i) {return i > 0;})) {
            return std::vector<int>();
        }
        return tsort;
    }
};
