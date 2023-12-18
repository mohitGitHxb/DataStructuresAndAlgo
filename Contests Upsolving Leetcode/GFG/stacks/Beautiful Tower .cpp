#include <bits/stdc++.h>
using namespace std;

/*

**Intuition:**

To maximize the sum of heights in a beautiful configuration of towers, we need to distribute the available heights in such a way that we satisfy the conditions of a mountain array while keeping each tower's height within the given limits (`maxHeights`).

One key observation is that we should set the height of the tallest tower to the maximum allowed height (`maxHeights[i]`) to make the most of its height. Additionally, we should distribute the remaining heights to the left and right of this tallest tower to form a mountain-shaped configuration.

To do this efficiently, we can precompute two arrays: `prefix` and `suffix`. These arrays will store the maximum sum of heights achievable up to and after a specific tower, respectively. This will help us quickly compute the sum of heights for a given configuration.

Here's how the algorithm works:

1. Initialize two vectors `prefix` and `suffix` of the same size as `maxHeights` to store the maximum sum of heights achievable up to and after each tower, respectively.

2. Implement the `preCompute` function, which takes the input array `arr`, computes the `prefix` values, and stores them in the `prefix` vector:
   - Initialize an empty stack `s` to store pairs of values `(height, index)` where `height` is the tower height, and `index` is its index.
   - Initialize the first element of `prefix` as `arr[0]` and push `{arr[0], 0}` into the stack.
   - Iterate through the elements of `arr` starting from the second element.
   - While the stack is not empty and the current height `arr[i]` is less than the height at the top of the stack, pop elements from the stack. For each popped element, update the corresponding `prefix` value.
   - If the stack becomes empty, set `prefix[i]` as the product of `arr[i]` and `(i + 1)`. Otherwise, set `prefix[i]` as the sum of `prefix[s.top().second]` and `(i - s.top().second) * arr[i]`. Push `{arr[i], i}` into the stack.
   - After processing all elements, the `prefix` vector will contain the maximum sum of heights achievable up to each tower.

3. Reverse the `maxHeights` array and compute the `suffix` values using the `preCompute` function. Reverse the `suffix` array as well to match the original order.

4. Initialize a variable `res` to store the maximum possible sum of heights.

5. Iterate through the towers using an index `i`:
   - Compute the total sum of heights for the configuration where the tallest tower is at index `i` by adding `prefix[i]` and `suffix[i]` and subtracting `maxHeights[i]`.
   - Update `res` with the maximum of its current value and the computed sum.

6. After the loop, `res` will contain the maximum possible sum of heights for a beautiful configuration. Return `res`.

**Time Complexity:**

- The algorithm has a time complexity of O(n), where `n` is the number of towers.

**Space Complexity:**

- The space complexity is O(n) to store the `prefix` and `suffix` arrays.

**Hint:**

- To maximize the sum of heights, set the height of the tallest tower to the maximum allowed height (`maxHeights[i]`) and distribute the remaining heights to form a mountain configuration. Use `prefix` and `suffix` arrays to efficiently compute the sum of heights for different configurations.
 */

class Solution
{
public:
    void preCompute(vector<int> &arr, vector<long long> &prefix)
    {
        stack<pair<int, int>> s;
        prefix.front() = arr.front();
        s.push({arr.front(), 0});
        for (int i = 1; i < arr.size(); i++)
        {
            while (!s.empty() && arr[i] < s.top().first)
            {
                s.pop();
            }
            if (s.empty())
            {
                prefix.at(i) = arr.at(i);
                prefix.at(i) *= (1LL * (i + 1));
            }
            else
            {
                prefix.at(i) = prefix.at(s.top().second);
                prefix.at(i) += (1LL * (i - s.top().second) * arr.at(i));
            }
            s.push({arr[i], i});
        }
    }
    long long maximumSumOfHeights(vector<int> &maxHeights)
    {
        vector<long long> prefix(maxHeights.size()), suffix(maxHeights.size());
        preCompute(maxHeights, prefix);
        reverse(maxHeights.begin(), maxHeights.end());
        preCompute(maxHeights, suffix);
        reverse(suffix.begin(), suffix.end());
        reverse(maxHeights.begin(), maxHeights.end());

        long long res = 0;
        for (int i = 0; i < maxHeights.size(); i++)
        {
            long long val = maxHeights.at(i);
            val = (prefix[i] + suffix[i]) - val;
            res = max(res, val);
        }
        return res;
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