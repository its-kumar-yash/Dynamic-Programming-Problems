// You are given a 2D array of integers envelopes where envelopes[i] = [wi, hi] represents the width and the height of an envelope.

// One envelope can fit into another if and only if both the width and height of one envelope are greater than the other envelope's width and height.

// Return the maximum number of envelopes you can Russian doll (i.e., put one inside the other).

// Note: You cannot rotate an envelope.

//LC - 354

#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    static bool cmp(vector<int> &a, vector<int> &b){
        if(a[0] == b[0]){
            //decreasing order of height
            return a[1] > b[1];
        }
        //increasing order of width
        return a[0] < b[0];
    }

    int maxEnvelopes(vector<vector<int>>& envelopes) {
        //sort by length in increasing order.
        //if length is same, sort by breadth in decreasing order
        sort(envelopes.begin(), envelopes.end(), cmp);

        //LIS
        int n  = envelopes.size();
        vector<int> ans;
        ans.push_back(envelopes[0][1]);

        for(int i = 0; i < n; i++){
            if(envelopes[i][1] > ans.back()){
                ans.push_back(envelopes[i][1]);
            }
            else{
                int idx = lower_bound(ans.begin(), ans.end(), envelopes[i][1]) - ans.begin();
                ans[idx] = envelopes[i][1];
            }
        }

        return ans.size();
    }
};

int main(){
    
    return 0;
}