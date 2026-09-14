#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - Two binary (0/1) n×n matrices img1 and img2
     * - Translate img1 by any (rowOffset, colOffset) — no rotation
     * - Count positions where both images have '1' after translation
     * - Return the maximum overlap count over all possible translations
     *
     * KEY INSIGHT – Brute Force over All Translations:
     *
     * OBSERVATION 1: Translation Space
     * - Row offset ∈ [-(n-1), n-1]: (2n-1) choices
     * - Col offset ∈ [-(n-1), n-1]: (2n-1) choices
     * - Total translations: (2n-1)^2
     * - For each translation, count overlaps in O(n²) → O(n^4) total
     *
     * OBSERVATION 2: How Translation Works
     * - Shifting img1 right by colOff means img1[i][j] aligns with img2[i][j+colOff]
     * - Shifting img1 down by rowOff means img1[i][j] aligns with img2[i+rowOff][j+colOff]
     * - Cell (i,j) in img1 maps to cell (i+rowOff, j+colOff) in img2
     * - Skip if the mapped cell is out of bounds (those bits "fall off")
     *
     * EXAMPLE: img1 = [[1,1,0],[0,1,0],[0,1,0]], img2 = [[0,0,0],[0,1,1],[0,0,1]]
     *
     * Best translation: rowOff=1, colOff=1 (img1 shifted down 1, right 1)
     *
     * img1 shifted:              img2:
     *   0 0 0                    0 0 0
     *   1 1 0  ←───overlap───→   0 1 1
     *   0 1 0                    0 0 1
     *
     * Overlapping 1s at: (1,1), (2,2) ... let's verify all 3:
     *   img1[0][0]=1 → img2[1][1]=1 ✓
     *   img1[0][1]=1 → img2[1][2]=1 ✓
     *   img1[1][1]=1 → img2[2][2]=1 ✓
     *   → count = 3 ✓
     *
     * TIME:  O(n^4) – (2n-1)^2 translations × O(n^2) per overlap count
     * SPACE: O(1) – no extra arrays needed
     */

    /**
     * Counts overlapping 1-bits when img1 is shifted by (rowOffset, colOffset)
     * relative to img2.
     *
     * For each cell (i, j) in img1, it maps to (i + rowOffset, j + colOffset)
     * in img2. We count positions where both are 1.
     *
     * @param img1       first binary image
     * @param img2       second binary image (fixed, img1 slides over it)
     * @param rowOffset  vertical shift (positive = img1 moves down)
     * @param colOffset  horizontal shift (positive = img1 moves right)
     * @return number of cells where both images have a 1 after translation
     */
    int countOverlaps(const vector<vector<int>> &img1,
                      const vector<vector<int>> &img2,
                      int rowOffset, int colOffset)
    {
        int n = img1.size();
        int overlapCount = 0;

        for (int row = 0; row < n; row++)
        {
            for (int col = 0; col < n; col++)
            {
                // Map img1[row][col] to its position in img2 after translation
                int mappedRow = row + rowOffset;
                int mappedCol = col + colOffset;

                // Skip if translation moves this cell outside img2's bounds
                if (mappedRow < 0 || mappedRow >= n ||
                    mappedCol < 0 || mappedCol >= n)
                {
                    continue;
                }

                // Count overlap only when both cells are 1
                if (img1[row][col] == 1 && img2[mappedRow][mappedCol] == 1)
                {
                    overlapCount++;
                }
            }
        }

        return overlapCount;
    }

public:
    int largestOverlap(vector<vector<int>> &img1, vector<vector<int>> &img2)
    {
        int n = img1.size();
        int maxOverlap = 0;

        // Try every possible translation offset
        // rowOffset ∈ [-(n-1), n-1]: covers all vertical shifts
        // colOffset ∈ [-(n-1), n-1]: covers all horizontal shifts
        for (int rowOffset = -(n - 1); rowOffset < n; rowOffset++)
        {
            for (int colOffset = -(n - 1); colOffset < n; colOffset++)
            {
                int overlap = countOverlaps(img1, img2, rowOffset, colOffset);
                maxOverlap = max(maxOverlap, overlap);
            }
        }

        return maxOverlap;
    }
};

/*
 * DETAILED WALKTHROUGH – Example 1:
 * img1 = [[1,1,0],[0,1,0],[0,1,0]]
 * img2 = [[0,0,0],[0,1,1],[0,0,1]]
 * n = 3
 *
 * ===== Translation Space =====
 * rowOffset ∈ {-2, -1, 0, 1, 2}
 * colOffset ∈ {-2, -1, 0, 1, 2}
 * Total: 25 translations to try
 *
 * ===== Key Translations =====
 *
 * (rowOffset=0, colOffset=0): no shift, align directly
 *   img1[i][j] vs img2[i][j]:
 *   (0,0): 1 vs 0 — no
 *   (0,1): 1 vs 0 — no
 *   (1,1): 1 vs 1 ✓
 *   count = 1
 *
 * (rowOffset=1, colOffset=1): shift img1 down 1, right 1 ← OPTIMAL
 *   img1[i][j] maps to img2[i+1][j+1]
 *
 *   img1 cell → img2 mapped cell:
 *   (0,0)=1 → img2[1][1]=1 ✓
 *   (0,1)=1 → img2[1][2]=1 ✓
 *   (0,2)=0 → skip (0 in img1)
 *   (1,0)=0 → skip
 *   (1,1)=1 → img2[2][2]=1 ✓
 *   (1,2)=0 → skip
 *   (2,0)=0 → skip
 *   (2,1)=1 → img2[3][2] = out of bounds → skip
 *   (2,2)=0 → skip
 *   count = 3 ← maximum!
 *
 * ===== Visual Verification (rowOff=1, colOff=1) =====
 *
 * img1 (original):    img1 (shifted ↓1 →1):   img2:
 *   1 1 0               . . . . .               0 0 0
 *   0 1 0       →       . 1 1 0 .     over      0 1 1
 *   0 1 0               . 0 1 0 .               0 0 1
 *
 * (dots represent positions shifted outside bounds)
 *
 * Overlapping region (top-left of img2):
 *   Position (1,1): img1[0][0]=1, img2[1][1]=1 ✓
 *   Position (1,2): img1[0][1]=1, img2[1][2]=1 ✓
 *   Position (2,2): img1[1][1]=1, img2[2][2]=1 ✓
 *   Total overlap = 3 ✓
 *
 * ===================================================================
 *
 * WHY THIS WORKS:
 *
 * 1. COMPLETE TRANSLATION COVERAGE:
 *    - rowOffset ∈ [-(n-1), n-1] covers every possible vertical alignment
 *    - At rowOffset = -(n-1), img1's bottom row aligns with img2's top row
 *    - At rowOffset = n-1, img1's top row aligns with img2's bottom row
 *    - All intermediate alignments are covered
 *
 * 2. OUT-OF-BOUNDS HANDLING:
 *    - Cells translated outside [0, n) are simply skipped
 *    - This correctly models "1 bits that are translated outside are erased"
 *    - No special casing needed; the bounds check handles it uniformly
 *
 * 3. OVERLAP COUNTING:
 *    - Only (1, 1) pairs contribute
 *    - img1[row][col] == 0 contributes 0 regardless of img2 → safe to skip
 *    - img2[mappedRow][mappedCol] == 0 similarly contributes 0
 *
 * COMPLEXITY ANALYSIS:
 * - Translations: (2n-1)^2 ≈ 4n^2
 * - Per translation: O(n^2)
 * - Total: O(n^4)
 * - For n=30: ~810,000 operations — well within limits
 * - Space: O(1) extra
 *
 * EDGE CASES:
 * - All zeros in one image: overlap always 0
 * - Single cell (n=1): only one translation (0,0), return img1[0][0]&img2[0][0]
 * - Images identical: best overlap = count of 1s in the image
 *
 * OPTIMIZATION OPPORTUNITY (not needed for n ≤ 30):
 * - Precompute list of (row, col) positions where img1[row][col] == 1
 * - Only iterate over those, skipping 0-cells early
 * - Reduces inner loop from n^2 to |ones in img1| per translation
 */
int main()
{
    return 0;
}