//Given an array of distinct integers nums and a target integer target, return the number of possible combinations that add up to target.

//The test cases are generated so that the answer can fit in a 32-bit integer.

 

#include <bits/stdc++.h> 
using namespace std;

//Recursion
int solve(vector<int> &nums, int tar, int &n){
    //base case
    if(tar == 0){
        return 1; //one possible answer
    }

    if(tar < 0){
        return 0;
    }

    int ans = 0;

    for(int i = 0; i < n; i++){
        ans += solve(nums, tar - nums[i], n);
    }

    return ans;
}

//Recursion + MEMO

int recurMEMO(vector<int> &nums, int tar, int n, vector<int> &dp){
    if(tar == 0){
        return 1;
    }

    if(tar < 0){
        return 0;
    }

    if(dp[tar] != -1){
        return dp[tar];
    }

    int ans = 0;
    for(int i = 0; i < n; i++){
        ans += recurMEMO(nums, tar - nums[i], n, dp);
    }

    dp[tar] = ans;
    return dp[tar];
}

//Tabulation

int tabulation(vector<int> &nums, int tar, int &n){
    vector<int> dp(tar + 1, 0);
    //base case
    dp[0] = 1;

    //traversing from 1 to tar
    for(int i = 1; i <= tar; i++){
        //checking every nums[i]
        for(int j = 0; j < n; j++){
            //edge case
            if(i - nums[j] >= 0){
               dp[i] += dp[i - nums[j]]; 
            }
        }
    }

    return dp[tar];
}

int findWays(vector<int> &num, int tar)
{   
    int n = num.size();
    //Method 1
    // return solve(num, tar, n);

    //Method 2
    // vector<int> dp(tar + 1, -1);
    // return recurMEMO(num, tar, n, dp);

    //Method 3
    // return tabulation(num, tar, n);

    //Method 4
    //NOT POSSIBLE

    //Method 5


}