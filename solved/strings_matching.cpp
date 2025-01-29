#include <bits/stdc++.h>
 
using i64 = long long;

class Solution {
public:
    // KMP
    static std::vector<int> get_pref(const std::string &s) {
        int n = (int)s.size();
        std::vector<int> pref_s(n);
        for (int i = 1, j = 0; i < n; i++) {
            while (j > 0 && s[j] != s[i]) {
                j = pref_s[j - 1];
            }

            if (s[i] == s[j]) j++;
            pref_s[i] = j;
        }

        return pref_s;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string P, T;
    std::cin >> T >> P;
    std::string S = P + '#' + T;
    std::vector<int> pref = Solution::get_pref(S);
    int ans = 0;
    for (int l : pref) {
        if (l == P.size()) {
            ans++;
        }
    }
    std::cout << ans << '\n';
}
