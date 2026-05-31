#include <bits/stdc++.h>
using namespace std;

string s, p;

//bottom-up/tabulation
bool wildcard_match(){
    vector dp(s.size()+1, vector<bool>(p.size()+1, 0));
    dp[0][0]=1;

    for(int i=1; i<=p.size(); i++) if(p[i-1]=='*') dp[0][i]=dp[0][i-1];

    for(int i=1; i<=s.size(); i++){
        for(int j=1; j<=p.size(); j++){
            if(p[j-1]=='*') dp[i][j]=dp[i][j-1]||dp[i-1][j];
            else if(p[j-1]=='?' || p[j-1]==s[i-1]) dp[i][j]=dp[i-1][j-1];
        }
    }

    return dp[s.size()][p.size()];
}

//top-down/memoization
vector<vector<int>> memo;

bool solve(int i, int j){
    if(j==p.size()) return i==s.size();
    if(memo[i][j]!=-1) return memo[i][j];

    bool ans=0;//false
    if(p[j]=='*'){
        ans=solve(i, j+1);
        if(i<s.size()) ans|=solve(i+1, j);
    }else if(i<s.size() && (p[j]=='?' || p[j]==s[i])) ans=solve(i+1, j+1);

    return memo[i][j]=ans;
}

int main(){
    cin >> s >> p;
    memo.assign(s.size()+1, vector<int>(p.size()+1, -1));

    cout << (wildcard_match() ? "true" : "false") << '\n';
    cout << (solve(0,0) ? "true" : "false");

    return 0;
}
