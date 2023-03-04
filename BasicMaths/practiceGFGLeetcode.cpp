#include <bits/stdc++.h>
using namespace std;


/* reversing an interger */
// int reverseInt(int x)
// {
//     string str = to_string(x);
//     if (x < 0)
//     {
//     reverse(++str.begin(), str.end());
//         return stoi(str);
//     }
//     reverse(str.begin(), str.end());
//     // cout<<str;
//     return stoi(str);
// }
int reverse(int x) {
        bool neg = (x < 0 ? true : false);
        string s = to_string(x);
        string v(s.rbegin(), s.rend());
        long res = (neg ? -1 : 1) * stol(v);
        return (res <= INT_MIN + 1 || res >= INT_MAX - 1) ? 0 : (int) res;
    }

int main(int argc, char const *argv[])
{
    cout<<reverse(1534236469);
    return 0;
}
