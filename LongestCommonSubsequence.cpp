//LC - 1143

// Given two strings text1 and text2, return the length of their longest common subsequence. If there is no common subsequence, return 0.

// A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

// For example, "ace" is a subsequence of "abcde".
// A common subsequence of two strings is a subsequence that is common to both strings.

//{ Driver Code Starts
#include<bits/stdc++.h>
const int mod=1e9+7;
using namespace std;

// } Driver Code Ends
// function to find longest common subsequence

class Solution
{
    public:
    int n, m;
    
    //Recursion - TLE
    int solve(string s1, string s2, int i, int j){
        //base case
        if(i >= n || j >= m){
            return 0;
        }
        
        //target condition
        //when two character matches
        if(s1[i] == s2[j]){
            return 1 + solve(s1, s2, i + 1, j + 1);
        }
        else{
            //when donot match
            //try both possible ways 
            //and take the max answer
            return max(solve(s1, s2, i + 1, j), solve(s1, s2, i, j + 1));
        }
    }
    
    //Recursion + MEMO
    int recurMEMO(string s1, string s2, int i, int j, vector<vector<int>> dp){
        if(i >= n || j >= m){
            return 0;
        }
        
        if(dp[i][j] != -1){
            return dp[i][j];
        }
        int ans = 0;
        if(s1[i] == s2[j]){
            ans = 1 + recurMEMO(s1, s2, i + 1, j + 1, dp);
        }
        else{
            ans = max(recurMEMO(s1, s2, i + 1, j, dp), recurMEMO(s1, s2, i, j + 1, dp));
        }
        
        return dp[i][j] = ans;
    }
    
    //Tabulation
    int tabulation(string s1, string s2){
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        
        for(int i = n - 1; i >= 0; i--){
            for(int j = m - 1; j >= 0; j--){
                int ans = 0;
                if(s1[i] == s2[j]){
                    ans = 1 + dp[i + 1][j + 1];
                }
                else{
                    ans = max(dp[i + 1][j], dp[i][j + 1]);
                }
                
                dp[i][j] = ans;
            }
        }
        
        return dp[0][0];
    }
    
    //Space Optimization
    int spaceOp(string s1, string s2){
        vector<int> curr(m + 1, 0);
        vector<int> next(m + 1, 0);
        
        for(int i = n - 1; i >= 0; i--){
            for(int j = m - 1; j >= 0; j--){
                int ans = 0;
                if(s1[i] == s2[j]){
                    ans = 1 + next[j + 1];
                }
                else{
                    ans = max(next[j], curr[j + 1]);
                }
                
                curr[j] = ans;
            }
            next = curr;
        }
        
        return curr[0];
    }
    
    
    //Function to find the length of longest common subsequence in two strings.
    int lcs(int x, int y, string s1, string s2)
    {
        n = x;
        m = y;
        
        //Method 1
        return solve(s1, s2, 0, 0);
        
        //Method 2
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
        
        return recurMEMO(s1, s2, 0, 0, dp);
        
        //Method 3
        return tabulation(s1, s2);
        
        //Method 4
        return spaceOp(s1, s2);
    }
};


//{ Driver Code Starts.
int main()
{
    int t,n,k,x,y;
    cin>>t;
    while(t--)
    {
        cin>>x>>y;          // Take size of both the strings as input
        string s1,s2;
        cin>>s1>>s2;        // Take both the string as input
        Solution ob;
        cout << ob.lcs(x, y, s1, s2) << endl;
    }
    return 0;
}

// } Driver Code Ends