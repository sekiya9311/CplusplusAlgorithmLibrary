// ダイクストラ,経路数
// pair<min cost, route count>
template<typename T = int>
std::pair<std::vector<T>, std::vector<long long>>
dijkstra_with_route_count(std::vector<std::pair<int, T>> G[],
                          int size,
                          int st,
                          const T inf) {
    std::priority_queue<std::pair<T, int>,
                        std::vector<std::pair<T, int>>,
                        std::greater<std::pair<T, int>>> pq;
    pq.push({0, st});
    std::vector<T> dist(size, inf);
    std::vector<long long> cnt(size, 0);
    dist[st] = 0;
    cnt[st] = 1;
    while (!pq.empty()) {
        const auto now = pq.top();
        pq.pop();
        if (dist[now.second] < now.first) {
            continue;
        }
        for (auto nxt : G[now.second]) {
            const T nextCost = dist[now.second] + nxt.second;
            if (dist[nxt.first] > nextCost) {
                dist[nxt.first] = nextCost;
                cnt[nxt.first] += cnt[now.second];
                pq.push(make_pair(nextCost, nxt.first));
            } else if (dist[nxt.first] == nextCost) {
                cnt[nxt.first] += cnt[now.second];
            }
        }
    }
    return {dist, cnt};
}
