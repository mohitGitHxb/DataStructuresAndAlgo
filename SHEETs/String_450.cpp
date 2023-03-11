#include <bits/stdc++.h>
using namespace std;

//^ 1 Reverse the string;
void reverseString(string &s){
    reverse(s.begin(), s.end());
}

//^ 2 Palindrome string
bool checkPalindrome(string &s){
    int low = 0, high = s.length() - 1;
    while(low < high){
        if(s[low]!= s[high])
            return false;
        low++;
        high--;
    }
    return true;
}

//^ 3 Duplicate character in a string
void duplicatesInString(string &s){
    vector<int> hash(255);
    for(int i = 0; i < s.length(); i++){
        hash[s[i]]++;
    }
    string ans = "";
    for(int i = 0; i < 255; i++){
        if(hash[i] > 0){
            ans.push_back((char)hash[i]);
        }
    }
    cout << ans;

}

int main(){
    string str = "RiCantSnipe";
    duplicatesInString(str);
    return 0;
}