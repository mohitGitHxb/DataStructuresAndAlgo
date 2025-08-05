#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL_TESTING
#include "../container_printer.hpp"
#endif
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define ull unsigned long long
#define deb(x) cout << #x << "=" << x << endl
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};
static int init = []()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();
class Solution
{
private:
    /*
You have two fruit baskets containing n fruits each. You are given two 0-indexed integer arrays basket1 and basket2 representing the cost of fruit in each basket. You want to make both baskets equal. To do so, you can use the following operation as many times as you want:

    Choose two indices i and j, and swap the ith fruit of basket1 with the jth fruit of basket2.
    The cost of the swap is min(basket1[i], basket2[j]).

Two baskets are considered equal if sorting them according to the fruit cost makes them exactly the same baskets.

Return the minimum cost to make both the baskets equal or -1 if impossible.



Example 1:

Input: basket1 = [4,2,2,2], basket2 = [1,4,1,2]
Output: 1
Explanation: Swap index 1 of basket1 with index 0 of basket2, which has cost 1. Now basket1 = [4,1,2,2] and basket2 = [2,4,1,2]. Rearranging both the arrays makes them equal.

Example 2:

Input: basket1 = [2,3,4,1], basket2 = [3,2,5,1]
Output: -1
Explanation: It can be shown that it is impossible to make both the baskets equal.



     */
public:
    long long minCost(vector<int> &basket1, vector<int> &basket2)
    {
        const int n = basket1.size();                    // Size of the baskets
        unordered_map<int, int, custom_hash> difference; // Map to store the difference in counts of each fruit for basket1 += 1 , basket2 -= 1
        ll totalCost = 0;                                // Total cost of swaps
        int minimumElement = INT_MAX;                    // Minimum element in the baskets
        for (int i = 0; i < n; i++)
        {
            difference[basket1[i]]++;                                       // Increment count for basket1 fruit
            difference[basket2[i]]--;                                       // Decrement count for basket2 fruit
            minimumElement = min({minimumElement, basket1[i], basket2[i]}); // Update minimum element
        }
        for (auto it = difference.begin(); it != difference.end();)
        {
            if (it->second == 0)
            {
                it = difference.erase(it);
            }
            else
            {
                ++it;
            }
        } // Remove fruits that are balanced
        int minCost = INT_MAX;                      // Minimum cost of a swap
        vector<int> surplusBasket1, surplusBasket2; // Vectors to store surplus fruits in each basket
        for (const auto &[fruit, count] : difference)
        {
            const int absCount = abs(count);
            if (absCount & 1)
            {
                return -1; // If the count is odd, it's impossible to balance the baskets
            }
            const int halfCount = absCount / 2;
            vector<int> &surplus = count > 0 ? surplusBasket1 : surplusBasket2;
            for (int i = 0; i < halfCount; i++)
            {
                surplus.push_back(fruit); // Add surplus fruit to the corresponding basket
            }
        }
        if (surplusBasket1.size() != surplusBasket2.size())
        {
            return -1; // If the number of surplus fruits is not equal, it's impossible to balance
        }
        sort(surplusBasket1.begin(), surplusBasket1.end());                 // Sort surplus fruits in basket1
        sort(surplusBasket2.begin(), surplusBasket2.end(), greater<int>()); // Sort surplus fruits in basket2 in descending
        const int m = surplusBasket1.size();                                // Number of surplus fruits in each basket
        for (int i = 0; i < m; i++)
        {
            const ll minSwapCost = min<ll>(surplusBasket1[i], surplusBasket2[i]); // Calculate the minimum swap cost
            const ll swapCostThroughMinimumElement = 2 * minimumElement;          // Cost of swapping through the minimum element
            minCost = min(minSwapCost, swapCostThroughMinimumElement);            // Choose the minimum swap cost
            totalCost += minCost;                                                 // Add the minimum cost to the total cost
        }
        return totalCost; // Return the total cost of swaps to balance the baskets
    }
};

#ifdef LOCAL_TESTING
int main()
{
    Solution obj;
    // Test cases for local testing
    return 0;
}
#endif