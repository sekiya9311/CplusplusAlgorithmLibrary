// 最大流,FordFulkerson,MaxFlow
// O(|MaxFlow||E|)
class ford_fulkerson {
    struct edge {
        int to, rev;    //行き先，逆辺(のid)
        long long cap;  //容量
        edge(int _to, int _rev, long long _cap) {
            this->to = _to;
            this->rev = _rev;
            this->cap = _cap;
        }
    };
private:
    std::vector<std::vector<edge>> G;
    std::vector<bool> used;
    const long long inf = 1e18;
    long long dfs(int v, int t, long long f) {
        if (v == t) {
            return f;
        }
        used[v] = true;
        for (auto &&el : G[v]) {
            if (used[el.to] || el.cap <= 0) {
                continue;
            }
            const long long d = dfs(el.to, t, std::min(f, el.cap));
            if (d > 0) {
                el.cap -= d;
                G[el.to][el.rev].cap += d;
                return d;
            }
        }
        return 0;
    }
public:
    ford_fulkerson() {}
    ford_fulkerson(int n) {
        G.resize(n);
        used.resize(n, false);
    }
    void add_edge(int from, int to, long long cap) {
        G[from].emplace_back(edge(to, G[to].size(), cap));
        G[to].emplace_back(edge(from, G[from].size() - 1, 0));
    }
    long long max_flow(int s, int t) {
        if (s == t) {
            return 0;
        }
        long long flow = 0;
        while (true) {
            std::fill(std::begin(used), std::end(used), false);
            const long long f = dfs(s, t, inf);
            if (f == 0) {
                return flow;
            }
            flow += f;
        }
    }
};
