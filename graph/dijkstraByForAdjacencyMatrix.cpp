// ダイクストラ,dijkstra,隣接行列,AdjacencyMatrix
// O(|V|^2)
template<typename T = int>
void dijkstra(int V, int s, T **cost, T *dist, const T inf) {
    std::vector<bool> used(V, false);
    std::fill(dist, dist + V, inf);
    dist[s] = 0;
    while (true) {
        int v = -1;
        for (int i = 0; i < V; ++i) {
            if (!used[i] && (v == -1 || dist[i] < dist[v])) {
                v = i;
            }
        }
        if (v == -1) {
            break;
        }
        used[v] = true;
        for (int i = 0; i < V; ++i) {
            if (dist[i] > dist[v] + cost[v][i]) {
                dist[i] = dist[v] + cost[v][i];
            }
        }
    }
    return;
}
