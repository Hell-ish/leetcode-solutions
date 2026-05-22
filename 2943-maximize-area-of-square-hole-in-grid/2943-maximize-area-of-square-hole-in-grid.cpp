class Solution {
public:
    int maximizeSquareHoleArea(int n, int m, vector<int>& hBars, vector<int>& vBars) {
        sort(hBars.begin(), hBars.end());
        sort(vBars.begin(), vBars.end());

        int maxH = longestConsecutive(hBars);
        int maxV = longestConsecutive(vBars);

        int side = min(maxH, maxV) + 1;
        return side * side;
    }

    int longestConsecutive(vector<int>& bars) {
        int best = 1;
        int curr = 1;

        for (int i = 1; i < bars.size(); i++) {
            if (bars[i] == bars[i - 1] + 1) {
                curr++;
            } else {
                curr = 1;
            }

            best = max(best, curr);
        }

        return best;
    }
};