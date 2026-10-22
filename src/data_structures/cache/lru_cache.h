#ifndef DSA_LRU_CACHE_H
#define DSA_LRU_CACHE_H

#include <cstddef>
#include <list>
#include <optional>
#include <stdexcept>
#include <unordered_map>
#include <utility>

// ---------------------------------------------------------------------------
// LRU cache (least recently used)
//
// Combines a hash map with a doubly linked list:
//   - the map finds a key in O(1)
//   - the list keeps recency order: front = most recent, back = least recent
//
// get(key)   : return the value and move it to the front
// put(k, v)  : insert/update and move to the front; evict the back if full
//
// Time:  O(1) average per operation
// Space: O(capacity)
// ---------------------------------------------------------------------------
template <typename Key, typename Value>
class LruCache {
public:
    explicit LruCache(std::size_t capacity) : capacity_(capacity) {
        if (capacity == 0) {
            throw std::invalid_argument("LruCache: capacity must be positive");
        }
    }

    std::optional<Value> get(const Key& key) {
        auto found = index_.find(key);
        if (found == index_.end()) return std::nullopt;

        touch(found);
        return found->second->second;
    }

    void put(const Key& key, const Value& value) {
        auto found = index_.find(key);

        if (found != index_.end()) {
            found->second->second = value;
            touch(found);
            return;
        }

        if (entries_.size() == capacity_) {
            index_.erase(entries_.back().first);
            entries_.pop_back();
        }

        entries_.push_front({key, value});
        index_[key] = entries_.begin();
    }

    bool contains(const Key& key) const {
        return index_.find(key) != index_.end();
    }

    bool erase(const Key& key) {
        auto found = index_.find(key);
        if (found == index_.end()) return false;

        entries_.erase(found->second);
        index_.erase(found);
        return true;
    }

    std::size_t size() const { return entries_.size(); }

    std::size_t capacity() const { return capacity_; }

private:
    using Entry = std::pair<Key, Value>;
    using Iterator = typename std::list<Entry>::iterator;

    void touch(typename std::unordered_map<Key, Iterator>::iterator found) {
        entries_.splice(entries_.begin(), entries_, found->second);
    }

    std::size_t capacity_;
    std::list<Entry> entries_;
    std::unordered_map<Key, Iterator> index_;
};

#endif // DSA_LRU_CACHE_H
