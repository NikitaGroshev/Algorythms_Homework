#include <iostream>
#include <vector>
#include <algorithm>


struct DataEntry 
{
    std::string Name;
    std::vector<int> parametrs;
    std::vector<int> priority;
};

bool EntryCompare(const DataEntry& d1, const DataEntry& d2) {
    for (int i = 0; i < d1.priority.size(); i++) {
        if (d1.parametrs[d1.priority[i] - 1] != d2.parametrs[d2.priority[i] - 1]) {
            return d1.parametrs[d1.priority[i] - 1] > d2.parametrs[d2.priority[i] - 1];
        }
    }
    return false;
}

int main() {
    int N, k;
    std::cin >> N;
    std::cin >> k;
    std::vector<int> priorities;
    for (int i = 0; i < k; i++) {
        int p; std::cin >> p;
        priorities.push_back(p);
    }

    std::vector<DataEntry> data_base;
    for (int i = 0; i < N; i++) {
        DataEntry d;
        std::string name; std::cin >> name;
        d.Name = name;
        d.priority = priorities;
        for (int i = 0; i < k; i++) {
            int param; std::cin >> param;
            d.parametrs.push_back(param);
        }
        data_base.push_back(d);
    }

    std::sort(data_base.begin(), data_base.end(), EntryCompare);

    for (int i = 0; i < N; i++) {
        std::cout << data_base[i].Name << "\n";
    }
}