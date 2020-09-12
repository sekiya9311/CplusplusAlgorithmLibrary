
// 重心を求める
// O(N)
std::vector<int> calc_centroids(const int N, const std::vector<int> *G) {
  std::vector<int> centroid, size(N, 1);
  std::function<void(int, int)> dfs = [&](int cur, int par) {
    bool is_c = true;
    for (auto to : G[cur]) {
      if (to == par)
        continue;
      dfs(to, cur);
      if (size[to] > N / 2)
        is_c = false;
      size[cur] += size[to];
    }
    if (N - size[cur] > N / 2)
      is_c = false;
    if (is_c) {
      centroid.emplace_back(cur);
    }
  };

  dfs(0, -1);
  return centroid;
}
