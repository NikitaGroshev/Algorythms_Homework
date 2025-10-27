#include <bits/stdc++.h>


using namespace std;


class Solution {
public:
    void findEulerPath(string s, vector<string>& res, unordered_map<string, vector<string>>& g) {
        while (!g[s].empty()) {
            auto beg = g[s].begin();
            string to = g[s][0];
            g[s].erase(beg);
            findEulerPath(to, res, g);
        }
        res.push_back(s);
    }

    static bool compare(const vector<string>& v1, const vector<string>& v2) {
        string s1 = v1[0] + v1[1];
        string s2 = v2[0] + v2[1];
        return s1 < s2;
    }

    vector<string> findItinerary(vector<vector<string>>& tickets) {
        unordered_map<string, vector<string>> g;
        vector<string> result;

        sort(tickets.begin(), tickets.end(), compare);

        for (const vector<string>& ticket : tickets) {
            g[ticket[0]].push_back(ticket[1]);
        }

        findEulerPath("JFK", result, g);

        reverse(result.begin(), result.end());

        return result;
    }
};