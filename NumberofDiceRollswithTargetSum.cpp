// 1155. Number of Dice Rolls With Target Sum

//You have n dice, and each die has k faces numbered from 1 to k.

// Given three integers n, k, and target, return the number of possible ways (out of the kn total ways) to roll the dice, so the sum of the face-up numbers equals target. Since the answer may be too large, return it modulo 109 + 7.

//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution {
  public:
    //Recursion - TLE
    long long solve(int dice, int face, int target){
        //base case
        if(target < 0){
            return 0;
        }
        if(dice == 0 && target != 0){
            return 0;
        }
        if(target == 0 && dice != 0){
            return 0;
        }
        if(target == 0 && dice == 0){
            return 1;
        }
        
        
        //try every possible possibility of dice
        long long ans = 0;
        for(int f = 1; f <= face; f++){
            ans = ans + solve(dice - 1, face, target - f);
        }
        
        return ans;
    }
    
    //Recursion + MEMO 
    
    long long recurMEMO(int dice, int face, int target, vector<vector<long long>> &dp){
        //base case
        if(target < 0){
            return 0;
        }
        if(target == 0 && dice != 0){
            return 0;
        }
        if(dice == 0 && target != 0){
            return 0;
        }
        if(dice == 0 && target == 0){
            return 1;
        }
        
        if(dp[dice][target] != -1){
            return dp[dice][target];
        }
        
        long long ans = 0;
        
        for(int f = 1; f <= face; f++){
            ans = ans + recurMEMO(dice - 1, face, target - f, dp);
        }
        
        dp[dice][target] = ans;
        
        return dp[dice][target];
    }
    
    //Tabulation
    
    long long tabulation(int dice, int face, int target){
        vector<vector<long long>> dp(dice + 1, vector<long long>(target + 1, 0));
        dp[0][0] = 1;
        
        for(int d = 1; d <= dice; d++){
            for(int t = 1; t <= target; t++){
                long long ans = 0;        
                for(int f = 1; f <= face; f++){
                    if(t - f >= 0){
                       ans = ans + dp[d - 1][t - f];  
                    }
                }
                dp[d][t] = ans; 
            }
        }
        
        return dp[dice][target];
    }
    
    //Space Optimization
    
    long long spaceOP(int dice, int face, int target){
        vector<long long> prev(target + 1, 0);
        vector<long long> curr(target + 1, 0);
        
        prev[0] = 1;
        
        for(int d = 1; d <= dice; d++){
            for(int t = 1; t <= target; t++){
                long long ans = 0;        
                for(int f = 1; f <= face; f++){
                    if(t - f >= 0){
                       ans = ans + prev[t - f];  
                    }
                }
                curr[t] = ans; 
            }
            prev = curr;
        }
        
        return prev[target];
    }
  
    long long noOfWays(int M , int N , int X) {
        //Method 1
        return solve(N, M, X);
        
        //Method 2
        vector<vector<long long>> dp(N + 1, vector<long long>(X + 1, -1));
        
        return recurMEMO(N, M, X, dp);
        
        //Method 3
        return tabulation(N, M, X);
        
        //Method 4
        return spaceOP(N, M, X);
    }
};

//{ Driver Code Starts.
int main() {
    int t;
    cin >> t;
    while (t--) {
        int M,N,X;
        
        cin>>M>>N>>X;

        Solution ob;
        cout << ob.noOfWays(M,N,X) << endl;
    }
    return 0;
}
// } Driver Code Ends