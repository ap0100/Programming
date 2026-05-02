#include <bits/stdc++.h>
using namespace std;


int main() {
    int n;
    cin >> n;

    vector distances(n, vector<int>(n));
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cin >> distances[i][j];
            if (i==j) distances[i][j]=0;
            if (distances[i][j]==0 && i!=j) distances[i][j]=INT_MAX; //if there's no path, input is 0, but weight should be set to infinity
        }
    }

    //bottom-up - tabulation implementation
    for (int k=0; k<n; k++) {
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                if (distances[i][k]<INT_MAX && distances[k][j]<INT_MAX) {
                    distances[i][j]=min(distances[i][j], distances[i][k]+distances[k][j]);
                }
            }
        }
    }

    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (distances[i][j]>=INT_MAX) cout << "inf. ";
            else cout << distances[i][j] << " ";
        }
        cout << '\n';
    }


    return 0;
}