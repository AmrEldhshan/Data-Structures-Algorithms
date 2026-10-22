#ifndef DSA_BINOMIAL_HEAP_H
#define DSA_BINOMIAL_HEAP_H

#include <algorithm>
#include <cstddef>
#include <functional>
#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

// ---------------------------------------------------------------------------
// Binomial heap
//
// A collection of binomial trees. A tree of degree k has 2^k nodes and is
// formed by linking two trees of degree k-1. The heap keeps at most one tree of
// each degree, so it behaves like a binary representation of the size.
//
// insert:      O(log n) amortised
// findMin:     O(log n)
// extractMin:  O(log n)
// merge:       O(log n)
// ---------------------------------------------------------------------------
template <typename T, typename Compare = std::less<T>>
class BinomialHeap {
public:
    BinomialHeap() = default;

    explicit BinomialHeap(Compare compare) : compare_(std::move(compare)) {}

    BinomialHeap(const BinomialHeap&) = delete;
    BinomialHeap& operator=(const BinomialHeap&) = delete;

    BinomialHeap(BinomialHeap&&) noexcept = default;
    BinomialHeap& operator=(BinomialHeap&&) noexcept = default;

    bool empty() const { return size_ == 0; }
    std::size_t size() const { return size_; }

    const T& minimum() const {
        if (empty()) throw std::out_of_range("BinomialHeap: empty");

        const T* result = nullptr;
        for (const auto& tree : trees_) {
            if (tree != nullptr && (result == nullptr || compare_(tree->key, *result))) {
                result = &tree->key;
            }
        }
        return *result;
    }

    void insert(const T& value) {
        BinomialHeap other(compare_);
        other.trees_.push_back(std::make_unique<Node>(value));
        other.size_ = 1;
        merge(std::move(other));
    }

    T extractMin() {
        if (empty()) throw std::out_of_range("BinomialHeap: empty");

        std::size_t minimumIndex = trees_.size();
        for (std::size_t i = 0; i < trees_.size(); ++i) {
            if (trees_[i] == nullptr) continue;
            if (minimumIndex == trees_.size() ||
                compare_(trees_[i]->key, trees_[minimumIndex]->key)) {
                minimumIndex = i;
            }
        }

        std::unique_ptr<Node> minimumTree = std::move(trees_[minimumIndex]);

        BinomialHeap rest(compare_);
        rest.trees_.resize(minimumTree->children.size());
        for (std::size_t i = 0; i < minimumTree->children.size(); ++i) {
            rest.trees_[i] = std::move(minimumTree->children[i]);
            rest.size_ += (std::size_t{1} << i);
        }

        size_ = 0;
        for (const auto& tree : trees_) {
            if (tree != nullptr) size_ += (std::size_t{1} << tree->degree);
        }

        T result = minimumTree->key;
        merge(std::move(rest));
        return result;
    }

    void merge(BinomialHeap&& other) {
        std::vector<std::unique_ptr<Node>> merged;
        merged.reserve(std::max(trees_.size(), other.trees_.size()) + 1);

        std::unique_ptr<Node> carry;
        std::size_t limit = std::max(trees_.size(), other.trees_.size());

        for (std::size_t degree = 0; degree <= limit; ++degree) {
            std::unique_ptr<Node> a =
                degree < trees_.size() ? std::move(trees_[degree]) : nullptr;
            std::unique_ptr<Node> b =
                degree < other.trees_.size() ? std::move(other.trees_[degree]) : nullptr;

            std::unique_ptr<Node> result;
            int count = (a != nullptr) + (b != nullptr) + (carry != nullptr);

            if (count == 0) {
                result = nullptr;
            } else if (count == 1) {
                result = a != nullptr ? std::move(a)
                         : b != nullptr ? std::move(b)
                                        : std::move(carry);
                carry = nullptr;
            } else if (count == 2) {
                if (a == nullptr) {
                    a = std::move(carry);
                    carry = nullptr;
                } else if (b == nullptr) {
                    b = std::move(carry);
                    carry = nullptr;
                }

                carry = link(std::move(a), std::move(b));
            } else {
                result = std::move(carry);
                carry = link(std::move(a), std::move(b));
            }

            merged.push_back(std::move(result));
        }

        while (merged.size() > 1 && merged.back() == nullptr) merged.pop_back();
        trees_ = std::move(merged);
        other.trees_.clear();
        other.size_ = 0;
        recalculateSize();
    }

    std::vector<T> values() const {
        std::vector<T> result;
        result.reserve(size_);
        for (const auto& tree : trees_) collect(tree.get(), result);
        std::sort(result.begin(), result.end(), compare_);
        return result;
    }

private:
    struct Node {
        T key;
        std::size_t degree = 0;
        std::vector<std::unique_ptr<Node>> children;

        explicit Node(const T& value) : key(value) {}
    };

    Compare compare_;
    std::vector<std::unique_ptr<Node>> trees_;
    std::size_t size_ = 0;

    std::unique_ptr<Node> link(std::unique_ptr<Node> a,
                               std::unique_ptr<Node> b) {
        if (compare_(b->key, a->key)) std::swap(a, b);
        a->children.push_back(std::move(b));
        ++a->degree;
        return a;
    }

    void recalculateSize() {
        size_ = 0;
        for (std::size_t i = 0; i < trees_.size(); ++i) {
            if (trees_[i] != nullptr) size_ += (std::size_t{1} << i);
        }
    }

    static void collect(const Node* node, std::vector<T>& result) {
        if (node == nullptr) return;
        result.push_back(node->key);
        for (const auto& child : node->children) collect(child.get(), result);
    }
};

#endif
