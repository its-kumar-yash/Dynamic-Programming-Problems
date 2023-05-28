//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution{

	public:
	//Recursion - TLE
	int recursion(int coins[], int M, int target){
	    //base case
	    if(target == 0){
	        return 0;
	    }    
	    
	    if(target < 0){
	        return INT_MAX;
	    }
	       
	       
	    int mini = INT_MAX;
	    //check for every coin
	    for(int i = 0; i < M; i++){
	        
	        int ans = recursion(coins, M, target - coins[i]);
	        
	        if(ans != INT_MAX){
	            // adding current coin
	            mini = min(mini, 1 + ans);
	        }
	    }
	    
	    return mini;
	}
	
	// Recursion + Memoization
	
	int recursionMEMO(int coins[], int M, int target, vector<int> &dp){
	    
	    if(target == 0){
	        return 0;
	    }
	    
	    if(target < 0){
	        return INT_MAX;
	    }
	    
	    if(dp[target] != -1){
	        return dp[target];
	    } 
	    
	    int mini = INT_MAX;
	    
	    for(int i = 0; i < M; i++){
	        int ans = recursionMEMO(coins, M, target - coins[i], dp);
	        
	        if(ans != INT_MAX){
	            mini = min(mini, 1 + ans);
	        }
	    }
	    
	    dp[target] = mini;
	    
	    return mini;
	}
	
	//Tabulation - bottom up
	
	int tabulation(int coins[], int M, int target){
	    vector<int> dp(target + 1, INT_MAX);
	    
	    dp[0] = 0;
	    
	    for(int i = 1; i <= target; i++){
	        //solve every amt from 1 to target
	        for(int j = 0; j < M; j++){
	            if(i - coins[j] >= 0 && dp[i - coins[j]] != INT_MAX){
	               dp[i] = min(dp[i], 1 + dp[i - coins[j]]);
	            }
	            
	        }
	    }
	    
	    if(dp[target] == INT_MAX){
	        return -1;
	    }
	    
	    return dp[target];
	}
	
	
	int minCoins(int coins[], int M, int V) 
	{ 
	   //Method 1
	   int res = recursion(coins, M, V);
	    
	   if(res == INT_MAX){
	       return -1;
	   }
	    
	   return res;
	   
	   //Method 2
	   vector<int> dp(V + 1, -1);
	   
	   int res = recursionMEMO(coins, M, V, dp);
	   if(res == INT_MAX){
	       return -1;
	   }
	    
	   return res;
	   
	   //Method 3
	   return tabulation(coins, M, V);
	} 
	  
};

//{ Driver Code Starts.
int main() 
{
   
   
   	int t;
    cin >> t;
    while (t--)
    {
        int v, m;
        cin >> v >> m;

        int coins[m];
        for(int i = 0; i < m; i++)
        	cin >> coins[i];

      
	    Solution ob;
	    cout << ob.minCoins(coins, m, v) << "\n";
	     
    }
    return 0;
}

// } Driver Code Ends