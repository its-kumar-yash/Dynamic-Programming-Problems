//LC - 375
// We are playing the Guessing Game. The game will work as follows:

// I pick a number between 1 and n.
// You guess a number.
// If you guess the right number, you win the game.
// If you guess the wrong number, then I will tell you whether the number I picked is higher or lower, and you will continue guessing.
// Every time you guess a wrong number x, you will pay x dollars. If you run out of money, you lose the game.
// Given a particular n, return the minimum amount of money you need to guarantee a win regardless of what number I pick.


#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    //Recursion - TLE
    int solve(int start, int end){
        //base case
        if(start >= end){
            return 0;
        }
        
        int ans = INT_MAX;
        //find answer for every number between the range
        for(int i = start; i <= end; i++){
            ans = min(ans, i + max(solve(start, i - 1), solve(i + 1, end)));
        }

        return ans;
    }

    //Recursion + MEMO - 306 ms
    int recurMEMO(int start, int end, vector<vector<int>> &dp){
        if(start >= end){
            return 0;
        }

        if(dp[start][end] != -1){
            return dp[start][end];
        }

        int ans = INT_MAX;
        for(int i = start; i <= end; i++){
            ans = min(ans, i + max(recurMEMO(start, i - 1, dp), recurMEMO(i + 1, end, dp)));
        }

        dp[start][end] = ans;

        return dp[start][end];
    }

    //Tabulation - 99 ms
    int tabulation(int n){
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

        for(int start = n; start >= 1; start--){
            for(int end = start; end <= n; end++){
                if(start == end){
                    continue;
                }
                else{
                    int ans = INT_MAX;
                    for(int i = start; i <= end; i++){
                        ans = min(ans, i + max(dp[start][i - 1], dp[i + 1][end]));
                    }
                    dp[start][end] = ans;
                }
                
            }
        }

        return dp[1][n];
    }



    int getMoneyAmount(int n) {
        //Method 1
        return solve(1, n);

        //Method 2
        //since start and end are changing so use 2d dp
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));

        return recurMEMO(1, n, dp);

        //Method 3
        return tabulation(n);

        //Method 4
        // Space OPtimization Not Possible 
    }
};


int main(){
    
    return 0;
}