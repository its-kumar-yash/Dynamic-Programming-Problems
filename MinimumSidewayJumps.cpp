// There is a 3 lane road of length n that consists of n + 1 points labeled from 0 to n. A frog starts at point 0 in the second lane and wants to jump to point n. However, there could be obstacles along the way.

// You are given an array obstacles of length n + 1 where each obstacles[i] (ranging from 0 to 3) describes an obstacle on the lane obstacles[i] at point i. If obstacles[i] == 0, there are no obstacles at point i. There will be at most one obstacle in the 3 lanes at each point.

// For example, if obstacles[2] == 1, then there is an obstacle on lane 1 at point 2.
// The frog can only travel from point i to point i + 1 on the same lane if there is not an obstacle on the lane at point i + 1. To avoid obstacles, the frog can also perform a side jump to jump to another lane (even if they are not adjacent) at the same point if there is no obstacle on the new lane.

// For example, the frog can jump from lane 3 at point 3 to lane 1 at point 3.
// Return the minimum number of side jumps the frog needs to reach any lane at point n starting from lane 2 at point 0.

// Note: There will be no obstacles on points 0 and n.

//LC - 1824

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    //Recursion - TLE
    int solve(vector<int> &obstacles, int currLane, int currPos, int n){
        //base case
        //when reached the last position
        if(currPos == n){
            return 0;
        }

        //check karo same lane me agli position pe obstacle toh nhi hai
        if(obstacles[currPos + 1] != currLane){
            //seedhe chale jao aage
            return solve(obstacles, currLane, currPos + 1, n);
        }
        //agar aage obstacle hai
        else{
            //then do side ways jump
            //for jump we have three options
            int ans = INT_MAX; // multiple jumping options can be possible so find the minimum one
            for(int i = 1; i <= 3; i++){
                if(currLane != i && obstacles[currPos] != i){
                   ans = min(ans, 1 + solve(obstacles, i, currPos, n)); 
                }  
            }

            return ans;
        }
    }

    // Recursion + MEMO - 354 ms
    int recurMEMO(vector<int> &obstacles, int currLane, int currPos, int n, vector<vector<int>> &dp){
        if(currPos == n){
            return 0;
        }

        if(dp[currLane][currPos] != -1){
            return dp[currLane][currPos];
        }

        //check karo same lane me agli position pe obstacle toh nhi hai
        if(obstacles[currPos + 1] != currLane){
            //seedhe chale jao aage
            return dp[currLane][currPos] = recurMEMO(obstacles, currLane, currPos + 1, n, dp);
        }
        //agar aage obstacle hai
        else{
            //then do side ways jump
            //for jump we have three options
            int ans = INT_MAX; // multiple jumping options can be possible so find the minimum one
            for(int i = 1; i <= 3; i++){
                if(currLane != i && obstacles[currPos] != i){
                   ans = min(ans, 1 + recurMEMO(obstacles, i, currPos, n, dp)); 
                }  
            }

            return dp[currLane][currPos] = ans;
        }

    }

    //Tabulation - 397 ms
    int tabulation(vector<int> &obstacles){
        int n = obstacles.size() - 1;
        // dp[i][j] ->
        vector<vector<int>> dp(4, vector<int>(obstacles.size(), 1e9));

        //base case - already at dest position
        dp[0][n] = 0;
        dp[1][n] = 0;
        dp[2][n] = 0;
        dp[3][n] = 0;

        //now start from [pos][n - 1] ----> (2, 0)
        for(int currPos = n - 1; currPos >= 0; currPos--){
            for(int currLane = 1; currLane <= 3; currLane++){
                if(obstacles[currPos + 1] != currLane){
                //seedhe chale jao aage
                    dp[currLane][currPos] = dp[currLane][currPos + 1] ;
                }

                //agar aage obstacle hai
                else{
                //then do side ways jump
                //for jump we have three options
                    int ans = 1e9; // multiple jumping options can be possible so find the minimum one
                    for(int i = 1; i <= 3; i++){
                        if(currLane != i && obstacles[currPos] != i){
                            ans = min(ans, 1 + dp[i][currPos + 1]); 
                        }  
                    }

                    dp[currLane][currPos] = ans;
                }
            }
            
        }

        return min({dp[2][0], 1 + dp[1][0], 1 + dp[3][0]});
    }

    //Space Optimization - 433 ms

    int spaceOP(vector<int> &obstacles){
        //using two vectors
        int n = obstacles.size() - 1;
        vector<int> curr(4, INT_MAX);
        vector<int> next(4, INT_MAX);

        next[0] = 0;
        next[1] = 0;
        next[2] = 0;
        next[3] = 0;

        for(int currPos = n - 1; currPos >= 0; currPos--){
            for(int currLane = 1; currLane <= 3; currLane++){
                if(obstacles[currPos + 1] != currLane){
                //seedhe chale jao aage
                    curr[currLane] = next[currLane] ;
                }

                //agar aage obstacle hai
                else{
                //then do side ways jump
                //for jump we have three options
                    int ans = 1e9; // multiple jumping options can be possible so find the minimum one
                    for(int i = 1; i <= 3; i++){
                        if(currLane != i && obstacles[currPos] != i){
                            ans = min(ans, 1 + next[i]); 
                        }  
                    }

                    curr[currLane] = ans;
                }
            }

            next = curr;
        }

        return min({next[2], 1 + next[1], 1 + next[3]});
    }


    int minSideJumps(vector<int>& obstacles) {
        int n = obstacles.size();

        //Method 1 
        return solve(obstacles, 2, 0, n);

        //Method 2
        // total lanes = 4(considering 0th lane also)
        vector<vector<int>> dp(4, vector<int>(n + 1, -1));
        return recurMEMO(obstacles, 2, 0, n, dp);

        //Method 3
        return tabulation(obstacles);

        //Method 4
        return spaceOP(obstacles);
    }
};


int main(){
    
    return 0;
}