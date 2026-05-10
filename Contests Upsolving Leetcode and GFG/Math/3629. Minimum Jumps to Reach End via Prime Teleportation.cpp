#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - Array of integers, start at index 0, reach index n-1
     * - Two types of moves:
     *   1. Adjacent step: move to i±1
     *   2. Prime teleportation: if nums[i] is prime p, jump to any j where nums[j] % p == 0
     * - Goal: Minimum jumps to reach end
     *
     * KEY INSIGHT - BFS with Prime-Based Graph Expansion:
     *
     * OBSERVATION 1: BFS for Shortest Path
     * - This is an unweighted graph shortest path problem
     * - Each index is a node, moves are edges
     * - BFS guarantees finding shortest path
     *
     * OBSERVATION 2: Prime Teleportation Creates Edges
     * - If nums[i] = prime p, can jump to all indices j where nums[j] % p == 0
     * - This includes multiples of p: p, 2p, 3p, etc.
     * - Creates many potential edges from one prime position
     *
     * OBSERVATION 3: Avoid Redundant Processing
     * - If we've already processed prime value p from some index
     * - No need to reprocess it from another index with same value
     * - Use "seen primes" set to prevent redundant edge exploration
     *
     * OBSERVATION 4: Precompute Primes
     * - Use Sieve of Eratosthenes to find all primes up to max(nums)
     * - O(n log log n) preprocessing enables O(1) prime checks
     *
     * APPROACH:
     * 1. Build value-to-indices mapping
     * 2. Precompute prime numbers using sieve
     * 3. BFS from index 0:
     *    - Try adjacent moves (i±1)
     *    - If nums[i] is prime and not yet processed:
     *      - Jump to all indices with multiples of nums[i]
     *      - Mark this prime as processed
     * 4. Return steps when reaching n-1
     *
     * EXAMPLE: nums = [1,2,4,6]
     *
     * Value mapping:
     * 1 → [0]
     * 2 → [1]
     * 4 → [2]
     * 6 → [3]
     *
     * Primes: {2}
     *
     * BFS:
     * Step 0: Queue = [0]
     *   From 0: can go to 1 (adjacent)
     *   nums[0]=1 (not prime)
     * Step 1: Queue = [1]
     *   From 1: can go to 0,2 (adjacent)
     *   nums[1]=2 (prime!): multiples are 2,4,6
     *     Jump to indices with values 2,4,6 → indices 1,2,3
     *     Index 3 reached! ✓
     *
     * Answer: 2 steps
     *
     * TIME: O(n + max_val log log max_val + n × max_val/min_prime)
     * SPACE: O(n + max_val)
     */

    vector<bool> isPrime;

    /**
     * Builds Sieve of Eratosthenes to identify prime numbers
     *
     * @param maxValue - maximum value to check for primality
     */
    void buildPrimeSieve(int maxValue)
    {
        isPrime.resize(maxValue + 1, true);

        isPrime[0] = false;
        isPrime[1] = false;

        for (int num = 2; num * num <= maxValue; num++)
        {
            if (isPrime[num])
            {
                // Mark all multiples as composite
                for (int multiple = num * num; multiple <= maxValue; multiple += num)
                {
                    isPrime[multiple] = false;
                }
            }
        }
    }

public:
    int minJumps(vector<int> &nums)
    {
        int n = nums.size();

        // Map: value → list of indices with that value
        unordered_map<int, vector<int>> valueToIndices;
        int maxValue = 0;

        for (int i = 0; i < n; i++)
        {
            valueToIndices[nums[i]].push_back(i);
            maxValue = max(maxValue, nums[i]);
        }

        // Precompute all primes up to maxValue
        buildPrimeSieve(maxValue);

        // BFS setup
        queue<int> bfsQueue;
        vector<bool> visited(n, false);

        bfsQueue.push(0);
        visited[0] = true;

        // Track which prime values have been processed
        // Prevents redundant teleportation exploration
        unordered_set<int> processedPrimes;

        int steps = 0;

        // BFS to find shortest path
        while (!bfsQueue.empty())
        {
            int levelSize = bfsQueue.size();

            // Process all nodes at current level
            for (int i = 0; i < levelSize; i++)
            {
                int currentIndex = bfsQueue.front();
                bfsQueue.pop();

                // Reached destination
                if (currentIndex == n - 1)
                {
                    return steps;
                }

                // Move 1: Adjacent step left
                if (currentIndex - 1 >= 0 && !visited[currentIndex - 1])
                {
                    bfsQueue.push(currentIndex - 1);
                    visited[currentIndex - 1] = true;
                }

                // Move 2: Adjacent step right
                if (currentIndex + 1 < n && !visited[currentIndex + 1])
                {
                    bfsQueue.push(currentIndex + 1);
                    visited[currentIndex + 1] = true;
                }

                int currentValue = nums[currentIndex];

                // Move 3: Prime teleportation
                // Skip if value is not prime or already processed
                if (!isPrime[currentValue] || processedPrimes.count(currentValue))
                {
                    continue;
                }

                // Jump to all indices with multiples of this prime
                for (int multiple = currentValue; multiple <= maxValue; multiple += currentValue)
                {
                    if (!valueToIndices.count(multiple))
                    {
                        continue;
                    }

                    // Jump to all indices with this multiple
                    for (int targetIndex : valueToIndices[multiple])
                    {
                        if (!visited[targetIndex])
                        {
                            bfsQueue.push(targetIndex);
                            visited[targetIndex] = true;
                        }
                    }
                }

                // Mark this prime as processed
                processedPrimes.insert(currentValue);
            }

            steps++;
        }

        // Should never reach here if input is valid
        return steps;
    }
};

/*
 * DETAILED WALKTHROUGH - Example 2: nums = [2,3,4,7,9]
 *
 * ===== Setup =====
 * valueToIndices:
 *   2 → [0]
 *   3 → [1]
 *   4 → [2]
 *   7 → [3]
 *   9 → [4]
 *
 * Primes (via sieve): {2, 3, 5, 7}
 * maxValue = 9
 *
 * ===== BFS Execution =====
 *
 * Step 0:
 * Queue: [0]
 *
 * Process index 0:
 *   Adjacent: 1
 *   nums[0] = 2 (prime!)
 *   Multiples of 2: 2, 4, 6, 8
 *   Indices with these values: [0, 2]
 *   Add index 2 to queue
 *   Mark prime 2 as processed
 *
 * Queue after step 0: [1, 2]
 * visited: [T, T, T, F, F]
 *
 * Step 1:
 * Queue: [1, 2]
 *
 * Process index 1:
 *   Adjacent: 0 (visited), 2 (visited)
 *   nums[1] = 3 (prime!)
 *   Multiples of 3: 3, 6, 9
 *   Indices: [1, 4]
 *   Add index 4 to queue ← DESTINATION!
 *   Mark prime 3 as processed
 *
 * Process index 2:
 *   Adjacent: 1 (visited), 3
 *   Add index 3
 *   nums[2] = 4 (not prime)
 *
 * Queue after step 1: [4, 3]
 *
 * Step 2:
 * Process index 4:
 *   currentIndex == n-1 → RETURN 2 ✓
 *
 * ===================================================================
 *
 * WHY THIS WORKS - Algorithm Correctness:
 *
 * 1. BFS SHORTEST PATH:
 *    - Level-by-level exploration guarantees shortest path
 *    - Each level represents one additional jump
 *    - First time we reach destination is optimal
 *
 * 2. PRIME TELEPORTATION OPTIMIZATION:
 *    - From prime p, can reach any index with value divisible by p
 *    - Instead of checking all indices, generate multiples
 *    - For each multiple, look up indices with that value
 *
 * 3. PROCESSED PRIMES SET:
 *    - If we've explored edges from prime p once
 *    - No need to re-explore from another index with value p
 *    - All reachable nodes are already in BFS queue or visited
 *    - Prevents O(n²) redundant work
 *
 * 4. SIEVE PREPROCESSING:
 *    - Upfront O(max_val log log max_val) cost
 *    - Enables O(1) prime checks during BFS
 *    - Trade-off: space for time
 *
 * 5. VALUE-TO-INDICES MAPPING:
 *    - O(1) lookup of all indices with a given value
 *    - Critical for efficient teleportation
 *    - Space: O(n) for storing indices
 *
 * COMPLEXITY ANALYSIS:
 * - Sieve: O(max_val log log max_val)
 * - Mapping: O(n)
 * - BFS: O(n + E) where E = edges from teleportation
 *   - Each index visited once: O(n)
 *   - Each prime processed once
 *   - Per prime: visit multiples ≤ max_val/prime
 *   - Total edges: O(max_val log log max_val) approximately
 * - Total: O(n + max_val log log max_val)
 * - Space: O(n + max_val)
 *
 * EDGE CASES:
 * - n=1: already at destination, return 0
 * - No primes: only adjacent steps possible
 * - All same prime: can teleport between all indices
 * - Large primes: fewer multiples, less teleportation
 */
int main()
{
    return 0;
}