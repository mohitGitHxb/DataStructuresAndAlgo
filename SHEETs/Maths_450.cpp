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
/*
^ Binary Exponentiation
 */

class BinaryExpo
{
private:
    const int MOD = 1e9 + 7;
    unordered_map<long long, unordered_map<long long, long long>> memo;

public:
    /*
    * Time Complexity Recurrence: O(log(n))
    * Space Complexity Recurrence: O(log(n))
    Using Memoization time complexity O(log(n)) and space complexity O(log(n)) because at most we can have log(n) levels of recursion stack.
    * Time complexity of iterative approach O(log(n)) and space complexity O(1)
     */
    long long binpow(long long base, long long exponent)
    {
        if (exponent == 0)
            return 1;
        if (memo.count(base) && memo[base].count(exponent))
            return memo[base][exponent];
        if (exponent % 2 == 1)
            return memo[base][exponent] = (binpow(base, exponent - 1) * base) % MOD;
        long long res = binpow(base, exponent / 2);
        return memo[base][exponent] = (res * res) % MOD;
    }

    // This function calculates the result of raising a base number to an exponent using an iterative approach.
    long long binpowIterative(long long base, long long exponent)
    {
        // Initialize the result variable to 1.
        long long res = 1;

        // While the exponent is greater than 0:
        while (exponent > 0)
        {
            // If the current exponent is odd (bitwise AND with 1 returns true):
            if (exponent & 1)
            {
                // Multiply the result by the base and take the modulo of the result with MOD.
                res = (res * base) % MOD;
            }

            // Square the base and take the modulo of the base with MOD.
            base = (base * base) % MOD;

            // Right shift the exponent by 1 (equivalent to dividing it by 2).
            exponent >>= 1;
        }

        // Return the final result.
        return res;

        /*
        %for very large value of a we can take the modulo of the result with MOD.
        a = a % MOD; at the beginning of the function

        %for very large value of MOD we cannot simply multiply result we need to use
        binary multiplication algorithm.

        %if the value of exponent is very large (>10^18) use ETF (Euler Totient Function)

        & Coprime numbers : a and b are coprime if gcd(a,b) = 1

        & Euler Totient Function : phi(n) = n * (1 - 1/p1) * (1 - 1/p2) * ... * (1 - 1/pk) where p1, p2, ... pk are prime numbers
        & ETF(prime) = prime - 1

        & Euler's theorem: a^b congruence (a ^ (b mod phi(n))) mod n
        & Congruency of p congruent to q mod x means we divide p by x and the remainder is q

        & (a ^ b) % MOD = (a ^ (b mod phi(MOD))) % MOD :: MOD is Prime
         */
    }

    long long binMultiplication(long long a, long long b)
    {
        long long res = 0;
        while (b > 0)
        {
            if (b & 1)
            {
                res = (res + a) % MOD;
            }
            a = (a + a) % MOD;
            b >>= 1;
        }
    }
};
int main()
{

    return 0;
}