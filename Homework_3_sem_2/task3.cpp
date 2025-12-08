#include <bits/stdc++.h>


using namespace std;


constexpr int INF = 1e9;

int get_vertex(const vector<string>& grid, char target) {
    int m = grid.size();
    int n = grid[0].size();

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == target) {
                return n * i + j;
            }
        }
    }

    return -1;
}

int coord_to_vertex(int i, int j, int n) {
    return n * i + j;
}

pair<int, int> vertex_to_coord(int v, int n) {
    return {v / n, v % n};
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

vector<int> bfs_dist(const vector<vector<int>>& g, int s) {
    vector<bool> visited(g.size(), false);
    queue<int> q;
    vector<int> dist(g.size(), -1);

    dist[s] = 0;
    visited[s] = true;
    q.push(s);
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

    return dist;
}


vector<int> bfs_path(const vector<vector<int>>& g, int s, int f) {
    vector<bool> visited(g.size(), false);
    vector<int> p(g.size(), -1);
    queue<int> q;

    visited[s] = true;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == f) break;

        for (const int v: g[u]) {
            if (!visited[v]) {
                p[v] = u;
                visited[v] = true;
                q.push(v);
            }
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
    getline(cin, input_map);    // Usage: #######\n#A....#\n#.###.#\n#.#.#.#\n#.#.#.#\n#...B.#\n###F###\n (one string)

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

    int m = grid.size();
    int n = grid[0].size();

    int A = get_vertex(grid, 'A');
    int B = get_vertex(grid, 'B');
    int F = get_vertex(grid, 'F');

    if (A == -1 || B == -1 || F == -1) {
        cout << "Not all points (A,B,F) were found" << '\n';
        return 0;
    }

    vector<vector<int>> g = build_graph(grid);

    vector<int> dist_a = bfs_dist(g, A);
    vector<int> dist_b = bfs_dist(g, B);
    vector<int> dist_f = bfs_dist(g, F);

    int min_m = -1;
    int min_total = INF;

    for (int v = 0; v < m * n; v++) {
        auto [x, y] = vertex_to_coord(v, n);
        if (grid[x][y] == '#') continue;

        if (dist_a[v] != -1 && dist_b[v] != -1 && dist_f[v] != -1) {
            int total = dist_a[v] + dist_b[v] + dist_f[v];
            if (total < min_total) {
                min_total = total;
                min_m = v;
            }
        }
    }

    if (min_m == -1) {
        cout << "No solution" << '\n';
        return 0;
    }

    vector<int> path_am = bfs_path(g, A, min_m);
    vector<int> path_bm = bfs_path(g, B, min_m);
    vector<int> path_mf = bfs_path(g, min_m, F);

    if (path_am.size() == 0 || path_bm.size() == 0 || path_mf.size() == 0) {
        cout << "No path" << '\n';
        return 0;
    }

    unordered_set<int> full_path;

    for (int i = 1; i < path_am.size(); i++) {
        full_path.insert(path_am[i]);
    }
    for (int i = 1; i < path_bm.size(); i++) {
        full_path.insert(path_bm[i]);
    }
    for (int i = 0; i < path_mf.size() - 1; i++) {
        full_path.insert(path_mf[i]);
    }

    for (int v : full_path) {
        auto [x, y] = vertex_to_coord(v, n);
        if (grid[x][y] != 'A' && grid[x][y] != 'B' && grid[x][y] != 'F') {
            grid[x][y] = 'o';
        }
    }

    auto [mx, my] = vertex_to_coord(min_m, n);
    if (min_m != F && grid[mx][my] != 'A' && grid[mx][my] != 'B') {
        grid[mx][my] = 'M';
    }

    for (int i = 0; i < grid.size(); i++) {
        cout << grid[i] << '\n';
    }

    return 0;
}