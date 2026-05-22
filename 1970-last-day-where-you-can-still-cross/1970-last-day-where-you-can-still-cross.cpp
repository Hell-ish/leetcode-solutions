class Solution {
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells) {
        int n = row * col;
        vector<int> parent(n + 2), rank(n + 2, 0);

        int top = n;
        int bottom = n + 1;

        for (int i = 0; i < n + 2; i++) {
            parent[i] = i;
        }

        function<int(int)> find = [&](int x) {
            if (parent[x] != x)
                parent[x] = find(parent[x]);
            return parent[x];
        };

        auto unite = [&](int a, int b) {
            int pa = find(a), pb = find(b);
            if (pa == pb) return;

            if (rank[pa] < rank[pb]) {
                parent[pa] = pb;
            } else if (rank[pa] > rank[pb]) {
                parent[pb] = pa;
            } else {
                parent[pb] = pa;
                rank[pa]++;
            }
        };

        vector<vector<int>> grid(row, vector<int>(col, 0));

        int dirs[5] = {-1, 0, 1, 0, -1};

        // Go backwards: water becomes land
        for (int day = n - 1; day >= 0; day--) {
            int r = cells[day][0] - 1;
            int c = cells[day][1] - 1;

            grid[r][c] = 1;
            int id = r * col + c;

            if (r == 0) unite(id, top);
            if (r == row - 1) unite(id, bottom);

            for (int k = 0; k < 4; k++) {
                int nr = r + dirs[k];
                int nc = c + dirs[k + 1];

                if (nr >= 0 && nr < row && nc >= 0 && nc < col && grid[nr][nc] == 1) {
                    unite(id, nr * col + nc);
                }
            }

            if (find(top) == find(bottom)) {
                return day;
            }
        }

        return 0;
    }
};