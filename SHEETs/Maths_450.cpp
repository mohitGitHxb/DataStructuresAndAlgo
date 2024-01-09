#include <bits/stdc++.h>
using namespace std;

/*
^ GCD and LCM
 */
pair<int, int> getGCDandLCM(int a, int b)
{
    //? Using inbuilt gcd function with formula O(log(min(a,b)))
    int gcd = __gcd(a, b);
    int lcm = (a * b) / gcd;
    return {gcd, lcm};

    //? Using Euclidean Algorithm O(log(min(a,b)))
    while (b != 0)
    {
        int temp = a % b;
        a = b;
        b = temp;
    }
    int gcd = a;
    int lcm = (a * b) / gcd;
    return {gcd, lcm};

    //? Using Recursion O(log(min(a,b)))
    function<int(int, int)> gcdRecur = [&](int a, int b)
    {
        return b == 0 ? a : gcdRecur(b, a % b);
    };
}

int main()
{

    return 0;
}