// 括弧のみの文字列の深さ計算
// O(L)
std::vector<int> calc_bracket_rank(const std::string brackets) {
    const int L = brackets.length();
    std::vector<int> ret(L);
    int nowRank = 0;
    for (int i = 0; i < L; i++) {
        if (brackets[i] == '(') {
            nowRank++;
            ret[i] = nowRank;
        } else if (brackets[i] == ')') {
            ret[i] = nowRank;
            nowRank--;
        } else {
            throw std::runtime_error("contains not bracket character.");
        }
    }
    if (nowRank != 0) {
        throw std::runtime_error("invalid rank");
    }
    return ret;
}
