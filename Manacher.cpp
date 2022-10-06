class Manacher {
    std::string s;

public:
    std::vector<int> lps;

    Manacher(std::string s) {
        this->s = std::string(2 * s.length() + 3, '#');
        lps = std::vector<int>(this->s.length());
        this->s[0] = '^', this->s[this->s.length() - 1] = '$';
        for (int i = 1; i <= s.length(); i++) this->s[2 * i] = s[i - 1];
        int c = 2, r = 2;
        for (int i = 2; i < lps.size() - 2; i++) {
            int left_mirror = 2 * c - i;
            if (i < r) lps[i] = std::min(lps[left_mirror], r - i);
            while (this->s[i - lps[i] - 1] == this->s[i + lps[i] + 1]) lps[i]++;
            if (i + lps[i] > r) c = i, r = i + lps[i];
        }
    }

    std::string LPS() {
        std::string substr;
        int max_pos = 2;
        for (int i = 3; i < lps.size(); i++) {
            if (lps[i] > lps[max_pos]) max_pos = i;
        }
        for (int i = max_pos - lps[max_pos]; i <= max_pos + lps[max_pos]; i++) {
            if (s[i] != '#') substr.push_back(s[i]);
        }
        return substr;
    }
};
