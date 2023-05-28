//LC - 188

// You are given an integer array prices where prices[i] is the price of a given stock on the ith day, and an integer k.

// Find the maximum profit you can achieve. You may complete at most k transactions: i.e. you may buy at most k times and sell at most k times.

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

    //Recursion + MEMO - 44 ms
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
    
    //Tabulation - 20 ms
    int tabulation(vector<int> &prices, int k){
        vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(k + 1, 0)));

        for(int idx = n - 1; idx >= 0; idx--){
            for(int buyFlag = 0; buyFlag <= 1; buyFlag++){
                for(int limit = 1; limit <= k; limit++){
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

        return dp[0][1][k];
    }

    //Space Optimization - 15 ms
    int spaceOp(vector<int>& prices, int k){
        vector<vector<int>> curr(2, vector<int>(k + 1, 0));
        vector<vector<int>> next(2, vector<int>(k + 1, 0));

        for(int idx = n - 1; idx >= 0; idx--){
            for(int buyFlag = 0; buyFlag <= 1; buyFlag++){
                for(int limit = 1; limit <= k; limit++){
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

        return curr[1][k];
    }

    /*-----------------------------Transaction Number---------------------------------------*/

    //Recursion - TLE
    int solveTN(vector<int>& prices, int idx, int operation, int k){
        //operation -> denotes the operation number 
        //for any value of k, max operations can be 2*k

        //base case
        if(idx >= n || operation == 2*k){
            return 0;
        }

        // BUY - Associated with EVEN Operation Number
        // SELL - Associated with ODD Operation Number

        int profit = 0;
        //when operation --> even, then either we can buy a stock or skip it
        if(operation%2 == 0){
            //when buy a stock, price will be added with -ive sign in profit
            int buyStock = -prices[idx] + solveTN(prices, idx + 1, operation + 1, k);
            int skipStock = 0 + solveTN(prices, idx + 1, operation, k);
            //profit will be max of both cases
            profit += max(buyStock, skipStock);
        }
        //when operation --> odd, then either we can sell a stock or skip it
        else{
            //when sell a stock, price will be added with +ive sign in profit
            int sellStock = prices[idx] + solveTN(prices, idx + 1, operation + 1, k);
            int skipStock = 0 + solveTN(prices, idx + 1, operation, k);
            //profit will be max of both cases
            profit += max(sellStock, skipStock);
        }

        return profit;
    }

    //Recursion + MEMO - 24 ms
    int recurMEMOTN(vector<int>& prices, int idx, int operation, int k, vector<vector<int>> &dp){
        if(idx >= n || operation == 2*k){
            return 0;
        }

        if(dp[idx][operation] != -1){
            return dp[idx][operation];
        }

        int profit = 0;

        if(operation%2 == 0){

            int buyStock = -prices[idx] + recurMEMOTN(prices, idx + 1, operation + 1, k, dp);
            int skipStock = 0 + recurMEMOTN(prices, idx + 1, operation, k, dp);

            profit += max(buyStock, skipStock);
        }
        else{
            int sellStock = prices[idx] + recurMEMOTN(prices, idx + 1, operation + 1, k, dp);
            int skipStock = 0 + recurMEMOTN(prices, idx + 1, operation, k, dp);

            profit += max(sellStock, skipStock);
        }

        return dp[idx][operation] = profit;
    }

    //Tabulation - 14 ms
    int tabulationTN(vector<int>& prices, int k){
        vector<vector<int>> dp(n + 1, vector<int>(2*k + 1, 0));

        for(int idx = n - 1; idx >= 0; idx--){
            for(int operation = 2*k - 1; operation >= 0; operation--){
                int profit = 0;

                if(operation%2 == 0){

                    int buyStock = -prices[idx] + dp[idx + 1][operation + 1];
                    int skipStock = 0 + dp[idx + 1][operation];

                    profit += max(buyStock, skipStock);
                }
                else{
                    int sellStock = prices[idx] + dp[idx + 1][operation + 1];
                    int skipStock = 0 + dp[idx + 1][operation];

                    profit += max(sellStock, skipStock);
                }

                dp[idx][operation] = profit;
            }
        }

        return dp[0][0];
    }

    //Space Optimization - 6 ms
    int spaceOpTN(vector<int>& prices, int k){
        vector<int> curr(2*k + 1, 0);
        vector<int> next(2*k + 1, 0);

        for(int idx = n - 1; idx >= 0; idx--){
            for(int operation = 2*k - 1; operation >= 0; operation--){
                int profit = 0;

                if(operation%2 == 0){

                    int buyStock = -prices[idx] + next[operation + 1];
                    int skipStock = 0 + next[operation];

                    profit += max(buyStock, skipStock);
                }
                else{
                    int sellStock = prices[idx] + next[operation + 1];
                    int skipStock = 0 + next[operation];

                    profit += max(sellStock, skipStock);
                }

                curr[operation] = profit;
            }

            next = curr;
        }

        return curr[0];
    }


    int maxProfit(int k, vector<int>& prices) {
        n = prices.size();

        //Method 1
        return solve(prices, 0, 1, k);

        //Method 2
        // vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(k + 1, -1)));

        // return recurMEMO(prices, 0, 1, k, dp);

        //Method 3
        return tabulation(prices, k);

        //Method 4
        return spaceOp(prices, k);

        /*-----------------------------Transaction Number---------------------------------------*/

        //Method 1
        return solveTN(prices, 0, 0, k);

        //Method 2
        vector<vector<int>> dp(n + 1, vector<int>(2*k + 1, - 1));

        return recurMEMOTN(prices, 0, 0, k, dp);

        //Method 3
        return tabulationTN(prices, k);

        //Method 4
        return spaceOpTN(prices, k);
    }
};



int main(){
    
    return 0;
}