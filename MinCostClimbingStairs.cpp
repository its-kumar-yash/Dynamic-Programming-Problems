//{ Driver Code Starts
//Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    //Recursion - TLE
    int solve(int N, vector<int> &cost){
        //base case
        if(N == 0){
            return cost[0];
        }
        
        if(N == 1){
            return cost[1];
        }
        
        
        int minCost = cost[N] + min(solve(N - 1, cost), solve(N - 2, cost));
        
        return minCost;
    }
    
    //Top - Down Approach - Recursion + Memo
    // TC - O(N)
    // SC - O(N) + O(N)
    
    int solve1(int N, vector<int> &cost, vector<int> &dp){
        //base Case remains same
        if(N == 0){
            return cost[0];
        }
        
        if(N == 1){
            return cost[1];
        }
        
        //Step 3
        if(dp[N] != -1){
            return dp[N];        
            
        }
        
        //Step 2
        dp[N] = cost[N] + min(solve1(N - 1, cost, dp), solve1(N - 2, cost, dp));
        
        return dp[N];
    }
    
    //Bottom - Up Approach - Tabulation
    // TC - O(N)
    // SC - O(N)
    
    int solve2(int N, vector<int> &cost){
        //creating dp array
        vector<int> dp(N + 1, -1);
        //analysing base case
        dp[0] = cost[0];
        dp[1] = cost[1];
        
        for(int i = 2; i < N; i++){
            dp[i] = cost[i] + min(dp[i - 1], dp[i - 2]);
        }
        
        return min(dp[N - 1], dp[N - 2]);
    }
    
    //Space Optimization
    // TC - O(N)
    // SC - O(1)

    int solve3(int N, vector<int> &cost){
        int prev2 = cost[0];
        int prev1 = cost[1];
        
        for(int i = 2; i < N; i++){
            int curr = cost[i] + min(prev1, prev2);
            prev2 = prev1;
            prev1 = curr;
        }
        
        return min(prev1, prev2);
    }
  
    int minCostClimbingStairs(vector<int>&cost ,int N) {
        //Method 1
        return min(solve(N - 1, cost), solve(N - 2, cost));
        
        //Method 2
        //STEP 1
        vector<int> dp(N + 1, -1);
        
        return min(solve1(N - 1, cost, dp), solve1(N - 2, cost, dp));
        
        // Method 3
        return solve2(N, cost);
        
        //Method 4
        return solve3(N, cost);
    }
};

//{ Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {
        int N;
        
        cin>>N;
        vector<int>cost(N);
        
        for(int i=0 ; i<N ; i++){
            cin>>cost[i];
        }

        Solution ob;
        cout<<ob.minCostClimbingStairs(cost,N);
        cout<<"\n";
    }
    return 0;
}
// } Driver Code Ends