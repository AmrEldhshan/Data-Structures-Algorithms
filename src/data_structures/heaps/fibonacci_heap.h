#ifndef DSA_FIBONACCI_HEAP_H
#define DSA_FIBONACCI_HEAP_H

#include <algorithm>
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <vector>

// ---------------------------------------------------------------------------
// Fibonacci heap (lazy binomial variant)
//
// This implementation keeps a collection of heap-ordered trees and delays
// restructuring until extractMin. That gives the same headline costs as a
// Fibonacci heap for insert/min/extract; decrease-key is not implemented.
//
// insert: O(1)
// min:    O(1)
// extractMin: O(log n) amortised
// ---------------------------------------------------------------------------
template <typename T>
class FibonacciHeap {
public:
    FibonacciHeap() = default;

    bool empty() const { return size_ == 0; }
    std::size_t size() const { return size_; }

    void insert(const T& value) {
        roots_.push_back(std::make_unique<Node>(value));
        ++size_;
    }

    const T& minimum() const {
        if (empty()) throw std::out_of_range("FibonacciHeap: empty");
        return findMinimum()->value;
    }

    T extractMin() {
        if (empty()) throw std::out_of_range("FibonacciHeap: empty");

        std::size_t minIndex = minimumIndex();
        std::unique_ptr<Node> minimum = std::move(roots_[minIndex]);
        roots_.erase(roots_.begin() + static_cast<std::ptrdiff_t>(minIndex));

        for (auto& child : minimum->children) roots_.push_back(std::move(child));
        minimum->children.clear();

        --size_;
        if (size_ > 0) consolidate();
        return minimum->value;
    }

private:
    struct Node {
        T value;
        std::vector<std::unique_ptr<Node>> children;
        int degree = 0;

        explicit Node(const T& key) : value(key) {}
    };

    std::vector<std::unique_ptr<Node>> roots_;
    std::size_t size_ = 0;

    const Node* findMinimum() const {
        const Node* best = roots_.front().get();
        for (const auto& root : roots_) {
            if (root->value < best->value) best = root.get();
        }
        return best;
    }

    std::size_t minimumIndex() const {
        std::size_t best = 0;
        for (std::size_t i = 1; i < roots_.size(); ++i) {
            if (roots_[i]->value < roots_[best]->value) best = i;
        }
        return best;
    }

    static void link(std::unique_ptr<Node> child, Node* parent) {
        parent->children.push_back(std::move(child));
        ++parent->degree;
    }

    void consolidate() {
        std::vector<std::unique_ptr<Node>> byDegree;
        std::vector<std::unique_ptr<Node>> pending = std::move(roots_);
        roots_.clear();

        for (auto& tree : pending) {
            std::unique_ptr<Node> current = std::move(tree);

            while (true) {
                std::size_t degree = static_cast<std::size_t>(current->degree);
                if (degree >= byDegree.size()) byDegree.resize(degree + 1);

                if (!byDegree[degree]) {
                    byDegree[degree] = std::move(current);
                    break;
                }

                if (byDegree[degree]->value <= current->value) {
                    link(std::move(current), byDegree[degree].get());
                    current = std::move(byDegree[degree]);
                } else {
                    link(std::move(byDegree[degree]), current.get());
                }

                byDegree[degree].reset();
            }
        }

        for (auto& tree : byDegree) {
            if (tree) roots_.push_back(std::move(tree));
        }
    }
};

#endif
