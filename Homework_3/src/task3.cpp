#include <iostream>
#include <vector>

// MAX HEAP пар вида: (значение , индекс)

void SiftUp(std::vector<std::pair<int, int>>& heap, int i) {
    while (i > 0 && heap[i].first > heap[(i-1) / 2].first) {
        std::swap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void SiftDown(std::vector<std::pair<int, int>>& heap, int i) {
    int n = heap.size();
    while (2*i + 1 < n) {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int j = left;
        if (right < n && heap[right].first > heap[left].first) {
            j = right;
        }
        if (heap[i].first >= heap[j].first) {
            break;
        }
        std::swap(heap[i], heap[j]);
        i = j;
    }
}

void BuildHeap(std::vector<std::pair<int, int>>& heap) {
    for (int i = heap.size(); i >= 0; i--) {
        SiftDown(heap, i);
    }
}

void HeapPop(std::vector<std::pair<int, int>>& heap) {
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();
    SiftDown(heap, 0);
}

void AddElement(std::vector<std::pair<int, int>>& heap, int elem, int i) {
    heap.push_back({elem, i});
    SiftUp(heap, heap.size() - 1);
}

int main() {
    int n; std::cin >> n;
    std::vector<int> arr;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        arr.push_back(x);
    }
    int k; std::cin >> k;
    std::vector<std::pair<int, int>> max_heap;
    for (int i = 0; i < n; i++) {
        AddElement(max_heap, arr[i], i);
        if (i >= k - 1) {
            while (max_heap[0].second <= i - k) {
                HeapPop(max_heap);
            }
            std::cout << max_heap[0].first << " ";
        }
    }
}