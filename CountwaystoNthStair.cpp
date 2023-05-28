// There are N stairs, and a person standing at the bottom wants to reach the top. The person can climb either 1 stair or 2 stairs at a time. Count the number of ways, the person can reach the top (order does not matter).

// Recursion + Memomization

//{ Driver Code Starts
#include<bits/stdc++.h>
using namespace std;

// } Driver Code Ends
class Solution{
	public:
	    const int MOD = 1e9 + 7;
	    
	    int solve(int n, int dp[]){
	        //target condition
	        if(n == 0){
	            return 1;
	        }
	        
	        //base case
	        if(n < 0){
	            return 0;
	        }
	        
	        if(dp[n] != -1){
	            return dp[n];
	        }
	        
	        int one  = solve(n-1, dp);
	        int two  = solve(n-2, dp);
	       
	        return dp[n] = 1 + min(one, two);
	    }
	    
		int nthStair(int n){
		    int dp[n + 1];
		    memset(dp, -1, sizeof(dp));
		    return solve(n, dp);
		}
};

//{ Driver Code Starts.
int main(){
	int tc;
	cin >> tc;
	while(tc--){
		int n;
		cin >> n;
		Solution ob;
		int ans  = ob.nthStair(n);
		cout << ans <<"\n";
	}
	return 0;
}
// } Driver Code Ends