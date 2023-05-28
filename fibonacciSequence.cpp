#include<bits/stdc++.h>
using namespace std;

//Top - Down Approach - Recursion + Memoization 

int fiboMEMO(int n, vector<int> &dp){
    if(n == 0 || n == 1){
        return n;
    } 

    //step 3 
    if(dp[n] != -1){
        return dp[n];
    }

    //step 2
    return dp[n] = fiboMEMO(n - 1, dp) + fiboMEMO(n - 2, dp);
}

//Botton - Up Approach - Tabulation

int fiboTabulation(int n){
    int dp[n + 1];
    dp[0] = 0;
    dp[1] = 1;

    for(int i = 2; i <= n; i++){
        dp[i] = dp[i - 1] + dp[i - 2];
    } 

    return dp[n];
}

//Space Optimization

int fiboSpace(int n){
    int prev1 = 1;
    int prev2 = 0;

    for(int i = 2; i <= n; i++){
        int curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    }

    return prev1;
}

int main(){
    int n;
    cin >> n;
    //step 1
    vector<int> dp(n + 1, -1);
    cout<<fiboMEMO(n, dp)<<endl;
    cout<<fiboTabulation(n)<<endl;
    cout<<fiboSpace(n)<<endl;

    return 0;
}