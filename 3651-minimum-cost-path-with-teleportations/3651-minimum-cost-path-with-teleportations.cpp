class Solution {
public:
    int minCost(vector<vector<int>>& grid, int k) {
        int m = grid.size(), n = grid[0].size();
        const long long INF = 1e18;
        const int MAXV = 10000;

        vector<vector<long long>> dp(m, vector<long long>(n, INF));

        dp[0][0] = 0;

        auto relaxNormalMoves = [&]() {
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (i > 0) {
                        dp[i][j] = min(dp[i][j], dp[i - 1][j] + grid[i][j]);
                    }
                    if (j > 0) {
                        dp[i][j] = min(dp[i][j], dp[i][j - 1] + grid[i][j]);
                    }
                }
            }
        };

        relaxNormalMoves();

        long long ans = dp[m - 1][n - 1];

        for (int used = 1; used <= k; used++) {
            vector<long long> best(MAXV + 2, INF);

            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    best[grid[i][j]] = min(best[grid[i][j]], dp[i][j]);
                }
            }

            for (int v = MAXV - 1; v >= 0; v--) {
                best[v] = min(best[v], best[v + 1]);
            }

            vector<vector<long long>> ndp = dp;

            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    ndp[i][j] = min(ndp[i][j], best[grid[i][j]]);
                }
            }

            dp = ndp;
            relaxNormalMoves();

            ans = min(ans, dp[m - 1][n - 1]);
        }

        return (int)ans;
    }
};