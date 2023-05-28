#include <bits/stdc++.h> 
using namespace std;

//Recursion 

long long int recursion(vector<int> arr, int idx){
    //base case
    if(idx < 0){
        return 0;
    }
    if(idx == 0){
        return arr[0];
    }

    long long int incl = recursion(arr, idx - 2) + arr[idx];

    long long int excl = recursion(arr, idx - 1);

    return max(incl, excl);
}

//Recusrion + MEMO
long long int recurMEMO(vector<int> &arr, int idx, vector<int> &dp){
    if(idx < 0){
        return 0;
    }

    if(idx == 0){
        return arr[0];
    }

    if(dp[idx] != -1){
        return dp[idx];
    }

    long long int incl = recurMEMO(arr, idx - 2, dp) + arr[idx];

    long long int excl = recurMEMO(arr, idx - 1, dp);

    return dp[idx] = max(incl, excl);
}

//Tabulation

long long int tabulation(vector<int> &arr, int n){
    vector<int> dp(n, 0);
    dp[0] = arr[0];

    for(int i = 1; i < n; i++){
        long long int incl = dp[i - 2] + arr[i];
        long long int excl = dp[i - 1];

        dp[i] = max(incl, excl); 
    }

    return dp[n - 1];
}

//Space Optimization

long long int spaceOp(vector<int> &arr, int n){
    long long int prev2 = 0;
    long long int prev1 = arr[0];

    for(int i = 1; i < n; i++){
        long long int incl = prev2 + arr[i];
        long long int excl = prev1;

        long long curr = max(incl, excl);

        prev2 = prev1;
        prev1 = curr;
    }

    return prev1;
}



long long int houseRobber(vector<int>& valueInHouse)
{
    int n = valueInHouse.size();
    //edge case
    if(n == 1){
        return valueInHouse[0];
    }

    //create two arrays
    // first include last exclude
    //last include first exclude
    vector<int> first, second;

    for(int i = 0; i < n; i++){
        if(i != n - 1){
            first.push_back(valueInHouse[i]);
        }
        if(i != 0){
            second.push_back(valueInHouse[i]);
        }
    }

    //Method 1 
    long long int ans1 = recursion(first, n - 2);
    long long int ans2 = recursion(second, n - 2);

    return max(ans1, ans2);

    //Method 2
    vector<int> dp1(n - 1, -1);
    vector<int> dp2(n - 1, -1);

    long long int ans1 = recurMEMO(first, n - 2, dp1);
    long long int ans2 = recurMEMO(second, n - 2, dp2);

    return max(ans1, ans2);

    //Method 3
    long long int ans1 = tabulation(first, n - 1);
    long long int ans2 = tabulation(second, n - 1);

    return max(ans1, ans2);

    //Method 4
    long long int ans1 = spaceOp(first, n - 1);
    long long int ans2 = spaceOp(second,n - 1);

    return max(ans1, ans2);
}