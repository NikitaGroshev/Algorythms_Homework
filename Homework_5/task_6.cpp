#include <iostream>
#include <vector>
#include <sstream>
#include <inttypes.h>

std::vector<int> Merge(std::vector<int> left , std::vector<int> right, int64_t* inv) {
    std::vector<int> result;
    int64_t i = 0;
    int64_t j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] > right[j]) {
            result.push_back(right[j]);
            j++;
            *inv += left.size() - i;
        } else {
            result.push_back(left[i]);
            i++; 
        }
    }
    while (i != left.size())
    {
        result.push_back(left[i]);
        i++;
    }
    while (j != right.size())
    {
        result.push_back(right[j]);
        j++;
    }
    return result;
}

std::vector<int> MergeSort(std::vector<int>& arr, int64_t* inv) {
    if (arr.size() <= 1) {
        return arr;
    }

    std::vector<int> left;
    std::vector<int> right;

    for (size_t i = 0; i < arr.size() / 2; i++) {
        left.push_back(arr[i]);
    }
    for (size_t i = arr.size() / 2; i < arr.size(); i++) {
        right.push_back(arr[i]);
    }

    return Merge(MergeSort(left, inv), MergeSort(right, inv), inv);
}

int main() {
    std::vector<int> vec;
    std::string arr;
    std::getline(std::cin, arr);
    std::istringstream iss(arr);

    int num;
    while (iss >> num) {
        vec.push_back(num);
    }

    int64_t res = 0;
    int64_t* result = &res;
    MergeSort(vec, result);
    std::cout << *result; 
}