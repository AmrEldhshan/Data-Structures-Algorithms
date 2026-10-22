#ifndef DSA_SQRT_DECOMPOSITION_H
#define DSA_SQRT_DECOMPOSITION_H

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <vector>

// ---------------------------------------------------------------------------
// Sqrt decomposition
//
// Split an array into blocks of about sqrt(n). Range updates and queries touch
// whole blocks in O(1) and at most two partial blocks element by element.
//
// Range add / range sum: O(sqrt n) per operation.
// ---------------------------------------------------------------------------
template <typename T>
class SqrtDecomposition {
public:
    explicit SqrtDecomposition(const std::vector<T>& values)
        : values_(values),
          blockSize_(std::max<std::size_t>(1, static_cast<std::size_t>(
                                                  std::sqrt(values.size())))),
          blockSum_((values.size() + blockSize_ - 1) / blockSize_, 0),
          blockAdd_(blockSum_.size(), 0) {
        for (std::size_t i = 0; i < values_.size(); ++i) {
            blockSum_[i / blockSize_] += values_[i];
        }
    }

    void add(std::size_t left, std::size_t right, T value) {
        if (left >= right || left >= values_.size()) return;
        right = std::min(right, values_.size());

        std::size_t firstBlock = left / blockSize_;
        std::size_t lastBlock = (right - 1) / blockSize_;

        if (firstBlock == lastBlock) {
            for (std::size_t i = left; i < right; ++i) values_[i] += value;
            blockSum_[firstBlock] += value * static_cast<T>(right - left);
            return;
        }

        std::size_t firstEnd = (firstBlock + 1) * blockSize_;
        for (std::size_t i = left; i < firstEnd; ++i) values_[i] += value;
        blockSum_[firstBlock] += value * static_cast<T>(firstEnd - left);

        for (std::size_t block = firstBlock + 1; block < lastBlock; ++block) {
            blockAdd_[block] += value;
            blockSum_[block] += value * static_cast<T>(blockSize_);
        }

        std::size_t lastStart = lastBlock * blockSize_;
        for (std::size_t i = lastStart; i < right; ++i) values_[i] += value;
        blockSum_[lastBlock] += value * static_cast<T>(right - lastStart);
    }

    T sum(std::size_t left, std::size_t right) const {
        if (left >= right || left >= values_.size()) return T{};
        right = std::min(right, values_.size());

        std::size_t firstBlock = left / blockSize_;
        std::size_t lastBlock = (right - 1) / blockSize_;

        if (firstBlock == lastBlock) {
            T result = 0;
            for (std::size_t i = left; i < right; ++i) {
                result += values_[i] + blockAdd_[firstBlock];
            }
            return result;
        }

        T result = 0;
        std::size_t firstEnd = (firstBlock + 1) * blockSize_;
        for (std::size_t i = left; i < firstEnd; ++i) {
            result += values_[i] + blockAdd_[firstBlock];
        }

        for (std::size_t block = firstBlock + 1; block < lastBlock; ++block) {
            result += blockSum_[block];
        }

        std::size_t lastStart = lastBlock * blockSize_;
        for (std::size_t i = lastStart; i < right; ++i) {
            result += values_[i] + blockAdd_[lastBlock];
        }

        return result;
    }

private:
    std::vector<T> values_;
    std::size_t blockSize_;
    std::vector<T> blockSum_;
    std::vector<T> blockAdd_;
};

#endif
