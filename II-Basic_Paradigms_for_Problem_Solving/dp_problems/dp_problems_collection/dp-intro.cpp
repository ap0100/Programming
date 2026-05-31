#include <bits/stdc++.h>
using namespace std;

//4th order Fibonacci
//memoization dp
vector<long long> arr(1000, 0);
long long fib_memo(int n) {
    if (n<4) return 1;
    if (!arr[n]) return arr[n]=fib_memo(n-1)+fib_memo(n-2)+fib_memo(n-3)+fib_memo(n-4);
    return arr[n];
}

int fib_basic_rec(int n) {
    if (n<4) return 1;
    return fib_basic_rec(n-1)+fib_basic_rec(n-2)+fib_basic_rec(n-3)+fib_basic_rec(n-4);
}

//tabulation dp
vector<long long> arr2(1000);
long long fib_iterative(int n) {
    arr2[0]=1;
    arr2[1]=1;
    arr2[2]=1;
    arr2[3]=1;
    for (int i=4; i<=n; i++) arr2[i]=arr2[i-1]+arr2[i-2]+arr2[i-3]+arr2[i-4];
    return arr2[n];
}

int fib_iterative2(int n) {
    int p1=1, p2=1, p3=1, p4=1;
    int res=0;
    if (n<4) return 1;
    for (int i=4; i<=n; i++) {
        if (i%4==0) {
            res=p1+p2+p3+p4;
            p4=res;
        }else if (i%4==1) {
            res=p1+p2+p3+p4;
            p3=p4;
            p4=res;
        }else if (i%4==2) {
            res=p1+p2+p3+p4;
            p2=p3;
            p3=p4;
            p4=res;
        }else {
            res=p1+p2+p3+p4;
            p1=p2;
            p2=p3;
            p3=p4;
            p4=res;
        }
    }

    return res;
}


//----------------------------------------------------------------------------------------------------------------------


//Optimal coin change
//memoization
vector<int> coins={1,5,8,10};
int change_memo(int c, vector<int> &change){
    for (int i=0; i<coins.size(); i++) {
        if (c==coins[i]) return change[c]=1;
        if(c>coins[i]) change[c]=min(change[c], 1+change_memo(c-coins[i], change));
    }

    return change[c];
}


int main() {
    int n;
    cin >> n;

    vector<int> change(n+1, INT_MAX);

    cout << change_memo(n, change);
    //cout << fib_iterative2(n);


    return 0;
}
