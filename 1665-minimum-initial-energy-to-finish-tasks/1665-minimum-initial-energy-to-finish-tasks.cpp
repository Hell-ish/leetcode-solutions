class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        sort(tasks.begin(), tasks.end(), [](auto &a, auto &b) {
            return (a[1] - a[0]) > (b[1] - b[0]);
        });

        int ans = 0;
        int energy = 0;

        for (auto &task : tasks) {
            int actual = task[0];
            int minimum = task[1];

            if (energy < minimum) {
                ans += minimum - energy;
                energy = minimum;
            }

            energy -= actual;
        }

        return ans;
    }
};