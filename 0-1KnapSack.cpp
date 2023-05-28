#include <bits/stdc++.h>
using namespace std;

// Recursion - TLE

// moving from right to left
int solve(vector<int> weight, vector<int> value, int maxWeight, int idx)
{

	// base case
	// if only 1 item to steal
	if (idx == 0)
	{
		// include
		if (weight[0] <= maxWeight)
		{
			return value[0];
		}
		// exclude
		else
		{
			return 0;
		}
	}

	int incl = 0;
	if (weight[idx] <= maxWeight)
	{
		incl = value[idx] + solve(weight, value, maxWeight - weight[idx], idx - 1);
	}

	int excl = solve(weight, value, maxWeight, idx - 1);

	int ans = max(incl, excl);

	return ans;
}

// Recursion + MEMO

int recurMEMO(vector<int> weight, vector<int> value, int maxWeight, int idx, vector<vector<int>> &dp)
{
	// if only 1 item to steal
	if (idx == 0)
	{
		// include
		if (weight[0] <= maxWeight)
		{
			return value[0];
		}
		// exclude
		else
		{
			return 0;
		}
	}

	if (dp[idx][maxWeight] != -1)
	{
		return dp[idx][maxWeight];
	}

	int incl = 0;
	if (weight[idx] <= maxWeight)
	{
		incl = value[idx] + recurMEMO(weight, value, maxWeight - weight[idx], idx - 1, dp);
	}

	int excl = recurMEMO(weight, value, maxWeight, idx - 1, dp);

	dp[idx][maxWeight] = max(incl, excl);

	return dp[idx][maxWeight];
}

// Tabulation

int tabulation(vector<int> weight, vector<int> value, int maxWeight, int idx)
{

	vector<vector<int>> dp(idx, vector<int>(maxWeight + 1, 0));

	// analysis of base case
	for (int w = weight[0]; w <= maxWeight; w++)
	{
		if (weight[0] <= maxWeight)
		{
			dp[0][w] = value[0];
		}
		// exclude
		else
		{
			dp[0][w] = 0;
		}
	}

	for (int i = 1; i < idx; i++)
	{
		for (int w = 0; w <= maxWeight; w++)
		{
			int incl = 0;

			if (weight[i] <= w)
			{
				incl = value[i] + dp[i - 1][w - weight[i]];
			}

			int excl = dp[i - 1][w];

			dp[i][w] = max(incl, excl);
		}
	}

	return dp[idx - 1][maxWeight];
}

// Space Optimization

int SO(vector<int> &weight, vector<int> &value, int n, int W)
{

	vector<int> prev(W + 1, 0);

	vector<int> curr(W + 1, 0);

	for (int j = weight[0]; j <= W; j++)
		prev[j] = value[0];

	for (int i = 1; i < n; i++)
	{

		for (int j = 0; j <= W; j++)
		{

			int in = 0;

			if (weight[i] <= j)

				in = value[i] + prev[j - weight[i]];

			int ex = prev[j];

			curr[j] = max(in, ex);
		}

		for (int k = 0; k <= W; k++)

			prev[k] = curr[k];
	}

	return prev[W];
}

int SO2(vector<int> &weight, vector<int> &value, int n, int W)
{

	vector<int> curr(W + 1, 0);

	for (int j = weight[0]; j <= W; j++)
		curr[j] = value[0];

	for (int i = 1; i < n; i++)
	{

		for (int j = W; j >= 0; j--)
		{

			int in = 0;

			if (weight[i] <= j)

				in = value[i] + curr[j - weight[i]];

			int ex = curr[j];

			curr[j] = max(in, ex);
		}
	}

	return curr[W];
}

int knapsack(vector<int> weight, vector<int> value, int n, int maxWeight)
{
	// Method 1

	// start from last index
	//  return solve(weight, value, maxWeight, n - 1);

	// Method 2

	// 2D dp
	// paremeter changing
	// vector<vector<int>> dp(n, vector<int>(maxWeight + 1, -1));

	// return recurMEMO(weight, value, maxWeight, n - 1, dp);

	// Method 3

	return tabulation(weight, value, maxWeight, n);

	// SPACE OPTIMIZATION --> using two vectors

	// return SO(weight,value,n,maxWeight);

	// SPACE OPTIMIZATION --> using single vector

	return SO2(weight, value, n, maxWeight);
}