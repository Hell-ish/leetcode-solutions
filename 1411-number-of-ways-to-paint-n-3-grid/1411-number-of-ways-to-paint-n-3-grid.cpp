class Solution {
public:
    int numOfWays(int n) {
        const long long MOD = 1e9 + 7;

        long long aba = 6; // patterns like RYR
        long long abc = 6; // patterns like RYG

        for (int i = 2; i <= n; i++) {
            long long newAba = (aba * 3 + abc * 2) % MOD;
            long long newAbc = (aba * 2 + abc * 2) % MOD;

            aba = newAba;
            abc = newAbc;
        }

        return (aba + abc) % MOD;
    }
};