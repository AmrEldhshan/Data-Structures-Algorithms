#ifndef DSA_MIN_MAX_HEAP_H
#define DSA_MIN_MAX_HEAP_H

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <vector>

// ---------------------------------------------------------------------------
// Min-max heap
//
// A complete binary tree stored in an array that supports both the minimum and
// the maximum in O(1). Nodes on even levels are "min" levels; nodes on odd
// levels are "max" levels.
//
// insert / extractMin / extractMax: O(log n)
// ---------------------------------------------------------------------------
template <typename T, typename Compare = std::less<T>>
class MinMaxHeap {
public:
    MinMaxHeap() = default;

    explicit MinMaxHeap(Compare compare) : compare_(std::move(compare)) {}

    std::size_t size() const { return data_.size(); }
    bool empty() const { return data_.empty(); }

    void clear() { data_.clear(); }

    const T& minimum() const {
        if (empty()) throw std::out_of_range("MinMaxHeap: empty");
        return data_[0];
    }

    const T& maximum() const {
        if (empty()) throw std::out_of_range("MinMaxHeap: empty");
        if (data_.size() == 1) return data_[0];
        if (data_.size() == 2) return data_[1];
        return compare_(data_[1], data_[2]) ? data_[2] : data_[1];
    }

    void insert(const T& value) {
        data_.push_back(value);
        bubbleUp(data_.size() - 1);
    }

    T extractMin() {
        if (empty()) throw std::out_of_range("MinMaxHeap: empty");

        T result = data_[0];
        T last = data_.back();
        data_.pop_back();

        if (!data_.empty()) {
            data_[0] = last;
            trickleDown(0);
        }

        return result;
    }

    T extractMax() {
        if (empty()) throw std::out_of_range("MinMaxHeap: empty");
        if (data_.size() == 1) {
            T result = data_[0];
            data_.pop_back();
            return result;
        }

        std::size_t index = data_.size() == 2
                                ? 1
                                : (compare_(data_[1], data_[2]) ? 2 : 1);

        T result = data_[index];
        T last = data_.back();
        data_.pop_back();

        if (index < data_.size()) {
            data_[index] = last;
            trickleDown(index);
        }

        return result;
    }

private:
    std::vector<T> data_;
    Compare compare_;

    static bool isMinLevel(std::size_t index) {
        std::size_t level = 0;
        while (index > 0) {
            index = (index - 1) / 2;
            ++level;
        }
        return level % 2 == 0;
    }

    static std::size_t parent(std::size_t index) { return (index - 1) / 2; }
    static std::size_t left(std::size_t index) { return 2 * index + 1; }
    static std::size_t right(std::size_t index) { return 2 * index + 2; }

    static std::size_t grandparent(std::size_t index) {
        return parent(parent(index));
    }

    bool less(std::size_t a, std::size_t b) const {
        return compare_(data_[a], data_[b]);
    }

    bool greater(std::size_t a, std::size_t b) const {
        return compare_(data_[b], data_[a]);
    }

    void swapAt(std::size_t a, std::size_t b) { std::swap(data_[a], data_[b]); }

    std::size_t smallestChildOrGrandchild(std::size_t index) const {
        std::size_t result = index;
        std::size_t candidates[] = {
            left(index), right(index),
            left(left(index)), right(left(index)),
            left(right(index)), right(right(index))
        };

        for (std::size_t candidate : candidates) {
            if (candidate < data_.size() && less(candidate, result)) {
                result = candidate;
            }
        }

        return result;
    }

    std::size_t largestChildOrGrandchild(std::size_t index) const {
        std::size_t result = index;
        std::size_t candidates[] = {
            left(index), right(index),
            left(left(index)), right(left(index)),
            left(right(index)), right(right(index))
        };

        for (std::size_t candidate : candidates) {
            if (candidate < data_.size() && greater(candidate, result)) {
                result = candidate;
            }
        }

        return result;
    }

    void bubbleUp(std::size_t index) {
        if (index == 0) return;

        if (isMinLevel(index)) {
            if (less(parent(index), index)) {
                swapAt(index, parent(index));
                bubbleUpMax(parent(index));
            } else {
                bubbleUpMin(index);
            }
        } else {
            if (less(index, parent(index))) {
                swapAt(index, parent(index));
                bubbleUpMin(parent(index));
            } else {
                bubbleUpMax(index);
            }
        }
    }

    void bubbleUpMin(std::size_t index) {
        while (index >= 3) {
            std::size_t grand = grandparent(index);
            if (!less(index, grand)) break;
            swapAt(index, grand);
            index = grand;
        }
    }

    void bubbleUpMax(std::size_t index) {
        while (index >= 3) {
            std::size_t grand = grandparent(index);
            if (!greater(index, grand)) break;
            swapAt(index, grand);
            index = grand;
        }
    }

    void trickleDown(std::size_t index) {
        if (isMinLevel(index)) trickleDownMin(index);
        else trickleDownMax(index);
    }

    void trickleDownMin(std::size_t index) {
        while (left(index) < data_.size()) {
            std::size_t target = smallestChildOrGrandchild(index);
            if (target == index || !less(target, index)) break;

            std::size_t previous = index;
            swapAt(index, target);

            if (parent(target) != previous) {
                if (less(target, parent(target))) swapAt(target, parent(target));
            }

            index = target;
        }
    }

    void trickleDownMax(std::size_t index) {
        while (left(index) < data_.size()) {
            std::size_t target = largestChildOrGrandchild(index);
            if (target == index || !greater(target, index)) break;

            std::size_t previous = index;
            swapAt(index, target);

            if (parent(target) != previous) {
                if (less(target, parent(target))) swapAt(target, parent(target));
            }

            index = target;
        }
    }
};

#endif
