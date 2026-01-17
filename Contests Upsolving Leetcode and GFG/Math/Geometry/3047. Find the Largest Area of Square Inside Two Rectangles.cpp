#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - Given n rectangles with axis-aligned edges
     * - Each rectangle defined by bottom-left and top-right corners
     * - Find maximum area of a square that fits in intersection of at least 2 rectangles
     *
     * KEY INSIGHT - Rectangle Intersection Properties:
     *
     * For two rectangles to intersect:
     *   Rectangle 1: [x1_min, y1_min] to [x1_max, y1_max]
     *   Rectangle 2: [x2_min, y2_min] to [x2_max, y2_max]
     *
     * Intersection rectangle (if exists):
     *   left   = max(x1_min, x2_min)  ← rightmost left edge
     *   right  = min(x1_max, x2_max)  ← leftmost right edge
     *   bottom = max(y1_min, y2_min)  ← topmost bottom edge
     *   top    = min(y1_max, y2_max)  ← bottommost top edge
     *
     * Valid intersection exists if: right > left AND top > bottom
     *
     * Intersection dimensions:
     *   width  = right - left
     *   height = top - bottom
     *
     * Maximum square side = min(width, height)
     *
     * APPROACH:
     * 1. Try all pairs of rectangles (i, j) where i < j
     * 2. Compute their intersection rectangle
     * 3. If intersection exists, find largest square that fits
     * 4. Track maximum square area across all pairs
     *
     * EXAMPLE: bottomLeft = [[1,1],[2,2],[3,1]], topRight = [[3,3],[4,4],[6,6]]
     *
     * Visual representation:
     *
     *   y
     *   6 |           ┌─────────┐
     *   5 |           │    2    │
     *   4 |     ┌───┐ │         │
     *   3 |     │ 1 │ └─────────┘
     *   2 | ┌─┐ └───┘
     *   1 | │0│       ┌─────────┐
     *   0 | └─┘       │    2    │
     *     └─────────────────────── x
     *       1 2 3 4 5 6
     *
     * Rectangle 0: [1,1] to [3,3]
     * Rectangle 1: [2,2] to [4,4]
     * Rectangle 2: [3,1] to [6,6]
     *
     * Pair (0,1): Intersection [2,2] to [3,3] → 1×1 square → area = 1
     * Pair (0,2): No intersection (right=3 not > left=3)
     * Pair (1,2): Intersection [3,2] to [4,4] → 1×2 rectangle → 1×1 square → area = 1
     *
     * Maximum area = 1 ✓
     *
     * TIME: O(n²) - check all pairs of rectangles
     * SPACE: O(1) - only constant extra space
     */

    /**
     * Computes the intersection rectangle of two rectangles
     * Returns the dimensions if valid intersection exists
     *
     * @param rect1BottomLeft - bottom-left corner of rectangle 1
     * @param rect1TopRight - top-right corner of rectangle 1
     * @param rect2BottomLeft - bottom-left corner of rectangle 2
     * @param rect2TopRight - top-right corner of rectangle 2
     * @param width - output parameter for intersection width
     * @param height - output parameter for intersection height
     * @return true if valid intersection exists, false otherwise
     */
    bool computeIntersection(const vector<int> &rect1BottomLeft,
                             const vector<int> &rect1TopRight,
                             const vector<int> &rect2BottomLeft,
                             const vector<int> &rect2TopRight,
                             int &width,
                             int &height)
    {
        // Compute boundaries of intersection rectangle
        // For intersection to exist, we need the "overlap" region
        int intersectLeft = max(rect1BottomLeft[0], rect2BottomLeft[0]);
        int intersectRight = min(rect1TopRight[0], rect2TopRight[0]);
        int intersectBottom = max(rect1BottomLeft[1], rect2BottomLeft[1]);
        int intersectTop = min(rect1TopRight[1], rect2TopRight[1]);

        // Check if intersection is valid (has positive area)
        if (intersectRight > intersectLeft && intersectTop > intersectBottom)
        {
            width = intersectRight - intersectLeft;
            height = intersectTop - intersectBottom;
            return true;
        }

        return false; // No valid intersection
    }

    /**
     * Calculates the area of the largest square that fits in a rectangle
     *
     * @param width - width of the rectangle
     * @param height - height of the rectangle
     * @return area of the largest square (side²)
     */
    long long getLargestSquareArea(int width, int height)
    {
        // The largest square that fits has side length = min(width, height)
        long long side = min(static_cast<long long>(width),
                             static_cast<long long>(height));
        return side * side;
    }

public:
    long long largestSquareArea(vector<vector<int>> &bottomLeft,
                                vector<vector<int>> &topRight)
    {
        int numRectangles = bottomLeft.size();
        long long maxSquareArea = 0;

        // Try all pairs of rectangles
        for (int i = 0; i < numRectangles; i++)
        {
            for (int j = i + 1; j < numRectangles; j++)
            {
                int intersectionWidth, intersectionHeight;

                // Check if rectangles i and j intersect
                if (computeIntersection(bottomLeft[i], topRight[i],
                                        bottomLeft[j], topRight[j],
                                        intersectionWidth, intersectionHeight))
                {
                    // Compute area of largest square in this intersection
                    long long squareArea = getLargestSquareArea(intersectionWidth,
                                                                intersectionHeight);
                    maxSquareArea = max(maxSquareArea, squareArea);
                }
            }
        }

        return maxSquareArea;
    }
};

/*
 * DETAILED WALKTHROUGH - Example 1:
 * bottomLeft = [[1,1],[2,2],[3,1]], topRight = [[3,3],[4,4],[6,6]]
 *
 * ===== Rectangle Definitions =====
 * Rectangle 0: bottom-left=[1,1], top-right=[3,3]
 *   Visual: x ∈ [1,3], y ∈ [1,3]
 *
 * Rectangle 1: bottom-left=[2,2], top-right=[4,4]
 *   Visual: x ∈ [2,4], y ∈ [2,4]
 *
 * Rectangle 2: bottom-left=[3,1], top-right=[6,6]
 *   Visual: x ∈ [3,6], y ∈ [1,6]
 *
 * ===== Checking All Pairs =====
 *
 * --- Pair (0, 1): Rectangles 0 and 1 ---
 * Intersection calculation:
 *   left   = max(1, 2) = 2
 *   right  = min(3, 4) = 3
 *   bottom = max(1, 2) = 2
 *   top    = min(3, 4) = 3
 *
 * Validity check:
 *   right > left? 3 > 2 ✓
 *   top > bottom? 3 > 2 ✓
 *   Valid intersection! ✓
 *
 * Intersection dimensions:
 *   width  = 3 - 2 = 1
 *   height = 3 - 2 = 1
 *
 * Largest square:
 *   side = min(1, 1) = 1
 *   area = 1² = 1
 *
 * maxSquareArea = max(0, 1) = 1
 *
 * --- Pair (0, 2): Rectangles 0 and 2 ---
 * Intersection calculation:
 *   left   = max(1, 3) = 3
 *   right  = min(3, 6) = 3
 *   bottom = max(1, 1) = 1
 *   top    = min(3, 6) = 3
 *
 * Validity check:
 *   right > left? 3 > 3 ✗
 *   No valid intersection (rectangles touch but don't overlap)
 *
 * Skip this pair.
 *
 * --- Pair (1, 2): Rectangles 1 and 2 ---
 * Intersection calculation:
 *   left   = max(2, 3) = 3
 *   right  = min(4, 6) = 4
 *   bottom = max(2, 1) = 2
 *   top    = min(4, 6) = 4
 *
 * Validity check:
 *   right > left? 4 > 3 ✓
 *   top > bottom? 4 > 2 ✓
 *   Valid intersection! ✓
 *
 * Intersection dimensions:
 *   width  = 4 - 3 = 1
 *   height = 4 - 2 = 2
 *
 * Largest square:
 *   side = min(1, 2) = 1
 *   area = 1² = 1
 *
 * maxSquareArea = max(1, 1) = 1
 *
 * ===== Final Result =====
 * Maximum square area = 1 ✓
 *
 * ===================================================================
 *
 * EXAMPLE 2 WALKTHROUGH:
 * bottomLeft = [[1,1],[1,3],[1,5]], topRight = [[5,5],[5,7],[5,9]]
 *
 * All rectangles have same x-range [1,5] (width = 4)
 *
 * Rectangle 0: y ∈ [1,5], height = 4
 * Rectangle 1: y ∈ [3,7], height = 4
 * Rectangle 2: y ∈ [5,9], height = 4
 *
 * --- Pair (0, 1) ---
 * Intersection: x ∈ [1,5], y ∈ [3,5]
 *   width = 4, height = 2
 *   square side = min(4, 2) = 2
 *   area = 4
 *
 * --- Pair (0, 2) ---
 * Intersection: x ∈ [1,5], y ∈ [5,5]
 *   top = bottom = 5 → no valid intersection (touching at boundary)
 *
 * --- Pair (1, 2) ---
 * Intersection: x ∈ [1,5], y ∈ [5,7]
 *   width = 4, height = 2
 *   square side = min(4, 2) = 2
 *   area = 4
 *
 * Maximum area = 4 ✓
 *
 * ===================================================================
 *
 * WHY THIS WORKS - Algorithm Correctness:
 *
 * 1. INTERSECTION FORMULA:
 *    - Using max/min for boundaries ensures we capture the overlap region
 *    - left = max of left edges → rightmost starting point
 *    - right = min of right edges → leftmost ending point
 *    - Similar logic for vertical boundaries
 *
 * 2. VALIDITY CHECK:
 *    - right > left ensures positive width (strict inequality for area)
 *    - top > bottom ensures positive height
 *    - Both conditions needed for non-zero area
 *
 * 3. SQUARE CONSTRAINT:
 *    - A square must have equal width and height
 *    - In a width × height rectangle, largest square is min(width, height)
 *    - Cannot exceed the smaller dimension
 *
 * 4. EXHAUSTIVE SEARCH:
 *    - O(n²) checks all pairs → guaranteed to find maximum
 *    - Problem constraint: "at least two rectangles"
 *    - We check exactly pairs (not triples, etc.)
 *
 * 5. EDGE CASES:
 *    - No intersection: function returns false, skip pair
 *    - Rectangles touching but not overlapping: right=left or top=bottom
 *      → strict inequality check correctly rejects
 *    - Single rectangle: loop doesn't execute (i < j), returns 0
 *
 * COMPLEXITY ANALYSIS:
 * - Time: O(n²) where n = number of rectangles
 *   - Nested loops: n(n-1)/2 pairs
 *   - Each pair: O(1) computation
 * - Space: O(1) - only constant variables
 *
 * OPTIMIZATION OPPORTUNITIES:
 * - For very large n, could use spatial data structures (quad-tree, R-tree)
 * - Current approach is optimal for small to medium n
 * - Problem constraints likely keep n reasonable
 */

int main(int argc, char const *argv[])
{
    Solution obj;
    return 0;
}
