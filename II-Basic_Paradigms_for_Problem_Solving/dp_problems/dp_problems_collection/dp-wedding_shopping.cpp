#include <bits/stdc++.h>
using namespace std;

int m, c, k;

//top-down - memoization approach
int memo (int money, int n, vector<vector<int>> &p, vector<vector<int>> &prices, vector<vector<bool>> &v) {
    if (money<0) return -1;
    if (n==c) return m-money;
    if (v[money][n]) return p[money][n];

    v[money][n]=true;

    int res=-1;
    for(int i=0; i<prices[n].size(); i++)
        res=max(res, memo(money-prices[n][i], n+1, p, prices, v));
    return p[money][n]=res;
}


int main() {
    /*M-budget, C-broj razlichni parchinja shto trb da se kupat, K-cenite, od sekoj model trb tochno edno*/
    cin >> m >> c;

    int ans=0;
    vector<vector<int>> prices(c);
    for (int i=0; i<c; i++) {
        cin >> k;
        prices[i].resize(k);
        for (int j=0; j<k; j++) cin >> prices[i][j];
    }

    //top-down/memoization
    vector p(m+1, vector(c, -1));
    vector visited(m+1, vector(c, false));
    ans=memo(m, 0, p, prices, visited);
    ans<0 ? cout << "no solution" : cout << ans;
    

    //bottom-up/tabulation
    vector dp(c+1, vector(m+1, 0));
    dp[0][0]=1;

    for(int i=0; i<c; i++){
        for(int j=0; j<=m; j++){
            if(!dp[i][j]) continue;
            for(int price: prices[i]) if(j+price<=m) dp[i+1][j+price]=1;
        }
    }

    for(int i=m; i>=0; i--){
        if(dp[c][i]){
            ans=i;
            break;
        }
    }
    ans<0 ? cout << "no solution" : cout << ans;


    return 0;
}


//test case
/*
m=200, c=6, c1={20,15,18,60}, c2={20,80,45,100}, c3={18,23}, c4={22,90,18}, c5={12,18,37,59}, c5={1,2,3,8};

200 6
4
20 15 18 60
4
20 80 45 100
2
18 23
3
22 90 18
4
12 18 37 59
4
1 2 3 8
*/
