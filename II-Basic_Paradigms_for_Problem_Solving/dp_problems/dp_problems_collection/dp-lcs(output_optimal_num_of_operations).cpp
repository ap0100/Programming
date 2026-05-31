#include <bits/stdc++.h>
using namespace std;

string X, Y;

//top-down/memoization
vector<vector<int>>  memo;
int lcs(int i, int j){
    if(i==X.size() || j==Y.size()) return 0;
    if(memo[i][j]!=-1) return memo[i][j];
    if(X[i]==Y[j]) return memo[i][j]=1+lcs(i+1, j+1);

    return memo[i][j]=max(lcs(i+1,j), lcs(i,j+1));
}


int main() {
    cin >> X >> Y;
    int x=X.size(), y=Y.size();

    memo.assign(x, vector<int>(y,-1));
    cout << lcs(0,0);

    //bottom-up - tabulation approach
    vector res(x+1, vector(y+1, 0));

    for (int i=1; i<x+1; i++) {
        for (int j=1; j<y+1; j++) {
            if (X[i-1]==Y[j-1]) res[i][j]=res[i-1][j-1]+1;
            else res[i][j]=max(res[i-1][j], res[i][j-1]);
        }
    }

    cout << res[x][y]; //tehnichki res[x][y]-1 e tochnoto ako gi broime tochno samo + i - operaciite


    return 0;
}
