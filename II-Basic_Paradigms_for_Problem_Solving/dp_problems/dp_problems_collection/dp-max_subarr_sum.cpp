#include <bits/stdc++.h>
using namespace std;


int main() {
    /*maximum subarray problem
    dadena niza so n elementi (koi moze da se i neg), se bara podniza so max suma*/
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i=0; i<n; i++) cin >> arr[i];

    //kadane
    int current=arr[0], max_now=arr[0];
    for (int i=1; i<n; i++) {
        current=max(arr[i], arr[i]+current);
        max_now=max(max_now, current);
    }

    cout << max_now;


    //prefix dp
    vector<int> pref(n);
    pref[0]=arr[0];
    for(int i=1; i<n; i++) pref[i]=pref[i-1]+arr[i];

    int min_pref=0, best=INT_MIN;
    for(int i=0; i<n; i++){
        best=max(best, pref[i]-min_pref);
        min_pref=min(min_pref, pref[i]);
    }

    cout << best;


    //2D dp
    vector dp(n, vector<int>(n,0));
    int brute=INT_MIN;
    for(int i=0; i<n; i++){
        dp[i][i]=arr[i];
        brute=max(brute, arr[i]);

        for(int j=i+1; j<n; j++){
            dp[i][j]=dp[i][j-1]+arr[j];
            brute=max(brute, dp[i][j]);
        }
    }

    cout << brute;


    return 0;
}
