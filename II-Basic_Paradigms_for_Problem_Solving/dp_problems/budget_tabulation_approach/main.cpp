#include <bits/stdc++.h>
using namespace std;

int m,c,k;

int main() {
    cin >> m >> c;

    vector<vector<int>> prices(c);
    for (int i=0; i<c; i++) {
        cin >> k;
        prices[i].resize(k);
        for (int j=0; j<k; j++) cin >> prices[i][j];
    }

    //bottom-up - tabulation approach
    vector p(c+1, vector(m+1, 0));
    p[0][0]=1;

    for (int i=0; i<c; i++) {
        for (int j=0; j<=m; j++) {
            if (!p[i][j]) continue;

            for (int price: prices[i]) {
                if (j+price<=m) p[i+1][j+price]=1;
            }
        }
    }

    for (int i=m; i>=0; i--) {
        if (p[c][i]) {
            cout << i;
            break;
        }
    }


    return 0;
}