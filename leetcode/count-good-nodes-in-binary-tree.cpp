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
    void checkGoods(TreeNode* root, int lastMax, int &count) {
        if (!root) return;

        if (root->val >= lastMax) {
            lastMax = root->val;
            count++;
        }

        checkGoods(root->left, lastMax, count);
        checkGoods(root->right, lastMax, count);
    }
    int goodNodes(TreeNode* root) {
        if (!root) return 0;
        int count = 0;
        checkGoods(root, root->val, count);

        return count;
    }
};