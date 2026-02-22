#include <iostream>
#include <vector>
#include <climits>
using namespace std;

//za min subarray sum, istata logika, samo namesto max, se koristi min funkcija i namesto INT_MIN, se stava INT_MAX (bukvalno sekade kade ima max, se stava min)
int find_cross_max(vector<int> &arr, int l, int m, int r) {
    int sum=0, left_max=INT_MIN, right_max=INT_MIN;

    for (int i=m; i>=l; i--) {
        sum+=arr[i];
        left_max=max(left_max, sum);
    }

    sum=0;
    for (int i=m+1; i<=r; i++) {
        sum+=arr[i];
        right_max=max(right_max, sum);
    }

    return left_max+right_max;
}

int find_max_sum_in_subarr(vector<int> &arr, int l, int r) {
    int m=(l+r)/2;

    if (l==r) return arr[l];

    int left_max=find_max_sum_in_subarr(arr, l, m),
        right_max=find_max_sum_in_subarr(arr, m+1, r),
        cross_max=find_cross_max(arr, l, m, r);

    return max(cross_max, max(left_max, right_max));
}

int main() {
    cout << "enter array (enter any other non-integer character to stop input): " << '\n';
    int input;
    vector<int> arr;

    while (cin >> input) arr.push_back(input);

    cin.clear();
    cin.ignore(1000, '\n');

    cout << "max sum: " << find_max_sum_in_subarr(arr, 0, arr.size()-1);

    return 0;
}