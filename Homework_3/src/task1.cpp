#include <iostream>
#include <vector>

// MIN HEAP

void SiftUp(std::vector<int>& heap, int i) {
    while (i > 0 && heap[i] < heap[(i-1) / 2]) {
        std::swap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void SiftDown(std::vector<int>& heap, int i) {
    while (2*i + 1 < heap.size()) {
        int left = 2*i + 1;
        int right = 2*i + 2;
        int j = left;
        if (right < heap.size() && heap[right] < heap[left]) {
            j = right;
        }
        if (heap[i] <= heap[j]) {
            break;
        }
        std::swap(heap[i], heap[j]);
        i = j;
    }
}

void BuildHeap(std::vector<int>& heap) {
    for (int i = heap.size(); i >= 0; i--) {
        SiftDown(heap, i);
    }
}

int HeapPop(std::vector<int>& heap) {
    int temp = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();
    SiftDown(heap, 0);
    return temp;
}

void AddElement(std::vector<int>& heap, int elem) {
    heap.push_back(elem);
    SiftUp(heap, heap.size() - 1);
}

int main() {
    int n; std::cin >> n;
    std::vector<int> vec;
    for (int i = 0; i < n; i++) {
        int x;
        std::cin >> x;
        vec.push_back(x);
    }
    if (n == 1) {
        std::cout << vec[0];
        return 0;
    }
    BuildHeap(vec);
    int result = 0;
    while (vec.size() > 1) {
        int first = HeapPop(vec);
        int second = HeapPop(vec);
        int sum = first + second;
        result += sum;
        AddElement(vec, sum);
    }
    std::cout << result;
}