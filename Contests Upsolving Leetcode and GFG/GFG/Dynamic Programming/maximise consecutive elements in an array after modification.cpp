#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    /*
    LIS supremacy!!!
    unordered_map<int,int> dp;

    dp[nums[i] + 1] = dp[nums[i]] + 1;

    dp[nums[i]] : maximum length of consecutive sequence ending at element nums[i];

    dp[nums[i]] = dp[nums[i] - 1] + 1;
     */
    int maxSelectedElements(vector<int> &nums)
    {
        unordered_map<int, int> dp;
        int ans = 0;
        sort(nums.begin(), nums.end());
        for (int &element : nums)
        {
            dp[element + 1] = dp[element] + 1;
            dp[element] = dp[element - 1] + 1;
            ans = max({ans, dp[element], dp[element + 1]});
        }
        return ans;
    }
};
int main()
{
    return 0;
}