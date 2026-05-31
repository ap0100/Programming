#include <bits/stdc++.h>
using namespace std;

static const int MOD=1e9+7;
int n;
vector<string> grid;

//bottom-up/tabulation
int solve_tab(){
    vector<vector<int>> dp(n, vector<int>(n, 0));

    if(grid[0][0]=='*') return 0;

    grid[0][0]=1;

    for(int j=1; j<n; j++) if(grid[0][j]=='.') dp[0][j]=dp[0][j-1];
    for(int i=1; i<n; i++) if(grid[i][0]=='.') dp[i][0]=dp[i-1][0];
    for(int i=1; i<n; i++){
        for(int j=1; j<n; j++){
            if(grid[i][j]=='*') dp[i][j]=0;
            else dp[i][j]=(dp[i-1][j]+dp[i][j-1])%MOD;
        }
    }

    return dp[n-1][n-1];
}

//top-down/memoization
vector<vector<int>> memo;

int solve(int i, int j){
    if(i>=n || j>=n) return 0;
    if(grid[i][j]=='*') return 0;
    if(i==n-1 && j==n-1) return 1;
    if(memo[i][j]!=-1) return memo[i][j];

    long long ways=solve(i+1,j)+solve(i,j+1);
    return memo[i][j]=ways%MOD;
}

int solve_memo(){
    memo.assign(n, vector<int>(n, -1));
    return solve(0,0);
}


int main(){
    cin >> n;
    grid.resize(n);

    for(auto &r: grid) cin >> r;

    cout << solve_tab() << '\n';
    cout << solve_memo();

    return 0;
}
