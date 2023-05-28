// You have planned some train traveling one year in advance. The days of the year in which you will travel are given as an integer array days. Each day is an integer from 1 to 365.

// Train tickets are sold in three different ways:

// a 1-day pass is sold for costs[0] dollars,
// a 7-day pass is sold for costs[1] dollars, and
// a 30-day pass is sold for costs[2] dollars.
// The passes allow that many days of consecutive travel.

// For example, if we get a 7-day pass on day 2, then we can travel for 7 days: 2, 3, 4, 5, 6, 7, and 8.
// Return the minimum number of dollars you need to travel every day in the given list of days.

#include <bits/stdc++.h>
using namespace std;

//Recursion
int solve(int idx, int n, vector<int> &days, vector<int> &cost)
{
    // base case
    if (idx >= n)
    {
        return 0; // can't travel after last day
    }

    // 1 - Day Pass
    int cost1 = cost[0] + solve(idx + 1, n, days, cost);

    // 7 - Day Pass
    int max7Day = days[idx] + 7;
    int j = idx;
    // increment j till 7 days
    while (j < n && days[j] < max7Day)
    {
        j++;
    }

    int cost7 = cost[1] + solve(j, n, days, cost);

    // 30 - Day Pass
    int max30Day = days[idx] + 30;
    int k = idx;
    while (k < n && days[k] < max30Day)
    {
        k++;
    }

    int cost30 = cost[2] + solve(k, n, days, cost);

    // Take minimum of all three cost
    int ans = min(cost1, min(cost7, cost30));

    return ans;
}

// Recursion + MEMO 

int recurMEMO(int idx, int n, vector<int> &days, vector<int> &cost,
              vector<int> &dp)
{
    if (idx >= n)
    {
        return 0;
    }

    if (dp[idx] != -1)
    {
        return dp[idx];
    }

    // 1 - Day Pass
    int cost1 = cost[0] + recurMEMO(idx + 1, n, days, cost, dp);

    // 7 - Day Pass
    int max7Day = days[idx] + 7;
    int j = idx;
    // increment j till 7 days
    while (j < n && days[j] < max7Day)
    {
        j++;
    }

    int cost7 = cost[1] + recurMEMO(j, n, days, cost, dp);

    // 30 - Day Pass
    int max30Day = days[idx] + 30;
    int k = idx;
    while (k < n && days[k] < max30Day)
    {
        k++;
    }

    int cost30 = cost[2] + recurMEMO(k, n, days, cost, dp);

    dp[idx] = min({cost1, cost7, cost30});

    return dp[idx];
}

// Tabulation
int tabulation(int n, vector<int> &days, vector<int> &cost)
{
    vector<int> dp(n + 1, INT_MAX);

    dp[n] = 0;

    // Bottom Up
    for (int k = n - 1; k >= 0; k--)
    {
        // 1 - Day Pass
        int cost1 = cost[0] + dp[k + 1];

        // 7 - Day Pass
        int max7Day = days[k] + 7;
        int j = k;
        // increment j till 7 days
        while (j < n && days[j] < max7Day)
        {
            j++;
        }

        int cost7 = cost[1] + dp[j];

        // 30 - Day Pass
        int max30Day = days[k] + 30;
        int m = k;
        while (m < n && days[m] < max30Day)
        {
            m++;
        }

        int cost30 = cost[2] + dp[m];

        dp[k] = min({cost1, cost7, cost30});
    }

    return dp[0];
}

// Space Optimization

int spaceOp(int n, vector<int> &days, vector<int> &cost)
{
    int ans = 0;

    // initialize two queue
    //{day, cost till that day}
    queue<pair<int, int>> weekly;
    queue<pair<int, int>> monthly;

    for (auto d : days)
    {
        // step 1 - remove expired days from queue
        while (weekly.size() != 0 && weekly.front().first + 7 <= d)
        {
            weekly.pop();
        }

        while (monthly.size() != 0 && monthly.front().first + 30 <= d)
        {
            monthly.pop();
        }

        // Step 2 - push current day's cost into queue
        weekly.push({d, ans + cost[1]});
        monthly.push({d, ans + cost[2]});

        // Step 3 - update the ans
        ans = min({ans + cost[0], weekly.front().second, monthly.front().second});
    }

    return ans;
}

int minimumCoins(int n, vector<int> days, vector<int> cost)
{
    // Method 1
    return solve(0, n, days, cost);

    // Method 2
    vector<int> dp(n + 1, -1);
    return recurMEMO(0, n, days, cost, dp);

    // Method 3
    return tabulation(n, days, cost);

    // Method 4

    return spaceOp(n, days, cost);
}