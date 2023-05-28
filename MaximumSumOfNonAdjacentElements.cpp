// Stickler the thief wants to loot money from a society having n houses in a single line. He is a weird person and follows a certain rule when looting the houses. According to the rule, he will never loot two consecutive houses. At the same time, he wants to maximize the amount he loots. The thief knows which house has what amount of money but is unable to come up with an optimal looting strategy. He asks for your help to find the maximum money he can get if he strictly follows the rule. Each house has a[i]amount of money present in it.


//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

// } Driver Code Ends
class Solution
{
    public:
    
    //Recursion - TLE
    
    //going right to left
    int recursion(int arr[], int idx){
        //base case
        if(idx < 0){
            return 0;
        }
        
        if(idx == 0){
            return arr[0];
        }
        
        //include
        int incl = recursion(arr, idx - 2) + arr[idx];
        
        //exclude
        int excl = recursion(arr, idx - 1);
        
        return max(incl, excl);
    }
    
    // Recursion + Memoization
    
    int recurMEMO(int arr[], int idx, vector<int> &dp){
        //base case
        if(idx < 0){
            return 0;
        }
        
        if(idx == 0){
            return arr[0];
        }
        
        if(dp[idx] != -1){
            return dp[idx];
        }
        
        
        int incl = recurMEMO(arr, idx - 2, dp) + arr[idx];
        int excl = recurMEMO(arr, idx - 1, dp);
        
        return dp[idx] = max(incl, excl);
    }
    
    //Tabulation
    
    int tabulation(int arr[], int n){
        vector<int> dp(n, 0);
        dp[0] = arr[0];
        
        for(int i = 1; i < n; i++){
            int incl = dp[i - 2] + arr[i];
            int excl = dp[i - 1];
            dp[i] = max(incl, excl);
        }
        
        return dp[n - 1];
    }
    
    //Space Optimization
    
    int spaceOp(int arr[], int n){
        //since dp[i] is only dependent on dp[i - 2] & dp[i - 1]
        int prev2 = 0;
        int prev1 = arr[0];
        
        for(int i = 1; i < n; i++){
            int incl = prev2 + arr[i];
            int excl = prev1;
            
            int ans = max(incl, excl);
            
            prev2 = prev1;
            prev1 = ans;
        }
        
        return prev1;
    }
    
    int FindMaxSum(int arr[], int n)
    {
        //Method 1
        int ans = recursion(arr, n - 1);
        
        return ans;
        
        //Method 2
        vector<int> dp(n + 1, -1);
        
        int ans = recurMEMO(arr, n - 1, dp);
        
        return ans;
        
        //Method 3
        int ans = tabulation(arr, n);
        return ans;
        
        //Method 4 
        int ans = spaceOp(arr, n);
        return ans;
    }
};

//{ Driver Code Starts.
int main()
{
    //taking total testcases
	int t;
	cin>>t;
	while(t--)
	{
	    //taking number of houses
		int n;
		cin>>n;
		int a[n];
		
		//inserting money of each house in the array
		for(int i=0;i<n;++i)
			cin>>a[i];
		Solution ob;
		//calling function FindMaxSum()
		cout<<ob.FindMaxSum(a,n)<<endl;
	}
	return 0;
}

// } Driver Code Ends