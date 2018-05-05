// 二進Trie
class binary_trie {
    const static int NEXT_SIZE = 2;
    class node {
    public:
        int cnt = 0;
        node *nxt[NEXT_SIZE];
        node() {
            nxt[0] = nxt[1] = nullptr;
        }
    };
    node root;
    public:
    binary_trie() {
        root = node();
    }
    void add(int val, int deg = 29, node* now = nullptr) {
        if (now == nullptr) now = &root;
        if (deg == -1) {
            now->cnt++;
            return;
        }
        const int nxt = !!(val & (1 << deg));
        if (now->nxt[nxt] == nullptr) {
            now->nxt[nxt] = new node();
        }
        add(val, deg - 1, now->nxt[nxt]);
    }
    bool remove(int val, int deg = 29, node* now = nullptr) {
        if (now == nullptr) {
            now = &root;
        }
        if (deg == -1) {
            now->cnt--;
            return now->cnt == 0;
        }
        const int nxt = !!(val & (1 << deg));
        if (remove(val, deg - 1, now->nxt[nxt])) {
            now->nxt[nxt] = nullptr;
            if (now->nxt[nxt ^ 1] == nullptr) {
                return true;
            }
        }
        return false;
    }
    int get(int val, int deg = 29, node* now = nullptr) {
        // TODO
        return 0;
    }
};
