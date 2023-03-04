#include <bits/stdc++.h>
using namespace std;

// void frequencyOfcharacters(string &s){
//     map<char,int> m;
//     for (int i = 0; i < s.length(); i++)
//     {
//         m[s[i]]++;
//     }
//     for (auto &y : m)
//     {
//         cout<<y.first<<" -> "<<y.second<<endl;
//     }
// }

// check pallindrome Ø(N) space and time
// bool isPallindrome(string &str){
//     string temp = str;
//     reverse(temp.begin(),temp.end());
//     return str == temp;
// }

// efficient sol. O(n) time and O(1) space
//  bool isPallindrome_v2(string &str){
//      uint_fast16_t low = 0 , high = str.length()-1;
//      while (low<=high)
//      {
//          if(str[low] != str[high] ){
//              return false;
//          }
//          low++; high--;
//      }
//      return true;
//  }

// subsequence of strings Ø(n+m);
//  bool isSubsequence(string &str1,string &str2){
//      uint_fast16_t i = 0 ,  j = 0;
//      if (str1.length()<str2.length())
//      {
//          return false;
//      }

//     while (i<str1.length() && j<str2.length())
//     {
//         if (str1[i] == str2[j])
//         {
//             i++;
//             j++;
//         }else{i++;}

//     }
//     return(j == str2.length());
// }

// recursive subsequence sol
//  bool isSubsequence(const string &str1, const string &str2){
//      static int i = 0 , j = 0;
//      if (str1[i] == str2[j] && i<str1.length())
//      {
//          i++;
//          j++;

//         return isSubsequence(str1,str2);

//     }
//     else if(i<str1.length() && j<str2.length() && (str1.length()>str2.length())){
//         i++;
//         return isSubsequence(str1,str2);

//     }
//     else
//     return (j == str2.length());

// }

// check if two strings are anagram or not O(nlogn)
//  bool isAnagram(string &s1,string &s2){
//      if(s1.length() != s2.length())
//          return false;
//      sort(s1.begin(),s1.end());
//      sort(s2.begin(),s2.end());
//      return (s1==s2);
//  }

// O(n)
// bool areAnagram(string &s1, string &s2)
// {
//     if (s1.length() != s2.length())
//     {
//         return false;
//     }
//     vector<int> count(256);
//     for (int i = 0; i < s1.length(); i++)
//     {
//         count[s1[i]]++; /*for every char of s1 increment the count , for every char of s2 decrement the count*/
//         count[s2[i]]--;
//     }
//     for (int i = 0; i < 256; i++)
//     {
//         if (count[i] != 0)
//         {
//             return false;
//         }
//     }
//     return true;
// }

// leftmost repeating character O(n^2)
//  int getLeftmostRepeatingCHAR(string &s){
//      for (int i = 0; i < s.size(); i++)
//      {
//          for (int j = i + 1; j < s.length(); j++)
//          {
//              if (s[i] == s[j])
//              {
//                  return i;
//              }

//         }

//     }
//     return -1;

// }

// better solution
//  int getLeftmostRepeatingCHAR(string &str){
//      vector<int> Count(UINT8_MAX); /* using char as indices(ascii values)*/
//      for (int i = 0; i < str.length(); i++)
//      {
//          Count[str[i]]++;
//      }
//      for (int i = 0; i < str.length(); i++)
//      {
//          if (Count[str[i]]>1)
//          {
//              return i;
//          }
//
//     return -1;
// }

// effiecient approach -1 O(n)
//  int getLeftmostRepeatingCHAR(string &str){
//      vector<int> fIndex(UINT8_MAX,-1); /* using char as indices(ascii values)*/
//      int res = INT32_MAX;
//      for (int i = 0; i < str.length(); i++)
//      {
//          int fi = fIndex[str[i]];
//          if (fi == -1)
//          {
//              fIndex[str[i]] = i;
//          }
//          else
//              res = min(res,fi); /*keeping track of leftmost repeating element*/

//     }
//     return(res==INT32_MAX)?-1:res;

// }

// leftmost non repeating element (using extra space)
// int getLeftmostNonRepeatingCHAR(string &str)
// {
//     unordered_map<char, int> mp;
//     for (int i = 0; i < str.length(); i++)
//     {
//         mp[str[i]]++;
//     }
//     int lowestInd = INT8_MAX;
//     for (auto &x : mp)
//     {
//         if (x.second == 1)
//         {
//             int currIND = str.find(x.first);
//             lowestInd = min(lowestInd, currIND);
//         }
//     }
//     mp.clear();
//     if(lowestInd != INT8_MAX)
//          return lowestInd;
//     return -1;
// }

// dual traversal solution
// int nonRepeatingCHAR(string &str){
//     vector<int> Cnt(UINT8_MAX);    //uint8_max = 255
//     for (int i = 0; i < str.length(); i++)
//     {
//         Cnt[str[i]]++;
//     } //increment count for every char in the string
//     for (int i = 0; i < str.length(); i++)
//     {
//         if (Cnt[str[i]]==1) //this element is not repeating
//         {
//             return i; //first element that isn't repeating...
//         }

//     }

//     return -1;
// }

// single traversal solution Ø(n+255)
//  int nonRepeatingCHAR(string &str){
//      vector<int> firstIndexes(UINT8_MAX,-1); //stores first indexes
//      for (int i = 0; i < str.length(); i++)
//      {
//          if (firstIndexes[str[i]] == -1)
//          {
//              firstIndexes[str[i]] = i; //stores the non repeating element
//          }
//          else
//              firstIndexes[str[i]] = -2; //indicates whether a element has repeated itself or not

//     }
//     int res = UINT16_MAX;
//     for (int i = 0; i < UINT8_MAX; i++)
//     {
//         if (firstIndexes[i]>=0)
//         {
//             res = min(res,firstIndexes[i]);
//         }

//     }
//     return (res==UINT16_MAX)?-1:res;

// }

// reverse words in a string
//  void StrReverse(string &str){
//      // string temp = s;
//      stack<string> s;
//      string temp = "";
//      for (int i = 0; i <= str.length(); i++)
//      {
//          if(str[i] == ' ' || i == str.length()){
//              s.push(temp+" ");
//              temp.clear();
//              continue;
//          }
//          temp = temp+str[i];

//     }
//     str.clear();
//     while (!s.empty())
//     {
//         str+=s.top();
//         s.pop();
//     }
// }

// void StrReverse_v2(char str[] , int n){
//     int start = 0;
//     for (int end = 0; end < n; end++)
//     {
//         if (str[end] == ' ') //traversing char by char which aren't spaces
//         {
//             // reverse(str,start,end-1);
//             reverse(str+start,str+end);
//             start=end+1;
//         }

//     }
//     reverse(str+start,str+n); //reversing the last word
//     reverse(str+0,str+n); //reversing the whole string

// }

// pattern searching in a string; algo-1 O((n-m+1)*m)
// void getPatternsIndex(string &str, string pat)
// {
//     uint_least16_t m = pat.length(), n = str.length();
//     for (int i = 0; i <= n - m; i++)
//     {
//         uint_fast16_t j = 0;
//         for (j = 0; j < m; j++)
//         {
//              /*checks whether the pattern and current string chars are in sync or not*/
//             if (pat[j] != str[i + j])
//             {
//                 break;
//             }
//         }
//         if (j == m) /* if j == m then it means the pattern(chars of patterns) is found in a consecutive manner*/
//         {
//             cout << i << " ";
//         }
//     }
// }

// algorithm 2 - improved naive solution
//  void getPatternIndex_v2(string &str , string pat){
//      uint_least16_t m = pat.length(), n = str.length();
//      for (int i = 0; i <= n - m;)
//      {
//          uint_fast16_t j = 0;
//          for (j = 0; j < m; j++)
//          {
//               /*checks whether the pattern and current string chars are in sync or not*/
//              if (pat[j] != str[i + j])
//              {
//                  break;
//              }
//          }
//          if (j == m) /* if j == m then it means the pattern(chars of patterns) is found in a consecutive manner*/
//          {
//              cout << i << " ";
//          }
//          if(j == 0){i++;}
//          else{i+=j;} //shifts the pattern window to j pos ahead(only for distinct chars in pat)
//      }
//      return;

// }

// rabin karp algorithm (hashing)
//  void getPatternIndex_v3(string &s , string pat){
/*AFTER LEARNING HASHMAPS🥱🥱*/
// }

// KMP algorithm pt 1: constructing longest proper prefix suffix array
// int longestProperSuffixArray(string &str, int n)
// {
//   for (int len = n - 1; len > 0; len--)
//   {
//     bool flag = true;
//     for (int i = 0; i < len; i++)
//     {
//       if (str[i] != str[n - len + i])
//       {
//         false;
//       }
//     }
//     if (flag == true)
//     {
//       return len;
//     }
//   }
//   return 0;
// }
// void fillLPS(string &str, int lps[])
// {
//   for (int i = 0; i < str.length(); i++)
//   {
//     lps[i] = longestProperSuffixArray(str, i + 1);
//   }
// }

// efficient approach for constructing lps
void fillLps_v2(string &str, int lps[])
{
  int n = str.length(), len = 0;
  lps[0] = 0;
  int i = 1;
  while (i < n)
  {
    if (str[i] == str[len])
    {
      len++;
      lps[i] = len;
      i++;
    }
    else
    {
      if (len == 0)
      {
        lps[i] = 0;
        i++;
      }
      else
      {
        len = lps[len - 1];
      }
    }
  }
}

// kmp algorithm implementation❇✳
void kmp(string &str, string pat)
{
  int N = str.length();
  int M = pat.length();
  int lps[M];
  fillLps_v2(pat, lps);
  int i = 0, j = 0;
  while (i < N)
  {
    if (pat[j] == str[i])
    {
      i++;
      j++;
    }
    else if (j == M)
    {
      cout << i - j << " ";
      j = lps[j - 1];
    }
    else if (i < N && pat[j] != str[i])
    {
      if (j == 0)
      {
        i++;
      }
      else
      {
        j = lps[j - 1];
      }
    }
  }
}

// bool checkRotated(string &str, string &rotatedString)
// {
//   if (str.length() != rotatedString.length())
//   {
//     return false;
//   }
//   return ((str + str).find(rotatedString) != string::npos); // add the string to itself to get a rotated string
// }

// anagram searching  O((n-m+1)*m)
// bool isPresent(string &txt, string &pat)
// {
//   uint_fast32_t n = txt.length(), m = pat.length();
//   for (int i = 0; i <= n - m; i++)
//   {
//     if (areAnagram(pat, txt, i))
//       return true;
//   }
//   return false
// }

// bool areAnagram(string &pat, string &txt, int i)
// {
//   vector<int> COUNT(UINT8_MAX, 0);
//   for (int j = 0; j < txt.length(); j++)
//   {
//     COUNT[pat[i]]++;
//     COUNT[txt[i + j]]--;
//   }
//   for (int j = 0; j < UINT8_MAX; j++)
//   {
//     if (COUNT[j] != 0)
//       return false;
//   }
//   return true;
// }

// efficient solution O(m+(n-m)*255)
// bool isPresent_v2(string &txt , string &pat){
//   vector<int> COUNTtxt(UINT8_MAX);
//   vector<int> COUNTpat(UINT8_MAX);
//   for (int i = 0; i < pat.length(); i++)
//   {
//     COUNTtxt[txt[i]]++;  /*creating frequency arrays for both txt and string */
//     COUNTpat[pat[i]]++;
//   }
//   for (int i = pat.length(); i < txt.length(); i++)
//   {
//     if(COUNTtxt == COUNTpat) //checks if the two vec are equal if they are then we have got our anagram
//       return true;
//     COUNTtxt[txt[i]]++; //adding last character to the window
//     COUNTtxt[txt[i-pat.length()]]--; //removing first char of the previous window
//   }

// }

// lexicographic rank of a string with distinct char O(n*255)
// int lexicographicRank(string &str)
// {
//   /*we calculate how many characters are smaller than str[0]
//   on the right side then str[1] and so on.after than we count all
//   the permutations of the chars smaller than str[0,1,...]*/
//   int res = 1;
//   uint_fast32_t n = str.length();
//   int multplierVar = fact(n);
//   vector<int> COUNT(UINT8_MAX);
//   for (int i = 0; i < n; i++)
//   {
//     COUNT[str[i]]++;
//   }
//   for (int i = 1; i < COUNT.size(); i++)
//   {
//     COUNT[i] += COUNT[i - 1]; // cumulative COUNT vector similar to prefix sum array to get the smaller char of right side
//   }
//   for (int i = 0; i < n - 1; i++)
//   {
//     multplierVar = multplierVar / (n - i);
//     res = res + COUNT[str[i] - 1] * multplierVar;
//     for (int j = str[i]; j < UINT8_MAX; j++) /*we remove the left char(which is fixed for the permutations) by decreasing count*/
//     {
//       COUNT[j]--;
//     }
//   }
//   return res;
// }


//longest substring with distinct characters O(n^3) time + O(n) space
// int longSubstr(string &s){
//   if(s.length() == 0)return 0;
//   if(s.length() == 1)return 1;
//   uint_fast16_t len = 0; 
//   for (int i = 0; i < s.length(); i++)
//   {
//     unordered_set<char> uniqueChar;
//     for (int j = i; j < s.length(); j++)
//     {
//       if (uniqueChar.find(s[j])==uniqueChar.end())
//       {
//         uniqueChar.insert(s[j]);
       
//         continue;
//       }
//       else{
//         break;
//       }
      
//     }
//     len = (len>uniqueChar.size())?len:uniqueChar.size();
    
//   }
//   return len;
// }


// int longSubstr_v2(string &str){
//   uint_fast16_t n = str.length();
//   int res = 0;
//   for (int i = 0; i < n; i++)
//   {
//     vector<bool> visited(256);
//     for (int j = i; j < n; j++)
//     {
//       if(visited[str[j]] == true)
//         break;
//       else
//       {
//         res = max(res,j - i + 1);
//         visited[str[j]] = true;
//       }
      
//     }
    
//   }
//   return res;
// }


//best solution O(n)
// int longSubStr_v3(string &str){
//   int n = str.length() , res = 0;
//   vector<int> prev(256,-1);
//   int i = 0;
//   for (int j = 0; j < n; j++)
//   {
//     i = max(i,prev[str[j]]+1);
//     int maxEnd = j - i + 1;
//     res = max(res,maxEnd);
//     prev[str[j]] = j;
//   }
//   return res;
// }
int main(int argc, char const *argv[])
{
  string str = "abaacdbab";
  char str1[] = "all of us are dead";
  string str2 = "silent";
  // frequencyOfcharacters(str);
  // cout<<isSubsequence(str,str2);
  // cout << areAnagram(str, str2);
  // cout<<getLeftmostRepeatingCHAR(str);
  // cout<<getLeftmostNonRepeatingCHAR(str);
  // StrReverse_v2(str1, strlen(str1));
  // getPatternIndex_v2(str, "eek");
  // kmp(str, "eek");
  // cout<<longSubstr(str);
  // cout << str1;
  return 0;
}
