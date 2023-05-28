//LC - 85

//Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.


#include<bits/stdc++.h>
using namespace std;


class Solution {
public:
    vector<int> rightBoundary(vector<int> nums, int n){
        vector<int> ans(n);
        stack<int> st;

        st.push(n - 1);
        ans[n - 1] = n;

        for(int i = n - 2; i >= 0; i--){
            
            while(!st.empty() && nums[i] <= nums[st.top()]){
                st.pop();
            }

            if(st.empty()){
                ans[i] = n;
            }
            else{
                ans[i] = st.top();
            }

            st.push(i);
        }

        return ans;
    }
    vector<int> leftBoundary(vector<int> nums, int n){
        vector<int> ans(n);
        stack<int> st;

        st.push(0);
        ans[0] = -1;

        for(int i = 1; i < n; i++){
            
            while(!st.empty() && nums[i] <= nums[st.top()]){
                st.pop();
            }

            if(st.empty()){
                ans[i] = -1;
            }
            else{
                ans[i] = st.top();
            }

            st.push(i);
        }

        return ans;
    }
    //Function to find largest rectangular area possible in a given histogram.
    int largestArea(vector<int> nums){
        int n = nums.size();
        
        vector<int> rb(n);
        rb = rightBoundary(nums, n);

        vector<int> lb(n);
        lb = leftBoundary(nums, n);

        int maxArea = INT_MIN;

        for(int i = 0; i < n; i++){
            
            int width = rb[i] - lb[i] - 1;

            int area = width * nums[i];

            maxArea = max(maxArea, area);
        }

        return maxArea;
    }
    int maximalRectangle(vector<vector<char>>& matrix) {

        if(matrix.size() == 0){
            return 0;
        }

        vector<int> height(matrix[0].size(), 0);

        int maxArea = INT_MIN;

        for(int i = 0; i < matrix.size(); i++){ // Updating in the matrix itself

            for(int j = 0; j < matrix[0].size(); j++){

                if(matrix[i][j] == '0'){// if zero is there leave that element as it is coz it wll break the height of that building
                    height[j] = 0;
                }

                else{
                    height[j]++; // else add the previous height of that building
                }
            }
            int area = largestArea(height);

            maxArea = max(maxArea, area);
        }

        return maxArea;
    }
};

int main(){
    
    return 0;
}