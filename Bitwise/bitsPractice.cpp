#include <bits/stdc++.h>
using namespace std;

vector<int> changeBits(int N)
{
    int num = 0, p = 0, n = N;
    while (n != 0)
    {
        num += 1 << (p++);
        n /= 2;
    }
    return vector<int>{abs(N - num), num};
}
int main(int argc, char const *argv[])
{
    changeBits(6);
    return 0;
}
