// ret[rank][idx] = (left idx, right idx) の構造で括弧のみの文字列の深さと, ペアのindexを持つvectorを返却
// O(L) ?
std::vector<std::vector<std::pair<int, int>>> calc_bracket_pair_rank(const std::string &brackets) {
    const int L = brackets.length();
    {   // valid check
        std::vector<int> rankVec(L + 1);
        for (int i = 0;  i < L; i++) {
            if (brackets[i] == '(') {
                rankVec[i]++;
            } else if (brackets[i] == ')') {
                rankVec[i]--;
            } else {
                throw std::runtime_error("contains not bracket character.");
            }
        }
        for (int i = 0; i < L; i++) {
            rankVec[i + 1] += rankVec[i];
        }
        if (rankVec.back() != 0) {
            throw std::runtime_error("invalid rank");
        }
    }
    std::vector<std::vector<std::pair<int, int>>> ret(L);
    std::vector<bool> vis(L);
    std::function<int(int, int)> dfs = [&](int now, int rank) {
        for (int i = now + 1; i < L; i++) {
            if (brackets[i] == ')' && !vis[i]) {
                vis[i] = true;
                ret[rank].emplace_back(now, i);
                return i;
            } else if (brackets[i] == '(' && !vis[i]) {
                vis[i] = true;
                i = dfs(i, rank + 1);
            }
        }
        return 0;
    };
    for (int i = 0; i < L; i++) {
        if (!vis[i]) {
            vis[i] = true;
            dfs(i, 0);
        }
    }
    while (ret.size() > 0 && ret.back().size() == 0) {
        ret.pop_back();
    }
    return ret;
}
