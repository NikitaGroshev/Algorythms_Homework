#include <iostream>
#include <vector>
#include <algorithm>

// MAX HEAP

void SiftUp(std::vector<int>& heap, int i) {
    while (i > 0 && heap[i] > heap[(i-1) / 2]) {
        std::swap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void SiftDown(std::vector<int>& heap, int i) {
    int n = heap.size();
    while (2*i + 1 < n) {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int j = left;
        if (right < n && heap[right] > heap[left]) {
            j = right;
        }
        if (heap[i] >= heap[j]) {
            break;
        }
        std::swap(heap[i], heap[j]);
        i = j;
    }
}

void HeapPop(std::vector<int>& heap) {
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();
    SiftDown(heap, 0);
}

void AddElement(std::vector<int>& heap, int elem) {
    heap.push_back(elem);
    SiftUp(heap, heap.size() - 1);
}

int main() {
    int n, k; std::cin >> n >> k;
    std::vector<int> arr;
    for (int i = 0; i < n; i++) {
        int num; std::cin >> num;
        arr.push_back(num);
    }

    std::vector<int> max_heap;
    for (int i = 0; i < n; i++) {
        if (i < k) {
            AddElement(max_heap, arr[i]);
        } else {
            if (arr[i] < max_heap[0]) {
                HeapPop(max_heap);
                AddElement(max_heap, arr[i]);
            }
        }
    }
    std::sort(max_heap.begin(), max_heap.end());

    for (int i = 0; i < k; i++) {
        std::cout << max_heap[i] << " ";
    }

}