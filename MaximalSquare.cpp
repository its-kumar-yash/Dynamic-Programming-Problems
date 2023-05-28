// LC - 221

//Given a binary matrix mat of size n * m, find out the maximum size square sub-matrix with all 1s.

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++

class Solution{
public:
    //Recursion
    int solve(vector<vector<int>> &mat, int i, int j, int &maxi){
        //base case
        if(i >= mat.size() || j >= mat[0].size()){
            return 0;
        }
        
        //Check three direction
        int right = solve(mat, i, j + 1, maxi);
        int diagonal = solve(mat, i + 1, j + 1, maxi);
        int down = solve(mat, i + 1, j, maxi);
        
        //now check if the current cell is 1 or not
        if(mat[i][j] == 1){
            //find minimum of three answers
            int ans = 1 + min({right, diagonal, down});
            //update maxi
            maxi = max(maxi, ans);
            
            return ans;
        }
        else{
            return 0;
        }
    }
    
    //Recursion + MEMO
    int recurMEMO(vector<vector<int>> &mat, int i, int j, int &maxi, vector<vector<int>> &dp){
        if(i >= mat.size() || j >= mat[0].size()){
            return 0;
        }
        
        if(dp[i][j] != -1){
            return dp[i][j];
        }
        
        //Check three direction
        int right = recurMEMO(mat, i, j + 1, maxi, dp);
        int diagonal = recurMEMO(mat, i + 1, j + 1, maxi, dp);
        int down = recurMEMO(mat, i + 1, j, maxi, dp);
        
        if(mat[i][j] == 1){
            //find minimum of three answers
            dp[i][j] = 1 + min({right, diagonal, down});
            //update maxi
            maxi = max(maxi, dp[i][j]);
            
            return dp[i][j];
        }
        else{
            return dp[i][j] = 0;
        }
    }

    //Tabulation
    
    int tabulation(vector<vector<int>> &mat, int &n, int &m, int &maxi){
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        
        dp[n][m] = 0;
        
        for(int row = n - 1; row >= 0; row--){
            for(int col = m - 1; col >= 0; col--){
                int right = dp[row][col + 1];
                int diagonal = dp[row + 1][col + 1];
                int down = dp[row + 1][col];
                
                if(mat[row][col] == 1){
                    dp[row][col] = 1 + min({right, diagonal, down});
                    maxi = max(maxi, dp[row][col]);
                }
                else{
                    dp[row][col] = 0;
                }
            }
        }
        
        return dp[0][0];
    }
    
    //Space Optimization
    
    int spaceOP(vector<vector<int>> &mat, int &n, int &m, int &maxi){
        vector<int> curr(m + 1, 0); 
        vector<int> next(m + 1, 0);
        
        for(int i = n - 1; i >= 0; i--){
            for(int j = m - 1; j >= 0; j--){
                int right = curr[j + 1];
                int diagonal = next[j + 1];
                int down = next[j];
                
                if(mat[i][j] == 1){
                    curr[j] = 1 + min({right, diagonal, down});
                    maxi = max(maxi, curr[j]);
                }
                else{
                    curr[j] = 0;
                }
            }
            
            next = curr;
        }
        
        return next[0];
    }
    
    
    
    int maxSquare(int n, int m, vector<vector<int>> mat){
        //Method 1
        int maxi = 0;
        solve(mat, 0, 0, maxi);
        return maxi;
        
        //Method 2
        vector<vector<int>> dp(n, vector<int>(m, -1));
        
        int maxi = 0;
        recurMEMO(mat, 0, 0, maxi, dp);
        return maxi;
        
        //Method 3
        int maxi = 0;
        tabulation(mat, n, m, maxi);
        return maxi;
        
        //Method 4
        int maxi = 0;
        spaceOP(mat, n, m, maxi);
        return maxi;
        
    }
};

//{ Driver Code Starts.

int main(){
    int t;
    cin>>t;
    while(t--){
        int n, m;
        cin>>n>>m;
        vector<vector<int>> mat(n, vector<int>(m, 0));
        for(int i = 0;i < n*m;i++)
            cin>>mat[i/m][i%m];
        
        Solution ob;
        cout<<ob.maxSquare(n, m, mat)<<"\n";
    }
    return 0;
}
// } Driver Code Ends