class Solution {
public:
    vector<string> result;

    void backtrack(string current, int open, int close, int n) {
        // Base case
        if (current.length() == n * 2) {
            result.push_back(current);
            return;
        }

        // Add opening bracket
        if (open < n) {
            backtrack(current + "(", open + 1, close, n);
        }

        // Add closing bracket
        if (close < open) {
            backtrack(current + ")", open, close + 1, n);
        }
    }

    vector<string> generateParenthesis(int n) {
        backtrack("", 0, 0, n);
        return result;
    }
};