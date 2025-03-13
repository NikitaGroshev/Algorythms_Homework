#include <iostream>
#include <vector>

int trap(std::vector<int>& height) {
    if (height.size() == 0) {
        return 0;
    }
    int left = 0;
    int right = height.size() - 1;      // Два указателя , один идет слева направо, другой - справа налево
    int max_left = height[left];
    int max_right = height[right];
    int ans = 0;
    while (left < right) {
        if (max_left < max_right) {
            left += 1;
            max_left = std::max(max_left, height[left]);
            ans += max_left - height[left];
        }
        else {
            right -= 1;
            max_right = std::max(max_right, height[right]);
            ans += max_right - height[right];
        }

    }
    return ans;
}

int main() {
    std::vector<int> heights = {0, 1, 0, 3, 1, 0, 1, 2, 2, 1, 2, 1};
    std::cout << trap(heights) << std::endl;
}