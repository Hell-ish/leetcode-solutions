class Solution {
public:
    long long maxSumTrionic(vector<int>& nums) {
        int n = nums.size();
        const long long NEG = -4e18;

        long long inc1 = NEG; // increasing part
        long long dec2 = NEG; // increasing then decreasing
        long long inc3 = NEG; // increasing then decreasing then increasing

        long long ans = NEG;

        for (int i = 1; i < n; i++) {
            long long newInc1 = NEG;
            long long newDec2 = NEG;
            long long newInc3 = NEG;

            if (nums[i - 1] < nums[i]) {
                // Start or extend first increasing segment
                newInc1 = max(
                    (long long)nums[i - 1] + nums[i],
                    inc1 + nums[i]
                );

                // Start or extend third increasing segment
                if (dec2 != NEG) {
                    newInc3 = max(newInc3, dec2 + nums[i]);
                }
                if (inc3 != NEG) {
                    newInc3 = max(newInc3, inc3 + nums[i]);
                }
            }

            if (nums[i - 1] > nums[i]) {
                // Start or extend decreasing segment
                if (inc1 != NEG) {
                    newDec2 = max(newDec2, inc1 + nums[i]);
                }
                if (dec2 != NEG) {
                    newDec2 = max(newDec2, dec2 + nums[i]);
                }
            }

            inc1 = newInc1;
            dec2 = newDec2;
            inc3 = newInc3;

            ans = max(ans, inc3);
        }

        return ans;
    }
};