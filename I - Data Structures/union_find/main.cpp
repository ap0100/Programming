#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
#include "include/UnionFind.h"
using namespace std;


//----------Number of Closed Islands-------------------------------------------
int count_closed_islands(const int* grid, const int rows, const int columns) {
    int edgeIndex=rows*columns;
    UnionFind land(rows*columns+1);

    for (int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++) {
            int currentIndex=i*columns+j;

            if (grid[currentIndex]==1) continue;

            if (i==0 || i==rows-1 || j==0 || j==columns-1)
                land.unite(currentIndex, edgeIndex, "by size", "simple");

            if (j+1<columns && grid[i*columns+(j+1)]==0)
                land.unite(currentIndex, i*columns+(j+1), "by size", "simple");

            if (i+1<rows && grid[(i+1)*columns+j]==0)
                land.unite(currentIndex, (i+1)*columns+j, "by size", "simple");
        }
    }

    set<int> closed_islands;
    int edge=land.smart_find(edgeIndex);

    for (int i=0; i<rows*columns; i++) {
        if (grid[i]==0) {
            int root=land.smart_find(i);
            if (root!=edge) closed_islands.insert(root);
        }
    }

    return closed_islands.size();
}


//----------Find If Path Exits in Graph-------------------------------
bool path_in_graph(const vector<vector<int>> &edges, int s, int d, int n) {
    UnionFind graph(n);
    for (int i=0; i<n-1; i++) {
        graph.unite(edges[i][0], edges[i][1], "by rank", "smart");
    }

    return graph.smart_find(s)==graph.smart_find(d);
}


//----------GCD Sort of an Array-------------------------------
int gcd(int a, int b) {
    if (b==0) return a;
    return gcd(b, a%b);
}

bool gcd_sort(const vector<int> &nums) {
    UnionFind nums_unions(nums.size());
    vector<pair<int,int>> sorted;

    for (int i=0; i<nums.size()-1; i++)
        for (int j=i+1; j<nums.size(); j++)
            if(gcd(nums[i], nums[j]) > 1) nums_unions.unite(i, j, "by rank", "smart");

    for (int i=0; i<nums.size()-1; i++)
        sorted.push_back({nums[i], i});

    sort(sorted.begin(), sorted.end());

    for (int i=0; i<nums.size(); i++)
        if( nums_unions.smart_find(i) != nums_unions.smart_find(sorted[i].second) ) return false;

    return true;
}


int main() {
    //0 - land, 1 - water
    int grid[5*8]= {
        1,1,1,1,1,1,1,0,
        1,0,0,0,0,1,1,0,
        1,0,1,0,1,1,1,0,
        1,0,0,0,0,1,0,1,
        1,1,1,1,1,1,1,0
    };

    cout << "There are " << count_closed_islands(grid, 5, 8) << " closed islands." << '\n';


    int n=6, source=0, destination=5;
    vector<vector<int>> edges={
        {0,1},
        {0,2},
        {3,5},
        {5,4},
        {4,3}
    };

    cout << ",,A path between " << source << " and  " << destination << " exists:'' " << path_in_graph(edges, source, destination, n) << '\n';


    vector<int> nums={5,2,6,2};

    cout << ",,Array can be GCD sorted'': " << gcd_sort(nums) << '\n';


    return 0;
}