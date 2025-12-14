#include <iostream>
#include <vector>
#include <set>
using namespace std;

class UnionFind {
    vector<int> parents;

    public:
        UnionFind(int n) { parents.resize(n, -1); }

        //---Simple find---
        int find(int x) {
            if (parents[x]<0) return x;
            return find(parents[x]);
        }

        //---Smart find, path compression---
        int smart_find(int x) {
            if (parents[x]<0) return x;
            return parents[x] = smart_find(parents[x]);
        }

        void arbitrary_union(int root1, int root2) {
            if (root1==root2) return;

            parents[root1] = root2;//or parents[root2]=root1
        }

        //---Smaller tree attaches to the bigger tree---
        void union_by_size(int root1, int root2) {
            if (root1==root2) return;
            //parents[x]=-size(x)
            if (parents[root1]<parents[root2]) {
                parents[root1]+=parents[root2];
                //root1 is the bigger tree -> root1 is the parent
                parents[root2]=root1;
            }else{
                parents[root2]+=parents[root1];
                //root2 is the bigger tree -> root2 is the parent
                parents[root1]=root2;
            }
        }

        //---Shallower tree attaches to deeper tree---
        void union_by_rank(int root1, int root2) {
            if (root1==root2) return;
            //parents[x]=-rank(x)
            if (parents[root1]<parents[root2]) {
                //root1 is the deeper tree -> root1 is the parent
                parents[root2]=root1;
            }else  {
                //if they're equally deep (same rank), then make root1 deeper; parent[x]-- is like rank(x)++, hence parent[x]=-rank(x)
                if (parents[root1]==parents[root2]) parents[root1]--;
                //root2 is the deeper tree -> root2 is the parent
                parents[root1]=root2;
            }
        }

        void unite(int x, int y, const string& strategy, const string& findType) {
            int root1, root2;

            if (findType=="simple") {
                root1 = find(x);
                root2 = find(y);
            }else {
                root1 = smart_find(x);
                root2 = smart_find(y);
            }

            if (strategy=="arbitrary") arbitrary_union(root1, root2);
            else if (strategy=="by size") union_by_size(root1, root2);
            else union_by_rank(root1, root2);
        }

        ~UnionFind() {};
};

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