//LC - 121

// You are given an array prices where prices[i] is the price of a given stock on the ith day.
// You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.
// Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.

#include<bits/stdc++.h>
using namespace std;


class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int maxProfit = 0; //max Profit can get
        int mini = prices[0]; //minimum priced day to buy stock 

        for(int i = 1; i < n; i++){
            int diff = prices[i] - mini;
            maxProfit = max(maxProfit, diff);
            mini = min(mini, prices[i]);
        }

        return maxProfit;
    }
};

int main(){
    
    return 0;
}

 