class Solution {
public:
    long long minimumCost(
        string source,
        string target,
        vector<string>& original,
        vector<string>& changed,
        vector<int>& cost
    ) {
        const long long INF = 1e18;

        unordered_map<string, int> id;
        vector<string> words;

        auto getId = [&](string& s) {
            if (!id.count(s)) {
                id[s] = words.size();
                words.push_back(s);
            }
            return id[s];
        };

        for (auto& s : original) getId(s);
        for (auto& s : changed) getId(s);

        int W = words.size();
        vector<vector<long long>> dist(W, vector<long long>(W, INF));

        for (int i = 0; i < W; i++) dist[i][i] = 0;

        for (int i = 0; i < cost.size(); i++) {
            int u = id[original[i]];
            int v = id[changed[i]];
            dist[u][v] = min(dist[u][v], (long long)cost[i]);
        }

        // Floyd Warshall: minimum cost to convert one substring to another
        for (int k = 0; k < W; k++) {
            for (int i = 0; i < W; i++) {
                if (dist[i][k] == INF) continue;
                for (int j = 0; j < W; j++) {
                    if (dist[k][j] == INF) continue;
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }

        int n = source.size();
        vector<long long> dp(n + 1, INF);
        dp[0] = 0;

        unordered_set<int> lens;
        for (auto& s : original) lens.insert(s.size());
        for (auto& s : changed) lens.insert(s.size());

        for (int i = 0; i < n; i++) {
            if (dp[i] == INF) continue;

            // No operation needed for this character
            if (source[i] == target[i]) {
                dp[i + 1] = min(dp[i + 1], dp[i]);
            }

            // Try converting substrings starting at i
            for (int len : lens) {
                if (i + len > n) continue;

                string a = source.substr(i, len);
                string b = target.substr(i, len);

                if (!id.count(a) || !id.count(b)) continue;

                int u = id[a];
                int v = id[b];

                if (dist[u][v] == INF) continue;

                dp[i + len] = min(dp[i + len], dp[i] + dist[u][v]);
            }
        }

        return dp[n] == INF ? -1 : dp[n];
    }
};