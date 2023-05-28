//LC - 1218 Longest Arithmetic Subsequence of Given Difference

// Given an integer array arr and an integer difference, return the length of the longest subsequence in arr which is an arithmetic sequence such that the difference between adjacent elements in the subsequence equals difference.

// A subsequence is a sequence that can be derived from arr by deleting some or no elements without changing the order of the remaining elements.

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        int ans = 0;
        int n = arr.size();

        unordered_map<int, int> dp;

        for(int i = 0; i < n; i++){
            int temp = arr[i] - difference; //element behind

            //search for temp in the map and extract the value
            int storedAns = 0;
            if(dp.count(temp)){
                storedAns = dp[temp];
            }

            //update current ans
            dp[arr[i]] = 1 + storedAns;

            //update ans
            ans = max(ans, dp[arr[i]]);
        }

        return ans;
    }
};

int main(){
    
    return 0;
}
 