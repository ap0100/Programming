#ifndef UNION_FIND_UNIONFIND_H
#define UNION_FIND_UNIONFIND_H
#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
    vector<int> parents;

    public:
        UnionFind(int n);

        int find(int x);
        int smart_find(int x);

        void arbitrary_union(int root1, int root2);
        void union_by_size(int root1, int root2);
        void union_by_rank(int root1, int root2);

        void unite(int x, int y, const string& strategy, const string& findType);
};

#endif //UNION_FIND_UNIONFIND_H