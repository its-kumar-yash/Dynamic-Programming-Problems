// You have a convex n-sided polygon where each vertex has an integer value. You are given an integer array values where values[i] is the value of the ith vertex (i.e., clockwise order).

// You will triangulate the polygon into n - 2 triangles. For each triangle, the value of that triangle is the product of the values of its vertices, and the total score of the triangulation is the sum of these values over all n - 2 triangles in the triangulation.

// Return the smallest possible total score that you can achieve with some triangulation of the polygon.

//LC _ 1039

#include <bits/stdc++.h>
using namespace std; 

//Recursion

int solve(vector<int> &arr, int i, int j){
	//base case
	//only two vertices are present
	//cannot form triangle
	if(i + 1 == j){
		return 0;
	}

	//now try for each value of k
	//that lies between i + 1 to j - 1
	int ans = INT_MAX;
	for(int k = i + 1; k < j; k++){
		//min(ans , curr triangle + subproblems)
		ans = min(ans, (arr[i]*arr[j]*arr[k]) + solve(arr, i, k) + solve(arr, k, j));
	}

	return ans;
}

//Recursion + MEMO

int recurMEMO(vector<int> &arr, int i, int j, vector<vector<int>> &dp){
	if(i + 1 == j){
		return 0;
	}

	if(dp[i][j] != -1){
		return dp[i][j];
	}

	int ans = INT_MAX;

	for(int k = i + 1; k < j; k++){
		//min(ans , curr triangle + subproblems)
		ans = min(ans, (arr[i]*arr[j]*arr[k]) + recurMEMO(arr, i, k, dp) + recurMEMO(arr, k, j, dp));

	}
	dp[i][j] = ans;

	return dp[i][j];
}

//Tabulation

int tabulation(vector<int>&arr, int &n){
	//create dp
	vector<vector<int>> dp(n, vector<int>(n, 0));


	for(int i = n - 1; i >= 0; i--){
		//min three points are req to form a triangle
		for(int j = i + 2; j < n; j++){
			int ans = INT_MAX;
			for(int k = i + 1; k < j; k++){
				ans = min(ans, (arr[i]*arr[j]*arr[k]) + dp[i][k] + dp[k][j]);
			}
			dp[i][j] = ans;
		}
	}

	return dp[0][n - 1];
}




int minimumTriangleScore(vector<int> &arr, int n){
	//Method 1
	// return solve(arr, 0, n - 1);

	//Method 2
	// vector<vector<int>> dp(n, vector<int>(n, -1));
	// return recurMEMO(arr, 0, n - 1, dp);

	//Method 3
	return tabulation(arr, n);
}