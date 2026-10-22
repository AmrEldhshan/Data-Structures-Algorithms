#ifndef DSA_HASH_MAP_H
#define DSA_HASH_MAP_H

#include <cstddef>
#include <functional>
#include <list>
#include <stdexcept>
#include <utility>
#include <vector>

// ---------------------------------------------------------------------------
// Hash map with separate chaining
//
// buckets_[h] holds every entry whose hash maps to h. A bucket is a linked
// list, so collisions are handled by appending to the list. When the load
// factor (size / buckets) exceeds `maxLoad`, the table doubles and entries are
// redistributed.
//
// Average: O(1) insert / find / erase
// Worst:   O(n) when every key collides
// Space:   O(n + buckets)
// ---------------------------------------------------------------------------
template <typename Key, typename Value, typename Hash = std::hash<Key>>
class HashMap {
public:
    explicit HashMap(std::size_t initialBuckets = 16,
                     double maxLoad = 0.75)
        : buckets_(initialBuckets == 0 ? 1 : initialBuckets),
          maxLoad_(maxLoad) {
        if (maxLoad <= 0.0 || maxLoad >= 1.0) {
            throw std::invalid_argument("HashMap: maxLoad must be in (0, 1)");
        }
    }

    // Returns true when the key was new, false when its value was updated.
    bool insert(const Key& key, const Value& value) {
        auto& bucket = buckets_[bucketFor(key)];
        for (Entry& entry : bucket) {
            if (entry.first == key) {
                entry.second = value;
                return false;
            }
        }

        bucket.emplace_front(key, value);
        ++size_;

        if (loadFactor() > maxLoad_) rehash(buckets_.size() * 2);
        return true;
    }

    Value* find(const Key& key) {
        auto& bucket = buckets_[bucketFor(key)];
        for (Entry& entry : bucket) {
            if (entry.first == key) return &entry.second;
        }
        return nullptr;
    }

    const Value* find(const Key& key) const {
        const auto& bucket = buckets_[bucketFor(key)];
        for (const Entry& entry : bucket) {
            if (entry.first == key) return &entry.second;
        }
        return nullptr;
    }

    bool contains(const Key& key) const { return find(key) != nullptr; }

    bool erase(const Key& key) {
        auto& bucket = buckets_[bucketFor(key)];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                --size_;
                return true;
            }
        }
        return false;
    }

    // Inserts a default-constructed value when the key is missing.
    Value& operator[](const Key& key) {
        if (Value* existing = find(key)) return *existing;
        insert(key, Value{});
        return *find(key);
    }

    std::size_t size() const { return size_; }

    bool empty() const { return size_ == 0; }

    std::size_t bucketCount() const { return buckets_.size(); }

    double loadFactor() const {
        return static_cast<double>(size_) / static_cast<double>(buckets_.size());
    }

private:
    using Entry = std::pair<Key, Value>;

    std::size_t bucketFor(const Key& key) const {
        return Hash{}(key) % buckets_.size();
    }

    void rehash(std::size_t newBucketCount) {
        std::vector<std::list<Entry>> grown(newBucketCount);

        for (const auto& bucket : buckets_) {
            for (const Entry& entry : bucket) {
                std::size_t index = Hash{}(entry.first) % newBucketCount;
                grown[index].push_back(entry);
            }
        }

        buckets_ = std::move(grown);
    }

    std::vector<std::list<Entry>> buckets_;
    std::size_t size_ = 0;
    double maxLoad_;
};

#endif // DSA_HASH_MAP_H
