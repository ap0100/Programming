#include "../include/UnionFind.h"
#include <vector>
#include <iostream>
using namespace std;

UnionFind::UnionFind(int n) { this->parents.resize(n, -1); }

//---Simple find---
int UnionFind::find(int x) {
    if (this->parents[x]<0) return x;
    return find(this->parents[x]);
}

//---Smart find, path compression---
int UnionFind::smart_find(int x) {
    if (this->parents[x]<0) return x;
    return this->parents[x] = smart_find(this->parents[x]);
}

void UnionFind::arbitrary_union(int root1, int root2) {
    if (root1==root2) return;

    this->parents[root1] = root2;//or this->parents[root2]=root1
}

//---Smaller tree attaches to the bigger tree---
void UnionFind::union_by_size(int root1, int root2) {
    if (root1==root2) return;
    //this->parents[x]=-size(x)
    if (this->parents[root1]<this->parents[root2]) {
        this->parents[root1]+=this->parents[root2];
        //root1 is the bigger tree -> root1 is the parent
        this->parents[root2]=root1;
    }else{
        this->parents[root2]+=this->parents[root1];
        //root2 is the bigger tree -> root2 is the parent
        this->parents[root1]=root2;
    }
}

//---Shallower tree attaches to deeper tree---
void UnionFind::union_by_rank(int root1, int root2) {
    if (root1==root2) return;
    //this->parents[x]=-rank(x)
    if (this->parents[root1]<this->parents[root2]) {
        //root1 is the deeper tree -> root1 is the parent
        this->parents[root2]=root1;
    }else  {
        //if they're equally deep (same rank), then make root1 deeper; parent[x]-- is like rank(x)++, hence parent[x]=-rank(x)
        if (this->parents[root1]==this->parents[root2]) this->parents[root1]--;
        //root2 is the deeper tree -> root2 is the parent
        this->parents[root1]=root2;
    }
}

void UnionFind::unite(int x, int y, const string& strategy, const string& findType) {
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
