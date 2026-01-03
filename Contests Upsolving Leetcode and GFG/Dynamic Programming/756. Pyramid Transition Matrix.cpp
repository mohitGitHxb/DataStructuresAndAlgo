#include <bits/stdc++.h>
using namespace std;

class Solution
{
private:
    /*
     * PROBLEM UNDERSTANDING:
     * - Building a pyramid from bottom to top, each row has one less block
     * - Each pair of adjacent blocks determines possible blocks above them
     * - Given: bottom row and allowed patterns [left, right, top]
     * - Goal: Can we build all the way to a single top block?
     *
     * KEY INSIGHT - Recursive Row Building with Backtracking:
     *
     * APPROACH:
     * 1. For each row, process pairs of adjacent blocks left-to-right
     * 2. For each pair, try all allowed top blocks
     * 3. When we finish a row, recursively build the next row above
     * 4. Base case: row has only 1 block → pyramid complete!
     *
     * MEMOIZATION:
     * - Same bottom row configuration will always produce same result
     * - Cache results at the START of processing each row
     * - Key: the current row string (represents entire state)
     *
     * EXAMPLE: bottom = "BCD", allowed = ["BCC","CDE","CEA","FFF"]
     *
     * Preprocessing: Build lookup map
     *   "BC" → ["C"]
     *   "CD" → ["E"]
     *   "CE" → ["A"]
     *   "FF" → ["F"]
     *
     * Execution:
     * Level 1 (bottom): "BCD"
     *   Pair "BC" → can place "C"
     *   Pair "CD" → can place "E"
     *   Next row: "CE"
     *
     * Level 2: "CE"
     *   Pair "CE" → can place "A"
     *   Next row: "A"
     *
     * Level 3: "A"
     *   Length = 1 → SUCCESS! ✓
     *
     * TIME: O(n * m^n) worst case, but memoization helps significantly
     *       n = bottom.length(), m = max allowed patterns per pair
     * SPACE: O(n^2) for memoization map
     */

    // Memoization: maps row string to whether pyramid can be built from it
    unordered_map<string, bool> memo;

    /**
     * Recursively builds pyramid from current row upward
     *
     * @param position - current position in the row being processed (0-indexed)
     * @param currentRow - the row we're currently building from
     * @param patternMap - map from "XY" pair to list of possible top blocks
     * @param nextRow - the row being built above currentRow (accumulated)
     * @return true if pyramid can be completed from this state
     */
    bool canBuildPyramid(int position,
                         const string &currentRow,
                         const unordered_map<string, vector<string>> &patternMap,
                         const string &nextRow)
    {
        // Base case: Single block remaining → pyramid complete!
        if (currentRow.length() <= 1)
        {
            return true;
        }

        // Memoization: Check if we've seen this row configuration before
        // Only check at start of processing a row (position == 0)
        if (position == 0 && memo.count(currentRow))
        {
            return memo[currentRow];
        }

        // Finished building the next row → recursively build from it
        if (position == currentRow.length() - 1)
        {
            bool canComplete = canBuildPyramid(0, nextRow, patternMap, "");
            memo[currentRow] = canComplete; // Cache result for this row
            return canComplete;
        }

        // Get the current pair of adjacent blocks
        string blockPair = currentRow.substr(position, 2);

        // Check if this pair has any allowed patterns
        if (patternMap.find(blockPair) == patternMap.end())
        {
            return false; // No valid block can be placed above this pair
        }

        // Try each possible block that can go above this pair
        for (const string &topBlock : patternMap.at(blockPair))
        {
            // Recursively try building rest of row with this choice
            if (canBuildPyramid(position + 1, currentRow, patternMap, nextRow + topBlock))
            {
                return true; // Found a valid path!
            }
            // Implicit backtracking: try next option if this didn't work
        }

        return false; // None of the options worked
    }

    /**
     * Preprocesses allowed patterns into efficient lookup structure
     *
     * @param allowed - list of 3-char patterns "XYZ" (X+Y → Z)
     * @return map from "XY" to vector of possible top blocks
     */
    unordered_map<string, vector<string>> buildPatternMap(
        const vector<string> &allowed)
    {

        unordered_map<string, vector<string>> patternMap;

        for (const string &pattern : allowed)
        {
            // pattern = "XYZ" means blocks X and Y support block Z
            string basePair = pattern.substr(0, 2); // "XY"
            string topBlock = pattern.substr(2, 1); // "Z"

            patternMap[basePair].push_back(topBlock);
        }

        return patternMap;
    }

public:
    bool pyramidTransition(string bottom, vector<string> &allowed)
    {
        // Preprocess: Build lookup map for O(1) pattern queries
        unordered_map<string, vector<string>> patternMap = buildPatternMap(allowed);

        // Start building pyramid from the bottom row
        return canBuildPyramid(0, bottom, patternMap, "");
    }
};

/*
 * DETAILED WALKTHROUGH - Example 1: bottom = "BCD", allowed = ["BCC","CDE","CEA","FFF"]
 *
 * ===== STEP 1: Build Pattern Map =====
 * "BCC" → "BC" can support "C"
 * "CDE" → "CD" can support "E"
 * "CEA" → "CE" can support "A"
 * "FFF" → "FF" can support "F"
 *
 * patternMap = {
 *   "BC" → ["C"],
 *   "CD" → ["E"],
 *   "CE" → ["A"],
 *   "FF" → ["F"]
 * }
 *
 * ===== STEP 2: Build Pyramid =====
 *
 * Visual representation:
 *       A          ← Level 3 (top)
 *      / \
 *     C   E        ← Level 2
 *    / \ / \
 *   B   C   D      ← Level 1 (bottom)
 *
 * --- Processing Level 1: "BCD" ---
 * Call: canBuildPyramid(0, "BCD", patternMap, "")
 *
 * Position 0: Process pair "BC"
 *   patternMap["BC"] = ["C"]
 *   Try topBlock = "C"
 *   Call: canBuildPyramid(1, "BCD", patternMap, "C")
 *
 * Position 1: Process pair "CD"
 *   patternMap["CD"] = ["E"]
 *   Try topBlock = "E"
 *   Call: canBuildPyramid(2, "BCD", patternMap, "CE")
 *
 * Position 2: Reached end of row (position = length - 1)
 *   nextRow = "CE" is complete
 *   Move to next level
 *   Call: canBuildPyramid(0, "CE", patternMap, "")
 *
 * --- Processing Level 2: "CE" ---
 * Call: canBuildPyramid(0, "CE", patternMap, "")
 *
 * Position 0: Process pair "CE"
 *   patternMap["CE"] = ["A"]
 *   Try topBlock = "A"
 *   Call: canBuildPyramid(1, "CE", patternMap, "A")
 *
 * Position 1: Reached end of row
 *   nextRow = "A" is complete
 *   Move to next level
 *   Call: canBuildPyramid(0, "A", patternMap, "")
 *
 * --- Processing Level 3: "A" ---
 * Call: canBuildPyramid(0, "A", patternMap, "")
 *
 * Base case: currentRow.length() = 1 ≤ 1
 * Return: TRUE ✓
 *
 * Result: Pyramid can be built!
 *
 * ===================================================================
 *
 * DETAILED WALKTHROUGH - Example 2: bottom = "AAAA"
 * allowed = ["AAB","AAC","BCD","BBE","DEF"]
 *
 * Pattern Map:
 *   "AA" → ["B", "C"]
 *   "BC" → ["D"]
 *   "BB" → ["E"]
 *   "DE" → ["F"]
 *
 * --- Processing Level 1: "AAAA" ---
 *
 * Position 0: pair "AA" → try "B", continue
 * Position 1: pair "AA" → try "B", continue
 * Position 2: pair "AA" → try "B", continue
 * Next row attempt: "BBB"
 *
 * --- Processing Level 2: "BBB" ---
 * Position 0: pair "BB" → try "E"
 * Position 1: pair "BB" → try "E"
 * Next row attempt: "EE"
 *
 * --- Processing Level 3: "EE" ---
 * Position 0: pair "EE"
 * patternMap["EE"] = NOT FOUND ✗
 * Return: FALSE
 *
 * Backtrack: Try "AA" → "C" instead...
 * (Similar process, but all paths fail)
 *
 * Result: Cannot build pyramid
 *
 * ===================================================================
 *
 * WHY THIS WORKS - Algorithm Design:
 *
 * 1. RECURSIVE STRUCTURE:
 *    - Each row depends only on the row below it
 *    - Natural recursive decomposition: build row N-1 from row N
 *    - Base case when we reach single block at top
 *
 * 2. BACKTRACKING:
 *    - When we try a block choice and it fails later, we backtrack
 *    - Try alternative blocks for the same position
 *    - Exhaustively explores all valid pyramid configurations
 *
 * 3. MEMOIZATION STRATEGY:
 *    - Key insight: Same row configuration always yields same result
 *    - Example: If "CE" can build to top from one path, it can from any path
 *    - Cache at START of row processing (position == 0)
 *    - Don't cache mid-row states (they depend on nextRow accumulation)
 *
 * 4. STATE REPRESENTATION:
 *    - currentRow: what we're building from
 *    - position: where in currentRow we are
 *    - nextRow: accumulated blocks for row above (partial state)
 *    - Only currentRow matters for memoization (represents complete state)
 *
 * 5. PATTERN MAP OPTIMIZATION:
 *    - Preprocess allowed patterns into map
 *    - O(1) lookup instead of O(k) scan where k = allowed.length
 *    - Maps "XY" → [list of possible Z's]
 *
 * 6. CORRECTNESS:
 *    - We try all possible combinations through backtracking
 *    - Memoization prevents redundant work
 *    - Base case correctly identifies pyramid completion
 *    - Return true on first success (don't need all solutions)
 *
 * COMPLEXITY ANALYSIS:
 * - Without memoization: O(m^(n-1) * (n-2) * ... * 1) ≈ O(m^(n²/2))
 *   where m = avg patterns per pair, n = bottom length
 * - With memoization: O(n² * m^n) in worst case
 *   but typically much better due to pruning
 * - Space: O(n²) for storing memoized rows
 */
int main()
{
    return 0;
}