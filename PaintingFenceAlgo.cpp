// Given a fence with n posts and k colors, find out the number of ways of painting the fence so that not more than two consecutive posts have the same colors. Since the answer can be large return it modulo 10^9 + 7.

//{ Driver Code Starts
#include <bits/stdc++.h>
#include<stdio.h>
#include<math.h>
using namespace std;

// } Driver Code Ends
class Solution{
    public:
    const int MOD = 1e9 + 7;
    
    //Recursion
    
    long long recursion(int n, int k){
        
        //base case
        //for painting 1 post we have k options
        if(n == 1){
            return k;
        }
        
        if(n == 2){
            return (k%MOD + (k * (k - 1))%MOD)%MOD; // k + (k * (k - 1))
        }
        
        
        long long same = ((k - 1) * recursion(n - 2, k))%MOD;
        long long diff = ((k - 1) * recursion(n - 1, k))%MOD;
        
        long long ans = (same + diff)%MOD;
        
        return ans;
    }
    
    //Recursion + MEMO
    
    long long recurMEMO(int n, int k, vector<long long> &dp){
        //base case
        //for painting 1 post we have k options
        if(n == 1){
            return k;
        }
        
        if(n == 2){
            return (k%MOD + (k * (k - 1))%MOD)%MOD; // k + (k * (k - 1))
        }
        
        if(dp[n] != -1){
            return dp[n];
        }
        
        long long same = ((k - 1) * recurMEMO(n - 2, k, dp))%MOD;
        long long diff = ((k - 1) * recurMEMO(n - 1, k, dp))%MOD;
        
        dp[n] = (same + diff)%MOD;
        
        return dp[n];
    }
    
    //Tabulation
    long long tabulation(int n, int k){
        vector<long long> dp(n + 1, 0);
        
        dp[1] = k;
        dp[2] = (k%MOD + (k * (k - 1))%MOD)%MOD;
        
        //for every post
        for(int i = 3; i <= n; i++){
            long long same = ((k - 1) * dp[i - 2])%MOD;
            long long diff = ((k - 1) * dp[i - 1])%MOD;
            
            dp[i] = (same + diff)%MOD;
        }
        
        return dp[n];
    }
    
    //Space Optimization
    
    long long spaceOp(int n, int k){
        if(n == 1){
            return k;
        }
        
        if(n == 2){
            return (k%MOD + (k * (k - 1))%MOD)%MOD;
        }
        //dp[i] is dependent on dp[i - 1] & dp[i - 2]
        long long prev2 = k;
        long long prev1 = (k%MOD + (k * (k - 1))%MOD)%MOD;
        
        for(int i = 3; i <= n; i++){
            long long same = ((k - 1) * prev2)%MOD;
            long long diff = ((k - 1) * prev1)%MOD;
            
            long long curr = (same + diff)%MOD;
            
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1;
    }
    
    
    long long countWays(int n, int k){
        //Method 1
        return recursion(n, k);
        
        //Method 2
        vector<long long> dp(n + 1, -1);
        
        return recurMEMO(n, k, dp);
        
        //Method 3
        
        return tabulation(n, k);
        
        //Method 4
        return spaceOp(n, k);
    }
};

//{ Driver Code Starts.

int main()
{
	
	int t;
	cin>>t;
	while(t--)
	{
		int n,k;
		cin>>n>>k;
		Solution ob;
		cout<<ob.countWays(n,k)<<endl;
	}
	return 0;
}
// } Driver Code Ends