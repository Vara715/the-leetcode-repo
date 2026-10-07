class Solution {
public:
    vector<int> maxDepthAfterSplit(string seq) {
        int n = seq.size();
        vector<int> indices(n);

        int a_open = 0;
        int b_open = 0;

        for (int i=0; i<n; i++) {

            if (seq[i] == '(') {
                if (a_open == b_open) {
                    indices[i] = 0;
                    a_open++;
                } else if (a_open > b_open) {
                    indices[i] = 1;
                    b_open++;
                }
            } else {
                if (a_open > b_open) {
                    indices[i] = 0;
                    a_open--;
                } else {
                    indices[i] = 1;
                    b_open--;
                }
            }
        }

        return indices;
    }
};