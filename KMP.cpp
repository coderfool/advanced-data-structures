class KMP {
public:
    std::string pattern;
    std::vector<int> LPS;
    KMP(std::string pattern) {
        this->pattern = pattern;
        LPS = std::vector<int>(pattern.length());
        for (int i = 1, j = 0; i < LPS.size();) {
            if (pattern[i] == pattern[j]) LPS[i++] = ++j;
            else if (j > 0) j = LPS[j - 1];
            else i++;
        }
    }

    std::vector<int> find_all(std::string text) {
        std::vector<int> indexes;
        for (int i = 0, j = 0; i < text.length();) {
            if (text[i] == pattern[j]) {
                i++, j++;
                if (j == pattern.length()) {
                    indexes.push_back(i - pattern.length());
                    j = LPS[j - 1];
                }
            }
            else {
                if (j == 0) i++;
                else j = LPS[j - 1];
            }
        }
        return indexes;
    }
};
