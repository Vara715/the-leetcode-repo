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
    int helper(TreeNode* root, long long currSum, int targetSum, unordered_map<long long, int> &mp) {
        if (!root) return 0;

        currSum += (long long)root->val;
        int count = 0;

        //prevSum = currSum - targetSum
        //checking whether there exits a path before curr that if subtracted form curr gives target
        if (mp.count(currSum - targetSum)) {
            count += mp[currSum - targetSum];
        }

        mp[currSum]++;

        count += helper(root->left, currSum, targetSum, mp);
        count += helper(root->right, currSum, targetSum, mp);

        mp[currSum]--;

        return count;
    }
    int pathSum(TreeNode* root, int targetSum) {
        unordered_map<long long, int> mp;
        mp[0] = 1;   //0 sum can only occur once
        return helper(root, 0, targetSum, mp);
    }
};