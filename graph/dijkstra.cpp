// ダイクストラ法
// 優先度付きキュー(priority_queue)使用
// グラフは二次元の std::vector で表現
template<typename cost_type = int>
std::vector<cost_type> dijkstra(
  const std::vector<std::vector<std::pair<int, cost_type>>> &G,
  const int st,
  const cost_type inf = std::numeric_limits<cost_type>::max() / 3) {
  
  const int SZ = G.size();
  std::vector<cost_type> dist(SZ, inf);
  dist[st] = 0;

  std::priority_queue<
    std::pair<cost_type, int>,
    std::vector<std::pair<cost_type, int>>,
    std::greater<std::pair<cost_type, int>>> pq;
  pq.emplace(0, st);
  while (!pq.empty()) {
    const auto cur_cost = std::get<0>(pq.top());
    const auto cur = std::get<1>(pq.top());
    pq.pop();
    if (dist[cur] < cur_cost) {
      continue;
    }
    for (auto &&nxt : G[cur]) {
      const auto nxt_p = std::get<0>(nxt);
      const auto nxt_cost = cur_cost + std::get<1>(nxt);
      if (dist[nxt_p] <= nxt_cost) {
        continue;
      }
      dist[nxt_p] = nxt_cost;
      pq.emplace(nxt_cost, nxt_p);
    }
  }

  return dist;
}
