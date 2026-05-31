#include <bits/stdc++.h>
using namespace std;

using ll=long long;
const ll NEG=LLONG_MIN/4;


int main(){
    int n;
    cin >> n;

    vector<ll> A(n);
    for(int i=0; i<n; i++) cin >> A[i];

    ll dp1=NEG, dp2=NEG, dp3=NEG, dp4=NEG;
    for(int i=0; i<n; i++){
        dp4=max(dp4, dp3+A[i]);//+A[s]
        dp3=max(dp3, dp2-A[i]);//-A[r]
        dp2=max(dp2, dp1+A[i]);//+A[q]
        dp1=max(dp1, -A[i]);//-A[p]
    }

    cout << dp4;


    return 0;
}
