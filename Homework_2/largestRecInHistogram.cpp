#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

std::vector<int> NearestMinLeft(const std::vector<int> &heights) {     //Строим массив высот, ближайших меньших слева
    std::stack<std::pair<int, int>> st;
    std::vector<int> min_l;
    st.push({heights[0], 1});   //Индексация столбов с единицы
    min_l.push_back(0);
    for (size_t i = 1; i < heights.size(); ++i) {
        if (heights[i] > st.top().first) {
            min_l.push_back(st.top().second);
            st.push({heights[i], i + 1});
        }
        else {
            while (!st.empty())
            {
                if (st.top().first < heights[i]) {
                    min_l.push_back(st.top().second);
                    st.push({heights[i], i + 1});
                    break;
                }
                st.pop();
            }
            if (st.empty()) {
                min_l.push_back(0);
                st.push({heights[i], i + 1});
            }
        }
    }
    return min_l;
}

std::vector<int> NearestMinRight(const std::vector<int> &heights) {     //Строим массив высот, ближайших меньших справа
    std::stack<std::pair<int, int>> st;
    std::vector<int> min_r;
    st.push({heights[heights.size() - 1], heights.size()});   //Индексация столбов с единицы
    min_r.push_back(heights.size() + 1);
    for (int i = heights.size() - 2; i >= 0; --i) {
        if (heights[i] > st.top().first) {
            min_r.push_back(st.top().second);
            st.push({heights[i], i + 1});
        }
        else {
            while (!st.empty())
            {
                if (st.top().first < heights[i]) {
                    min_r.push_back(st.top().second);
                    st.push({heights[i], i + 1});
                    break;
                }
                st.pop();
            }
            if (st.empty()) {
                min_r.push_back(heights.size() + 1);
                st.push({heights[i], i + 1});
            }
        }
    }
    std::reverse(min_r.begin(), min_r.end());
    return min_r;
}

int Solution(const std::vector<int> &heights) {
    int ans = 0;
    std::vector<int> min_l = NearestMinLeft(heights);
    std::vector<int> min_r = NearestMinRight(heights);
    for (size_t i = 0; i < heights.size(); i++) {
        int l = min_l[i] + 1;
        int r = min_r[i] - 1;
        ans = std::max(ans, heights[i] * (r - l + 1));     //По условию все столбы ширины 1
    }
    return ans;
}

int main() {
    std::vector<int> h = {2,1,5,6,2,3};
    std::cout << Solution(h) << '\n';
}