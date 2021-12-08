#ifndef LC_SOLUTION_H
#define LC_SOLUTION_H

#include <bits/stdc++.h>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    bool isCovered(vector<vector<int>> &ranges, int left, int right) {
        sort(ranges.begin(), ranges.end());
        for (auto &range:ranges) {
            if (range[0] <= left && range[1] >= left) {
                left = range[1] + 1;
            }
        }
        return left > right;
    }

    int sumNumbers(TreeNode *root) {
        return sumNumbersHelp(root, 0);
    }

    int sumNumbersHelp(TreeNode *root, int sum) {
        if (root == nullptr) return 0;
        int res = sum * 10 + root->val;
        if (root->left == nullptr && root->right == nullptr) {
            return res;
        } else {
            return sumNumbersHelp(root->left, res) + sumNumbersHelp(root->right, res);
        }
    }

    void rotate(vector<vector<int>> &matrix) {
        int m = matrix.size(), n = matrix[0].size();
        for (int i = 0; i < m / 2; ++i) {
            for (int j = 0; j < n; ++j) {
                swap(matrix[i][j], matrix[m - 1 - i][j]);
            }
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < i; ++j) {
                swap(matrix[i][j], matrix[j][i]);
            }
        }
    }

    vector<vector<int>> subsets(vector<int> &nums) {
        vector<vector<int>> res;
        vector<int> path;
        subsetsHelp(res, path, nums, 0);
        return res;
    }

    void subsetsHelp(vector<vector<int>> &res, vector<int> &path, vector<int> &nums, int start) {
        res.emplace_back(path);
        for (int i = start; i < nums.size(); ++i) {
            path.emplace_back(nums[i]);
            subsetsHelp(res, path, nums, i + 1);
            path.pop_back();
        }
    }

    bool hasPathSum(TreeNode *root, int targetSum) {
        if (root == nullptr) return false;
        if (root->left == nullptr && root->right == nullptr) {
            return targetSum == root->val;
        }
        return hasPathSum(root->left, targetSum - root->val) || hasPathSum(root->right, targetSum - root->val);
    }

    vector<vector<int>> combinationSum(vector<int> &candidates, int target) {
        vector<vector<int>> res;
        vector<int> path;
        combinationSumHelp(res, path, candidates, target, 0);
        return res;
    }

    void combinationSumHelp(vector<vector<int>> &res, vector<int> &path, vector<int> &nums, int target, int i) {
        if (i == nums.size()) return;
        if (target == 0) {
            res.emplace_back(path);
            return;
        }
        combinationSumHelp(res, path, nums, target, i + 1);
        if (target - nums[i] >= 0) {
            path.emplace_back(nums[i]);
            combinationSumHelp(res, path, nums, target - nums[i], i);
            path.pop_back();
        }
    }

    int isValidBSTPre = INT_MIN;

    bool isValidBST(TreeNode *root) {
        if (root == nullptr) return true;
        if (!isValidBST(root->left)) {
            return false;
        }
        if (root->val <= isValidBSTPre) return false;
        isValidBSTPre = root->val;
        return isValidBST(root->right);
    }

    int singleNumber(vector<int> &nums) {
        int res = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            res ^= nums[i];
        }
        return res;
    }

    vector<int> exchange(vector<int> &nums) {
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            while (nums[l] % 2 == 1 && l < r) {
                l++;
            }
            while (nums[r] % 2 == 0 && r > l) {
                r--;
            }
            swap(nums[l], nums[r]);
        }
        return nums;
    }

    int minSubArrayLen(int target, vector<int> &nums) {
        int sum = 0;
        int res = INT_MAX;
        int l = 0, r = 0;
        while (r < nums.size()) {
            sum += nums[r];
            while (sum >= target) {
                res = min(res, r - l + 1);
                sum -= nums[l];
                l++;
            }
            r++;
        }
        return res == INT_MAX ? 0 : res;
    }

    double myPow(double x, int n) {
        if (x == 0.0) return 0.0;
        long b = n;
        double res = 1;
        if (b < 0) {
            x = 1 / x;
            b = -b;
        }
        while (b != 0) {
            if ((b & 1) == 1) res *= x;
            x *= x;
            b = b >> 1;
        }
        return res;
    }

    vector<vector<int>> permuteUnique(vector<int> &nums) {
        vector<vector<int>> res;
        vector<int> path;
        vector<bool> vis(nums.size());
        sort(nums.begin(), nums.end());
        permuteUniqueHelp(res, path, nums, vis);
        return res;
    }

    void permuteUniqueHelp(vector<vector<int>> &res, vector<int> &path, vector<int> &nums, vector<bool> &vis) {
        if (path.size() == nums.size()) {
            res.emplace_back(path);
            return;
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (i > 0 && nums[i] == nums[i - 1] && !vis[i - 1]) {
                continue;
            } else if (vis[i] == false) {
                vis[i] = true;
                path.emplace_back(nums[i]);
                permuteUniqueHelp(res, path, nums, vis);
                path.pop_back();
                vis[i] = false;
            }
        }
    }

    string removeDuplicates(string s) {
        stack<char> stk;
        for (auto c:s) {
            if (stk.empty()) stk.push(c);
            else if (stk.top() == c) {
                stk.pop();
                continue;
            } else {
                stk.push(c);
            }
        }
        string res = "";
        while (!stk.empty()) {
            res.push_back(stk.top());
            stk.pop();
        }
        reverse(res.begin(), res.end());
        return res;
    }

    int majorityElement(vector<int> &nums) {
        int cnt = 1, res = -1;
        for (int i:nums) {
            if (res == i) {
                cnt++;
            } else if (--cnt == 0) {
                res = i;
                cnt = 1;
            }
        }
        return res;
    }

    int findLength(vector<int> &nums1, vector<int> &nums2) {
        int m = nums1.size(), n = nums2.size();
        int res = 0;
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                dp[i][j] = nums1[i - 1] == nums2[j - 1] ? dp[i - 1][j - 1] + 1 : 0;
                res = max(res, dp[i][j]);
            }
        }
        return res;
    }

    vector<string> permutation(string s) {
        vector<string> res;
        string path = "";
        sort(s.begin(), s.end());
        vector<bool> vis(s.size());
        permutationHelp(res, path, s, vis);
        return res;
    }

    void permutationHelp(vector<string> &res, string &path, string &s, vector<bool> &vis) {
        if (path.size() == s.size()) {
            res.emplace_back(path);
            return;
        }
        for (int i = 0; i < s.size(); ++i) {
            if (i > 0 && s[i] == s[i - 1] && !vis[i - 1]) continue;
            if (vis[i]) continue;
            vis[i] = true;
            path += s[i];
            permutationHelp(res, path, s, vis);
            vis[i] = false;
            path.pop_back();
        }
    }
};

#endif //LC_SOLUTION_H
