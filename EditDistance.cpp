//LC - 72

// Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

// You have the following three operations permitted on a word:

// Insert a character
// Delete a character
// Replace a character


//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution {
  public:
    int n, m;
    
    //Recursion
    int solve(string s, string t, int i, int j){
        //when first string exhausted, remaining operations will be insert
        if(i == n){
            return m - j;
        }
        //when second string exhausted, remaining operations will be insert
        if(j == m){
            return n - i;
        }
        
        //when character matches, call for remaining string
        int ans = 0;
        if(s[i] == t[j]){
            return solve(s, t, i + 1, j + 1);
        }
        else{
            //when character does not match
            //try all three operations
            //and take the minimum one
            
            //Insert
            int insertAns = 1 + solve(s, t, i, j + 1);
            
            //Delete
            int deleteAns = 1 + solve(s, t, i + 1, j);
            
            //Replace
            int replaceAns = 1 + solve(s, t, i + 1, j + 1);
            
            ans = min({insertAns, deleteAns, replaceAns});
        }
        
        return ans;
    }
    
    //Recursion + MEMO
    int recurMEMO(string s, string t, int i, int j, vector<vector<int>> &dp){
        if(i == n){
            return m - j;
        }
        //when second string exhausted, remaining operations will be insert
        if(j == m){
            return n - i;
        }
        
        if(dp[i][j] != -1){
            return dp[i][j];
        }
        
        //when character matches, call for remaining string
        int ans = 0;
        if(s[i] == t[j]){
            return dp[i][j] = recurMEMO(s, t, i + 1, j + 1, dp);
        }
        else{
            //when character does not match
            //try all three operations
            //and take the minimum one
            
            //Insert
            int insertAns = 1 + recurMEMO(s, t, i, j + 1, dp);
            
            //Delete
            int deleteAns = 1 + recurMEMO(s, t, i + 1, j, dp);
            
            //Replace
            int replaceAns = 1 + recurMEMO(s, t, i + 1, j + 1, dp);
            
            ans = min({insertAns, deleteAns, replaceAns});
        }
        
        return dp[i][j] = ans;
    }
    
    //Tabulation
    int tabulation(string s, string t){
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        
        //Base case analysis
        
        for(int j = 0; j < m; j++){
            dp[n][j] = m - j;
        }
        
        for(int i = 0; i < n; i++){
            dp[i][m] = n - i;
        }
        
        
        
        for(int i = n - 1; i >=0; i--){
            for(int j = m - 1; j >= 0; j--){
                int ans = 0;
                if(s[i] == t[j]){
                    ans = dp[i + 1][j + 1];
                }
                else{
                    //when character does not match
                    //try all three operations
                    //and take the minimum one
                    
                    //Insert
                    int insertAns = 1 + dp[i][j + 1];
                    
                    //Delete
                    int deleteAns = 1 + dp[i + 1][j];
                    
                    //Replace
                    int replaceAns = 1 + dp[i + 1][j + 1];
                    
                    ans = min({insertAns, deleteAns, replaceAns});
                }
                
                dp[i][j] = ans;
            }
        }
        
        return dp[0][0];
    }
    
    //Space Optimization
    int spaceOp(string s, string t){
        vector<int> curr(m + 1, 0);
        vector<int> next(m + 1, 0);
        
        //Base case analysis
        
        for(int j = 0; j < m; j++){
            next[j] = m - j;
        }
        
        
        for(int i = n - 1; i >=0; i--){
            for(int j = m - 1; j >= 0; j--){
                int ans = 0;
                
                //MOST IMP PART Using Base CAse
                curr[m] = n - i;
                
                
                
                if(s[i] == t[j]){
                    ans = next[j + 1];
                }
                else{
                    //when character does not match
                    //try all three operations
                    //and take the minimum one
                    
                    //Insert
                    int insertAns = 1 + curr[j + 1];
                    
                    //Delete
                    int deleteAns = 1 + next[j];
                    
                    //Replace
                    int replaceAns = 1 + next[j + 1];
                    
                    ans = min({insertAns, deleteAns, replaceAns});
                }
                
                curr[j] = ans;
            }
            next = curr;
        }
        
        return curr[0];
    }
    
    int editDistance(string s, string t) {
        n = s.length();
        m = t.length();
        
        if(n == 0){
            return m;
        }
        if(m == 0){
            return n;
        }

        //Method 1
        return solve(s, t, 0, 0);
        
        //Method 2
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
        
        return recurMEMO(s, t, 0, 0, dp);
        
        //Method 3
        return tabulation(s, t);
        
        //Method 4
        return spaceOp(s, t);
    }
};

//{ Driver Code Starts.
int main() {
    int T;
    cin >> T;
    while (T--) {
        string s, t;
        cin >> s >> t;
        Solution ob;
        int ans = ob.editDistance(s, t);
        cout << ans << "\n";
    }
    return 0;
}

// } Driver Code Ends