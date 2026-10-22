#ifndef DSA_DYNAMIC_ARRAY_H
#define DSA_DYNAMIC_ARRAY_H

#include <algorithm>
#include <cstddef>
#include <stdexcept>

// ---------------------------------------------------------------------------
// Dynamic array
//
// A from-scratch growable array. `size` is the number of live elements;
// `capacity` is the number of allocated slots. When the array is full, the
// capacity doubles, so appends are O(1) amortised.
//
// Access O(1); push/pop at the end O(1) amortised; insert/erase O(n).
// ---------------------------------------------------------------------------
template <typename T>
class DynamicArray {
public:
    DynamicArray() = default;

    explicit DynamicArray(std::size_t capacity) {
        if (capacity > 0) {
            data_ = new T[capacity];
            capacity_ = capacity;
        }
    }

    DynamicArray(const DynamicArray& other)
        : data_(other.size_ ? new T[other.size_] : nullptr),
          size_(other.size_),
          capacity_(other.size_) {
        std::copy(other.data_, other.data_ + other.size_, data_);
    }

    DynamicArray(DynamicArray&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) return *this;
        DynamicArray copy(other);
        swap(copy);
        return *this;
    }

    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this == &other) return *this;
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        return *this;
    }

    ~DynamicArray() { delete[] data_; }

    std::size_t size() const { return size_; }
    std::size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }

    T& operator[](std::size_t index) { return data_[index]; }
    const T& operator[](std::size_t index) const { return data_[index]; }

    T& at(std::size_t index) {
        checkIndex(index);
        return data_[index];
    }

    const T& at(std::size_t index) const {
        checkIndex(index);
        return data_[index];
    }

    T& front() {
        if (empty()) throw std::out_of_range("DynamicArray: empty");
        return data_[0];
    }

    const T& front() const {
        if (empty()) throw std::out_of_range("DynamicArray: empty");
        return data_[0];
    }

    T& back() {
        if (empty()) throw std::out_of_range("DynamicArray: empty");
        return data_[size_ - 1];
    }

    const T& back() const {
        if (empty()) throw std::out_of_range("DynamicArray: empty");
        return data_[size_ - 1];
    }

    void reserve(std::size_t newCapacity) {
        if (newCapacity <= capacity_) return;

        T* newData = new T[newCapacity];
        std::copy(data_, data_ + size_, newData);
        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }

    void push_back(const T& value) {
        if (size_ == capacity_) reserve(capacity_ == 0 ? 1 : capacity_ * 2);
        data_[size_++] = value;
    }

    void pop_back() {
        if (empty()) throw std::out_of_range("DynamicArray: empty");
        --size_;
    }

    void insert(std::size_t index, const T& value) {
        if (index > size_) throw std::out_of_range("DynamicArray: index");

        if (size_ == capacity_) reserve(capacity_ == 0 ? 1 : capacity_ * 2);

        for (std::size_t i = size_; i > index; --i) {
            data_[i] = data_[i - 1];
        }

        data_[index] = value;
        ++size_;
    }

    void erase(std::size_t index) {
        checkIndex(index);

        for (std::size_t i = index; i + 1 < size_; ++i) {
            data_[i] = data_[i + 1];
        }

        --size_;
    }

    void resize(std::size_t newSize) {
        if (newSize > capacity_) reserve(newSize);
        if (newSize > size_) {
            for (std::size_t i = size_; i < newSize; ++i) data_[i] = T{};
        }
        size_ = newSize;
    }

    void clear() { size_ = 0; }

    T* begin() { return data_; }
    T* end() { return data_ + size_; }
    const T* begin() const { return data_; }
    const T* end() const { return data_ + size_; }

    void swap(DynamicArray& other) noexcept {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

private:
    void checkIndex(std::size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("DynamicArray: index out of range");
        }
    }

    T* data_ = nullptr;
    std::size_t size_ = 0;
    std::size_t capacity_ = 0;
};

#endif
