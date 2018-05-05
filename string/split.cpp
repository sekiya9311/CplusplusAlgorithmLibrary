// 文字列分割

std::vector<std::string> split(const std::string &originalStr, const char sep) {
    std::vector<std::string> res;
    std::string element = "";
    for (const char c : originalStr) {
        if (c == sep) {
            res.emplace_back(element);
            element.clear();
        } else {
            element += c;
        }
    }
    if (!element.empty()) {
        res.emplace_back(element);
    }
    return res;
}
