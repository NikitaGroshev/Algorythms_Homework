#include "table.h"
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <functional>

using namespace std;

unordered_map<Table, Table, Table::Hash> solve(const Table& start) {
    unordered_map<Table, Table, Table::Hash> parent;
    unordered_set<Table, Table::Hash> to_visit;
    unordered_map<Table, int, Table::Hash> dist_from_start;
    unordered_map<Table, int, Table::Hash> f;
    priority_queue<Table, vector<Table>, function<bool(const Table& lhs, const Table& rhs)>> q(
        [&f](const Table& lhs, const Table& rhs) {
            return f[lhs] > f[rhs];
        }
    );

    Table finish;
    dist_from_start[start] = 0;
    q.push(start);
    to_visit.insert(start);
    f[start] = start.heuristic();

    while (!q.empty()) {
        auto current_table = q.top();
        if (current_table == finish) {
            return parent;
        }
        q.pop();
        to_visit.erase(current_table);
        for (auto direction: {Direction::D_LEFT, Direction::D_RIGHT, Direction::D_UP, Direction::D_DOWN}) {
            if (!current_table.can_move(direction)) {
                continue;
            }

            auto next_table = current_table.move(direction);
            int dist = dist_from_start[current_table] + 1;
            if (dist_from_start.find(next_table) != dist_from_start.end() && dist_from_start[next_table] <= dist) {
                continue;
            }

            parent[next_table] = current_table;
            dist_from_start[next_table] = dist;
            f[next_table] = dist + next_table.heuristic();
            if (to_visit.find(next_table) == to_visit.end()) {
                q.push(next_table);
                to_visit.insert(next_table);
            }
        }
    }

    return parent;
}

int main() {
    Table start_table;
    cin >> start_table;

    auto parent = solve(start_table);

    Table finish;
    cout << finish;
    auto prev = parent[finish];
    int count = 1;
    while (prev != start_table) {
        cout << "-------------------" << '\n';
        cout << prev;
        prev = parent[prev];
        ++count;
    }

    cout << "-------------------\n";
    cout << start_table;
    cout << "-------------------\n";
    cout << "Solved in " << count << " moves\n";

    return 0;
}