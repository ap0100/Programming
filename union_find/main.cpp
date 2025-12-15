#include <iostream>
#include <set>
#include "include/UnionFind.h"
using namespace std;

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

int main() {
    //0 - land, 1 - water
    int grid[5*8]= {
        1,1,1,1,1,1,1,0,
        1,0,0,0,0,1,1,0,
        1,0,1,0,1,1,1,0,
        1,0,0,0,0,1,0,1,
        1,1,1,1,1,1,1,0
    };

    cout << "There are " << count_closed_islands(grid, 5, 8) << " closed islands.";

    return 0;
}