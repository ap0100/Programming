#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int prim(vector<vector<pair<int, int>>> &graph) {
    int mst_weight = 0;

    vector<bool> in_mst(graph.size(), false);
    priority_queue<pair<int,int>, vector<pair<int,int>> , decltype([](const auto &a, const auto &b) {
        return a.first<b.first;
    })> pq;
    pq.push({0,0});

    while (!pq.empty()) {
        auto [weight, node]=pq.top();
        pq.pop();

        if (in_mst[node]) continue;

        in_mst[node]=true;
        mst_weight+=weight;

        for (auto &n: graph[node]) {
            int neighbour=n.first;
            int weight=n.second;

            if (!in_mst[neighbour]) pq.push({weight,neighbour});
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

    cout << "MST weight: " << prim(graph);

    return 0;
}