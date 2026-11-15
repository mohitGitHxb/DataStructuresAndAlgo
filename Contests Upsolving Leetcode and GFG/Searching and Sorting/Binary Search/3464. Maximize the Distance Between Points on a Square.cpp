#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - Square with corners at (0,0), (0,side), (side,0), (side,side)
     * - Points lie on the boundary of the square
     * - Select k points to maximize the minimum Manhattan distance between any pair
     * - On the boundary, Manhattan distance = distance along perimeter
     *
     * KEY INSIGHT - Flatten to 1D + Binary Search:
     *
     * OBSERVATION 1: Boundary as 1D Circle
     * - Points on square boundary can be mapped to positions on a circular path
     * - Perimeter = 4 × side
     * - Distance between points = min(clockwise, counter-clockwise) along perimeter
     *
     * OBSERVATION 2: Coordinate Flattening
     * - Map 2D boundary points to 1D positions [0, 4×side)
     * - Bottom edge (y=0): position = x
     * - Right edge (x=side): position = side + y
     * - Top edge (y=side): position = 3×side - x (going left)
     * - Left edge (x=0): position = 4×side - y (going down)
     *
     * OBSERVATION 3: Binary Search on Distance
     * - Answer is in range [0, 2×side] (max possible is half perimeter)
     * - For a given distance d, check if we can select k points with min distance ≥ d
     * - Binary search finds the maximum feasible d
     *
     * APPROACH:
     * 1. Flatten all points to 1D positions on perimeter
     * 2. Sort positions
     * 3. Duplicate array to handle circular wrapping
     * 4. Binary search on minimum distance
     * 5. For each candidate distance, greedily check feasibility
     *
     * EXAMPLE: side=2, points=[[0,0],[1,2],[2,0],[2,2],[2,1]], k=4
     *
     * Flattening:
     * - (0,0): bottom edge, x=0 → pos = 0
     * - (2,0): bottom edge, x=2 → pos = 2
     * - (2,1): right edge, y=1 → pos = 2+1 = 3
     * - (2,2): corner → pos = 4 (or 2+2)
     * - (1,2): top edge, x=1 → pos = 6-1 = 5
     *
     * Sorted: [0, 2, 3, 4, 5]
     * Perimeter = 8
     *
     * Binary search finds max distance where we can pick 4 points
     * Answer: 1 ✓
     *
     * TIME: O(n log n + n log(max_distance))
     * SPACE: O(n)
     */

    using ll = long long;

    /**
     * Flattens 2D boundary coordinate to 1D position along perimeter
     *
     * Perimeter traversal (counterclockwise starting from origin):
     * - Bottom edge (0,0) → (side,0): positions [0, side]
     * - Right edge (side,0) → (side,side): positions [side, 2×side]
     * - Top edge (side,side) → (0,side): positions [2×side, 3×side]
     * - Left edge (0,side) → (0,0): positions [3×side, 4×side]
     *
     * @param side - length of square edge
     * @param x - x-coordinate
     * @param y - y-coordinate
     * @return 1D position along perimeter [0, 4×side)
     */
    ll flattenCoordinate(int side, int x, int y)
    {
        // Bottom edge (y = 0): moving right
        if (y == 0)
        {
            return x;
        }
        // Right edge (x = side): moving up
        else if (x == side)
        {
            return side + y;
        }
        // Top edge (y = side): moving left
        else if (y == side)
        {
            return 3LL * side - x;
        }
        // Left edge (x = 0): moving down
        else
        {
            return 4LL * side - y;
        }
    }

    /**
     * Checks if we can select k points with minimum distance ≥ minDist
     * Uses greedy approach: pick points as far apart as possible
     *
     * @param positions - sorted 1D positions (duplicated for circular handling)
     * @param k - number of points to select
     * @param minDist - minimum distance to maintain
     * @param perimeter - total perimeter length
     * @return true if k points can be selected with min distance ≥ minDist
     */
    bool canSelectWithMinDistance(const vector<ll> &positions,
                                  int k,
                                  ll minDist,
                                  ll perimeter)
    {
        int n = positions.size() / 2; // Original array size

        // Try each position as starting point
        for (int startIdx = 0; startIdx < n; startIdx++)
        {
            int selectedCount = 1; // Start by selecting this point
            int currentIdx = startIdx;
            ll lastSelected = positions[startIdx];

            // Greedily select next points maintaining minDist
            while (selectedCount < k)
            {
                // Find next point at least minDist away
                auto nextIter = lower_bound(positions.begin() + currentIdx + 1,
                                            positions.begin() + n + startIdx,
                                            lastSelected + minDist);

                // No more points available in this direction
                if (nextIter == positions.begin() + n + startIdx)
                {
                    break;
                }

                lastSelected = *nextIter;
                currentIdx = nextIter - positions.begin();
                selectedCount++;
            }

            // Check if we selected k points AND the wrap-around distance is valid
            // Wrap-around distance: from last selected back to first selected
            ll wrapAroundDist = perimeter - (lastSelected - positions[startIdx]);

            if (selectedCount >= k && wrapAroundDist >= minDist)
            {
                return true;
            }
        }

        return false;
    }

public:
    int maxDistance(int side, vector<vector<int>> &points, int k)
    {
        vector<ll> flattenedPositions;
        ll perimeter = 4LL * side;

        // Flatten all 2D points to 1D positions
        for (const auto &point : points)
        {
            ll position = flattenCoordinate(side, point[0], point[1]);
            flattenedPositions.push_back(position);
        }

        // Sort positions
        sort(flattenedPositions.begin(), flattenedPositions.end());

        // Duplicate array to handle circular wrapping
        // positions[i] and positions[i + n] represent same physical point
        // but offset by full perimeter for easier circular distance calculation
        int n = flattenedPositions.size();
        for (int i = 0; i < n; i++)
        {
            flattenedPositions.push_back(perimeter + flattenedPositions[i]);
        }

        // Binary search on the minimum distance
        ll maxMinDistance = 0;
        ll left = 0;
        ll right = 2 * side; // Maximum possible is half the perimeter

        while (left <= right)
        {
            ll mid = (left + right) / 2;

            if (canSelectWithMinDistance(flattenedPositions, k, mid, perimeter))
            {
                // Can achieve this distance, try larger
                maxMinDistance = max(maxMinDistance, mid);
                left = mid + 1;
            }
            else
            {
                // Cannot achieve this distance, try smaller
                right = mid - 1;
            }
        }

        return maxMinDistance;
    }
};

/*
 * DETAILED WALKTHROUGH - Example 2:
 * side=2, points=[[0,0],[1,2],[2,0],[2,2],[2,1]], k=4
 *
 * ===== STEP 1: Flatten Coordinates =====
 *
 * Square perimeter = 8
 *
 * Visual representation:
 *   (0,2)---(1,2)---(2,2)
 *     |              |
 *   (0,1)          (2,1)
 *     |              |
 *   (0,0)----------(2,0)
 *
 * Flattening (counterclockwise from origin):
 * - (0,0): bottom edge, y=0 → pos = 0
 * - (2,0): bottom edge, y=0 → pos = 2
 * - (2,1): right edge, x=2 → pos = 2+1 = 3
 * - (2,2): right edge, x=2 → pos = 2+2 = 4
 * - (1,2): top edge, y=2 → pos = 6-1 = 5
 *
 * Sorted positions: [0, 2, 3, 4, 5]
 *
 * ===== STEP 2: Duplicate for Circular Handling =====
 *
 * Extended: [0, 2, 3, 4, 5, 8, 10, 11, 12, 13]
 *                         ↑ perimeter offset
 *
 * ===== STEP 3: Binary Search =====
 *
 * Range: [0, 4]
 *
 * --- Try mid=2 ---
 * Start at pos 0:
 *   Select pos 0
 *   Next ≥ 0+2 = 2: find pos 2
 *   Next ≥ 2+2 = 4: find pos 4
 *   Next ≥ 4+2 = 6: find pos 8 (which is 0+8)
 *   Selected: 4 points
 *   Wrap-around: 8 - (8-0) = 0 < 2 ✗
 *
 * Cannot achieve distance 2 with k=4
 *
 * --- Try mid=1 ---
 * Start at pos 0:
 *   Select pos 0
 *   Next ≥ 0+1 = 1: find pos 2
 *   Next ≥ 2+1 = 3: find pos 3
 *   Next ≥ 3+1 = 4: find pos 4
 *   Selected: 4 points
 *   Wrap-around: 8 - (4-0) = 4 ≥ 1 ✓
 *
 * Can achieve distance 1 ✓
 *
 * Answer: 1
 *
 * ===================================================================
 *
 * COORDINATE FLATTENING VISUALIZATION:
 *
 * For side=2:
 *
 *   6 ---5--- 4    Top edge: pos = 3×2 - x
 *   |         |
 *   7         3    Right edge: pos = 2 + y
 *   |         |    Left edge: pos = 8 - y
 *   0 ---1--- 2    Bottom edge: pos = x
 *
 * Perimeter positions:
 * 0: (0,0)
 * 1: (1,0)
 * 2: (2,0)
 * 3: (2,1)
 * 4: (2,2)
 * 5: (1,2)
 * 6: (0,2)
 * 7: (0,1)
 * 8: back to (0,0)
 *
 * ===================================================================
 *
 * WHY THIS WORKS - Algorithm Correctness:
 *
 * 1. FLATTENING CORRECTNESS:
 *    - Maps boundary to circular 1D path
 *    - Preserves distance relationships along boundary
 *    - Manhattan distance on boundary = perimeter distance
 *
 * 2. CIRCULAR HANDLING:
 *    - Duplicating array with perimeter offset
 *    - Allows treating circular array as linear for binary search
 *    - Distance from position i to i+perimeter = full circle
 *
 * 3. BINARY SEARCH VALIDITY:
 *    - Monotonicity: if distance d is feasible, d-1 is also feasible
 *    - Search space: [0, perimeter/2] (can't exceed half perimeter)
 *    - Converges to maximum feasible distance
 *
 * 4. GREEDY SELECTION:
 *    - For fixed minimum distance, greedy selection is optimal
 *    - Pick points as far apart as possible
 *    - Try all starting positions to handle circular nature
 *
 * 5. WRAP-AROUND CHECK:
 *    - Must verify distance from last selected back to first
 *    - Ensures circular constraint is satisfied
 *    - Distance = perimeter - (last - first)
 *
 * COMPLEXITY ANALYSIS:
 * - Flattening: O(n)
 * - Sorting: O(n log n)
 * - Duplication: O(n)
 * - Binary search iterations: O(log(2×side))
 * - Per iteration: O(n²) worst case (n starting points × n selections)
 * - Total: O(n log n + n² log(side))
 * - Space: O(n) for duplicated array
 *
 * EDGE CASES:
 * - k=1: always feasible, any distance works
 * - k=n: must use all points, distance = minimum gap
 * - All points clustered: small maximum distance
 * - Points evenly distributed: large maximum distance
 */
int main()
{
    return 0;
}