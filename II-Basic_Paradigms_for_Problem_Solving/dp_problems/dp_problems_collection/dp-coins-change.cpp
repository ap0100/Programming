#include <bits/stdc++.h>
using namespace std;

int coins[]={1,3,11,21};

//bottom-up/tabulation approach
int change_tab(int c) {
    vector change(c+1, INT_MAX);
    change[0]=0;

    for (int i=1; i<=c; i++)
        for (int coin: coins)
            if (i-coin>=0 && change[i-coin]!=INT_MAX)
                change[i]=min(change[i], change[i-coin]+1);

    return change[c];
}

//top-down/memoization
vector<int> memo;
int change_memo(int c){
    if(c==0) return 0;
    if(c<0) return INT_MAX;
    if(memo[c]!=-1) return memo[c];

    int ans=INT_MAX;
    for(int coin:coins){
        int sub=change_memo(c-coin);
        if(sub!=INT_MAX) ans=min(ans, sub+1);
    }
    return memo[c]=ans;
}


int main() {
    int c[]={124,226,121};

    for (int ch: c){
        memo.assign(ch+1, -1);
        cout << change_memo(ch) << '\n';
        cout << change_tab(ch) << '\n';
    }


    return 0;
}
