/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void solve(TreeNode* root, int target, int currSum, vector<vector<int>> &ans, vector<int> &curr) {
        
        if (!root) {
            return;
        }

        //wrong thinking
        // if ((target < 0 && currSum <= target) || (target >= 0 && currSum >= target)) return;

        curr.push_back(root->val);
        currSum += root->val;

        if (!root->left && !root->right) {
            if (currSum == target) {
                ans.push_back(curr);
            }
        }

        solve(root->left, target, currSum, ans, curr);

        solve(root->right, target, currSum, ans, curr);

        curr.pop_back();
        currSum-=root->val;
    }

    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        vector<int> curr;
        vector<vector<int>> ans;

        solve(root, targetSum, 0, ans, curr);

        return ans;
    }
};