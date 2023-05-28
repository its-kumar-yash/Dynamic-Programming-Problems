// Given an integer. Find how many structurally unique binary search trees are there that stores the values from 1 to that integer (inclusive). 

//LC - 96. Unique Binary Search Trees

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    //Recursion - 2703 ms
    int solve(int n){
        //base case
        if(n <= 1){
            return 1;
        }
        
        int ans = 0;
        
        //start making ith node as root one by one
        for(int i = 1; i <= n; i++){
            //find ans using recurrence relation
            ans += solve(i - 1)*solve(n - i);
        }
        
        return ans;
    }

    //Recursion + MEMO - 0 ms - 100%
    int recurMEMO(int n, vector<int> &dp){
        if(n <= 1){
            return 1;
        }

        if(dp[n] != -1){
            return dp[n];
        }

        int ans = 0;
        for(int i = 1; i <= n; i++){
            ans += recurMEMO(i - 1, dp) * recurMEMO(n - i, dp);
        } 

        return dp[n] = ans;
    }


    //Tabulation - 0 ms - 100%
    int tabulation(int n){
        vector<int> dp(n + 1, 0);
        dp[0] = dp[1] = 1;

        int ans = 0;
        //i-> number of nodes
        for(int i = 2; i <= n; i++){
            //j -> root node
            for(int j = 1; j <= i; j++){
                dp[i] += dp[j - 1] * dp[i - j];
            }
        }

        return dp[n];
    }
    
    //Space Optimization - 0ms - 100%
    int catalan(int n){
        //base case
        if(n <= 1){
            return 1;
        }

        double res = 1;

        for(int i = 1; i <= n; i++){
            res = res*(n + i)/i;
        }

        res = res/(n + 1);

        return (int)res;
    }

    int numTrees(int n) {
        //Method 1
        return solve(n);

        //Method 2
        vector<int> dp(n + 1, -1);

        return recurMEMO(n, dp);

        //Method 3
        return tabulation(n);

        //Method 4
        //Catalan Series
        return catalan(n);
    }
};

int main(){
    
    return 0;
}
