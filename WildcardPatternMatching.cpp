//LC - 44

// Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:

// '?' Matches any single character.
// '*' Matches any sequence of characters (including the empty sequence).
// The matching should cover the entire input string (not partial).


#include<bits/stdc++.h>
using namespace std;


class Solution {
public:
    int n, m;

    //Recursion - TLE
    bool solve(string &s, string &p, int i, int j){

        //base case
        //both string completely comsumed
        if(i < 0 && j < 0){
            return true;
        }
        //only pattern is consumed
        if (i >= 0 && j < 0){
            return false;
        }
        //only s is consumed
        if(i < 0 && j >= 0){
            //then check for "*"
            for(int k = 0; k <= j; k++){
                if(p[k] != '*'){
                    return false;
                }
            } 
            return true;
        }


        //condition for matching of two character
        // 1. s[i] == p[j]
        // 2. p[j] == '?'

        //condition for match
        if(s[i] == p[j] || p[j] == '?'){
            return solve(s, p, i - 1, j - 1);
        }
        //how to handle "*" :
        // 1. "*" --> empty string
        // 2. "*" --> "*" followed by required character
        else if(p[j] == '*'){
            bool case1 = solve(s, p, i, j - 1); // empty string
            bool case2 = solve(s, p, i - 1, j); // "*" followed by required char

            return case1 || case2;
        }  
        else{
            //character does not match
            return false;
        }
    }

    //Recursion + MEMO - 51 ms
    bool recurMEMO(string &s, string &p, int i, int j, vector<vector<int>> &dp){
        if(i < 0 && j < 0){
            return true;
        }
        if (i >= 0 && j < 0){
            return false;
        }
        if(i < 0 && j >= 0){
            for(int k = 0; k <= j; k++){
                if(p[k] != '*'){
                    return false;
                }
            } 
            return true;
        }

        if(dp[i][j] != -1){
            return dp[i][j];
        }

        if(s[i] == p[j] || p[j] == '?'){
            return dp[i][j] = recurMEMO(s, p, i - 1, j - 1, dp);
        }

        else if(p[j] == '*'){
            bool case1 = recurMEMO(s, p, i, j - 1, dp);
            bool case2 = recurMEMO(s, p, i - 1, j, dp); 

            return dp[i][j] = case1 || case2;
        }  
        else{
            //character does not match
            return false;
        }
    }

    //Tabulation - 83 ms
    bool tabulation(string s, string p){
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

        //base case analysis
        dp[0][0] = true;
        //IMP PART TO UNDERSTAND
        for(int j = 1; j <= m; j++){
            bool flag = true;
            for(int k = 1; k <= j; k++){
                if(p[k - 1] != '*'){
                    flag = false;
                    break;
                }
            } 
            dp[0][j] = flag;
        }

        //Using 1 - Based Indexing
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                if(s[i - 1] == p[j - 1] || p[j - 1] == '?'){
                    dp[i][j] = dp[i - 1][j - 1];
                }

                else if(p[j - 1] == '*'){
                    bool case1 = dp[i][j - 1];
                    bool case2 = dp[i - 1][j]; 

                    dp[i][j] = case1 || case2;
                }  
                else{
                    //character does not match
                    dp[i][j] = false;
                }
            }
        }

        return dp[n][m];
    }

    //Space Optimization - 48 ms
    bool spaceOp(string &s, string &p){
        vector<int> prev(m + 1, 0);
        vector<int> curr(m + 1, 0);

        prev[0] = true;
        //IMP PART TO UNDERSTAND
        for(int j = 1; j <= m; j++){
            bool flag = true;
            for(int k = 1; k <= j; k++){
                if(p[k - 1] != '*'){
                    flag = false;
                    break;
                }
            } 
            prev[j] = flag;
        }

        //Using 1 - Based Indexing
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                if(s[i - 1] == p[j - 1] || p[j - 1] == '?'){
                    curr[j] = prev[j - 1];
                }

                else if(p[j - 1] == '*'){
                    bool case1 = curr[j - 1];
                    bool case2 = prev[j]; 

                    curr[j] = case1 || case2;
                }  
                else{
                    //character does not match
                    curr[j] = false;
                }
            }
            prev = curr;
        }

        return prev[m];
    }

    bool isMatch(string s, string p) {
        n = s.length();
        m = p.length();

        //Method 1
        //start from last indexes of both the string
        return solve(s, p, n - 1, m - 1);

        //Method 2
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));

        return recurMEMO(s, p, n - 1, m - 1, dp);

        //Method 3
        return tabulation(s, p);

        //Method 4
        return spaceOp(s, p);
    }
};

int main(){
    
    return 0;
}