class Solution {
public:
    int longestBalanced(string s) {
        int n = s.size();
        int ans = 0;

        for (int l = 0; l < n; l++) {
            vector<int> freq(26, 0);

            for (int r = l; r < n; r++) {
                freq[s[r] - 'a']++;

                int target = 0;
                bool ok = true;

                for (int c = 0; c < 26; c++) {
                    if (freq[c] > 0) {
                        if (target == 0) {
                            target = freq[c];
                        } else if (freq[c] != target) {
                            ok = false;
                            break;
                        }
                    }
                }

                if (ok) {
                    ans = max(ans, r - l + 1);
                }
            }
        }

        return ans;
    }
};