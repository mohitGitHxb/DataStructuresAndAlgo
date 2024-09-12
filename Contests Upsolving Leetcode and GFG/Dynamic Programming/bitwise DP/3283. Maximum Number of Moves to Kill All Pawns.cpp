#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast", "inline", "unroll-loops", "no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native", "f16c")
#define ll long long
#define bigInt __int128_t
#define deb(x) cout << #x << "=" << x << endl
static void fast_read()
{
    ios_base::sync_with_stdio(false);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

static vector<vector<int>> minMoves[51][51];

class Solution
{
private:
    /*
        There is a 50 x 50 chessboard with one knight and some pawns on it. You are given two integers kx and ky where (kx, ky) denotes the position of the knight, and a 2D array positions where positions[i] = [xi, yi] denotes the position of the pawns on the chessboard.

Alice and Bob play a turn-based game, where Alice goes first. In each player's turn:

    The player selects a pawn that still exists on the board and captures it with the knight in the fewest possible moves. Note that the player can select any pawn, it might not be one that can be captured in the least number of moves.
    In the process of capturing the selected pawn, the knight may pass other pawns without capturing them. Only the selected pawn can be captured in this turn.

Alice is trying to maximize the sum of the number of moves made by both players until there are no more pawns on the board, whereas Bob tries to minimize them.

Return the maximum total number of moves made during the game that Alice can achieve, assuming both players play optimally.

Note that in one move, a chess knight has eight possible positions it can move to, as illustrated below. Each move is two cells in a cardinal direction, then one cell in an orthogonal direction.



Example 1:

Input: kx = 1, ky = 1, positions = [[0,0]]

Output: 4

Explanation:

The knight takes 4 moves to reach the pawn at (0, 0).

Example 2:

Input: kx = 0, ky = 2, positions = [[1,1],[2,2],[3,3]]

Output: 8

Explanation:

    Alice picks the pawn at (2, 2) and captures it in two moves: (0, 2) -> (1, 4) -> (2, 2).
    Bob picks the pawn at (3, 3) and captures it in two moves: (2, 2) -> (4, 1) -> (3, 3).
    Alice picks the pawn at (1, 1) and captures it in four moves: (3, 3) -> (4, 1) -> (2, 2) -> (0, 3) -> (1, 1).

Example 3:

Input: kx = 0, ky = 0, positions = [[1,2],[2,4]]

Output: 3

Explanation:

    Alice picks the pawn at (2, 4) and captures it in two moves: (0, 0) -> (1, 2) -> (2, 4). Note that the pawn at (1, 2) is not captured.
    Bob picks the pawn at (1, 2) and captures it in one move: (2, 4) -> (1, 2).

    @ Solution:
    Intuition

    Chess board, Knight & No of moves, all point out to graph being involved, and BFS will be needed.
    2 players are playing, and both can make optimal decisions as per the constraint, which point out to some form of DP.
    There can be any options at a given instant, like which pawn to pick up, which makes bit-mask DP a possiblity, and the range of no of position <15 confirm this.
    Knight will alway end at a pwn position. It can not end at any randome position.

Approach

Breaking down the approach:

    The dp can be formulated in such a manner, if knight is at a position p3(pawn no 3 position), it will have the choice of all remain pawn to choose from. So for a unique we need to know where he knight is, if its alices turn and pwns chosen untill now.
    dp(pawnIdx, isAlice, mask) -> max possible moves such that knight is at pawnPos, it is Alice's turn and no of selected pawns untill now stored in mask.
    There will be two transitions, one for alice and one for bob. Alice is concerned with maximising moves, so she chooses the pawn which is farthest, and Bob chooses the pawn which is nearest.
    _
    dp(pawnIdx, isAlice, mask) -> dp(i, !isAlice, mask`) + [no of moves]
    _
    Keep in mind, when alice is playing we are interested in maximising and when bob is palying we are interested in minimising.
    We pre calculate distance of all nodes from all pawn and from the knight, so that we can get dist [ curCell -> nextPawn] in O(1).
    We need to start with knight as our starting position, and my DP, I do not consider knight's starting position when modifying mask. This makes the implementation quiet clean.

     */
public:
    const uint32_t MOD = 1e9 + 7;
    Solution()
    {
        fast_read();
        if (minMoves[0][0].empty())
        {
            preprocess();
        }
    }
    vector<pair<int, int>> knightMoves = {{1, 2}, {1, -2}, {-1, 2}, {-1, -2}, {2, 1}, {2, -1}, {-2, 1}, {-2, -1}};
    ll dp[16][66000][2];
    vector<vector<int>> BFS(int row, int col)
    {
        vector<vector<int>> distance(50, vector<int>(50, 1e9));
        distance[row][col] = 0;
        queue<pair<int, int>> q;
        q.push({row, col});

        while (!q.empty())
        {
            auto [x, y] = q.front();
            q.pop();

            for (auto [i, j] : knightMoves)
            {
                int nx = x + i;
                int ny = y + j;

                if (nx >= 0 && nx < 50 && ny >= 0 && ny < 50 && distance[nx][ny] > distance[x][y] + 1)
                {
                    distance[nx][ny] = distance[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
        return distance;
    }
    void preprocess()
    {
        for (int i = 0; i < 50; i++)
        {
            for (int j = 0; j < 50; j++)
            {
                minMoves[i][j] = BFS(i, j);
            }
        }
    }

    int getDistance(int x1, int y1, int x2, int y2)
    {
        return minMoves[x1][y1][x2][y2];
    }

    ll solve(int pawnIdx, int capturedMask, bool isAliceTurn, vector<vector<int>> &positions)
    {
        int totalPawns = positions.size();
        if (capturedMask == (1 << totalPawns) - 1)
        {
            return 0;
        }

        //  cache check
        if (dp[pawnIdx][capturedMask][isAliceTurn] != -1)
        {
            return dp[pawnIdx][capturedMask][isAliceTurn];
        }

        ll ans = (isAliceTurn) ? INT_MIN : INT_MAX;
        /* Knight previous location */
        int kx = positions[pawnIdx][0];
        int ky = positions[pawnIdx][1];
        for (int i = 0; i < totalPawns; i++)
        {
            int pawnX = positions[i][0];
            int pawnY = positions[i][1];
            if (capturedMask & (1 << i))
            {
                continue;
            }
            if (isAliceTurn)
            {
                ans = max(ans, solve(i, capturedMask | (1 << i), false, positions) + getDistance(kx, ky, pawnX, pawnY));
            }
            else
            {
                ans = min(ans, solve(i, capturedMask | (1 << i), true, positions) + getDistance(kx, ky, pawnX, pawnY));
            }
        }
        return dp[pawnIdx][capturedMask][isAliceTurn] = ans;
    }

    int maxMoves(int kx, int ky, vector<vector<int>> &positions)
    {
        memset(dp, -1, sizeof(dp));
        positions.insert(positions.begin(), {kx, ky});
        return solve(0, 1, true, positions);
    }
};

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
