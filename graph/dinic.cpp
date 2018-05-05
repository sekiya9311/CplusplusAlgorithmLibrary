// Dinic,最大流,MaxFlow
// O(|E||V|^2)
class dinic {
private:
    const long long inf = 1e18;
    struct edge {
        int to, rev;    //行き先，逆辺(のid)
        long long cap;  //容量
        edge(int _to, int _rev, long long _cap) {
            this->to = _to;
            this->rev = _rev;
            this->cap = _cap;
        }
    };
    std::vector<std::vector<edge>> G;
    std::vector<int> dist;   //sからの距離
    std::vector<int> iter;   //どこまで調べ終わったか
    //sからの最短経路探索(distに格納)
    void bfs(int s) {
        std::fill(std::begin(dist), std::end(dist), -1);
        std::queue<int> q;
        q.push(s);
        dist[s] = 0;
        while (!q.empty()) {
            const int now = q.front(); q.pop();
            for (edge el : G[now]) {
                if (el.cap > 0 && dist[el.to] < 0) {
                    dist[el.to] = dist[now] + 1;
                    q.push(el.to);
                }
            }
        }
    }
    const long long dfs(int v, int t, long long f) {
        if (v == t) {
            return f;
        }
        for (int &id = iter[v]; id < (int) G[v].size(); id++) {
            auto &el = G[v][id];
            if (el.cap <= 0 || dist[v] >= dist[el.to]) {
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
    dinic() {}
    dinic(const int n) {
        G.resize(n);
        dist.resize(n, -1);
        iter.resize(n, 0);
    }
    void add_edge(int from, int to, long long cap) {
        G[from].emplace_back(edge(to, G[to].size(), cap));
        G[to].emplace_back(edge(from, G[from].size() - 1, 0));
    }
    const long long max_flow(int s, int t) {
        if (s == t) {
            return 0;
        }
        long long flow = 0;
        while (true) {
            bfs(s);
            if (dist[t] < 0) {
                return flow;
            }
            std::fill(std::begin(iter), std::end(iter), 0);
            const long long f = dfs(s, t, inf);
            if (f > 0) {
                flow += f;
            }
        }
    }
};
