#include "table.h"

#include <cmath>
#include <iomanip>

const std::array<std::pair<int, int>, Table::size.first * Table::size.second> right_pos = {
    {
        {3, 3}, {0, 0}, {0, 1}, {0, 2}, 
        {0, 3}, {1, 0}, {1, 1}, {1, 2}, 
        {1, 3}, {2, 0}, {2, 1}, {2, 2}, 
        {2, 3}, {3, 0}, {3, 1}, {3, 2}
    }
};

// Manhattan distance
int Table::heuristic() const {
    int res = 0;
    for (int i = 0; i < size.first; i++) {
        for (int j = 0; j < size.second; j++) {
            res += abs(i - right_pos[table[i][j]].first) +
                   abs(j - right_pos[table[i][j]].second);
        }
    }
    return res;
}

bool Table::operator==(const Table& other) const {
    for (int i = 0; i < size.first; i++) {
        for (int j = 0; j < size.second; j++) {
            if (table[i][j] != other[i][j]) {
                return false;
            }
        }
    }
    return true;
}

std::ostream &operator<<(std::ostream& out, const Table& other) {
    for (int i = 0; i < Table::size.first; i++) {
        for (const auto& val: other[i]) {
            out << std::setw(4) << static_cast<int>(val);
        }
        out << '\n';
    }
    return out;
}

std::istream &operator>>(std::istream &in, Table &other) {
    for (int i = 0; i < Table::size.first; ++i) {
        for (int j = 0; j < Table::size.second; ++j) {
            int number;
            in >> number;
            if (number == 0) {
                other.zero_index = {i, j};
            }
            other[i][j] = number;
        }
    }
    return in;
}

std::array<uint8_t, Table::size.first * Table::size.second> Table::flatten() const {
    std::array<uint8_t, Table::size.first * Table::size.second> res;
    int index = 0;
    for (const auto &row: table) {
        for (auto val: row) {
            res[index++] = val;
        }
    }
    return res;
}

std::pair<int, int> Table::move_zero_index(Direction direction) const {
    switch (direction) {
        case Direction::D_UP:
            return {zero_index.first - 1, zero_index.second};
        case Direction::D_DOWN:
            return {zero_index.first + 1, zero_index.second};
        case Direction::D_LEFT:
            return {zero_index.first, zero_index.second - 1};
        case Direction::D_RIGHT:
            return {zero_index.first, zero_index.second + 1};
    }
    return {-1, -1};
}
