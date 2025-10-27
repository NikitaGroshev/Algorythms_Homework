#include <bits/stdc++.h>


using namespace std;


struct DirGraph {
    vector<vector<int>> g, gr;
    vector<int> visited, order;

    void dfs1(int v) {
        visited[v] = 1;
        for (int to : gr[v]) {
            if (!visited[to]) {
                dfs1(to);
            }
        }
        order.push_back(v);
    }

    void dfs2(int v, int c) {
        visited[v] = c;
        for (int to : g[v]) {
            if(!visited[to]) {
                dfs2(to, c);
            }
        }
    }

    DirGraph(int verCount) {
        g.resize(verCount);
        gr.resize(verCount);
    }

    void addEdge(int a, int b) {
        g[a].push_back(b);
        gr[b].push_back(a);
    }

    pair<int, vector<int>> findScc() {
        visited.assign(g.size(), 0);
        for (int i = 0; i < g.size(); i++) {
            if (!visited[i]) {
                dfs1(i);
            }
        }
        reverse(order.begin(), order.end());
        
        visited.assign(g.size(), 0);
        int sccCount = 0;
        for (int v : order) {
            if (!visited[v]) {
                dfs2(v, ++sccCount);
            }
        }

        pair<int, vector<int>> res = {sccCount, visited};
        return res;
    }
};

bool isStronglyConnected(vector<int>& color) {
    int c1 = color[0];
    for (int i = 1; i < color.size(); i++) {
        if (c1 != color[i]) {
            return false;
        }
    }
    return true;
}

int solution(DirGraph& g) {
    pair<int, vector<int>> components = g.findScc();

    int comp = components.first;
    vector<int> color = components.second;

    if (isStronglyConnected(color)) {
        return 0;
    }

    set<pair<int, int>> s;

    for (int i = 0; i < g.g.size(); i++) {
        for (int to : g.g[i]) {
            if (color[i] != color[to]) {
                s.insert({color[i], color[to]});
            }
        }
    }

    vector<int> indeg(comp + 1, 0);
    vector<int> outdeg(comp + 1, 0);

    for (const auto& p : s) {
        indeg[p.second]++;
        outdeg[p.first]++;
    }

    int in_v = 0, out_v = 0;

    for (int i = 1; i <= comp; i++) {
        if (indeg[i] == 0) {
            in_v++;
        }
        if (outdeg[i] == 0) {
            out_v++;
        } 
    }

    return max(in_v, out_v);
}

int main() {
    int verCount, edgeCount;
    cin >> verCount >> edgeCount;

    DirGraph g = DirGraph(verCount);

    for (int i = 0; i < edgeCount; i++) {
        int a, b;
        cin >> a >> b;
        g.addEdge(a - 1, b - 1);        // вершины нумеруются с единицы
    }

    int res = solution(g);

    cout << res << '\n';
    
    return 0;
}