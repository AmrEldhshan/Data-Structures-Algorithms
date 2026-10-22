#ifndef DSA_ORDERED_MAP_H
#define DSA_ORDERED_MAP_H

#include "data_structures/ordered/treap.h"

#include <cstddef>
#include <functional>
#include <optional>
#include <stdexcept>
#include <utility>
#include <vector>

// ---------------------------------------------------------------------------
// OrderedMap
//
// A sorted key-value map backed by a treap. Keys are unique. Iteration order is
// ascending by key. Also exposes order statistics and neighbour queries.
//
// Expected: O(log n) insert / erase / find / kth / rank.
// ---------------------------------------------------------------------------
template <typename Key, typename Value, typename Compare = std::less<Key>>
class OrderedMap {
public:
    explicit OrderedMap(Compare compare = Compare()) : tree_(std::move(compare)) {}

    bool insert(const Key& key, const Value& value) {
        return tree_.insert(key, value);
    }

    bool erase(const Key& key) { return tree_.erase(key); }
    bool contains(const Key& key) const { return tree_.contains(key); }

    Value& at(const Key& key) {
        Value* value = tree_.findValue(key);
        if (value == nullptr) throw std::out_of_range("OrderedMap: missing key");
        return *value;
    }

    const Value& at(const Key& key) const {
        const Value* value = tree_.findValue(key);
        if (value == nullptr) throw std::out_of_range("OrderedMap: missing key");
        return *value;
    }

    Value& operator[](const Key& key) {
        Value* value = tree_.findValue(key);
        if (value == nullptr) {
            tree_.insert(key, Value{});
            value = tree_.findValue(key);
        }
        return *value;
    }

    std::size_t size() const { return tree_.size(); }
    bool empty() const { return tree_.empty(); }
    void clear() { tree_.clear(); }

    const Key& minimumKey() const { return tree_.minimum(); }
    const Key& maximumKey() const { return tree_.maximum(); }
    const Key& kthKey(std::size_t index) const { return tree_.kth(index); }
    std::size_t rank(const Key& key) const { return tree_.rank(key); }

    std::optional<Key> lowerBound(const Key& key) const {
        return tree_.lowerBound(key);
    }

    std::optional<Key> upperBound(const Key& key) const {
        return tree_.upperBound(key);
    }

    std::vector<Key> keys() const { return tree_.keys(); }
    std::vector<std::pair<Key, Value>> entries() const { return tree_.entries(); }

private:
    Treap<Key, Value, Compare> tree_;
};

#endif
