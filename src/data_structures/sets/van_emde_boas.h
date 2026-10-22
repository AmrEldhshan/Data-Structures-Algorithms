#ifndef DSA_VAN_EMDE_BOAS_H
#define DSA_VAN_EMDE_BOAS_H

#include <array>
#include <bit>
#include <cstddef>
#include <cstdint>
#include <stdexcept>

// ---------------------------------------------------------------------------
// Van Emde Boas set (two-level layout)
//
// Supports insert, remove, contains, successor, and predecessor on a universe
// of 16-bit integers. The universe is split into 256 clusters of 256 bits,
// with a 256-bit summary of non-empty clusters. This is the same recursive
// sqrt idea as a full vEB tree, flattened for readability.
//
// All operations: O(1) with this fixed universe.
// ---------------------------------------------------------------------------
class VanEmdeBoas {
public:
    static constexpr int UNIVERSE_BITS = 16;
    static constexpr int UNIVERSE = 1 << UNIVERSE_BITS;
    static constexpr int LOW_BITS = 8;
    static constexpr int CLUSTER_COUNT = 1 << LOW_BITS;
    static constexpr int WORDS = CLUSTER_COUNT / 64;

    VanEmdeBoas() { summary_.fill(0); }

    bool empty() const { return size_ == 0; }
    std::size_t size() const { return size_; }

    void insert(int value) {
        checkRange(value);
        if (contains(value)) return;

        int high = value >> LOW_BITS;
        int low = value & (CLUSTER_COUNT - 1);
        setBit(clusters_[high], low);
        setBit(summary_, high);
        ++size_;

        if (size_ == 1) {
            minimum_ = maximum_ = value;
        } else {
            minimum_ = std::min(minimum_, value);
            maximum_ = std::max(maximum_, value);
        }
    }

    bool contains(int value) const {
        if (value < 0 || value >= UNIVERSE) return false;
        int high = value >> LOW_BITS;
        int low = value & (CLUSTER_COUNT - 1);
        return testBit(clusters_[high], low);
    }

    int minimum() const {
        if (empty()) throw std::out_of_range("VanEmdeBoas: empty");
        return minimum_;
    }

    int maximum() const {
        if (empty()) throw std::out_of_range("VanEmdeBoas: empty");
        return maximum_;
    }

    int successor(int value) const {
        if (empty() || value >= maximum_) return -1;
        if (value < minimum_) return minimum_;

        int high = value >> LOW_BITS;
        int low = value & (CLUSTER_COUNT - 1);

        int nextLow = nextSet(clusters_[high], low + 1);
        if (nextLow != -1) return (high << LOW_BITS) | nextLow;

        int nextCluster = nextSet(summary_, high + 1);
        if (nextCluster == -1) return -1;

        return (nextCluster << LOW_BITS) | firstSet(clusters_[nextCluster]);
    }

    int predecessor(int value) const {
        if (empty() || value <= minimum_) return -1;
        if (value > maximum_) return maximum_;

        int high = value >> LOW_BITS;
        int low = value & (CLUSTER_COUNT - 1);

        int previousLow = previousSet(clusters_[high], low - 1);
        if (previousLow != -1) return (high << LOW_BITS) | previousLow;

        int previousCluster = previousSet(summary_, high - 1);
        if (previousCluster == -1) return -1;

        return (previousCluster << LOW_BITS) | lastSet(clusters_[previousCluster]);
    }

    void remove(int value) {
        if (!contains(value)) return;

        int high = value >> LOW_BITS;
        int low = value & (CLUSTER_COUNT - 1);
        clearBit(clusters_[high], low);
        --size_;

        if (clusterEmpty(clusters_[high])) clearBit(summary_, high);

        if (size_ == 0) {
            minimum_ = maximum_ = -1;
        } else {
            int firstCluster = firstSet(summary_);
            minimum_ = (firstCluster << LOW_BITS) |
                       firstSet(clusters_[firstCluster]);
            int lastClusterValue = lastSet(summary_);
            maximum_ = (lastClusterValue << LOW_BITS) |
                       lastSet(clusters_[lastClusterValue]);
        }
    }

private:
    std::array<std::array<std::uint64_t, WORDS>, CLUSTER_COUNT> clusters_{};
    std::array<std::uint64_t, WORDS> summary_{};
    std::size_t size_ = 0;
    int minimum_ = -1;
    int maximum_ = -1;

    static void checkRange(int value) {
        if (value < 0 || value >= UNIVERSE) {
            throw std::out_of_range("VanEmdeBoas: value out of range");
        }
    }

    static void setBit(std::array<std::uint64_t, WORDS>& words, int index) {
        words[static_cast<std::size_t>(index / 64)] |=
            (1ULL << (index % 64));
    }

    static void clearBit(std::array<std::uint64_t, WORDS>& words, int index) {
        words[static_cast<std::size_t>(index / 64)] &=
            ~(1ULL << (index % 64));
    }

    static bool clusterEmpty(const std::array<std::uint64_t, WORDS>& words) {
        for (std::uint64_t word : words) {
            if (word != 0) return false;
        }
        return true;
    }

    static bool testBit(const std::array<std::uint64_t, WORDS>& words,
                        int index) {
        return (words[static_cast<std::size_t>(index / 64)] >>
                (index % 64)) & 1ULL;
    }

    static int firstSet(const std::array<std::uint64_t, WORDS>& words) {
        for (int word = 0; word < WORDS; ++word) {
            if (words[word] != 0) {
                return word * 64 + std::countr_zero(words[word]);
            }
        }
        return -1;
    }

    static int lastSet(const std::array<std::uint64_t, WORDS>& words) {
        for (int word = WORDS - 1; word >= 0; --word) {
            if (words[word] != 0) {
                return word * 64 + 63 - std::countl_zero(words[word]);
            }
        }
        return -1;
    }

    static int nextSet(const std::array<std::uint64_t, WORDS>& words,
                       int from) {
        if (from < 0 || from >= CLUSTER_COUNT) return -1;

        int word = from / 64;
        std::uint64_t bits = words[word] & (~0ULL << (from % 64));

        while (true) {
            if (bits != 0) {
                return word * 64 + std::countr_zero(bits);
            }
            if (++word >= WORDS) return -1;
            bits = words[word];
        }
    }

    static int previousSet(const std::array<std::uint64_t, WORDS>& words,
                           int from) {
        if (from < 0) return -1;
        if (from >= CLUSTER_COUNT) from = CLUSTER_COUNT - 1;

        int word = from / 64;
        std::uint64_t bits = words[word] & (~0ULL >> (63 - (from % 64)));

        while (true) {
            if (bits != 0) {
                return word * 64 + 63 - std::countl_zero(bits);
            }
            if (--word < 0) return -1;
            bits = words[word];
        }
    }
};

#endif
