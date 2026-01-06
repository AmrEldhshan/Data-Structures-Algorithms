#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u, v, w;
};

vector<int> parent, rankArr;

void makeSet(int v) {
    parent[v] = v;
    rankArr[v] = 0;
}

int findSet(int v) {
    if (parent[v] != v)
        parent[v] = findSet(parent[v]);
    return parent[v];
}

void unionSet(int a, int b) {
    int rootA = findSet(a);
    int rootB = findSet(b);
    if (rootA == rootB) return;
    if (rankArr[rootA] < rankArr[rootB])
        parent[rootA] = rootB;
    else if (rankArr[rootA] > rankArr[rootB])
        parent[rootB] = rootA;
    else {
        parent[rootB] = rootA;
        rankArr[rootA]++;
    }
}

bool compareEdges(Edge a, Edge b) {
    return a.w < b.w;
}

int main() {
    int V = 6;
    vector<Edge> edges = {
        {0,1,4}, {0,2,4}, {1,2,2},
        {1,3,5}, {2,3,8}, {2,4,10},
        {3,4,2}, {3,5,6}, {4,5,3}
    };

    parent.resize(V);
    rankArr.resize(V);
    for (int i = 0; i < V; i++) makeSet(i);

    sort(edges.begin(), edges.end(), compareEdges);

    vector<Edge> MST;
    int totalWeight = 0;

    for (Edge e : edges) {
        if (findSet(e.u) != findSet(e.v)) {
            MST.push_back(e);
            unionSet(e.u, e.v);
            totalWeight += e.w;
        }
    }

    for (Edge e : MST)
        cout << e.u << " -- " << e.v << " == " << e.w << "\n";
    cout << "Total Weight = " << totalWeight << "\n";

    return 0;
}
