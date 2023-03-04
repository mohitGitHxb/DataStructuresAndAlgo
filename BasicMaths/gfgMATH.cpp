#include <bits/stdc++.h>
using namespace std;

// GCD(a,b) O(min(a,b))

// int gcd(int a , int b){  ✅
//     int res = min(a,b);
//     while (res != 0)
//     {
//         if (a%res==0 && b%res==0)
//         {
//             break;
//         }
//         res--;
//     }
//     return res;
// }



// Euclidean algo ✅
/*int gcd(int a , int b){
    while (a != b)
    {
        if(a > b){a-=b;}
        else{b-=a;}
    }
    return a;

}*/



// Optimized euclideon algo w/ recursion
// int gcd(int a, int b)
// {
//     if (b == 0)
//     {
//         return a;
//     }
//     else
//     {
//         return gcd(b, a % b);
//     }
// }



// LCM not so efficient solution
//  int lcm(int a , int b){
//      int res = max(a,b);
//      while (true)
//      {
//          if (res%a==0 && res%b==0)
//          {
//              return res;
//          }
//          else
//          {
//              res++;
//          }

//     }

// }

// optimized lcm O(Log(n))
// int lcm_v2(int a , int b){
//     int gcd_Res = gcd(a,b);
//     return (a * b)/gcd_Res;
// }

// Prime numbers O(n)🥱🥱
//  bool isPrime(int num){
//      if(num==1){return false;}
//      for (int i = 2; i < num; i++)
//      {
//          if (num%i==0){
//                          return false;
//      }
//      }
//      return true;

// }

// Prime numbers O(n^1/2)😀😀
//  bool isPrime_optimized(int num){
//      if (num==1){return false;}
//      for (int i = 2; i*i <= num; i++)
//      {
//          if (num%i==0)
//          {
//              return false;
//          }

//     }
//     return true;

// }

// Prime number v3 😎😎😎
// bool isPrime_moreOptimized(int num)
// {
//     if (num == 1)
//     {
//         return false;
//     }
//     else if (num == 2 || num == 3)
//     {
//         return true;
//     }
//     else if (num % 2 == 0 || num % 3 == 0)
//     {
//         return false;
//     }
//     else
//     {
//         for (int i = 5; i * i <= num; i += 6)
//         {
//             if (num % i == 0 || num % (i + 2) == 0)
//             {
//                 return false;
//             }
//         }
//         return true;
//     }
// }

// All divisors of a number naive sol O(n);🥱
/* void allDiv(int num){
    if (num == 0)
    {
        cout<<0<<endl;
    }
    else
    {
        for (int i = 1; i <= num; i++)
        {
            if (num%i == 0)
            {
                cout<<i<<" ";
            }

        }
        cout<<endl;

    }


} */
// allDivisors O(n^1/2);😎😎

// void allDivisors(int number){
//     if (number==0)
//     {
//         cout<<0<<endl;
//     }
//     else
//     {
//         for (int i = 1; i*i < number; i++)
//         {
//             if (number%i == 0)
//             {
//                 cout<<i<<" ";
//                 if (i != number/i)
//                 {
//                     cout<<number/i<<" ";
//                 }

//             }

//         }
//         cout<<endl;

//     }

// }

// printPrimes O(n x n^1/2)😐😐

// void printPrimes(int n){
//     for (int i = 2; i <= n; i++)
//     {
//         if (isPrime_moreOptimized(i))
//         {
//             cout<<i<<" ";
//         }

//     }
//     cout<<endl;

// }

// printPrimes sieve of erastosthenes method
//  void printPrimes_v2(int n){
//      vector<bool> vec(n+1,true);
//      for (int i = 2; i*i <= n; i++)
//      {
//          if(isPrime_moreOptimized(i)){
//              for (int j = 2*i; j <= n; j=j+i)
//              {
//                  vec[j]=false;
//              }

//         }
//     }
//     for (int i = 2; i <= n; i++)
//     {
//         if (isPrime_moreOptimized(i))
//         {
//             cout<<i<<" ";
//         }

//     }

// }

// printPrime most optimized

// void printPrimes_v3(int n)
// {
//     vector<bool> isPrime(n + 1, true);
//     for (int i = 2; i <= n; ++i)
//     {
//         if (isPrime_moreOptimized(i))
//         {
//             cout << i << " ";
//             for (int j = i * i; j <= n; j += i)
//             {
//                 isPrime[j] = false;
//             }
//         }
//     }
// }
// Pow function binary O(logn);
//  long power(int base , int exponent){
//      long int res = 1;
//      while (exponent>0)
//      {
//          if(exponent%2 != 0){
//              res = res * base;
//          }
//          base = base * base;
//          exponent = exponent / 2;
//      }
//      return res;

// }
class gfgMATH
{
public:
    int number1 = 0, number2 = 0;
    int gcd_v1(int a, int b)
    {
        int res = min(a, b);
        while (res != 0)
        {
            if (a % res == 0 && b % res == 0)
            {
                break;
            }
            res--;
        }
        return res;
    }
    int gcd_v2(int a, int b)
    {
        while (a != b)
        {
            if (a > b)
            {
                a -= b;
            }
            else
            {
                b -= a;
            }
        }
        return a;
    }
    int gcd_v3(int a, int b)
    {
        if (b == 0)
        {
            return a;
        }
        else
        {
            return gcd_v3(b, a % b);
        }
    }
    int lcm_v1(int a, int b)
    {
        int res = max(a, b);
        while (true)
        {
            if (res % a == 0 && res % b == 0)
            {
                return res;
            }
            else
            {
                res++;
            }
        }
    }
    int lcm_v2(int a, int b)
    {
        // int gcd_Res = gcd(a,b);
        return (a * b) / gcd_v3(a, b);
    }
    bool isPrime_v1(int num)
    {
        if (num == 1)
        {
            return false;
        }
        for (int i = 2; i < num; i++)
        {
            if (num % i == 0)
            {
                return false;
            }
        }
        return true;
    }
    bool isPrime_optimized(int num)
    {
        if (num == 1)
        {
            return false;
        }
        for (int i = 2; i * i <= num; i++)
        {
            if (num % i == 0)
            {
                return false;
            }
        }
        return true;
    }
    bool isPrime_moreOptimized(int num)
    {
        if (num == 1)
        {
            return false;
        }
        else if (num == 2 || num == 3)
        {
            return true;
        }
        else if (num % 2 == 0 || num % 3 == 0)
        {
            return false;
        }
        else
        {
            for (int i = 5; i * i <= num; i += 6)
            {
                if (num % i == 0 || num % (i + 2) == 0)
                {
                    return false;
                }
            }
            return true;
        }
    }
    void allDiv_v1(int num)
    {
        if (num == 0)
        {
            cout << 0 << endl;
        }
        else
        {
            for (int i = 1; i <= num; i++)
            {
                if (num % i == 0)
                {
                    cout << i << " ";
                }
            }
            cout << endl;
        }
    }
    void allDiv_v2(int number)
    {
        if (number == 0)
        {
            cout << 0 << endl;
        }
        else
        {
            for (int i = 1; i * i < number; i++)
            {
                if (number % i == 0)
                {
                    cout << i << " ";
                    if (i != number / i)
                    {
                        cout << number / i << " ";
                    }
                }
            }
            cout << endl;
        }
    }
    void printPrimes_v1(int n){
    for (int i = 2; i <= n; i++)
    {
        if (isPrime_moreOptimized(i))
        {
            cout<<i<<" ";
        }

    }
    cout<<endl;

}
    void printPrimes_v2(int n)
{
    vector<bool> isPrime(n + 1, true);
    for (int i = 2; i <= n; ++i)
    {
        if (isPrime_moreOptimized(i))
        {
            cout << i << " ";
            for (int j = i * i; j <= n; j += i)
            {
                isPrime[j] = false;
            }
        }
    }
}
 long double power(int base , int exponent){
     long double res = 1;
     while (exponent>0)
     {
         if(exponent%2 != 0){
             res = res * base;
         }
         base = base * base;
         exponent = exponent / 2;
     }
     return res;

}

};

int main(int argc, char const *argv[])
{
    gfgMATH *obj = new gfgMATH;
    cout<<obj->isPrime_optimized(6*(19215)+1);
    return 0;
}
