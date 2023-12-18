#include <bits/stdc++.h>
using namespace std;
/*
You are at a fruit market with different types of exotic fruits on display.

You are given a 1-indexed array prices, where prices[i] denotes the number of coins needed to purchase the ith fruit.

The fruit market has the following offer:

    If you purchase the ith fruit at prices[i] coins, you can get the next i fruits for free.

Note that even if you can take fruit j for free, you can still purchase it for prices[j] coins to receive a new offer.

Return the minimum number of coins needed to acquire all the fruits.



Example 1:

Input: prices = [3,1,2]
Output: 4
Explanation: You can acquire the fruits as follows:
- Purchase the 1st fruit with 3 coins, you are allowed to take the 2nd fruit for free.
- Purchase the 2nd fruit with 1 coin, you are allowed to take the 3rd fruit for free.
- Take the 3rd fruit for free.
Note that even though you were allowed to take the 2nd fruit for free, you purchased it because it is more optimal.
It can be proven that 4 is the minimum number of coins needed to acquire all the fruits.

Example 2:

Input: prices = [1,10,1,1]
Output: 2
Explanation: You can acquire the fruits as follows:
- Purchase the 1st fruit with 1 coin, you are allowed to take the 2nd fruit for free.
- Take the 2nd fruit for free.
- Purchase the 3rd fruit for 1 coin, you are allowed to take the 4th fruit for free.
- Take the 4th fruit for free.
It can be proven that 2 is the minimum number of coins needed to acquire all the fruits.


 */

/*
Intuition:

The problem involves finding the minimum number of coins needed to acquire all fruits, considering the offer that allows you to get the next i fruits for free if you purchase the i-th fruit. The key is to iterate through the fruits and make optimal choices to minimize the total cost.
Hints:

    Start iterating from the end to the beginning, considering the offer that allows getting the next i fruits for free.
    Keep track of the minimum cost needed to acquire the remaining fruits starting from the current fruit.
    Utilize dynamic programming to avoid redundant calculations.

Algorithm:

    Initialize a dynamic programming array dp of size prices.size() and set all values to a large number (representing infinity).
    Iterate through the fruits from the end to the beginning (from i = prices.size() - 1 to 0).
        Calculate the maximum index j such that you can get the next i fruits for free (i.e., j = i + i + 1).
        If j is greater than or equal to the last index of the array, set dp[i] to the cost of purchasing the i-th fruit only.
        Otherwise, for each index k from i + 1 to the minimum of (prices.size() - 1) and (i + countFree), update dp[i] by considering the cost of purchasing the i-th fruit plus the cost stored in dp[j].
    Return the value stored in dp[0], which represents the minimum cost needed to acquire all fruits.

Time Complexity:

The time complexity is O(n^2), where n is the size of the prices array. The nested loop iterates through each fruit, and for each fruit, it considers the costs of purchasing subsequent fruits.
Space Complexity:

The space complexity is O(n) for the dynamic programming array.
 */
class Solution
{
public:
    int minimumCoins(vector<int> &prices)
    {
        vector<int> dp(prices.size(), 1e9);
        for (int i = prices.size() - 1; i >= 0; i--)
        {
            int countFree = (i + 1) + 1;
            if (i + countFree >= prices.size())
            {
                dp[i] = prices[i];
            }
            for (int j = i + 1; j <= min((int)(prices.size() - 1), i + countFree); j++)
            {
                dp[i] = min(dp[i], prices[i] + dp[j]);
            }
        }
        return dp[0];
    }
};

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--)
    {
        // write code here
    }
    return 0;
}