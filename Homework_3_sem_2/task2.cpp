#include <bits/stdc++.h>


using namespace std;


int get_start_vertex(const vector<string>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    int k = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 'S') {
                k = n * i + j;
            }
        }
    }

    return k;
}

int get_finish_vertex(const vector<string>& grid) {
    int m = grid.size();
    int n = grid[0].size();

    for (int i = 0; i < m; i++) {
        if (i == 0) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '.') {
                    return n * i + j;
                }
            }
        }
        else if (i == m - 1) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '.') {
                    return n * i + j;
                }
            }
        }
        else {
            if (grid[i][0] == '.') return n * i;
            if (grid[i][n - 1] == '.') return n * i + n - 1; 
        }
    }

    return -1;
}

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
            if (j + 1 < n && grid[i][j + 1] != '#') {
                res[k].push_back(k + 1);
            }
            if (j - 1 > -1 && grid[i][j - 1] != '#') {
                res[k].push_back(k - 1);
            }
            if (i + 1 < m && grid[i + 1][j] != '#') {
                res[k].push_back(k + n);
            }
            if (i - 1 > -1 && grid[i - 1][j] != '#') {
                res[k].push_back(k - n);
            }
        }
    }

    return res;
}

vector<int> bfs(const vector<vector<int>>& g, int s, int f) {
    vector<bool> visited(g.size(), false);
    vector<int> p(g.size(), -1);
    queue<int> q;
    vector<int> dist(g.size(), 0);
    visited[s] = true;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (const int v: g[u]) {
            if (visited[v]) continue;

            p[v] = u;
            dist[v] = dist[u] + 1;
            visited[v] = true;
            q.push(v);
        }
    }

    vector<int> path;
    while (f != -1) {
        path.push_back(f);
        f = p[f];
    }

    reverse(path.begin(), path.end());
    return path;
}


int main() {
    string input_map;
    getline(cin, input_map);    // Usage: #####\n#.S.#\n###.#\n#...#\n#.###\n (one string)

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

    int start = get_start_vertex(grid);
    int finish = get_finish_vertex(grid);

    vector<int> path = bfs(g, start, finish);

    if (path.size() == 0) {
        cout << "No path" << '\n';
        return 0;
    }

    for (int k: path) {
        if (k == start) continue;
        int i = k / grid[0].size();
        int j = k % grid[0].size();
        grid[i][j] = 'o';    
    }

    for (int i = 0; i < grid.size(); i++) {
        cout << grid[i] << '\n';
    }

    return 0;
}