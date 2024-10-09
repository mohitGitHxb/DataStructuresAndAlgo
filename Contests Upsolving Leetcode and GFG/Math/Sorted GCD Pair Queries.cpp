#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> gcdValues(vector<int> &nums, vector<long long> &queries)
    {
        // Determine the maximum value in nums to size the gdcmulip array
        int maxVal = *max_element(nums.begin(), nums.end()) + 1;
        vector<long long> gdcmulip(maxVal, 0); // To hold count of pairs with GCD i
        vector<long long> cummsum(maxVal, 0);  // Cumulative sums of pairs

        // Count occurrences of each number in nums
        for (int num : nums)
        {
            gdcmulip[num]++;
        }

        // Calculate pairs for each possible GCD
        for (int i = 1; i < maxVal; ++i)
        {
            long long count = 0;
            for (int j = i; j < maxVal; j += i)
            {
                count += gdcmulip[j]; // Sum counts of multiples of i
            }
            gdcmulip[i] = count * (count - 1) / 2; // Calculate pairs
        }

        // Adjust counts to ensure gdcmulip[i] holds pairs with GCD exactly i
        for (int i = maxVal - 1; i >= 1; --i)
        {
            for (int j = i + i; j < maxVal; j += i)
            {
                gdcmulip[i] -= gdcmulip[j]; // Remove multiples from count
            }
        }

        // Calculate cumulative sums of pairs
        for (int i = 1; i < maxVal; ++i)
        {
            cummsum[i] = cummsum[i - 1] + gdcmulip[i];
        }

        vector<int> results; // To store results for each query
        for (long long query : queries)
        {
            // Use binary search to find the smallest k satisfying the query
            int k = lower_bound(cummsum.begin() + 1, cummsum.end(), query + 1) - cummsum.begin();
            results.push_back(k);
        }
        return results; // Return the results for all queries
    }
};
