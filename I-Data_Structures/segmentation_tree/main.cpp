#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;


void print_segment_tree(const vector<int>& v) {
    for (int i=0; i<v.size(); i++) cout << v[i] << ", ";
    cout << '\n';
}

//FINDING MINIMUM
void make_segment_tree(vector<int> &tree, const vector<int>& vals, const int pos, const int L, const int R) {
   if (L==R) {
       tree[pos]=vals[L];
       return;
   }

    int middle=(L+R)/2;
    make_segment_tree(tree, vals, 2*pos, L, middle);
    make_segment_tree(tree, vals, 2*pos+1, middle+1, R);

    tree[pos]=min(tree[2*pos], tree[2*pos+1]);
}

int query(const vector<int> &v, const int l, const int r, const int L, const int R, const int pos) {
    if (L>=l && r>=R) return v[pos];
    if (l>R || L>r) return INT_MAX;

    int middle=(L+R)/2;
    return min( query(v, l, r, L, middle, 2*pos), query(v, l, r, middle+1, R, 2*pos+1));
}

//--------------------------------------------------------------------------------------

//FINDING SUM
/*void make_segment_tree(vector<int> &tree, const vector<int>& vals, const int pos, const int L, const int R) {
    if (L==R) {
        tree[pos]=vals[L];
        return;
    }

    int middle=(L+R)/2;
    make_segment_tree(tree, vals, 2*pos, L, middle);
    make_segment_tree(tree, vals, 2*pos+1, middle+1, R);

    tree[pos]=tree[2*pos]+tree[2*pos+1];
}

int query(const vector<int> &v, const int l, const int r, const int L, const int R, const int pos) {
    if (L>=l && r>=R) return v[pos];
    if (l>R || L>r) return 0;

    int middle=(L+R)/2;
    return query(v, l, r, L, middle, 2*pos)+query(v, l, r, middle+1, R, 2*pos+1);
}
*/

int main() {
    vector<int> numbers={3,2,4,1,8,16,11};
    int n=numbers.size();

    vector<int> tree(4*n, INT_MAX);

    make_segment_tree(tree, numbers, 1, 0, n-1);
    //print_segment_tree(tree);

    cout << query(tree, 2, 5, 0, n-1, 1) << '\n';
    //print_segment_tree(tree);

    return 0;
}