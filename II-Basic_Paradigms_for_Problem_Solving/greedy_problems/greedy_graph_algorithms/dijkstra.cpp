#include <iostream>
#include <queue>
#include <vector>
#include <climits>
using namespace std;

vector<int> dijkstra(const vector<vector<pair<int, int>>> &graph, const int source) {
    vector<int> distances(graph.size(), INT_MAX); //distance between the ith node and the source
    distances[source]=0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype([](const pair<int,int> &a, const pair<int,int> &b) {
        return a.second>b.second;
    })> pq;
    pq.push({source, 0});//distance is second, the node is first

    while (!pq.empty()) {
        auto current_dist=pq.top().second;
        auto node=pq.top().first;
        pq.pop();

        if (current_dist>distances[node]) continue;

        for (auto &n: graph[node]) {
            int weight=n.second;
            int neighbour=n.first;

            if (distances[node]+weight<distances[neighbour]) {
                distances[neighbour]=distances[node]+weight;
                pq.push({neighbour, distances[neighbour]});
            }
        }
    }

    return distances;
}

int main() {
    vector<vector<pair<int,int>>> graph(6); //this is an oriented graph; first is the node, second is the distance from ith node to first
    graph[0]={{5,4}, {1,2}};
    graph[1]={{0,2}, {3,9}};
    graph[2]={{3,5}};
    graph[3]={{4,1}, {2,5}, {1,9}};
    graph[4]={{3,1}};
    graph[5]={{0,4}};

    auto dist=dijkstra(graph, 0);

    for (int i=0; i<dist.size(); i++) cout << i << ": " << dist[i] << '\n';


    return 0;
}