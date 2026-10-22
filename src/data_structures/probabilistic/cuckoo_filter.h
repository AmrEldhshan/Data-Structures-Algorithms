#ifndef DSA_CUCKOO_FILTER_H
#define DSA_CUCKOO_FILTER_H

#include <cstddef>
#include <cstdint>
#include <functional>
#include <stdexcept>
#include <vector>

// ---------------------------------------------------------------------------
// Cuckoo filter
//
// A probabilistic membership filter that supports deletion. Each item has a
// fingerprint and two candidate buckets. Insertion kicks an existing
// fingerprint to its alternate bucket when the chosen bucket is full.
//
// insert / contains / erase: O(1) expected
// ---------------------------------------------------------------------------
template <typename T>
class CuckooFilter {
public:
    explicit CuckooFilter(std::size_t bucketCount = 1024,
                          std::size_t bucketSize = 4)
        : buckets_(bucketCount), bucketSize_(bucketSize) {
        if (bucketCount == 0 || bucketSize == 0) {
            throw std::invalid_argument("CuckooFilter: dimensions must be positive");
        }
    }

    bool insert(const T& value) {
        std::size_t hash = std::hash<T>{}(value);
        std::uint16_t fingerprint = makeFingerprint(hash);
        std::size_t first = hash % buckets_.size();
        std::size_t second = alternate(first, fingerprint);

        if (hasSpace(first)) {
            buckets_[first].push_back(fingerprint);
            ++size_;
            return true;
        }
        if (hasSpace(second)) {
            buckets_[second].push_back(fingerprint);
            ++size_;
            return true;
        }

        // Relocate fingerprints until a free slot appears or the kick limit is hit.
        std::size_t index = first;
        std::uint16_t current = fingerprint;

        for (std::size_t kick = 0; kick < 500; ++kick) {
            std::size_t slot = mix(hash + kick) % buckets_[index].size();
            std::swap(current, buckets_[index][slot]);
            index = alternate(index, current);

            if (hasSpace(index)) {
                buckets_[index].push_back(current);
                ++size_;
                return true;
            }
        }

        return false;
    }

    bool contains(const T& value) const {
        std::size_t hash = std::hash<T>{}(value);
        std::uint16_t fingerprint = makeFingerprint(hash);
        std::size_t first = hash % buckets_.size();
        std::size_t second = alternate(first, fingerprint);

        return hasFingerprint(first, fingerprint) ||
               hasFingerprint(second, fingerprint);
    }

    bool erase(const T& value) {
        std::size_t hash = std::hash<T>{}(value);
        std::uint16_t fingerprint = makeFingerprint(hash);
        std::size_t first = hash % buckets_.size();
        std::size_t second = alternate(first, fingerprint);

        for (std::size_t index : {first, second}) {
            auto& bucket = buckets_[index];
            for (std::size_t i = 0; i < bucket.size(); ++i) {
                if (bucket[i] == fingerprint) {
                    bucket.erase(bucket.begin() + static_cast<std::ptrdiff_t>(i));
                    --size_;
                    return true;
                }
            }
        }

        return false;
    }

    std::size_t size() const { return size_; }
    std::size_t bucketCount() const { return buckets_.size(); }

private:
    std::vector<std::vector<std::uint16_t>> buckets_;
    std::size_t bucketSize_;
    std::size_t size_ = 0;

    bool hasSpace(std::size_t index) const {
        return buckets_[index].size() < bucketSize_;
    }

    bool hasFingerprint(std::size_t index, std::uint16_t fingerprint) const {
        for (std::uint16_t value : buckets_[index]) {
            if (value == fingerprint) return true;
        }
        return false;
    }

    static std::uint16_t makeFingerprint(std::size_t hash) {
        std::uint16_t fingerprint =
            static_cast<std::uint16_t>((hash >> 32) ^ hash);
        return fingerprint == 0 ? 1 : fingerprint;
    }

    std::size_t alternate(std::size_t index, std::uint16_t fingerprint) const {
        return (index ^ (static_cast<std::size_t>(fingerprint) * 0x5BD1E995ULL)) %
               buckets_.size();
    }

    static std::size_t mix(std::size_t value) {
        value ^= value >> 33;
        value *= 0xff51afd7ed558ccdULL;
        value ^= value >> 33;
        return value;
    }
};

#endif
