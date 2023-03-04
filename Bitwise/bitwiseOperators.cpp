#include <bits/stdc++.h>
using namespace std;

// kth bit is set or not '<<'
//  void KthBit(uint16_t n , uint16_t k){
//      if (n&(1<<(k-1)) != 0)
//      {
//          cout<<"yes";
//          return;
//      }
//      cout <<"no";
//  }
// kth bit is set or not '>>'
//  void KthBit(uint16_t n , uint16_t k){
//      if (((n>>(k-1))&1) == 1)
//      {
//          cout<<"yes";
//          return;
//      }
//      cout <<"no";
//  }

// power of 2 O(n^1/2)
//  void checKPowOf2(uint16_t n){
//      for (int i = 0; i*i <= n; i++)
//      {
//          if (n == pow(2,i))
//          {
//              cout<<"yes ";
//              return;
//          }

//     }
//     cout<<"no ";

// }

// using bits pow of 2
 bool checkPowOf2(uint16_t n){
     if(n==0){return false;}
     return ((n&(n-1))==0);
 }

// count set bits positive numbers only O(total bits in n)
//  int countBits(uint32_t n){
//      uint32_t ref = 1,count = 0;
//      for (int i = 0; i < 32; i++)
//      {
//          if (n&(ref<<i))
//          {
//              count++;
//          }

//     }
//     return count;
// }

// brion keningam's algorithm
// int countBits_v2(uint32_t n)
// {
//     uint_fast8_t res = 0;
//     while (n > 0)
//     {
//         n = (n & (n - 1));
//         res++;
//     }
// }

// lookup table method O(1)
// vector<int> vec;
// void initialize(void){
//     vec[0] = 0;
//     for (uint_fast16_t i = 1; i < 256; i++)
//     {
//         vec[i] = (i&1)+vec[i/2];
//     }
    
// }
// int countBits_v3(uint32_t n)
// {
//     int res = vec[n&0xff];
//     n=n>>8;
//     res+=vec[n&0xff];
//     n=n>>8;
//     res+=vec[n&0xff];
//     n=n>>8;
//     res+=vec[n&0xff];
//     return res;
    
// }

//find only odd occuring number O(n)

// int oddOccuring(const vector<int> &arr){
//     unordered_map<int,int> mp;
//     for (int i = 0; i < arr.size(); i++)
//     {
//         mp[arr[i]]++;
//     }
//     for(auto &x : mp){
//         if (x.second%2 != 0)
//         {
//             return x.first;
//         }
//     }
//     return 0;
    
// }

//find only odd occuring number O(n) bits version
int findOdd(vector<int> &arr){
    int res=0;
    for (int i = 0; i < arr.size(); i++)
    {
        res = res^arr[i];
    }
    return res;
    
}
int main(int argc, char const *argv[])
{
    // uint16_t x = 13;
    vector<int> test = {8,7,7,8,8};
    // cout<<oddOccuring(test);

    return 0;
}
