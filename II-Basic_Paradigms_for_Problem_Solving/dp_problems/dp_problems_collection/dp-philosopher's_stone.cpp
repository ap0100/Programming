#include <bits/stdc++.h>
using namespace std;

int h,w;
vector<vector<int>> stones;

//top-down/memoization
vector<vector<int>> memo;

int solve(int i, int j){
    if(j<0 || j>=w) return 0;
    if(i==h-1) return stones[i][j];
    if(memo[i][j]!=-1) return memo[i][j];

    return memo[i][j]=stones[i][j]+max({solve(i+1,j), solve(i+1,j+1), solve(i+1,j-1)});
}

int solve_memo(){
    memo.assign(h, vector<int>(w, -1));

    int ans=0;
    for(int j=0; j<w; j++) ans=max(ans, solve(0,j));
    return ans;
}


//bottom-up/tabulation
int solve_tab(){
    vector<vector<int>> dp=stones;

    for(int i=1; i<h; i++){
        for(int j=0; j<w; j++){
            int best=dp[i-1][j];

            if(j>0) best=max(best, dp[i-1][j-1]);
            if(j+1<w) best=max(best, dp[i-1][j+1]);

            dp[i][j]+=best;
        }
    }

    int ans=0;
    for(int j=0; j<w; j++) ans=max(ans, dp[h-1][j]);
    return ans;
}


int main(){
    int t;
    cin >> t;

    for(int k=0; k<t; k++){
        cin >> h >> w;

        stones.assign(h, vector<int>(w));

        for(int i=0; i<h; i++)
            for(int j=0; j<w; j++)
               cin >>stones[i][j];

        cout << solve_tab() << '\n';
        cout << solve_memo();
    }


    return 0;
}
