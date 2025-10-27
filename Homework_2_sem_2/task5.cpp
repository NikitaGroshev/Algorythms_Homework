#include <bits/stdc++.h>


using namespace std;


struct UndirGraph {
    vector<vector<int>> adj;
    int V;

    UndirGraph(int V) {
        this->V = V;
        adj.resize(V);
    }

    UndirGraph(vector<vector<int>> new_adj) {
        adj = new_adj;
        V = new_adj.size();
    }

    UndirGraph(vector<pair<int, int>> edges) {
        int max_v = 0;
        for (const auto edge: edges) {
            max_v = max(max_v, max(edge.first, edge.second));
        }

        vector<vector<int>> result(max_v + 1);
        for (const auto edge: edges) {
            result[edge.first].push_back(edge.second);
            result[edge.second].push_back(edge.first);
        }
        adj = result;
        V = max_v + 1;
    }

    void addEdge(int n, int m) {
        adj[n].push_back(m);
        adj[m].push_back(n);
    }
};

int solution(const UndirGraph& g, int s, int e) {
    vector<int> result(g.V, 0);
    vector<bool> visited(g.V, false);
    vector<int> dist(g.V, -1);
    
    queue<int> q;
    q.push(s);
    dist[s] = 0;
    result[s] = 1;
    visited[s] = true;
    
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        
        for (int to : g.adj[v]) {
            if (!visited[to]) {
                visited[to] = true;
                dist[to] = dist[v] + 1;
                result[to] = result[v];
                q.push(to);
            }
            else if (dist[to] == dist[v] + 1) {
                result[to] += result[v];
            }
        }
    }
    
    return result[e];
}

int main() {
    int verCount, edgeCount;
    cin >> verCount >> edgeCount;

    int s, e;
    cin >> s >> e;

    UndirGraph g = UndirGraph(verCount);

    for (int i = 0; i < edgeCount; i++) {
        int a, b;
        cin >> a >> b;
        g.addEdge(a, b);
    }

    int res = solution(g, s, e);

    cout << res << '\n';

    return 0;
}