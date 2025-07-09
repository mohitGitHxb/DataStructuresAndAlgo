#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> fullBloomFlowers(vector<vector<int>> &flowers, vector<int> &people)
    {
        // Step 1: Create difference array using map for coordinate compression
        // Map automatically keeps keys sorted, which is perfect for our needs
        map<int, int> diffArray;

        /*
         * DIFFERENCE ARRAY TECHNIQUE EXPLANATION:
         *
         * For each flower [start, end], we want to increment count from start to end (inclusive)
         * Instead of updating each position individually (which would be O(range) per flower),
         * we use difference array:
         * - Add +1 at start position (flower begins blooming)
         * - Add -1 at (end + 1) position (flower stops blooming after end)
         *
         * Example: flower [3, 7] means bloom from day 3 to 7
         * diffArray[3] += 1   (start blooming on day 3)
         * diffArray[8] -= 1   (stop blooming after day 7, so day 8)
         */

        for (auto &flower : flowers)
        {
            int start = flower[0];
            int end = flower[1];

            diffArray[start] += 1;   // Flower starts blooming
            diffArray[end + 1] -= 1; // Flower stops blooming (day after end)
        }

        // Step 2: Convert difference array to prefix sum array
        /*
         * PREFIX SUM CONVERSION:
         *
         * The difference array tells us the "change" at each point.
         * By computing prefix sum, we get the actual count at each point.
         *
         * Example with flowers [[1,6], [3,7]]:
         * After difference array: {1: +1, 3: +1, 7: -1, 8: -1}
         * After prefix sum: {1: 1, 3: 2, 7: 1, 8: 0}
         *
         * This means:
         * - From day 1-2: 1 flower blooming
         * - From day 3-6: 2 flowers blooming
         * - From day 7: 1 flower blooming
         * - From day 8+: 0 flowers blooming
         */

        int runningSum = 0;
        for (auto &entry : diffArray)
        {
            runningSum += entry.second; // Add the difference
            entry.second = runningSum;  // Store cumulative count
        }

        // Step 3: Answer queries using binary search
        /*
         * QUERY PROCESSING:
         *
         * For each person arriving at time t, we need to find how many flowers
         * are blooming at time t.
         *
         * Since our map is sorted by time, we use upper_bound(t) to find the
         * first entry with time > t, then move back one position to get the
         * count at time t.
         */

        vector<int> result;

        for (int arrivalTime : people)
        {
            // Find first time point > arrivalTime
            auto it = diffArray.upper_bound(arrivalTime);

            if (it == diffArray.begin())
            {
                // No flowers have started blooming before or at arrivalTime
                result.push_back(0);
            }
            else
            {
                // Move to the last time point <= arrivalTime
                it--;
                // The count at this time point is our answer
                result.push_back(it->second);
            }
        }

        return result;
    }
};

/*
 * COMPLEXITY ANALYSIS:
 *
 * Time Complexity: O(F log F + P log F)
 * - F = number of flowers, P = number of people
 * - Building difference array: O(F log F) due to map insertions
 * - Converting to prefix sum: O(F)
 * - Processing queries: O(P log F) due to binary search for each person
 *
 * Space Complexity: O(F)
 * - Map stores at most 2F entries (start and end+1 for each flower)
 *
 * WALKTHROUGH EXAMPLE:
 *
 * flowers = [[1,6],[3,7],[9,12],[4,13]], people = [2,3,7,11]
 *
 * Step 1 - Difference Array:
 * [1,6]: diffArray[1] += 1, diffArray[7] -= 1
 * [3,7]: diffArray[3] += 1, diffArray[8] -= 1
 * [9,12]: diffArray[9] += 1, diffArray[13] -= 1
 * [4,13]: diffArray[4] += 1, diffArray[14] -= 1
 *
 * Result: {1: 1, 3: 1, 4: 1, 7: -1, 8: -1, 9: 1, 13: -1, 14: -1}
 *
 * Step 2 - Prefix Sum:
 * {1: 1, 3: 2, 4: 3, 7: 2, 8: 1, 9: 2, 13: 1, 14: 0}
 *
 * Step 3 - Queries:
 * person at time 2: upper_bound(2) points to 3, go back to 1 → count = 1
 * person at time 3: upper_bound(3) points to 4, go back to 3 → count = 2
 * person at time 7: upper_bound(7) points to 8, go back to 7 → count = 2
 * person at time 11: upper_bound(11) points to 13, go back to 9 → count = 2
 *
 * Answer: [1, 2, 2, 2] ✓
 */