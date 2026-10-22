#ifndef DSA_ROPE_H
#define DSA_ROPE_H

#include <algorithm>
#include <cstddef>
#include <memory>
#include <string>
#include <utility>

// ---------------------------------------------------------------------------
// Rope
//
// A rope stores a string as a binary tree of chunks. Leaves hold short
// substrings; every node stores the total length of its subtree. This makes
// insertion/deletion/concat cheap for large texts, at the cost of random
// access being O(log n) instead of O(1).
//
// This implementation rebuilds a balanced chunk tree with `build` and uses
// split/merge for edits. The tree is not rebalanced after edits.
// ---------------------------------------------------------------------------
class Rope {
public:
    Rope() = default;
    explicit Rope(const std::string& text) { root_ = build(text); }

    std::size_t size() const { return root_ ? root_->length : 0; }
    bool empty() const { return size() == 0; }

    char at(std::size_t index) const {
        return charAt(root_.get(), index);
    }

    void append(const std::string& text) {
        insert(size(), text);
    }

    void insert(std::size_t position, const std::string& text) {
        if (position > size()) position = size();

        auto [left, right] = split(std::move(root_), position);
        root_ = merge(merge(std::move(left), build(text)), std::move(right));
    }

    void erase(std::size_t position, std::size_t count) {
        if (position >= size() || count == 0) return;
        if (count > size() - position) count = size() - position;

        auto [left, rest] = split(std::move(root_), position);
        auto [middle, right] = split(std::move(rest), count);
        root_ = merge(std::move(left), std::move(right));
    }

    std::string substring(std::size_t position, std::size_t count) const {
        if (position >= size()) return {};
        if (count > size() - position) count = size() - position;

        std::string result;
        result.reserve(count);
        collectRange(root_.get(), position, position + count, 0, result);
        return result;
    }

    std::string toString() const {
        std::string result;
        result.reserve(size());
        collect(root_.get(), result);
        return result;
    }

private:
    static constexpr std::size_t CHUNK_SIZE = 8;

    struct Node {
        std::string chunk;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;
        std::size_t length = 0;

        explicit Node(std::string text) : chunk(std::move(text)) {
            length = chunk.size();
        }

        Node(std::unique_ptr<Node> l, std::unique_ptr<Node> r)
            : left(std::move(l)), right(std::move(r)) {
            length = (left ? left->length : 0) + (right ? right->length : 0);
        }
    };

    std::unique_ptr<Node> root_;

    static std::unique_ptr<Node> build(const std::string& text) {
        if (text.empty()) return nullptr;
        if (text.size() <= CHUNK_SIZE) return std::make_unique<Node>(text);

        std::size_t middle = text.size() / 2;
        return std::make_unique<Node>(build(text.substr(0, middle)),
                                      build(text.substr(middle)));
    }

    static std::unique_ptr<Node> merge(std::unique_ptr<Node> left,
                                       std::unique_ptr<Node> right) {
        if (!left) return right;
        if (!right) return left;
        return std::make_unique<Node>(std::move(left), std::move(right));
    }

    static std::pair<std::unique_ptr<Node>, std::unique_ptr<Node>>
    split(std::unique_ptr<Node> node, std::size_t position) {
        if (!node) return {nullptr, nullptr};

        if (!node->left && !node->right) {
            if (position == 0) return {nullptr, std::move(node)};
            if (position >= node->chunk.size()) return {std::move(node), nullptr};

            std::string leftChunk = node->chunk.substr(0, position);
            std::string rightChunk = node->chunk.substr(position);
            return {std::make_unique<Node>(std::move(leftChunk)),
                    std::make_unique<Node>(std::move(rightChunk))};
        }

        std::size_t leftLength = node->left ? node->left->length : 0;

        if (position < leftLength) {
            auto [leftPart, rightPart] = split(std::move(node->left), position);
            return {std::move(leftPart),
                    merge(std::move(rightPart), std::move(node->right))};
        }

        auto [leftPart, rightPart] =
            split(std::move(node->right), position - leftLength);
        return {merge(std::move(node->left), std::move(leftPart)),
                std::move(rightPart)};
    }

    static char charAt(const Node* node, std::size_t index) {
        while (node->left && node->right) {
            std::size_t leftLength = node->left->length;
            if (index < leftLength) {
                node = node->left.get();
            } else {
                index -= leftLength;
                node = node->right.get();
            }
        }
        return node->chunk[index];
    }

    static void collect(const Node* node, std::string& result) {
        if (!node) return;
        if (!node->left && !node->right) {
            result += node->chunk;
            return;
        }
        collect(node->left.get(), result);
        collect(node->right.get(), result);
    }

    static void collectRange(const Node* node, std::size_t begin,
                             std::size_t end, std::size_t offset,
                             std::string& result) {
        if (!node || end <= offset || begin >= offset + node->length) return;

        if (!node->left && !node->right) {
            std::size_t localBegin = begin > offset ? begin - offset : 0;
            std::size_t localEnd = std::min(end - offset, node->chunk.size());
            result.append(node->chunk, localBegin, localEnd - localBegin);
            return;
        }

        std::size_t leftLength = node->left ? node->left->length : 0;
        collectRange(node->left.get(), begin, end, offset, result);
        collectRange(node->right.get(), begin, end, offset + leftLength, result);
    }
};

#endif
