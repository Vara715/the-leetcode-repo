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
    void zigZag(TreeNode* root, int left, int len, int &maxLen) {
        if (!root) return;

        maxLen = max(maxLen, len);

        if (left == 1) {
            zigZag(root->left, 0, len+1, maxLen);
            zigZag(root->right, 1, 1, maxLen);
        } else {
            zigZag(root->right, 1, len+1, maxLen);
            zigZag(root->left, 0, 1, maxLen);
        }
    }
    int longestZigZag(TreeNode* root) {
        if (!root) return 0;
        int maxLen = 0;
        zigZag(root, 1, 0, maxLen);
        zigZag(root, 0, 0, maxLen);
        return maxLen;
    }
};