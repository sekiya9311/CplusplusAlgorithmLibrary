// trie tree

template<typename T, char Key>
class trie {
public:
    const static int nxt_size = 26;
    struct node {
        node *nxt[nxt_size];
        T w = 0;
        node() {
            for (int i = 0; i < nxt_size; i++) {
                nxt[i] = nullptr;
            }
        }
    };
    trie() {
        root = node();
    }
    node* get_root() {return this->root;}
    //文字列strを追加
    void insert(const std::string& str, T cost) {
        node *now;
        now = &this->root;
        for (const char c : str) {
            if (now->nxt[c - Key] == nullptr) {
                now->nxt[c - Key] = new node();
            }
            now = now->nxt[c - Key];
        }
        now->w = cost;
    }
    //(重み, 文字列)のペアを持った配列を追加
    void insert(const std::vector<std::pair<T, std::string>>& v) {
        for (std::pair<T, std::string> &&p : v) {
            insert(p.second, p.first);
        }
    }
    //文字列strの探索，存在していたら重みを返す
    T search(const std::string& str) {
        node *now;
        now = &this->root;
        for (const char c : str) {
            if (now->nxt[c - Key] == nullptr) {
                return 0;
            }
            now = now->nxt[c - Key];
        }
        return now->w;
    }
    //now_node_search関数で現在見てるノードをrootでリセット
    void now_node_reset() {
        nownode = &this->root;
    }
    //nownodeからchar変数cの探索，あったらnownode更新
    T now_node_search(const char& c) {
        if (nownode->nxt[c - Key] == nullptr) {
            return errorRetNum;
        }
        nownode = nownode->nxt[c - Key];
        return nownode->w;
    }
private:
    node root;
    node *nownode;
    const T errorRetNum = -1;
};
