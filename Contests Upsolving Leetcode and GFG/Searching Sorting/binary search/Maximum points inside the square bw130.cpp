#include <bits/stdc++.h>
using namespace std;
/*
You are given a 2D array points and a string s where, points[i] represents the coordinates of point i, and s[i] represents the tag of point i.

A valid square is a square centered at the origin (0, 0), has edges parallel to the axes, and does not contain two points with the same tag.

Return the maximum number of points contained in a valid square.

Note:

    A point is considered to be inside the square if it lies on or within the square's boundaries.
    The side length of the square can be zero.



Example 1:

Input: points = [[2,2],[-1,-2],[-4,4],[-3,1],[3,-3]], s = "abdca"

Output: 2

Explanation:

The square of side length 4 covers two points points[0] and points[1].

Example 2:

Input: points = [[1,1],[-2,-2],[-2,2]], s = "abb"

Output: 1

Explanation:

The square of side length 2 covers one point, which is points[0].

Example 3:

Input: points = [[1,1],[-1,-1],[2,-2]], s = "ccd"

Output: 0

Explanation:

It's impossible to make any valid squares centered at the origin such that it covers only one point among points[0] and points[1].


 */
class Solution
{
public:
    // 1. check if a point is inside the square
    bool check(vector<vector<int>> &points, int i, int res)
    {
        return points[i][0] <= res && points[i][1] <= res;
    }
    /*


Checking Valid Squares: - ITo determine whether a square with side length mid can accommodate all points without overlapping for each possible side length mid.

    It guarantees that no two points with the same tag are inside the same square and that every point fits inside the square's bounds.

Search Range updation: - We then update res to mid and modify the search range to cover further side lengths if a valid square is discovered for a certain side length, mid. If not, we just reduce the search space to shorter side lengths. Just like we always do in binary search - based algorithms.

Counting the points: - At last we count the number of points that can fit inside a square with side length res after determining the maximum valid side length res. We accomplish this by continuously going over each point and determining whether or not it is inside the square's bounds.

Returning the Result: - In the end, it provides the number of points that can fit inside a vlid square

     */

    int maxPointsInsideSquare(vector<vector<int>> &points, string s)
    {
        int n = points.size();
        int minimumCoordinate = INT_MAX, maximumCoordinate = INT_MIN;
        for (int i = 0; i < n; ++i)
        {
            points[i][0] = abs(points[i][0]); //& making all the coordinates positive
            points[i][1] = abs(points[i][1]); //& because the square is centered at the origin
            minimumCoordinate = min(minimumCoordinate, max(points[i][0], points[i][1]));
            maximumCoordinate = max({maximumCoordinate, points[i][0], points[i][1]});
        }
        //? Applying binary search on all possible length of the square
        int left = minimumCoordinate, right = maximumCoordinate, res = 0;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            unordered_map<char, int> temp;
            bool flag = true;
            //? check if a point is inside the square of length mid
            for (int i = 0; i < n; ++i)
            {
                if (check(points, i, mid))
                {
                    temp[s[i]]++;
                }
                if (temp[s[i]] > 1)
                {
                    flag = false;
                    break;
                }
            }

            //? if a point is inside the square of length mid, update the result
            //? else, reduce the length of the square
            if (flag)
            {
                res = mid;
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        int ans = 0;
        for (int i = 0; i < n; ++i)
        {
            if (check(points, i, res))
            {
                ans++;
            }
        }

        return ans;
    }
    /* 
    
    @ 2nd approach using bottlenecking concept
    * time complexity - O(n) 
     */
    int maxPointsInsideSquare(vector<vector<int>> &points, string s)
    {
        vector<int> correspondingSquare(points.size());
        for (int i = 0; i < points.size(); i++)
        {
            correspondingSquare[i] = max(abs(points[i][0]), abs(points[i][1]));
        }
        // assert(correspondingSquare.size() == s.size());
        unordered_map<char, int> minimumSquare;
        int ignoreBigger = INT_MAX; // bottle neck
        for (int i = 0; i < s.size(); i++)
        {
            int currentSquare = correspondingSquare[i];
            if (minimumSquare.count(s[i]))
            {
                if (currentSquare < minimumSquare[s[i]])
                {
                    ignoreBigger = min(ignoreBigger, minimumSquare[s[i]]);
                    minimumSquare[s[i]] = currentSquare;
                }
                else
                {
                    ignoreBigger = min(ignoreBigger, currentSquare);
                }
            }
            else
            {
                minimumSquare[s[i]] = currentSquare;
            }
        }
        int ans = 0;
        // for (int &squareLength : correspondingSquare)
        // {
        //     ans += (squareLength < ignoreBigger);
        // }
        for (auto [k, v] : minimumSquare)
        {
            ans += (v < ignoreBigger);
        }
        return ans;
    }
};
int main()
{
    return 0;
}