//LC - 123

// You are given an array prices where prices[i] is the price of a given stock on the ith day.

// Find the maximum profit you can achieve. You may complete at most two transactions.

// Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n;
    //Recursion - TLE
    int solve(vector<int>& prices, int idx, int buyFlag, int limit){
        //limit - represent number of transaction can be made
        //base case
        if(idx >= n || limit == 0){
            return 0;
        } 

        int profit = 0;
        //when buy flag --> 1, then either we can buy a stock or skip it
        if(buyFlag){
            //when buy a stock, price will be added with -ive sign in profit
            int buyStock = -prices[idx] + solve(prices, idx + 1, 0, limit);
            int skipStock = 0 + solve(prices, idx + 1, 1, limit);
            //profit will be max of both cases
            profit += max(buyStock, skipStock);
        }
        //when buy flag --> 0, then either we can sell a stock or skip it
        else{
            //when sell a stock, price will be added with +ive sign in profit
            //also decrement the limit as one transaction is completed
            int sellStock = prices[idx] + solve(prices, idx + 1, 1, limit - 1);
            int skipStock = 0 + solve(prices, idx + 1, 0, limit);
            //profit will be max of both cases
            profit += max(sellStock, skipStock);
        }

        return profit;
    }

    //Recursion + MEMO - 888 ms
    int recurMEMO(vector<int>& prices, int idx, int buyFlag, int limit, vector<vector<vector<int>>> &dp){
        if(idx >= n || limit == 0){
            return 0;
        }

        if(dp[idx][buyFlag][limit] != -1){
            return dp[idx][buyFlag][limit];
        }

        int profit = 0;

        if(buyFlag){
            int buyStock = -prices[idx] + recurMEMO(prices, idx + 1, 0, limit, dp);
            int skipStock = 0 + recurMEMO(prices, idx + 1, 1, limit, dp);

            profit += max(buyStock, skipStock);
        }
        else{
            int sellStock = prices[idx] + recurMEMO(prices, idx + 1, 1, limit - 1, dp);
            int skipStock = 0 + recurMEMO(prices, idx + 1, 0, limit, dp);

            profit += max(sellStock, skipStock);
        }

        return dp[idx][buyFlag][limit] = profit;
    }

    //Tabulation - 740 ms
    int tabulation(vector<int> &prices){
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));

        for(int idx = n - 1; idx >= 0; idx--){
            for(int buyFlag = 0; buyFlag <= 1; buyFlag++){
                for(int limit = 1; limit <= 2; limit++){
                    int profit = 0;

                    if(buyFlag){
                        int buyStock = -prices[idx] + dp[idx + 1][0][limit];
                        int skipStock = 0 + dp[idx + 1][1][limit];

                        profit += max(buyStock, skipStock);
                    }
                    else{
                        int sellStock = prices[idx] + dp[idx + 1][1][limit - 1];
                        int skipStock = 0 + dp[idx + 1][0][limit];

                        profit += max(sellStock, skipStock);
                    }

                    dp[idx][buyFlag][limit] = profit;
                }
            }
        }

        return dp[0][1][2];
    }

    //Space Optimization - 317 ms
    int spaceOp(vector<int>& prices){
        vector<vector<int>> curr(2, vector<int>(3, 0));
        vector<vector<int>> next(2, vector<int>(3, 0));

        for(int idx = n - 1; idx >= 0; idx--){
            for(int buyFlag = 0; buyFlag <= 1; buyFlag++){
                for(int limit = 1; limit <= 2; limit++){
                    int profit = 0;

                    if(buyFlag){
                        int buyStock = -prices[idx] + next[0][limit];
                        int skipStock = 0 + next[1][limit];

                        profit += max(buyStock, skipStock);
                    }
                    else{
                        int sellStock = prices[idx] + next[1][limit - 1];
                        int skipStock = 0 + next[0][limit];

                        profit += max(sellStock, skipStock);
                    }

                    curr[buyFlag][limit] = profit;
                }
                next = curr;
            }
        }

        return curr[1][2];
    }

    int maxProfit(vector<int>& prices) {
        n = prices.size();
        //Method 1
        return solve(prices, 0, 1, 2);

        //Method 2
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, -1)));

        return recurMEMO(prices, 0, 1, 2, dp);

        //Method 3
        return tabulation(prices);

        //Method 4
        return spaceOp(prices);
    }
};


int main(){
    
    return 0;
}