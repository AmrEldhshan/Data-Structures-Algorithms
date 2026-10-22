#ifndef DSA_MIN_HEAP_H
#define DSA_MIN_HEAP_H

#include <functional>
#include <stdexcept>
#include <utility>
#include <vector>

// ---------------------------------------------------------------------------
// Min-heap (priority queue)
//
// A complete binary tree stored in an array. For index i:
//   parent      = (i - 1) / 2
//   left child  = 2 * i + 1
//   right child = 2 * i + 2
//
// The heap property is: every parent is <= both children. The minimum is
// therefore always at index 0.
//
// push / pop: O(log n)
// top:        O(1)
// build:      O(n) when constructed from a vector
// ---------------------------------------------------------------------------
template <typename T, typename Compare = std::less<T>>
class MinHeap {
public:
    MinHeap() = default;

    explicit MinHeap(std::vector<T> values) : data_(std::move(values)) {
        for (int i = static_cast<int>(data_.size()) / 2 - 1; i >= 0; --i) {
            siftDown(i);
        }
    }

    bool empty() const { return data_.empty(); }

    std::size_t size() const { return data_.size(); }

    const T& top() const {
        if (empty()) throw std::out_of_range("MinHeap::top: empty heap");
        return data_.front();
    }

    void push(const T& value) {
        data_.push_back(value);
        siftUp(static_cast<int>(data_.size()) - 1);
    }

    void pop() {
        if (empty()) throw std::out_of_range("MinHeap::pop: empty heap");

        data_.front() = std::move(data_.back());
        data_.pop_back();

        if (!empty()) siftDown(0);
    }

private:
    void siftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (!compare_(data_[index], data_[parent])) break;
            std::swap(data_[index], data_[parent]);
            index = parent;
        }
    }

    void siftDown(int index) {
        int count = static_cast<int>(data_.size());

        while (true) {
            int smallest = index;
            int left = 2 * index + 1;
            int right = 2 * index + 2;

            if (left < count && compare_(data_[left], data_[smallest])) {
                smallest = left;
            }
            if (right < count && compare_(data_[right], data_[smallest])) {
                smallest = right;
            }
            if (smallest == index) break;

            std::swap(data_[index], data_[smallest]);
            index = smallest;
        }
    }

    std::vector<T> data_;
    Compare compare_{};
};

#endif // DSA_MIN_HEAP_H
