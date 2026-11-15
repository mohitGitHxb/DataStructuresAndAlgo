#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target(                                                            \
    "sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ull unsigned long long
#define ll long long
#define deb(x) cout << #x << "=" << x << endl
struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

static auto init = [] {
    ios_base::sync_with_stdio(false);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    return 0;
}();
class Solution {
private:
    /*
        On an 2 x 3 board, there are five tiles labeled from 1 to 5, and an
empty square represented by 0. A move consists of choosing 0 and a
4-directionally adjacent number and swapping it.

The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].

Given the puzzle board board, return the least number of moves required so that
the state of the board is solved. If it is impossible for the state of the board
to be solved, return -1.



Example 1:

Input: board = [[1,2,3],[4,0,5]]
Output: 1
Explanation: Swap the 0 and the 5 in one move.

Example 2:

Input: board = [[1,2,3],[5,4,0]]
Output: -1
Explanation: No number of moves will make the board solved.

Example 3:

Input: board = [[4,1,2],[5,0,3]]
Output: 5
Explanation: 5 is the smallest number of moves that solves the board.
An example path:
After move 0: [[4,1,2],[5,0,3]]
After move 1: [[4,1,2],[0,5,3]]
After move 2: [[0,1,2],[4,5,3]]
After move 3: [[1,0,2],[4,5,3]]
After move 4: [[1,2,0],[4,5,3]]
After move 5: [[1,2,3],[4,5,0]]


     */
public:
    const vector<pair<int, int>> directions{{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

    string convertBoardToString(vector<vector<int>>& board) {
        string boardString;
        for (int i = 0; i < 6; ++i) {
            boardString += to_string(board[i / 3][i % 3]);
        }
        return boardString;
    }

    int slidingPuzzle(vector<vector<int>>& board) {
        const string solvedBoard = "123450";
        string boardString = convertBoardToString(board);
        queue<string> q;
        unordered_set<string> visited;
        q.push(boardString);
        visited.insert(boardString);
        int moves = 0;

        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                boardString = q.front();
                q.pop();

                if (boardString == solvedBoard)
                    return moves;

                int zeroIndex = boardString.find('0');

                for (auto& direction : directions) {
                    int newX = zeroIndex / 3 + direction.first;
                    int newY = zeroIndex % 3 + direction.second;

                    if (newX < 0 || newX > 1 || newY < 0 || newY > 2)
                        continue;

                    int newIndex = newX * 3 + newY;

                    // Create a copy of the board to modify
                    string newBoardString = boardString;
                    swap(newBoardString[zeroIndex], newBoardString[newIndex]);

                    if (!visited.count(newBoardString)) {
                        q.push(newBoardString);
                        visited.insert(newBoardString);
                    }
                }
            }
            ++moves;
        }
        return -1;
    }
};
