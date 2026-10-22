#ifndef DSA_ORDERED_SET_H
#define DSA_ORDERED_SET_H

#include "data_structures/ordered/treap.h"

#include <cstddef>
#include <functional>
#include <optional>
#include <variant>
#include <vector>

// ---------------------------------------------------------------------------
// OrderedSet
//
// A sorted set with unique keys, backed by a treap. Supports order statistics
// (kth and rank) and predecessor/successor queries through lowerBound and
// upperBound.
//
// Expected: O(log n) insert / erase / contains / kth / rank.
// ---------------------------------------------------------------------------
template <typename T, typename Compare = std::less<T>>
class OrderedSet {
public:
    explicit OrderedSet(Compare compare = Compare()) : tree_(std::move(compare)) {}

    bool insert(const T& value) { return tree_.insert(value, std::monostate{}); }
    bool erase(const T& value) { return tree_.erase(value); }
    bool contains(const T& value) const { return tree_.contains(value); }

    std::size_t size() const { return tree_.size(); }
    bool empty() const { return tree_.empty(); }
    void clear() { tree_.clear(); }

    const T& minimum() const { return tree_.minimum(); }
    const T& maximum() const { return tree_.maximum(); }
    const T& kth(std::size_t index) const { return tree_.kth(index); }
    std::size_t rank(const T& value) const { return tree_.rank(value); }

    std::optional<T> lowerBound(const T& value) const {
        return tree_.lowerBound(value);
    }

    std::optional<T> upperBound(const T& value) const {
        return tree_.upperBound(value);
    }

    std::vector<T> toVector() const { return tree_.keys(); }

private:
    Treap<T, std::monostate, Compare> tree_;
};

#endif
