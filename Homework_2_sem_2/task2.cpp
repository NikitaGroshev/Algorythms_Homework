#include <bits/stdc++.h>


using namespace std;


class Solution {
public:
    void findEulerPath(int v, vector<int>& res, unordered_map<int, vector<int>>& g) {
        while (!g[v].empty()) {
            int to = g[v].back();
            g[v].pop_back();
            findEulerPath(to, res, g);
        }
        res.push_back(v);
    }

    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        unordered_map<int, vector<int>> g;
        unordered_map<int, int> indeg;
        unordered_map<int, int> outdeg;
        vector<int> path;
        vector<vector<int>> result;
        set<int> vertex;

        for (int i : vertex) {
            outdeg[i] = 0;
            indeg[i] = 0;
        }

        for (const vector<int>& p : pairs) {
            g[p[0]].push_back(p[1]);
            outdeg[p[0]]++;
            indeg[p[1]]++;
            vertex.insert(p[0]);
            vertex.insert(p[1]);
        }

        int start = -1;
        for (auto& [v, _] : g) {
            if (outdeg[v] - indeg[v] == 1) {
                start = v;
                break;
            }
        }

        if (start == -1) {
            start = pairs[0][0];
        }

        findEulerPath(start, path, g);

        reverse(path.begin(), path.end());

        for (int i = 0; i < path.size() - 1; i++) {
            result.push_back({path[i], path[i + 1]});
        }

        return result;
    }
};