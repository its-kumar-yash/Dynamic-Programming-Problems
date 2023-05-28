//LC - 714

// You are given an array prices where prices[i] is the price of a given stock on the ith day, and an integer fee representing a transaction fee.

// Find the maximum profit you can achieve. You may complete as many transactions as you like, but you need to pay the transaction fee for each transaction.

// Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).


#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int n;
    //Recursion - TLE
    int solve(vector<int>& prices, int idx, int buyFlag, int &fees){
        //base case
        if(idx >= n){
            return 0;
        }

        int profit = 0;
        //when buy flag --> 1, then either we can buy a stock or skip it
        if(buyFlag){
            //when buy a stock, price will be added with -ive sign in profit
            int buyStock = -prices[idx] + solve(prices, idx + 1, 0, fees);
            int skipStock = 0 + solve(prices, idx + 1, 1, fees);
            //profit will be max of both cases
            profit += max(buyStock, skipStock);
        }
        //when buy flag --> 0, then either we can sell a stock or skip it
        else{
            //when sell a stock, price will be added with +ive sign in profit
            // also as one transaction is completed subtract the transaction fees
            int sellStock = prices[idx] - fees + solve(prices, idx + 1, 1, fees);
            int skipStock = 0 + solve(prices, idx + 1, 0, fees);
            //profit will be max of both cases
            profit += max(sellStock, skipStock);
        }

        return profit;
    }

    //Recursion + MEMO - 271 ms
    int recurMEMO(vector<int>& prices, int idx, int buyFlag, int &fees, vector<vector<int>> &dp){
        //base case
        if(idx >= n){
            return 0;
        }

        if(dp[idx][buyFlag] != -1){
            return dp[idx][buyFlag];
        }

        int profit = 0;
        if(buyFlag){
            int buyStock = -prices[idx] + recurMEMO(prices, idx + 1, 0, fees, dp);
            int skipStock = 0 + recurMEMO(prices, idx + 1, 1, fees, dp);
            profit += max(buyStock, skipStock);
        }

        else{
            int sellStock = prices[idx] - fees + recurMEMO(prices, idx + 1, 1, fees, dp);
            int skipStock = 0 + recurMEMO(prices, idx + 1, 0, fees, dp);
            profit += max(sellStock, skipStock);
        }

        return dp[idx][buyFlag] = profit;
    }

    //Tabulation - 264 ms
    int tabulation(vector<int>& prices, int &fees){
        vector<vector<int>> dp(n + 1, vector<int>(2, 0));

        for(int idx = n - 1; idx >= 0; idx--){
            for(int buyFlag = 0; buyFlag <= 1; buyFlag++){
                int profit = 0;

                if(buyFlag){
                    int buyStock = -prices[idx] + dp[idx + 1][0];
                    int skipStock = 0 + dp[idx + 1][1];
                    profit += max(buyStock, skipStock);
                }

                else{
                    int sellStock = prices[idx] - fees + dp[idx + 1][1];
                    int skipStock = 0 + dp[idx + 1][0];
                    profit += max(sellStock, skipStock);
                }

                dp[idx][buyFlag] = profit;
            }
        }
        
        return dp[0][1];
    }

    //Space Optimization - 126 ms
    int spaceOp(vector<int>& prices, int &fees){
        vector<int> curr(2, 0);
        vector<int> next(2, 0);

        for(int idx = n - 1; idx >= 0; idx--){
            for(int buyFlag = 0; buyFlag <= 1; buyFlag++){
                int profit = 0;

                if(buyFlag){
                    int buyStock = -prices[idx] + next[0];
                    int skipStock = 0 + next[1];
                    profit += max(buyStock, skipStock);
                }

                else{
                    int sellStock = prices[idx] - fees + next[1];
                    int skipStock = 0 + next[0];
                    profit += max(sellStock, skipStock);
                }

                curr[buyFlag] = profit;
            }

            next = curr;
        }

        return curr[1];
    }

    int maxProfit(vector<int>& prices, int fee) {
        n = prices.size();
        
        //Method 1
        return solve(prices, 0, 1, fee);
        
        //Method 2
        vector<vector<int>> dp(n + 1, vector<int>(2, -1));

        return recurMEMO(prices, 0, 1, fee, dp);

        //Method 3

        return tabulation(prices, fee);

        //Method 4
        
        return spaceOp(prices, fee);
    }
};

int main(){
    
    return 0;
}