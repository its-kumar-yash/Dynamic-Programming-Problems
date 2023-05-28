// Given an integer N denoting the Length of a line segment. You need to cut the line segment in such a way that the cut length of a line segment each time is either x , y or z. Here x, y, and z are integers.
// After performing all the cut operations, your total number of cut segments must be maximum.

// Note: if no segment can be cut then return 0.


//{ Driver Code Starts
#include<bits/stdc++.h>
using namespace std;



// } Driver Code Ends
class Solution
{
    public:
    //Recursion - TLE
    int recursion(int n, int &x, int &y, int &z){
        //base case
        if(n == 0){
            return 0;
        }
        
        if(n < 0){
            return INT_MIN;
        }
        
        //try all possibilities
        //plus 1 to consider curr segment
        int ans1 = recursion(n - x, x, y, z) + 1; 
        int ans2 = recursion(n - y, x, y, z) + 1;
        int ans3 = recursion(n - z, x, y, z) + 1;
        
        int maxi = max(ans1, max(ans2, ans3));
        return maxi;
    }
    
    //Recursion + Memoization
    int recurMEMO(int n, int &x, int &y, int &z, vector<int> &dp){
        //base case
        if(n == 0){
            return 0;
        }
        
        if(n < 0){
            return INT_MIN;
        }
        
        if(dp[n] != -1){
            return dp[n];
        }
        
        //try all possibilities
        //plus 1 to consider curr segment
        int ans1 = recurMEMO(n - x, x, y, z, dp) + 1; 
        int ans2 = recurMEMO(n - y, x, y, z, dp) + 1;
        int ans3 = recurMEMO(n - z, x, y, z, dp) + 1;
        
        dp[n] = max(ans1, max(ans2, ans3));
        return dp[n];
    }
    
    //Tabulation
    
    int tabulation(int n, int &x, int &y, int &z){
        vector<int> dp(n + 1, -1);
        
        dp[0] = 0;
        
        //for every length of rod
        for(int i = 1; i <= n; i++){
            if(i - x >= 0 && dp[i - x] != -1){
                dp[i] = max(dp[i], dp[i - x] + 1);
            }
            if(i - y >= 0 && dp[i - y] != -1){
                dp[i] = max(dp[i], dp[i - y] + 1); 
            }
            if(i - z >= 0 && dp[i - z] != -1){
                dp[i] = max(dp[i], dp[i - z] + 1);
            }
            
            
            // dp[i] = max({ans1, ans2, ans3});
        }
        
        if(dp[n] < 0){
            return 0;
        }
        
        return dp[n];
    }
    
    
    //Function to find the maximum number of cuts.
    int maximizeTheCuts(int n, int x, int y, int z)
    {   
        //Method 1
        int ans = recursion(n, x, y, z);
        if(ans == INT_MIN){
            return 0;
        }
        
        return ans;
        
        //Method 2
        vector<int> dp(n + 1, -1);
        int ans = recurMEMO(n, x, y, z, dp);
        if(ans < 0){
            return 0;
        }
        
        return ans;
        
        
        //Method 3
        int ans = tabulation(n, x, y, z);
        
        return ans;
        
        
         
        //Method 4
        //NOT POSSIBLE
    }
};

//{ Driver Code Starts.
int main() {
    
    //taking testcases
    int t;
    cin >> t;
    while(t--)
    {
        //taking length of line segment
        int n;
        cin >> n;
        
        //taking types of segments
        int x,y,z;
        cin>>x>>y>>z;
        Solution obj;
        //calling function maximizeTheCuts()
        cout<<obj.maximizeTheCuts(n,x,y,z)<<endl;

    }

	return 0;
}
// } Driver Code Ends