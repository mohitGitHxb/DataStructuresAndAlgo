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

class Divisors
{
public:
    // ! Brute Force approach O(N) time
    int divisors_1(int n)
    {
        int count = 0;
        int sum = 0;
        for (int i = 1; i <= n; i++)
        {
            if (n % i == 0)
            {
                count++;
                sum += i;
            }
        }
        return count;
    }

    //% Better approach O(sqrt(N)) time
    pair<int, int> divisors_2(int n)
    {
        int count = 0, sum = 0;
        for (int i = 1; i * i <= n; i++)
        {
            if (n % i == 0)
            {
                cout << i << " x " << n / i << "\n";
                count++;
                sum += i;
                if (n / i != i)
                {
                    count++;
                    sum += n / i;
                }
            }
        }
        return {count, sum};
    }
};

class PrimeNumbers
{
public:
    bool isPrime_brute(int n)
    {
        for (int i = 2; i < n; i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }
        return true;
    }

    bool isPrime_sqrt(int n)
    {
        if (n == 1)
            return false;
        for (int i = 2; i * i <= n; i++)
        {
            if (n % i == 0)
                return false;
        }
        return true;
    }

    vector<int> getPrimeFactors_v1(int num)
    {
        /*         vector<int> primes;
                for (int i = 2; i * i <= num; i++)
                {
                    while (num % i == 0)
                    {
                        primes.emplace_back(i);
                        num /= i;
                    }
                }
                if (num > 1)
                {
                    primes.emplace_back(num);
                }
                return primes; */

        //* More optimized O(sqrt(N)) approach

        vector<int> primes;
        while (num % 2 == 0)
        {
            if (primes.empty() || primes.back() != 2)
                primes.emplace_back(2);
            num /= 2;
        }
        for (int i = 3; i * i <= num; i += 2)
        {
            while (num % i == 0)
            {
                if (primes.empty() || primes.back() != i)
                    primes.emplace_back(i);
                num /= i;
            }
        }
        if (num > 1)
        {
            if (primes.empty() || primes.back() != num)
                primes.emplace_back(num);
        }
        return primes;
    }

    vector<bool> sieve_algo(int num)
    {
        vector<bool> sieve(num + 1, true);
        // vector<int> primes;
        sieve.at(0) = sieve.at(1) = false;
        for (int i = 2; i <= num; i++)
        {
            if (sieve.at(i))
            {
                // primes.emplace_back(i);
                for (int j = i * i; j <= num; j += i)
                {
                    sieve.at(j) = false;
                }
            }
        }
        return sieve;
    }

    vector<int> getPrimeNumbersTillN(int num)
    {
        vector<bool> sieve = sieve_algo(num);
        vector<int> primes;

        for (int i = 2; i <= num; i++)
        {
            if (sieve.at(i))
            {
                primes.emplace_back(i);
            }
        }
        return primes;
    }

    vector<int> getPrimeFactors_v2(int num)
    {
        vector<bool> sieve(num + 1, true);
        // lowest prime , highest prime
        vector<int> ans, lp(num + 1), hp(num + 1);
        sieve.at(0) = sieve.at(1) = false;

        for (int i = 2; i <= num; i++)
        {
            if (sieve.at(i))
            {
                lp[i] = hp[i] = i;
                for (int j = 2 * i; j <= num; j += i)
                {
                    sieve.at(j) = false;
                    hp[j] = i;
                    if (lp[j] == 0)
                    {
                        lp[j] = i;
                    }
                }
            }
        }

        while (num > 1)
        {
            ans.emplace_back(lp[num]);
            num /= lp[num];
        }

        return ans;
    }

    vector<int> getDivisors_v2(int num)
    {
        vector<bool> isPrime(num + 1, true);
        vector<vector<int>> divisors(num + 1);
        isPrime[0] = isPrime[1] = false;

        for (int i = 2; i <= num; i++)
        {
            if (isPrime[i])
            {
                for (int j = i; j <= num; j += i)
                {
                    divisors[j].emplace_back(i);
                }
            }
        }

        return divisors[num];
    }

    vector<int> primeRange(int M, int N)
    {
        vector<bool> check(N + 1, false);
        vector<int> ans;

        for (int i = 2; i <= N; i++)
        {
            if (i >= M && i <= N)
            {
                if (check[i] == false)
                {
                    ans.push_back(i);
                }
            }
            int temp = i;
            temp += i;
            while (temp <= N)
            {
                check[temp] = true;
                temp += i;
            }
        }
        return ans;
    }

    long long int nineDivisors(long long int N)
    {
        vector<bool> isprime(sqrt(N) + 2, true);
        isprime[1] = false;
        vector<long long> highestPrime(sqrt(N) + 2);
        for (long long i = 2; i * i <= N; i++)
        {
            if (isprime[i])
            {
                highestPrime[i] = i;
                for (long long j = 2 * i; j * j <= N; j += i)
                {
                    isprime[j] = false;
                    highestPrime[j] = i;
                }
            }
        }
        long long ans = 0;
        for (long long i = 2; i * i <= N; i++)
        {
            long long n = i * i;
            long long divisors = 1;
            while (n > 1)
            {
                long long hp = highestPrime[sqrt(n)];
                long long count = 0;
                while (n % hp == 0)
                {
                    count++;
                    n /= hp;
                }
                divisors *= (count + 1);
            }
            if (divisors == 9)
                ans++;
        }
        return ans;
    }
};

class ModularArithmetic
{
private:
    /*
    1. Addition: (a + b) mod n = ((a mod n) + (b mod n)) mod n
    2. Subtraction: (a - b) mod n = ((a mod n) - (b mod n) + n) mod n
    3. Multiplication: (a * b) mod n = ((a mod n) * (b mod n)) mod n
    4. Division: Division is not directly applicable in modular arithmetic. However, multiplicative inverse can be used. If you want to compute (a / b) mod n, you need to find the multiplicative inverse of b, let's call it b_inv, such that (b * b_inv) mod n = 1. Then, (a / b) mod n = (a * b_inv) mod n.
    5. Power: (a^b) mod n = ((a mod n)^b) mod n
    6. Distributive Laws: a mod n = (a mod m) mod n if m > n.
    7. Negative Numbers: If a < 0, then a mod n = n - ((-a) mod n), unless a is a multiple of n, in which case a mod n = 0.
    8. Modulo of a Modulo: (a mod n) mod n = a mod n
    9. Modulo of a Sum: (a + b) mod n = ((a mod n) + (b mod n)) mod n
    10. Modulo of a Difference: (a - b) mod n = ((a mod n) - (b mod n) + n) mod n
    11. Modulo of a Product: (a * b) mod n = ((a mod n) * (b mod n)) mod n

    Note: These rules are applicable under the assumption that the numbers are integers and the moduli are positive. Also, the division operation in modular arithmetic requires that the divisor has a multiplicative inverse, which is not always the case.


    The modular multiplicative inverse of a number 'num' under modulo 'mod' can be found using the Extended Euclidean Algorithm. The modular multiplicative inverse of 'num' modulo 'mod' is a number 'x' such that the product 'num*x' is equivalent to 1 modulo 'mod'.


    Fermat's Little Theorem states that if 'p' is a prime number, then for any integer 'a', the number 'a^p' is congruent to 'a' modulo 'p'. In the special case when 'a' is not divisible by 'p', Fermat's Little Theorem is equivalent to the statement that 'a^(p-1) - 1' is an integer multiple of 'p'.

    If 'p' is a prime number and 'a' is an integer not divisible by 'p', then 'a^(p-1) ≡ 1 (mod p)'. This can be used to find the modular multiplicative inverse when 'mod' is a prime number. The modular inverse of 'a' under 'mod' is 'a^(mod-2) % mod'.
     */
public:
    long long binaryExponentiation(long long base, long long exponent, long long mod)
    {
        long long res = 1;
        while (exponent > 0)
        {
            if (exponent % 2 == 1)
            {
                res = (res * base) % mod;
            }
            base = (base * base) % mod;
            exponent >>= 1;
        }
        return res;
    }
    long long getModularMultiplicativeInverse(long long num, long long mod)
    {
        // multiplicative inverse only exists if num and mod are relatively prime (coprime) i.e gcd(num, mod) = 1
        if (__gcd(num, mod) != 1)
        {
            return -1;
        }
        return binaryExponentiation(num, mod - 2, mod);
    }

    long long getAllPossiblePasswords(int n, int k)
    {
        // pre computing factorial
        vector<long long> fact(n + 1, 1);
        for (long long i = 1; i <= n; i++)
        {
            fact[i] = (fact[i - 1] * i) % k;
        }

        // need to find C(n, k) * n!
        long long numerator = (fact[n] * fact[k]) % 1000000007;
        long long denominator = (fact[n - k] * fact[n]);

        return (numerator * getModularMultiplicativeInverse(denominator, 1000000007)) % 1000000007;
    }
};

//% Sieve concept questions
//^ Given an array return all numbers that are divisible by numbers p or q or both;

class Question1
{
private:
    const int N = 2e5 + 10;
    const int MOD = 1e9 + 7;
    unordered_map<int, int> freq;
    vector<long> multiple_ct;

public:
    Question1(vector<long> &arr)
    {
        for (long i = 0; i < arr.size(); i++)
        {
            freq[arr[i]]++;
        }
        multiple_ct.resize(N);
    }
    long getLCM(long a, long b)
    {
        return (a * b) / __gcd(a, b);
    }

    void preCompute()
    {
        for (long i = 1; i < N; i++)
        {
            for (long j = i; j < N; j += i)
            {
                multiple_ct[i] += freq[j];
            }
        }
    }
    long solve(long n, long p, long q)
    {
        preCompute();
        long ans = multiple_ct[p] + multiple_ct[q];
        if (getLCM(p, q) < n)
        {
            ans -= multiple_ct[getLCM(p, q)];
        }
        return ans;
    }
};

/*
^ Problem
^   Alex has started hacking websites, and also started learning encryption and decryption of messages. Once he faced an interesting issue, where he needs to decrypt the message in a different way.
^   Initially, he will be given an array A of N integers, and has to decrypt Q messages. In each message he will get an integer X, and if X can be converted into product of two different or same prime numbers, then the real message is "YES" (without quotes), otherwise the message is "NO" (without quotes).

^   To convert X, he can choose one element from array say Y (X should be divisible Y), and can divide X by Y any number of times (till X is divisible by Y). Help Alex in decrypting the messages.
 */

class Question2
{
private:
    const int N = 1e5 + 10;
    const int MOD = 1e9 + 7;
    vector<bool> sieve;
    vector<int> hp, lp;
    unordered_map<int, vector<int>> prime_factors;

public:
    Question2()
    {
        sieve.resize(N, true);
        hp.resize(N, 0);
        lp.resize(N, 0);

        sieve[0] = sieve[1] = false;

        for (int i = 2; i < N; i++)
        {
            if (sieve[i])
            {
                lp[i] = hp[i] = i;
                for (int j = i * 2; j < N; j += i)
                {
                    sieve[j] = false;
                    hp[j] = i;
                    if (lp[j] == 0)
                    {
                        lp[j] = i;
                    }
                }
            }
        }

        for (int i = 2; i < N; i++)
        {
            int temp = i;
            while (temp > 1)
            {
                int p = lp[temp];
                while (temp % p == 0)
                    temp /= p;
                prime_factors[i].push_back(p);
            }
        }
    }

    void printHashmap(void)
    {
        for (auto &i : prime_factors)
        {
            cout << "{" << i.first << ":";
            for (auto &k : i.second)
            {
                cout << k << " ";
            }
            cout << "}\n";
        }
        cout << "\n";
    }

    vector<bool> getCanRemoveArray(int x, const vector<int> &arr)
    {
        vector<bool> canRemove(1e5 + 10);
        for (auto &i : arr)
        {
            canRemove[i] = true;
        }
        for (int i = 2; i < N; i++)
        {
            if (canRemove[i])
            {
                for (long j = i; j < N; j *= i)
                {
                    canRemove[j] = true;
                }
            }
        }
        return canRemove;
    }

    void solve(int x, vector<int> &arr)
    {
        vector<int> distinctPrimeFactors = prime_factors[x];
        vector<bool> canRemove = getCanRemoveArray(x, arr);
        bool isPossible;
        for (int i = 0; i < distinctPrimeFactors.size(); i++)
        {
            for (int j = i; j < distinctPrimeFactors.size(); j++)
            {
                int product = distinctPrimeFactors[i] * distinctPrimeFactors[j];
                if (i == j && x % product != 0)
                    continue;
                int toRemove = x / product;
                if (canRemove[toRemove] && toRemove == 1)
                {
                    isPossible = true;
                    break;
                }
            }
            if (isPossible)
            {
                break;
            }
        }

        cout << (isPossible ? "YES" : "NO") << "\n";
    }
};

int CommonFactor(int n)
{
    /*
    This C++ function, named `CommonFactor`, takes an integer `n` as an input and returns the count of common factors of `n`.

Here's a step-by-step explanation of the code:

1. The function starts by initializing two integer variables: `temp` and `count`. `temp` is set to the value of `n`, and `count` is initialized to 0. `count` will be used to keep track of the number of common factors.

2. A `for` loop is then started, which runs from 2 to `n` (inclusive). The loop variable is `i`.

3. Inside the loop, the code first checks if `temp` is divisible by `i` (i.e., `temp % i == 0`). If it is, `count` is incremented by 1, indicating that `i` is a factor of `n`.

4. If `temp` is not divisible by `i`, the code then checks if the greatest common divisor (gcd) of `i` and `n` is not 1 (`__gcd(i, n) != 1`). If this condition is true, `count` is again incremented by 1. This condition checks if `i` and `n` have any common factor other than 1.

5. After the loop finishes running, the function returns the value of `count`, which represents the number of common factors of `n`.

     */
    int temp = n, count = 0;
    for (int i = 2; i <= n; i++)
    {
        if (temp % i == 0)
            count++;
        else if (__gcd(i, n) != 1)
            count++;
    }
    return count;
}

int main()
{

    return 0;
}