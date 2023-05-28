//DP with Hashing
// Given an array called A[] of sorted integers having no duplicates, find the length of the Longest Arithmetic Progression (LLAP) in it.

//TIP:  agr geeksforgeeks pr submit krna hai to unordered<int,int> dp[n+1] * ki jagah *vector<vector<int>> dp(n+1, vector<int>(array_largetvalue - array_smallestvalue, -1)  banao aur by reference send kro ho jayega,     but leetcode pr submit krne ke liye Tabulation + vector<unordered_map<int,int>> dp(n+1) hi work krega coz test case tough hai uske geekforgeeks pr negatice difference nhi aayega but Leetcode pr aayega

//https://www.geeksforgeeks.org/longest-arithmetic-progression-dp-35/ - REFERENCE

//LC = 1027

//{ Driver Code Starts
//Initial template for C++

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
//User function template for C++

class Solution{   
public:
    //Recursion - TLE
    int solve(int idx, int diff, int a[]){
        //base case
        if(idx < 0){
            return 0;
        }
        
        int ans = 0;
        //Backward Check
        //now check backward for remaining element of AP
        for(int j = idx - 1; j >= 0; j--){
            if(a[idx] - a[j] == diff){
                // ans = max(ans , 1 + solve(j, diff, a));
                //Slight Optimization
                ans++;
                idx = j;
            }
        }
        
        return ans;
    }
    
    //Recursion + MEMO - TLE
    int recurMEMO(int idx, int diff, int a[], unordered_map<int, int> dp[]){
        if(idx < 0){
            return 0;
        }
        
        if(dp[idx].count(diff)){
            return dp[idx][diff];
        }
        
        int ans = 0;
        //Backward Check
        //now check backward for remaining element of AP
        for(int j = idx - 1; j >= 0; j--){
            if(a[idx] - a[j] == diff){
                ans = max(ans , 1 + recurMEMO(j, diff, a, dp));
            }
        }
        
        return dp[idx][diff] = ans;
        
    }
    
    //Tabulation
    
    int tabulation(int A[], int n){
        if(n <= 2){
            return n;
        }
        
        int ans = 0;
        unordered_map<int, int> dp[n + 1];
        
        for(int i = 1; i < n; i++){
            for(int j = 0; j < i; j++){
                int diff = A[i] - A[j];
                
                int cnt = 1;
                
                //check if answer already present
                if(dp[j].count(diff)){
                    cnt = dp[j][diff];
                }
                
                dp[i][diff] = 1 + cnt;
                ans = max(ans, dp[i][diff]);
            }
            
        }
        
        return ans;
    }
    
    //Space Optimization
    // Returns length of the longest
// AP subset in a given set
    int spaceOp(int a[], int n)
    {
        int ans = 2;
        if (n <= 2)
            return n;
        
        vector<int> A;
        for(int i = 0; i < n; i++){
            A.push_back(a[i]);
        }
 
        vector<int> llap(n, 2);
 
        sort(A.begin(), A.end());
 
        for (int j = n - 2; j >= 0; j--){
            int i = j - 1;
            int k = j + 1;
            while (i >= 0 && k < n)
            {
                if (A[i] + A[k] == 2 * A[j])
                {
                    llap[j] = max(llap[k] + 1, llap[j]);
                    ans = max(ans, llap[j]);
                    i -= 1;
                    k += 1;
                }
                else if (A[i] + A[k] < 2 * A[j])
                    k += 1;
                else
                    i -= 1;
            }
        }
        return ans;
}
    
    
    int lengthOfLongestAP(int A[], int n) {
        //when element are equal and less than 2
        if(n <= 2){
            return n;
        }
        
        //now choose two element as the last element of AP and find the remaining element
        int ans = 0;
        //Method 1
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                //as two element are already found
                //now search for remaining element of AP
                ans = max(ans, 2 + solve(i, A[j] - A[i], A));
            }
        }
        
        return ans;
        
        //Method 2
        unordered_map<int, int> dp[n + 1];
        
        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                //as two element are already found
                //now search for remaining element of AP
                ans = max(ans, 2 + recurMEMO(i, A[j] - A[i], A, dp));
            }
        }
        
        return ans;
        
        //Method 3
        return tabulation(A, n);
        
        //Method 4
        return spaceOp(A, n);
    }
};

//{ Driver Code Starts.
int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int A[n];
        for (int i = 0; i < n; i++) {
            cin >> A[i];
        }
        Solution ob;
        auto ans = ob.lengthOfLongestAP(A, n);
        cout << ans << "\n";
    }
    return 0;
}
// } Driver Code Ends