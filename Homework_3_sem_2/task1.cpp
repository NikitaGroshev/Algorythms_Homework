#include <bits/stdc++.h>


using namespace std;


int get_number_of_keys(const vector<string>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    int res = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] >= 'a' && grid[i][j] <= 'z') {
                res += 1;
            }
        }
    }

    return res;
}

int get_start_vertex(const vector<string>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    int k = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '@') {
                k = n * i + j;
            }
        }
    }

    return k;
}

int bfs(const vector<vector<pair<int, char>>>& g, int s, int all_keys) {
    queue<pair<int, string>> q;
    map<pair<int, string>, int> dist;
    pair<int, string> start = {s, ""};

    q.push(start);
    dist[start] = 0;
    
    while (!q.empty()) {
        auto [pos, keys] = q.front();
        q.pop();
        int cur_dist = dist[{pos, keys}];

        if (keys.size() == all_keys) {
            return cur_dist;
        }

        for (const auto& p: g[pos]) {
            string next_keys = keys;

            if (p.second >= 'a' && p.second <= 'z') {
                if (next_keys.find(p.second) == string::npos) {
                    next_keys += p.second;
                    sort(next_keys.begin(), next_keys.end());
                }
            }

            if (p.second >= 'A' && p.second <= 'Z') {
                if (next_keys.find(tolower(p.second)) == string::npos) {
                    continue;
                }
            }

            pair<int, string> next_state = {p.first, next_keys};

            if (dist.find(next_state) == dist.end()) {
                dist[next_state] = cur_dist + 1;
                q.push(next_state);
            }
        }
    }

    return -1;
}

vector<vector<pair<int, char>>> build_graph(const vector<string>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<pair<int, char>>> res(m * n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '#') {
                continue;
            }
            int k = i * n + j;
            if (j + 1 < n && grid[i][j + 1] != '#') {
                res[k].push_back({k + 1, grid[i][j + 1]});
            }
            if (j - 1 > -1 && grid[i][j - 1] != '#') {
                res[k].push_back({k - 1, grid[i][j - 1]});
            }
            if (i + 1 < m && grid[i + 1][j] != '#') {
                res[k].push_back({k + n, grid[i + 1][j]});
            }
            if (i - 1 > -1 && grid[i - 1][j] != '#') {
                res[k].push_back({k - n, grid[i - 1][j]});
            }
        }
    }

    return res;
}

class Solution {
public:
    int shortestPathAllKeys(vector<string>& grid) {
        vector<vector<pair<int, char>>> g = build_graph(grid);
        int start = get_start_vertex(grid);
        int all_keys = get_number_of_keys(grid);
        int result = bfs(g, start, all_keys);

        return result;
    }
}; 