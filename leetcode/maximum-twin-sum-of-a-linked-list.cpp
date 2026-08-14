/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    int pairSum(ListNode* head) {
        // int i = 0;
        // int n = 0;
        // ListNode* curr = head;

        // while (curr) {
        //     curr = curr->next;
        //     n++;
        // }

        // int twinSum = INT_MIN;
        // curr = head;
        // ListNode* target = nullptr;

        // while (i <= (n/2)-1) {
        //     int tarIdx = i;
        //     target = curr;

        //     while (tarIdx < n-i-1) {
        //         target = target->next;
        //         tarIdx++;
        //     }

        //     twinSum = max(twinSum, target->val + curr->val);
        //     i++;
        //     curr = curr->next;
        // }


        // return twinSum;

        vector<int> nums;
        ListNode* curr = head;

        while (curr) {
            nums.push_back(curr->val);
            curr = curr->next;
        }

        int n = nums.size();
        int twinSum = INT_MIN;

        for (int i=0; i<=(n/2)-1; i++) {
            twinSum = max(twinSum, nums[i]+nums[n-i-1]);
        }

        return twinSum;
    }
};