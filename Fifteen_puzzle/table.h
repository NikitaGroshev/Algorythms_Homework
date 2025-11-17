#ifndef TABLE_H
#define TABLE_H

#include <array>
#include <iostream>
#include <string>
#include <cstdint>

enum Direction {
    D_LEFT,
    D_RIGHT,
    D_UP,
    D_DOWN
};


class Table {
    public:
        static constexpr std::pair<int, int> size = {4, 4}; 

        Table(): table{
            {
                {1, 2, 3, 4},
                {5, 6, 7, 8},
                {9, 10, 11, 12},
                {13, 14, 15, 0}
            }
        } {}

        Table(const Table& other): table{other.table}, zero_index{other.zero_index} {}

        Table &operator=(const Table &other) {
            table = other.table;
            zero_index = other.zero_index;
            return *this;
        }

        bool can_move(Direction direction) const {
            auto pos = move_zero_index(direction);
            return pos.first >= 0 &&
                   pos.first < Table::size.first &&
                   pos.second >= 0 &&
                   pos.second < Table::size.second;
        }

        Table move(Direction direction) const {
            auto [new_i, new_j] = move_zero_index(direction);
            auto [i, j] = zero_index;
            Table new_table(*this);
            std::swap(new_table.table[i][j], new_table.table[new_i][new_j]);
            new_table.zero_index = {new_i, new_j};
            return new_table;
        }

        std::array<uint8_t, size.second> &operator[](size_t index) {
            return table[index];
        }

        const std::array<uint8_t, size.second> &operator[](size_t index) const {
            return table[index];
        }

        std::array<uint8_t, size.first * size.second> flatten() const;

        friend std::istream& operator>>(std::istream& in, Table& other); 

        bool operator==(const Table& other) const;

        bool operator!=(const Table& other) const {
            return !((*this) == other);
        }

        struct Hash {
            size_t operator()(const Table& other) const {
                auto flattened = other.flatten();
                std::string str(flattened.begin(), flattened.end());
                return std::hash<std::string>{}(str);
            }
        }; 

        int heuristic() const;

    private:
        std::array<std::array<uint8_t, size.second>, size.first> table;
        std::pair<int, int> zero_index = {size.first - 1, size.second - 1};
        std::pair<int, int> move_zero_index(Direction direction) const;
};

std::ostream &operator<<(std::ostream& out, const Table& other);

#endif // TABLE_H