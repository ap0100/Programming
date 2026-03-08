#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
    vector<int> parents;

    public:
        UnionFind(int n) {
            this->parents.resize(n, -1);
        }

        int find(int x) {
            if (this->parents[x]<0) return x;
            return this->parents[x]=find(this->parents[x]);
        }

        void union_by_rank(int root1, int root2) {
            if (root1==root2) return;

            if (this->parents[root1]<this->parents[root2]) this->parents[root2]=root1;
            else {
                if (this->parents[root1]==this->parents[root2]) this->parents[root1]--;
                this->parents[root1]=root2;
            }
        }

        void unite(int x, int y) {
            int root1=find(x), root2=find(y);
            union_by_rank(root1, root2);
        }
};

int kruskal(vector<vector<pair<int,int>>> &graph) {
    vector<tuple<int, int, int>> edges; //{weight, from, to}

    for (int node=0; node<graph.size(); node++) {
        for (auto &n: graph[node]) {
            int neighbour=n.first;
            int weight=n.second;

            if (node<neighbour) edges.push_back({weight, node, neighbour});
        }
    }

    sort(edges.begin(), edges.end());

    UnionFind uf(graph.size());
    int mst_weight=0;

    for (auto &[w,node,neighbour]: edges) {
        if (uf.find(node)!=uf.find(neighbour)) {
            uf.unite(node,neighbour);
            mst_weight += w;
        }
    }

    return mst_weight;
}

int main() {
    vector<vector<pair<int,int>>> graph(5); //this is an oriented graph; first is the node, second is the distance from ith node to first
    graph[0]={{1,5}};
    graph[1]={{2,1}, {3,2}};
    graph[2]={{4,1}};
    graph[4]={{3,-1}};

    cout << "MST weight: " << kruskal(graph);

    return 0;
}