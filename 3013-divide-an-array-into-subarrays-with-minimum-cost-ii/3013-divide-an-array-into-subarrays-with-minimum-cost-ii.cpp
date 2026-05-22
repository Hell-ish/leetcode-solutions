class Solution {
public:
    long long minimumCost(vector<int>& nums, int k, int dist) {
        int n = nums.size();

        int need = k - 1;          // choose starts of subarray 2..k
        int window = dist + 1;     // possible start indices window size

        multiset<long long> small, large;
        long long sumSmall = 0;

        auto rebalance = [&]() {
            while (small.size() > need) {
                auto it = prev(small.end());
                sumSmall -= *it;
                large.insert(*it);
                small.erase(it);
            }

            while (small.size() < need && !large.empty()) {
                auto it = large.begin();
                sumSmall += *it;
                small.insert(*it);
                large.erase(it);
            }

            while (!small.empty() && !large.empty() && *prev(small.end()) > *large.begin()) {
                auto itSmall = prev(small.end());
                auto itLarge = large.begin();

                long long a = *itSmall;
                long long b = *itLarge;

                sumSmall += b - a;

                small.erase(itSmall);
                large.erase(itLarge);

                small.insert(b);
                large.insert(a);
            }
        };

        auto add = [&](long long x) {
            if (small.empty() || x <= *prev(small.end())) {
                small.insert(x);
                sumSmall += x;
            } else {
                large.insert(x);
            }
            rebalance();
        };

        auto remove = [&](long long x) {
            auto it = small.find(x);
            if (it != small.end()) {
                sumSmall -= x;
                small.erase(it);
            } else {
                it = large.find(x);
                if (it != large.end()) {
                    large.erase(it);
                }
            }
            rebalance();
        };

        for (int i = 1; i <= dist + 1; i++) {
            add(nums[i]);
        }

        long long ans = nums[0] + sumSmall;

        for (int left = 2; left + dist < n; left++) {
            remove(nums[left - 1]);
            add(nums[left + dist]);

            ans = min(ans, nums[0] + sumSmall);
        }

        return ans;
    }
};