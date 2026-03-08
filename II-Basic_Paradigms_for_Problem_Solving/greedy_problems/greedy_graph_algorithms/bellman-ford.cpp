#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector<int> bellman_ford(vector<vector<pair<int, int>>> &graph, const int source) {
    vector<int> distances(graph.size(), INT_MAX);
    distances[source]=0;

    for (int i=0; i<graph.size()-1; i++) {
        for (int node=0; node<graph.size(); node++) {
            for (auto &n: graph[node]) {
                int neighbour=n.first;
                int weight=n.second;

                if (distances[node]!=INT_MAX && distances[node]+weight<distances[neighbour])
                    distances[neighbour]=distances[node]+weight;
            }
        }
    }

    for (int node=0; node<graph.size(); node++) {
        for (auto &n: graph[node]) {
            int neighbour=n.first;
            int weight=n.second;

            if (distances[node]!=INT_MAX && distances[node]+weight<distances[neighbour])
                return {-1};
        }
    }

    return distances;
}

int main() {
    vector<vector<pair<int,int>>> graph(5); //this is an oriented graph; first is the node, second is the distance from ith node to first
    graph[0]={{1,5}};
    graph[1]={{2,1}, {3,2}};
    graph[2]={{4,1}};
    graph[4]={{3,-1}};

    auto dist=bellman_ford(graph, 0);

    for (int i=0; i<graph.size(); i++) cout << i << ": " << dist[i] << '\n';

    return 0;
}