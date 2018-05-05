// 文字列連結

std::string join(const std::vector<std::string> &vec, const std::string &delimiter) {
    std::string res = "";
    for (int i = 0; i < (int) vec.size(); ++i) {
        res += vec[i] + (i + 1 == (int) vec.size() ? "" : delimiter);
    }
    return res;
}
