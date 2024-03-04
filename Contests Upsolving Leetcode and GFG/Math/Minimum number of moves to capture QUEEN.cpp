#include <cmath>
#include <algorithm>

int minMovesToCaptureTheQueen(int a, int b, int c, int d, int e, int f)
{
    int min_turns = 2; // Initialize the minimum turns to 2

    // Check if the queen is on the same row or column as the rook
    if (a == e || b == f)
    {
        // Check if the bishop is on the same row as the rook
        if (a == c)
        {
            // Check if the bishop is between the rook and the queen
            if ((b < d && d < f) || (b > d && d > f))
            {
                min_turns = std::min(min_turns, 2);
            }
            else
            {
                // Bishop is not between the rook and the queen
                min_turns = std::min(min_turns, 1);
            }
        }
        else if (b == d)
        { // Check if the bishop is on the same column as the rook
            // Check if the bishop is between the rook and the queen
            if ((a < c && c < e) || (a > c && c > e))
            {
                min_turns = std::min(min_turns, 2);
            }
            else
            {
                // Bishop is not between the rook and the queen
                min_turns = std::min(min_turns, 1);
            }
        }
        else
        {
            // Bishop is not on the same row or column as the rook
            min_turns = std::min(min_turns, 1);
        }
    }

    // Check if the queen is on the same diagonal as the bishop
    if (std::abs(e - c) == std::abs(f - d))
    {
        // Check if the rook is on the same diagonal as the bishop
        if (std::abs(a - c) == std::abs(b - d))
        {
            // Check if the rook is between the bishop and the queen
            if ((c < a && a < e) || (c > a && a > e))
            {
                min_turns = std::min(min_turns, 2);
            }
            else
            {
                // Rook is not between the bishop and the queen
                min_turns = std::min(min_turns, 1);
            }
        }
        else
        {
            // Rook is not on the same diagonal as the bishop
            min_turns = std::min(min_turns, 1);
        }
    }

    return min_turns;
}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}
