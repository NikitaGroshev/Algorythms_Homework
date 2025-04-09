#include <iostream>
#include <vector>

std::vector<int> Merge(std::vector<int> left, std::vector<int> right) {
    std::vector<int> result;
    int i = 0;
    int j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j]) {
            result.push_back(left[i]);
            i++;
        } else {
            result.push_back(right[j]);
            j++;
        }
    }
    while (i < left.size()) {
        result.push_back(left[i]);
        i++;
    }
    while (j < right.size()) {
        result.push_back(right[j]);
        j++;
    }

    return result;
}

std::vector<int> MergeSort(std::vector<int>& arr) {
    if (arr.size() <= 1) {
        return arr;
    }
    std::vector<int> left;
    std::vector<int> right;
    for (int i = 0; i < arr.size() / 2; i++) {
        left.push_back(arr[i]);
    }
    for (int i = arr.size() / 2; i < arr.size(); i++) {
        right.push_back(arr[i]);
    }
    return Merge(MergeSort(left), MergeSort(right));
}

std::vector<int> sortArray(std::vector<int>& nums) {
    if (nums.size() > 0) {
        std::vector<int> res = MergeSort(nums);
        return res;
    } else {
        return nums;
    }
}

int main() {
    std::vector<int> vec = {110, 100, 0};
    vec = sortArray(vec);
    for (size_t i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " " ;
    }
}