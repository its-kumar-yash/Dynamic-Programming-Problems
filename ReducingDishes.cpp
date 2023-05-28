// A chef has collected data on the satisfaction level of his n dishes. Chef can cook any dish in 1 unit of time.

// Like-time coefficient of a dish is defined as the time taken to cook that dish including previous dishes multiplied by its satisfaction level i.e. time[i] * satisfaction[i].

// Return the maximum sum of like-time coefficient that the chef can obtain after dishes preparation.

// Dishes can be prepared in any order and the chef can discard some dishes to get this maximum value.

//1402. Reducing Dishes
#include<bits/stdc++.h>
using namespace std;


class Solution {
public:
//0 - 1 KnapSack Problem  
    int n;
    //Recursion - TLE
    int solve(vector<int> &satisfaction, int idx, int time){
        //base case
        //no dish present
        if(idx == n){
            return 0;
        }

        //include the current dish
        //time will increase only when we create a dish
        //not when we exclude it
        int incl = satisfaction[idx]*time + solve(satisfaction, idx + 1, time + 1);

        //exclude the current dish
        int excl = solve(satisfaction, idx + 1, time);

        //max of both
        return max(incl, excl);
    }

    //Recursion + MEMO - 44 ms

    int recurMEMO(vector<int> &satisfaction, int idx, int time, vector<vector<int>> &dp){
        
        if(idx == n){
            return 0;
        }

        if(dp[idx][time] != -1){
            return dp[idx][time];
        }

        int incl = satisfaction[idx]*time + recurMEMO(satisfaction, idx + 1, time + 1, dp);

        int excl = recurMEMO(satisfaction, idx + 1, time, dp);

        return dp[idx][time] = max(incl, excl);
    }

    //Tabulation - 36 ms

    int tabulation(vector<int> &satisfaction, int &n){
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));

        for(int idx = n - 1; idx >= 0; idx--){
            for(int time = idx; time >= 0; time--){
                int incl = satisfaction[idx]*(time + 1)+ dp[idx + 1][time + 1];

                int excl = dp[idx + 1][time];

                dp[idx][time] = max(incl, excl);
            }
        }

        return dp[0][0];
    }


    //Space Optimization - 26 ms
    int spaceOP(vector<int> &satisfaction, int &n){
        vector<int> curr(n + 1, 0);
        vector<int> next(n + 1, 0);

        for(int idx = n - 1; idx >= 0; idx--){
            for(int time = idx; time >= 0; time--){
                int incl = satisfaction[idx]*(time + 1) + next[time + 1];
                int excl = next[time];

                curr[time] = max(incl, excl);
            }

            next = curr;
        }

        return next[0];
    }

    int maxSatisfaction(vector<int>& satisfaction) {
        n = satisfaction.size();
        //sort the array 
        sort(satisfaction.begin(), satisfaction.end());

        //Method 1
        return solve(satisfaction, 0, 1);

        //Method 2
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, -1));

        return recurMEMO(satisfaction, 0, 1, dp);
    
        //Method 3
        return tabulation(satisfaction, n);

        //Method 4
        return spaceOP(satisfaction, n);
    }
};



int main(){
    
    return 0;
}