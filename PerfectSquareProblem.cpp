// Given a number N. Find the minimum number of squares of any number that sums to N. For Example: If N = 100 , N can be expressed as (10*10) and also as (5*5 + 5*5 + 5*5 + 5*5) but the output will be 1 as minimum number of square is 1 , i.e (10*10).

#include <bits/stdc++.h>
using namespace std;

// } Driver Code Ends
// User function Template for C++

class Solution
{
public:
    // Recursion

    int solve(int n)
    {
        // base case
        if (n == 0)
        {
            return 0; // it is not possible to make using perfect sqaures
        }

        int mini = n;

        // checking for every perfect square
        for (int i = 1; i * i <= n; i++)
        {

            int ans = 1 + solve(n - i * i);
            // adding 1 for the number being used in the call(here i*i)
            mini = min(mini, ans);
        }

        return mini;
    }

    // Recursion + MEMO
    int recurMEMO(int n, vector<int> &dp)
    {
        if (n == 0)
        {
            return 0;
        }

        if (dp[n] != -1)
        {
            return dp[n];
        }

        int mini = n;

        for (int i = 1; i * i <= n; i++)
        {
            int ans = 1 + recurMEMO(n - i * i, dp);
            mini = min(mini, ans);
        }

        dp[n] = mini;

        return dp[n];
    }

    // Tabulation

    int tabulation(int n)
    {
        vector<int> dp(n + 1, INT_MAX);
        dp[0] = 0;

        // for every value of n
        for (int i = 1; i <= n; i++)
        {
            // every possible perfect square
            for (int j = 1; j * j <= i; j++)
            {
                int ans = 1 + dp[i - j * j];
                dp[i] = min(dp[i], ans);
            }
        }

        return dp[n];
    }

    int MinSquares(int n)
    {
        // Method 1
        return solve(n);

        // Method 2
        vector<int> dp(n + 1, -1);

        return recurMEMO(n, dp);

        // Method 3

        return tabulation(n);

        // Method 4
        // Not Possible
    }
};

//{ Driver Code Starts.
int main()
{
    int tc;
    cin >> tc;
    while (tc--)
    {
        int n;
        cin >> n;
        Solution ob;
        int ans = ob.MinSquares(n);
        cout << ans << "\n";
    }
    return 0;
}
// } Driver Code Ends