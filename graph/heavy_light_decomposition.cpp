class heavy_light_decomposition {
private:
    int N, pos;
    std::vector<std::vector<int>> G;
    std::vector<int> parent;
    std::vector<int> depth;
    std::vector<int> heavy;                 // next node of heavy path
    std::vector<int> sub_tree_cnt;
    std::vector<int> maximum_sub_tree_cnt;
    std::vector<int> tree_th_num;           // what number of tree ?
    std::vector<int> vid, inv_vid;          // re numbering node for decomp (vertex_index)
    std::vector<int> head;                  // root of SubTree in this node

    // calc SubTree count of this node
    int dfs(const int now, const int prev) {
        parent[now] = prev;
        int sub_tree_all_cnt = 1; // include now node
        int max_sub_tree_cnt = 0;
        for (auto &&nxt : this->G[now]) {
            if (nxt == prev) {
                continue;
            }
            this->depth[nxt] = this->depth[now] + 1;
            const int now_sub_tree_cnt = this->dfs(nxt, now);
            sub_tree_all_cnt += now_sub_tree_cnt;
            if (max_sub_tree_cnt < now_sub_tree_cnt) {
                max_sub_tree_cnt = now_sub_tree_cnt;
                this->heavy[now] = nxt;
            }
        }
        return this->sub_tree_cnt[now] = sub_tree_all_cnt;
    }

    void bfs(const int root, const int th) {
        std::queue<int> que;
        que.emplace(root);
        while (!que.empty()) {
            const int now_head = que.front();
            que.pop();
            for (int now = now_head; now != -1; now = this->heavy[now]) {
                this->tree_th_num[now] = th;
                this->vid[now] = pos++;
                this->inv_vid[this->vid[now]] = now;
                this->head[now] = now_head;
                for (auto &&nxt : this->G[now]) {
                    if (nxt != this->parent[now]
                        && nxt != this->heavy[now]) {
                        // not parent && not same heavy path
                        // == different heavy path && haven't search yet
                        que.emplace(nxt);
                    }
                }
            }
        }
    }

public:
    heavy_light_decomposition()
        : heavy_light_decomposition(0) {}
    heavy_light_decomposition(int g_size) :
        N(g_size), pos(0), G(g_size), parent(g_size),
        depth(g_size), heavy(g_size, -1),
        sub_tree_cnt(g_size), tree_th_num(g_size),
        vid(g_size), inv_vid(g_size), head(g_size) {}

    void add_edge(const int a, const int b) {
        this->G[a].emplace_back(b);
        this->G[b].emplace_back(a);
    }

    // if forest, tree roots in argument
    void build(const std::vector<int> roots = std::vector<int>(1, 0)) {
        for (int th = 0; th < (int) roots.size(); th++) {
            this->dfs(roots[th], -1);
            this->bfs(roots[th], th);
        }
    }

    // node(vertex) func in [l, r] !!!!!
    void for_each_node(int a, int b, const std::function<void(int, int)> &func) {
        if (this->vid[a] > this->vid[b]) {
            std::swap(a, b);
        }
        func(std::max(this->vid[this->head[b]], this->vid[a]), this->vid[b]);
        if (this->head[a] != this->head[b]) {
            this->for_each_node(a, this->parent[this->head[b]], func);
        }
    }

    // edge func in [l, r] !!!!!
    void for_each_edge(int a, int b, const std::function<void(int, int)> &func) {
        if (this->vid[a] > this->vid[b]) {
            std::swap(a, b);
        }
        if (this->head[a] != this->head[b]) {
            func(this->vid[this->head[b]], this->vid[b]);
            this->for_each_edge(a, this->parent[this->head[b]], func);
        } else {
            if (a != b) {
                func(this->vid[a] + 1, this->vid[b]);
            }
        }
    }
};
