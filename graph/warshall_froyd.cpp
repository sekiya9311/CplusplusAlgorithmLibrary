// ワーシャルフロイド
// O(V^3)
template<typename T = int>
void warshall_froyd(std::vector<std::vector<T>> &costs) {
    const int N = costs.size();
    assert(costs.size() == costs.front().size());
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                costs[i][j] = std::min(costs[i][j], costs[i][k] + costs[k][j]);
            }
        }
    }
    return;
}
