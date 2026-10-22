#ifndef DSA_DEQUE_H
#define DSA_DEQUE_H

#include <cstddef>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// ---------------------------------------------------------------------------
// Double-ended queue (deque)
//
// A growable circular buffer. Both ends support O(1) insertion and removal.
// `head_` is the physical slot of logical element 0; logical index i lives at
// (head_ + i) % capacity.
//
// Amortized time: O(1) per push/pop (occasional O(n) resize).
// Space: O(n).
// ---------------------------------------------------------------------------
template <typename T>
class Deque {
public:
    Deque() = default;

    bool empty() const { return count_ == 0; }

    std::size_t size() const { return count_; }

    void clear() {
        buffer_.clear();
        head_ = 0;
        count_ = 0;
    }

    void pushBack(const T& value) {
        ensureCapacity();
        buffer_[physical(count_)] = value;
        ++count_;
    }

    void pushFront(const T& value) {
        ensureCapacity();
        head_ = (head_ + buffer_.size() - 1) % buffer_.size();
        buffer_[head_] = value;
        ++count_;
    }

    void popBack() {
        checkNotEmpty("popBack");
        --count_;
    }

    void popFront() {
        checkNotEmpty("popFront");
        head_ = (head_ + 1) % buffer_.size();
        --count_;
    }

    T& front() {
        checkNotEmpty("front");
        return buffer_[head_];
    }

    const T& front() const {
        checkNotEmpty("front");
        return buffer_[head_];
    }

    T& back() {
        checkNotEmpty("back");
        return buffer_[physical(count_ - 1)];
    }

    const T& back() const {
        checkNotEmpty("back");
        return buffer_[physical(count_ - 1)];
    }

    T& operator[](std::size_t index) {
        checkIndex(index);
        return buffer_[physical(index)];
    }

    const T& operator[](std::size_t index) const {
        checkIndex(index);
        return buffer_[physical(index)];
    }

private:
    std::size_t physical(std::size_t index) const {
        return (head_ + index) % buffer_.size();
    }

    void checkNotEmpty(const char* operation) const {
        if (empty()) {
            throw std::out_of_range(std::string("Deque::") + operation +
                                    ": empty deque");
        }
    }

    void checkIndex(std::size_t index) const {
        if (index >= count_) {
            throw std::out_of_range("Deque: index out of range");
        }
    }

    void ensureCapacity() {
        if (buffer_.empty()) {
            buffer_.resize(1);
            return;
        }
        if (count_ < buffer_.size()) return;

        std::vector<T> grown(buffer_.size() * 2);
        for (std::size_t i = 0; i < count_; ++i) {
            grown[i] = std::move(buffer_[physical(i)]);
        }

        buffer_ = std::move(grown);
        head_ = 0;
    }

    std::vector<T> buffer_;
    std::size_t head_ = 0;
    std::size_t count_ = 0;
};

#endif // DSA_DEQUE_H
