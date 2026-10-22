#ifndef DSA_SUFFIX_TREE_H
#define DSA_SUFFIX_TREE_H

#include "data_structures/trees/radix_tree.h"

#include <cstddef>
#include <string>

// ---------------------------------------------------------------------------
// Suffix tree (constructed by inserting every suffix into a radix tree)
//
// This is the straightforward O(n²) construction. Production suffix trees use
// Ukkonen's algorithm for O(n), but the resulting query structure is the same:
// every node path is a substring, and suffixes end at terminal nodes.
//
// contains: O(m)
// occurrences: O(n) to count suffixes in the matching subtree
// ---------------------------------------------------------------------------
class SuffixTree {
public:
    explicit SuffixTree(const std::string& text) : text_(text) {
        for (std::size_t i = 0; i < text_.size(); ++i) {
            tree_.insert(text_.substr(i));
        }
    }

    bool contains(const std::string& pattern) const {
        return tree_.containsPrefix(pattern);
    }

    int occurrences(const std::string& pattern) const {
        return static_cast<int>(tree_.countPrefix(pattern));
    }

    std::size_t suffixCount() const { return text_.size(); }

private:
    std::string text_;
    RadixTree tree_;
};

#endif
