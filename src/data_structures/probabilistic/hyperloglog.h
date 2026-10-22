#ifndef DSA_HYPERLOGLOG_H
#define DSA_HYPERLOGLOG_H

#include <algorithm>
#include <bit>
#include <cmath>
#include <cstdint>
#include <functional>
#include <stdexcept>
#include <vector>

// ---------------------------------------------------------------------------
// HyperLogLog
//
// Estimates the number of distinct elements using a small array of registers.
// Each element updates the register selected by its hash prefix with the
// position of the first 1 bit in the remaining suffix. The harmonic mean of
// 2^register gives the estimate.
//
// add: O(1)
// Space: O(2^precision) bytes
// Relative error: about 1.04 / sqrt(2^precision)
// ---------------------------------------------------------------------------
template <typename T>
class HyperLogLog {
public:
    explicit HyperLogLog(unsigned precision = 12)
        : precision_(precision), registers_(std::size_t{1} << precision, 0) {
        if (precision < 4 || precision > 18) {
            throw std::invalid_argument("HyperLogLog: precision must be 4..18");
        }
    }

    void add(const T& value) {
        std::uint64_t hash = mix(std::hash<T>{}(value));
        std::size_t index = hash & (registers_.size() - 1);
        std::uint64_t remaining = hash >> precision_;

        // The shift leaves `precision_` zero bits at the top; ignore those
        // when counting how many leading zeros the suffix actually has.
        std::uint8_t rank = static_cast<std::uint8_t>(
            std::countl_zero(remaining) - precision_ + 1);
        registers_[index] = std::max(registers_[index], rank);
    }

    double estimate() const {
        double sum = 0.0;
        std::size_t zeros = 0;

        for (std::uint8_t registerValue : registers_) {
            sum += std::ldexp(1.0, -static_cast<int>(registerValue));
            if (registerValue == 0) ++zeros;
        }

        double m = static_cast<double>(registers_.size());
        double alpha = 0.7213 / (1.0 + 1.079 / m);
        double result = alpha * m * m / sum;

        if (result <= 2.5 * m && zeros > 0) {
            result = m * std::log(m / static_cast<double>(zeros));
        }

        return result;
    }

    void clear() { std::fill(registers_.begin(), registers_.end(), 0); }

private:
    unsigned precision_;
    std::vector<std::uint8_t> registers_;

    static std::uint64_t mix(std::uint64_t value) {
        value += 0x9E3779B97F4A7C15ULL;
        value = (value ^ (value >> 30)) * 0xBF58476D1CE4E5B9ULL;
        value = (value ^ (value >> 27)) * 0x94D049BB133111EBULL;
        return value ^ (value >> 31);
    }
};

#endif
