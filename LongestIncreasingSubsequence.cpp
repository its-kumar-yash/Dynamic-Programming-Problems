
//Given an array of integers, find the length of the longest (strictly) increasing subsequence from the given array.

//Longest Increasing Subsequence

//LC 300

#include<bits/stdc++.h>
using namespace std;

// } Driver Code Ends


class Solution
{
    public:
    
    //Recursion - TLE
    int solve(int n, int a[], int curr, int prev){
        //base case
        if(curr == n){
            return 0;
        }
        
        //inclusion condition for element
        int incl = 0;
        //either first element or greater element than prev element
        if(prev == -1 || a[curr] > a[prev]){
            //prev becomes curr
            incl = 1 + solve(n , a, curr + 1, curr);
        }
        
        //exclude current element
        //prev remains same
        int excl = solve(n , a, curr + 1, prev);
        
        return max(incl, excl);
    }
    
    //Recursion + MEMO
    
    int recurMEMO(int n, int a[], int curr, int prev, vector<vector<int>> &dp){
        if(curr == n){
            return 0;
        }
        
        if(dp[curr][prev + 1] != -1){
            return dp[curr][prev+1];
        }
        
        //inclusion condition for element
        int incl = 0;
        //either first element or greater element than prev element
        if(prev == -1 || a[curr] > a[prev]){
            //prev becomes curr
            incl = 1 + recurMEMO(n , a, curr + 1, curr, dp);
        }
        
        //exclude current element
        //prev remains same
        int excl = recurMEMO(n , a, curr + 1, prev, dp);
        
        return dp[curr][prev + 1] = max(incl, excl);
    }
    
    //Tabulation
    
    int tabulation(int n, int a[]){
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        
        for(int curr = n - 1; curr >= 0; curr--){
            for(int prev = curr - 1; prev >= -1; prev--){
                int incl = 0;
                //either first element or greater element than prev element
                if(prev == -1 || a[curr] > a[prev]){
                //prev becomes curr
                    incl = 1 + dp[curr + 1][curr + 1];
                }
        
                //exclude current element
                //prev remains same
                int excl = dp[curr + 1][prev + 1];
                
                dp[curr][prev + 1] = max(incl, excl);
            }
        }
        
        return dp[0][0];
    }
    
    //Space Optimization
    
    int spaceOP(int n, int a[]){
        vector<int> currRow(n + 1, 0);
        vector<int> nextRow(n + 1, 0);
        
        for(int curr = n - 1; curr >= 0; curr--){
            for(int prev = curr - 1; prev >= -1; prev--){
                int incl = 0;
                //either first element or greater element than prev element
                if(prev == -1 || a[curr] > a[prev]){
                //prev becomes curr
                    incl = 1 + nextRow[curr + 1];
                }
        
                //exclude current element
                //prev remains same
                int excl = nextRow[prev + 1];
                
                currRow[prev + 1] = max(incl, excl);
            }
            
            nextRow = currRow;
        }
        
        return nextRow[0];
    }
    
    // DP + Binary Search
    
    int binaryOP(int n, int a[]){
        if(n == 0){
            return 0;
        }
        
        vector<int> ans;
        ans.push_back(a[0]);
        
        for(int i = 1; i < n; i++){
            if(a[i] > ans.back()){
                ans.push_back(a[i]);
            }
            else{
                //find index of just bigger element
                int index = lower_bound(ans.begin(), ans.end(), a[i]) - ans.begin();
                ans[index] = a[i];
            }
        }
        
        return ans.size();
    }
    
    
    //Function to find length of longest increasing subsequence.
    int longestSubsequence(int n, int a[])
    {
        //Method 1
        return solve(n, a, 0, -1);
        
        //Method 2
        vector<vector<int>> dp(n, vector<int>(n + 1, -1));
        
        return recurMEMO(n, a, 0, -1, dp);
        
        //Method 3
        return tabulation(n, a);
        
        //Method 4
        return spaceOP(n, a);
        
        //Method 5
        return binaryOP(n, a);
    }
};

//{ Driver Code Starts.
int main()
{
    //taking total testcases
    int t,n;
    cin>>t;
    while(t--)
    {
        //taking size of array
        cin>>n;
        int a[n];
        
        //inserting elements to the array
        for(int i=0;i<n;i++)
            cin>>a[i];
        Solution ob;
        //calling method longestSubsequence()
        cout << ob.longestSubsequence(n, a) << endl;
    }
}

// } Driver Code Ends