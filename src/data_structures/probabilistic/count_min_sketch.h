#ifndef DSA_COUNT_MIN_SKETCH_H
#define DSA_COUNT_MIN_SKETCH_H

#include <algorithm>
#include <cstdint>
#include <functional>
#include <limits>
#include <stdexcept>
#include <vector>

// ---------------------------------------------------------------------------
// Count-min sketch
//
// A probabilistic frequency table. Each item is hashed once per row; the
// estimate is the minimum of the counters it touches. Counters only increase,
// so the estimate never underestimates (up to hash collisions), but it may
// overestimate because of collisions.
//
// add / estimate: O(depth)
// Space: O(width * depth)
// ---------------------------------------------------------------------------
template <typename T>
class CountMinSketch {
public:
    CountMinSketch(std::size_t width, std::size_t depth)
        : width_(width), depth_(depth), table_(depth, std::vector<int>(width, 0)) {
        if (width == 0 || depth == 0) {
            throw std::invalid_argument("CountMinSketch: dimensions must be positive");
        }

        seeds_.resize(depth);
        for (std::size_t i = 0; i < depth; ++i) seeds_[i] = mix(0x9E3779B97F4A7C15ULL + i);
    }

    void add(const T& value, int count = 1) {
        std::size_t hash = hashValue(value);

        for (std::size_t row = 0; row < depth_; ++row) {
            table_[row][index(hash, row)] += count;
        }
    }

    int estimate(const T& value) const {
        std::size_t hash = hashValue(value);
        int result = std::numeric_limits<int>::max();

        for (std::size_t row = 0; row < depth_; ++row) {
            result = std::min(result, table_[row][index(hash, row)]);
        }

        return result;
    }

    std::size_t width() const { return width_; }
    std::size_t depth() const { return depth_; }

private:
    std::size_t width_;
    std::size_t depth_;
    std::vector<std::vector<int>> table_;
    std::vector<std::uint64_t> seeds_;

    static std::uint64_t mix(std::uint64_t value) {
        value += 0x9E3779B97F4A7C15ULL;
        value = (value ^ (value >> 30)) * 0xBF58476D1CE4E5B9ULL;
        value = (value ^ (value >> 27)) * 0x94D049BB133111EBULL;
        return value ^ (value >> 31);
    }

    static std::size_t hashValue(const T& value) {
        return static_cast<std::size_t>(std::hash<T>{}(value));
    }

    std::size_t index(std::size_t hash, std::size_t row) const {
        return static_cast<std::size_t>(mix(hash ^ seeds_[row]) % width_);
    }
};

#endif
