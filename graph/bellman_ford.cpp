// ベルマンフォード
// O(|V||E|)

// TODO: cost の型
struct edge {int from, to, cost;};
template<typename T = int>
bool bellman_ford(const int V, const int E, int s, edge es[], T dist[], const T inf) {
    std::fill(dist, dist + V, inf);
    dist[s] = 0;
    int cnt = 0;
    while (true) {
        bool update = false;
        for (int i = 0; i < E; ++i) {
            if (dist[es[i].from] != inf && dist[es[i].to] > dist[es[i].from] + es[i].cost) {
                dist[es[i].to] = dist[es[i].from] + es[i].cost;
                update = true;
            }
        }
        if (!update) {
            break;
        }
        if (cnt == V - 1) {
            return true;
        }
        ++cnt;
    }
    return false;
}
