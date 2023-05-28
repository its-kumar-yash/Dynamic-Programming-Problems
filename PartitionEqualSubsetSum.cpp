// Given an integer array nums, return true if you can partition the array into two subsets such that the sum of the elements in both subsets is equal or false otherwise.

//LC - 416. Partition Equal Subset Sum
 //{ Driver Code Starts
// Initial Template for C++

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++

class Solution{
public:
    //Recursion - TLE
    int solve(int idx, int a[], int n, int target){
        //base case
        if(idx >= n){
            return 0; // target not acheived
        }
        if(target < 0){
            return 0;
        }
        //target condition
        if(target == 0){
            return 1;
        }
        
        //for every element we have two options
        //include or exclude
        
        int incl = solve(idx + 1, a, n, target - a[idx]);
        int excl = solve(idx + 1, a, n, target);
        
        //if any one of the call give true we find the answer 
        return incl || excl;
    }
    
    //Recursion + Memoization
    int recurMEMO(int idx, int a[], int n, int target, vector<vector<int>> &dp){
        //base case
        if(idx >= n){
            return 0; // target not acheived
        }
        if(target < 0){
            return 0;
        }
        //target condition
        if(target == 0){
            return 1;
        }
        
        if(dp[idx][target] != -1){
            return dp[idx][target];
        }
        
        int incl = recurMEMO(idx + 1, a, n, target - a[idx], dp);
        int excl = recurMEMO(idx + 1, a, n, target, dp);
        
        return dp[idx][target] = incl || excl;
    }
    
    //Tabulation
    int tabulation(int idx, int a[], int n, int target){
        vector<vector<int>> dp(n + 1, vector<int>(target + 1, 0));
        
        //target condition
        for(int i = 0; i <= n; i++){
            dp[i][0] = 1;
        }
        
        for(int idx = n - 1; idx >= 0; idx--){
            for(int t = 0; t <= target; t++){
                int incl = 0;
                if(t - a[idx] >= 0){
                    incl = dp[idx + 1][t - a[idx]]; 
                }
                
                int excl = dp[idx + 1][t];
                
                dp[idx][t] = incl || excl;
            }
        }
        
        return dp[0][target];
    }
    
    //Space Optimization
    int spaceOP(int idx, int a[], int n, int target){
        vector<int> curr(target + 1, 0);
        vector<int> next(target + 1, 0);
        
        //base case analysis
        curr[0] = 1;
        next[0] = 1;
        
        for(int idx = n - 1; idx >= 0; idx--){
            for(int t = 0; t <= target; t++){
                int incl = 0;
                if(t - a[idx] >= 0){
                    incl = next[t - a[idx]]; 
                }
                
                int excl = next[t];
                
                curr[t] = incl || excl;
            }
            next = curr;
        }
        
        return curr[target];
    }
    
    int equalPartition(int N, int arr[])
    {
        //find total sum
        int totalSum = 0;
        for(int i = 0; i < N; i++){
            totalSum += arr[i];
        }
        
        //if total sum is odd -> parition is not possible
        if(totalSum & 1){
            return 0;
        }
        
        //for even -> target for partition will be sum/2
        int target = totalSum/2;
        
        //Method 1
        return solve(0, arr, N, target);
        
        //Method 2
        vector<vector<int>> dp(N + 1, vector<int>(target + 1, -1));
        
        return recurMEMO(0, arr, N, target, dp);
        
        //Method 3
        return tabulation(0, arr, N, target);
        
        //Method 4
        return spaceOP(0, arr, N, target);
    }
};

//{ Driver Code Starts.

int main(){
    int t;
    cin>>t;
    while(t--){
        int N;
        cin>>N;
        int arr[N];
        for(int i = 0;i < N;i++)
            cin>>arr[i];
        
        Solution ob;
        if(ob.equalPartition(N, arr))
            cout<<"YES\n";
        else
            cout<<"NO\n";
    }
    return 0;
}
// } Driver Code Ends