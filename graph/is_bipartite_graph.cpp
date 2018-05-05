// 二部グラフ判定
// O(|V|)
bool is_bipartite_graph(std::vector<int> checkGraph[], int size, int now = 0, int prev = -1, int c = 0, bool isFirst = true) {
    static int color[MAX];
    if (isFirst) {
        memset(color, -1, sizeof(color));
        isFirst = false;
    }
    if (color[now] == -1) {
        color[now] = c;
        bool ret = true;
        for (int e : checkGraph[now]) {
            if (e != prev) {
                ret &= is_bipartite_graph(checkGraph, size, e, now, c ^ 1, false);
            }
        }
        return ret;
    } else {
        return color[now] == c;
    }
}
