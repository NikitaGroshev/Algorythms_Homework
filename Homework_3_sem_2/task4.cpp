#include <bits/stdc++.h>


using namespace std;

vector<vector<int>> build_graph(const vector<string>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int>> res(m * n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '#') {
                continue;
            }
            int k = i * n + j;
            if (j + 1 < n) {
                res[k].push_back(k + 1);
            }
            if (j - 1 > -1 && grid[i][j - 1]) {
                res[k].push_back(k - 1);
            }
            if (i + 1 < m && grid[i + 1][j]) {
                res[k].push_back(k + n);
            }
            if (i - 1 > -1 && grid[i - 1][j]) {
                res[k].push_back(k - n);
            }
        }
    }

    return res;
}

int bfs(const vector<vector<int>>& g, const vector<string>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    vector<bool> visited(n * m, false);
    queue<int> q;
    vector<int> dist(n * m, -1);

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int k = n * i + j;
            if (grid[i][j] == 'W') {
                visited[k] = true;
                dist[k] = 0;
                q.push(k);
            }
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const int v: g[u]) {
            if (visited[v]) continue;
            dist[v] = dist[u] + 1;
            visited[v] = true;
            q.push(v);
        }
    }

    int res = -1;

    for (int i = 0; i < dist.size(); i++) {
        res = max(res, dist[i]);
    }

    return res;
}


int main() {
    string input_map;
    getline(cin, input_map);    // Usage example: WWWWWWWWW\nWWWLLLWWW\nWWWLLLWWW\nWLLLLLLLW\nWLLLLLLLW\nWLLLLLLLW\nWWWLLLWWW\nWWWLLLWWW\nWWWWWWWWW\n (one string)       
                                //          WWWWWWWWW
                                //          WWWLLLWWW
                                //          WWWLLLWWW
                                //          WLLLLLLLW
                                //          WLLLLLLLW
                                //          WLLLLLLLW
                                //          WWWLLLWWW
                                //          WWWLLLWWW
                                //          WWWWWWWWW

    vector<string> grid;
    string line = "";

    for (int i = 0; i < input_map.size(); i++) {
        if (i + 1 < input_map.size() && input_map[i] == '\\' && input_map[i + 1] == 'n') {
            grid.push_back(line);
            line = "";
            i++;
        }
        else {
            line += input_map[i];
        }
    }

    vector<vector<int>> g = build_graph(grid);

    int result = bfs(g, grid);

    cout << result << '\n';

    return 0;
}