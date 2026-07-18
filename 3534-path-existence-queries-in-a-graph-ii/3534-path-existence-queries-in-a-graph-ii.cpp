class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {

        vector<pair<int,int>> arr;
        for (int i = 0; i < n; i++)
            arr.push_back({nums[i], i});

        sort(arr.begin(), arr.end());

        vector<int> pos(n);
        for (int i = 0; i < n; i++)
            pos[arr[i].second] = i;

        vector<int> next(n);

        int j = 0;
        for (int i = 0; i < n; i++) {
            while (j + 1 < n && arr[j + 1].first - arr[i].first <= maxDiff)
                j++;
            next[i] = j;
        }

        const int LOG = 20;
        vector<vector<int>> up(LOG, vector<int>(n));

        for (int i = 0; i < n; i++)
            up[0][i] = next[i];

        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++)
                up[k][i] = up[k - 1][up[k - 1][i]];
        }

        vector<int> ans;

        for (auto &q : queries) {

            int l = pos[q[0]];
            int r = pos[q[1]];

            if (l > r)
                swap(l, r);

            if (l == r) {
                ans.push_back(0);
                continue;
            }

            if (next[l] == l) {
                ans.push_back(-1);
                continue;
            }

            int cur = l;
            int steps = 0;

            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][cur] < r) {
                    cur = up[k][cur];
                    steps += (1 << k);
                }
            }

            if (next[cur] < r)
                ans.push_back(-1);
            else
                ans.push_back(steps + 1);
        }

        return ans;
    }
};