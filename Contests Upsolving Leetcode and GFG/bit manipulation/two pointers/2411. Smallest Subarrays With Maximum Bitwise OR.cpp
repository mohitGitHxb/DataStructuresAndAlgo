#include <vector>
#include <algorithm>

/*

You are given a 0-indexed array nums of length n, consisting of non-negative integers. For each index i from 0 to n - 1, you must determine the size of the minimum sized non-empty subarray of nums starting at i (inclusive) that has the maximum possible bitwise OR.

    In other words, let Bij be the bitwise OR of the subarray nums[i...j]. You need to find the smallest subarray starting at i, such that bitwise OR of this subarray is equal to max(Bik) where i <= k <= n - 1.

The bitwise OR of an array is the bitwise OR of all the numbers in it.

Return an integer array answer of size n where answer[i] is the length of the minimum sized subarray starting at i with maximum bitwise OR.

A subarray is a contiguous non-empty sequence of elements within an array.



Example 1:

Input: nums = [1,0,2,1,3]
Output: [3,3,2,2,1]
Explanation:
The maximum possible bitwise OR starting at any index is 3.
- Starting at index 0, the shortest subarray that yields it is [1,0,2].
- Starting at index 1, the shortest subarray that yields the maximum bitwise OR is [0,2,1].
- Starting at index 2, the shortest subarray that yields the maximum bitwise OR is [2,1].
- Starting at index 3, the shortest subarray that yields the maximum bitwise OR is [1,3].
- Starting at index 4, the shortest subarray that yields the maximum bitwise OR is [3].
Therefore, we return [3,3,2,2,1].

Example 2:

Input: nums = [1,2]
Output: [2,1]
Explanation:
Starting at index 0, the shortest subarray that yields the maximum bitwise OR is of length 2.
Starting at index 1, the shortest subarray that yields the maximum bitwise OR is of length 1.
Therefore, we return [2,1].


*/
class Solution
{
public:
    /**
     * @brief Finds the length of the smallest subarray starting at each index
     * with the maximum possible bitwise OR.
     * @param nums A 0-indexed array of non-negative integers.
     * @return An integer array where answer[i] is the length of the described subarray.
     */
    std::vector<int> smallestSubarrays(std::vector<int> &nums)
    {
        int n = nums.size();
        std::vector<int> answer(n);

        // last_occurrence[b] stores the index of the last time we saw bit 'b' set.
        // We iterate from right to left, so this is the "closest" occurrence to the right.
        std::vector<int> last_occurrence(32, -1);

        // Iterate from the end of the array to the beginning.
        for (int i = n - 1; i >= 0; --i)
        {

            // 1. Update the last known occurrence for each bit set in the current number.
            for (int bit = 0; bit < 32; ++bit)
            {
                if ((nums[i] >> bit) & 1)
                {
                    last_occurrence[bit] = i;
                }
            }

            // 2. Find the farthest index we need to go to cover all necessary bits.
            // The maximum possible OR from index `i` is formed by the bits in `nums[i]`
            // combined with all bits available in `nums[i+1...n-1]`.
            // The `last_occurrence` array currently holds the closest indices for all bits
            // to the right of `i`, plus the bits we just updated for `nums[i]`.
            // The end of our subarray is the maximum of these indices.
            int farthest_idx = i;
            for (int bit = 0; bit < 32; ++bit)
            {
                if (last_occurrence[bit] != -1)
                {
                    farthest_idx = std::max(farthest_idx, last_occurrence[bit]);
                }
            }

            // 3. The length of the subarray is the distance from `i` to this farthest index.
            answer[i] = farthest_idx - i + 1;
        }

        return answer;
    }
};