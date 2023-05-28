// You are given N balls numbered from 1 to N and there are N baskets numbered from 1 to N in front of you, the ith basket is meant for the ith ball. Calculate the number of ways in which no ball goes into its respective basket.

#include<bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

//Recursion

long long int solve(int n){
    //base case
    //no dearangement possible with 1 element
    if(n == 1){
        return 0;
    }

    if(n == 2){
        return 1;
    }

    //recurrance relation formed
    int ans = (((n - 1)%MOD)*((solve(n - 1)%MOD) + (solve(n - 2)%MOD)))%MOD;

    return ans;
}

//Recursion + MEMO

long long int recurMEMO(int n, vector<int> &dp){
    if(n == 1){
        return 0;
    }

    if(n == 2){
        return 1;
    }

    if(dp[n] != -1){
        return dp[n];
    }

    dp[n] = (((n - 1)%MOD)*((recurMEMO(n - 1, dp)%MOD) + (recurMEMO(n - 2, dp)%MOD)))%MOD;

    return dp[n];
}

//Tabulation

long long int tabulation(int n){
    vector<long long int> dp(n + 1, 0);
    dp[1] = 0;
    dp[2] = 1;

    //for every possible value of n
    for(int i = 3; i <= n; i++){

        long long int first = dp[i - 1]%MOD;
        
        long long int second = dp[i - 2]%MOD; 
        

        dp[i] = ((i-1)*(first + second))%MOD;
    } 

    return dp[n];
}

//Space Optimization

long long int spaceOp(int n){
    long long int prev2 = 0;
    long long int prev1 = 1;

    for(int i = 3; i <= n; i++){
        long long int curr = ((i - 1)*(prev1 + prev2))%MOD;
        prev2 = prev1;
        prev1 = curr;
    }

    return prev1;
}

long long int countDerangements(int n) {
    //Method 1
    
    return solve(n);

    //Method 2
    vector<int> dp(n + 1, -1);

    return recurMEMO(n, dp);

    //Method 3
    return tabulation(n);


    //Method 4
    return spaceOp(n);
}