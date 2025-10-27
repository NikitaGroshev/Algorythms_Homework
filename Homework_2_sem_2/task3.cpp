#include <bits/stdc++.h>


using namespace std;


class Solution {
public:
    void dfs(int v, vector<bool>& visited, vector<vector<int>>& g) {
        visited[v] = true;
        for (int to : g[v]) {
            if (to == v) {
                continue;
            }
            if (!visited[to]) {
                dfs(to, visited, g);
            }
        } 
    }

    vector<vector<int>> adj_list(vector<vector<int>> matrix) {
        vector<vector<int>> res(matrix.size());
        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[i].size(); j++) {
                if (matrix[i][j] == 1) {
                    if (i != j) {
                        res[i].push_back(j);
                        res[j].push_back(i);
                    } else {
                        res[i].push_back(j);
                    }
                }
            }
        }
        return res;
    }

    int findCircleNum(vector<vector<int>>& isConnected) {
        vector<vector<int>> adj = adj_list(isConnected);
        vector<bool> visited(adj.size(), false);
        int counter = 0;
        for (int i = 0; i < adj.size(); i++) {
            if (!visited[i]) {
                dfs(i, visited, adj);
                counter += 1;
            }
        }
        return counter;
    }
};