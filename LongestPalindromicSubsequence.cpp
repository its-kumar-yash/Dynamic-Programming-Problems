//LC 516

// Given a string s, find the longest palindromic subsequence's length in s.

// A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.


//{ Driver Code Starts
//Initial template for C++

#include<bits/stdc++.h>
using namespace std;


// } Driver Code Ends
//User function Template for C++

class Solution{
  public:
    int n;
    
    //Recursion
    int solve(string a, string b, int i, int j){
        if(i >= n || j >= n){
            return 0;
        }
        
        int ans = 0;
        if(a[i] == b[j]){
            ans = 1 + solve(a, b, i + 1, j + 1);
        }
        
        else{
            ans = max(solve(a, b, i + 1, j), solve(a, b, i, j + 1)); 
        }
        
        return ans;
    }
    
    //Recursion + MEMO
    int recurMEMO(string a, string b, int i, int j, vector<vector<int>> &dp){
        if(i >= n || j >= n){
            return 0;
        }
        
        if(dp[i][j] != -1){
            return dp[i][j];
        }
        
        int ans = 0;
        if(a[i] == b[j]){
            ans = 1 + solve(a, b, i + 1, j + 1);
        }
        
        else{
            ans = max(solve(a, b, i + 1, j), solve(a, b, i, j + 1)); 
        }
        
        return dp[i][j] = ans;
    }
    
    //Tabulation
    int tabulation(string a, string b){
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        
        for(int i = n - 1; i >= 0; i--){
            for(int j = n - 1; j >= 0; j--){
                int ans = 0;
                if(a[i] == b[j]){
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
    int spaceOp(string a, string b){
        vector<int> curr(n + 1, 0);
        vector<int> next(n + 1, 0);
        
        for(int i = n - 1; i >= 0; i--){
            for(int j = n - 1; j >= 0; j--){
                int ans = 0;
                if(a[i] == b[j]){
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
    
    
    
    int longestPalinSubseq(string A) {
        n = A.length();
        
        string B = A;
        reverse(B.begin(), B.end());
        
        //Method 1
        return solve(A, B, 0, 0);
        
        //Method 2
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, - 1));
        
        return recurMEMO(A, B, 0, 0, dp);
        
        //Method 3
        return tabulation(A, B);
        
        //Method 4
        return spaceOp(A, B);
    }
};

//{ Driver Code Starts.

int32_t main()
{
    int t; cin >> t;
    while (t--)
    {
        string s; cin >> s;
        Solution ob;
        cout << ob.longestPalinSubseq(s) << endl;
    }
}
// Contributed By: Pranay Bansal

// } Driver Code Ends