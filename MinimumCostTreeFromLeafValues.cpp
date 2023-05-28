//LC - 1130

// Given an array arr of positive integers, consider all binary trees such that:

// Each node has either 0 or 2 children;
// The values of arr correspond to the values of each leaf in an in-order traversal of the tree.
// The value of each non-leaf node is equal to the product of the largest leaf value in its left and right subtree, respectively.
// Among all possible binary trees considered, return the smallest possible sum of the values of each non-leaf node. It is guaranteed this sum fits into a 32-bit integer.

// A node is a leaf if and only if it has zero children.

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    //Recursion - TLE
    int solve(vector<int>& arr, map<pair<int, int>, int> &maxi, int leftIdx, int rightIdx){
        //base case
        //leaf node
        if(leftIdx == rightIdx){
            return 0;
        }

        int ans = INT_MAX;

        //making paritioning
        for(int i = leftIdx; i < rightIdx; i++){
            int leftAns = solve(arr, maxi, leftIdx, i);
            int rightAns = solve(arr, maxi, i + 1, rightIdx);
            int currAns = leftAns + rightAns + maxi[{leftIdx, i}]*maxi[{i + 1, rightIdx}];
            ans = min(ans,  currAns);
        }

        return ans;

    }

    //Recursion + MEMO - 55 ms
    int recurMEMO(vector<int>& arr, map<pair<int, int>, int> &maxi, int leftIdx, int rightIdx, vector<vector<int>> &dp){
        //base case
        //leaf node
        if(leftIdx == rightIdx){
            return 0;
        }

        if(dp[leftIdx][rightIdx] != -1){
            return dp[leftIdx][rightIdx];
        }


        int ans = INT_MAX;

        //making paritioning
        for(int i = leftIdx; i < rightIdx; i++){
            int leftAns = recurMEMO(arr, maxi, leftIdx, i, dp);

            int rightAns = recurMEMO(arr, maxi, i + 1, rightIdx, dp);
            
            int currAns = leftAns + rightAns + maxi[{leftIdx, i}]*maxi[{i + 1, rightIdx}];
            
            ans = min(ans,  currAns);
        }

        return dp[leftIdx][rightIdx] = ans;
    }

    //Tabulation - 53 ms
    int tabulation(vector<int> &arr, int &n, map<pair<int, int>, int> &maxi){
        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));

        for(int left = n - 1; left >= 0; left--){
            for(int right = left; right <= n - 1; right++){
                if(left == right){
                    continue;
                }
                else{
                    int ans = INT_MAX;
                    for(int i = left; i < right; i++){
                        int leftAns = dp[left][i];

                        int rightAns = dp[i + 1][right];
            
                        int currAns = leftAns + rightAns + maxi[{left, i}]*maxi[{i + 1, right}];
                        ans = min(ans,  currAns);
                    }   
                    dp[left][right] = ans;
                }
            }

        }

        return dp[0][n - 1];
    }


    int mctFromLeafValues(vector<int>& arr) {
        int n = arr.size();
        //precomputing maximum value between two indexes
        map<pair<int, int>, int> maxi;

        for(int i = 0; i < n; i++){
            //for leaf nodes
            maxi[{i, i}] = arr[i];
            for(int j = i + 1; j < n; j++){
                maxi[{i, j}] = max(arr[j], maxi[{i, j - 1}]);
            }
        }

        //Method 1
        return solve(arr, maxi, 0, n - 1);

        //Method 2
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));

        return recurMEMO(arr, maxi, 0, n - 1, dp);

        //Method 3
        return tabulation(arr, n, maxi);

    }
};


int main(){
    
    return 0;
}