#ifndef SKIP_LIST_H
#define SKIP_LIST_H

#include <iostream>
#include <stdexcept>
#include <memory>
#include <functional>
#include <vector>
#include <random>
#include <limits>

template <typename T, typename Compare = std::less<T>>
class SkipList {
public:
    explicit SkipList(size_t maxLevel = 16, double p = 0.5, Compare cmp = Compare())
        : MAX_LEVEL(maxLevel), P(p), comparator(cmp),
          head(new Node(T(), MAX_LEVEL - 1)), level(0), listSize(0),
          rng(std::random_device{}()), coin(0.0, 1.0)
    {
        // head->value is default-constructed and unused as a real key
    }

    ~SkipList() { clear(); delete head; }

    // No copy semantics for simplicity (could be added)
    SkipList(const SkipList&) = delete;
    SkipList& operator=(const SkipList&) = delete;

    // Insert unique value. Returns true if inserted, false if value already exists.
    bool insert(const T& value) {
        std::vector<Node*> update(MAX_LEVEL, nullptr);
        Node* x = head;

        // find path to insert
        for (int i = static_cast<int>(level); i >= 0; --i) {
            while (x->forward[i] && comparator(x->forward[i]->value, value)) {
                x = x->forward[i];
            }
            update[i] = x;
        }
        x = x->forward[0];

        // if already present, do nothing
        if (x && !comparator(value, x->value) && !comparator(x->value, value))
            return false;

        int rndLevel = randomLevel();
        if (rndLevel > static_cast<int>(level)) {
            for (size_t i = level + 1; i <= static_cast<size_t>(rndLevel); ++i)
                update[i] = head;
            level = rndLevel;
        }

        Node* newNode = new Node(value, rndLevel);
        for (int i = 0; i <= rndLevel; ++i) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
        ++listSize;
        return true;
    }

    // Erase value; returns true if erased, false if not found.
    bool erase(const T& value) {
        std::vector<Node*> update(MAX_LEVEL, nullptr);
        Node* x = head;
        for (int i = static_cast<int>(level); i >= 0; --i) {
            while (x->forward[i] && comparator(x->forward[i]->value, value)) {
                x = x->forward[i];
            }
            update[i] = x;
        }
        x = x->forward[0];

        if (!x || comparator(value, x->value) || comparator(x->value, value)) {
            return false; // not found
        }

        for (size_t i = 0; i <= static_cast<size_t>(level); ++i) {
            if (update[i]->forward[i] != x) break;
            update[i]->forward[i] = x->forward[i];
        }
        delete x;
        --listSize;

        // reduce level if necessary
        while (level > 0 && head->forward[level] == nullptr) {
            --level;
        }
        return true;
    }

    // Returns true if value exists.
    bool contains(const T& value) const {
        return findNode(value) != nullptr;
    }

    // Returns pointer to the value if found, nullptr otherwise.
    // Caller must not delete the returned pointer.
    const T* find(const T& value) const {
        Node* n = findNode(value);
        return n ? &n->value : nullptr;
    }

    // Remove all elements
    void clear() {
        Node* cur = head->forward[0];
        while (cur) {
            Node* next = cur->forward[0];
            delete cur;
            cur = next;
        }
        for (size_t i = 0; i < MAX_LEVEL; ++i) head->forward[i] = nullptr;
        level = 0;
        listSize = 0;
    }

    size_t size() const noexcept { return listSize; }
    bool empty() const noexcept { return listSize == 0; }

    // Debug: prints list levels
    void printList(std::ostream& os = std::cout) const {
        os << "SkipList (size=" << listSize << ", maxLevel=" << MAX_LEVEL << ", curLevel=" << level << ")\n";
        for (int i = static_cast<int>(level); i >= 0; --i) {
            os << "Level " << i << ": ";
            Node* x = head->forward[i];
            while (x) {
                os << x->value << " ";
                x = x->forward[i];
            }
            os << '\n';
        }
    }

private:
    struct Node {
        T value;
        std::vector<Node*> forward;
        Node(const T& val, int lvl) : value(val), forward(lvl + 1, nullptr) {}
    };

    Node* head;
    const size_t MAX_LEVEL;
    const double P;
    Compare comparator;

    int level;       // current highest level (0-based)
    size_t listSize;

    // random
    std::mt19937 rng;
    std::uniform_real_distribution<double> coin;

    int randomLevel() {
        int lvl = 0;
        while (coin(rng) < P && lvl + 1 < static_cast<int>(MAX_LEVEL)) {
            ++lvl;
        }
        return lvl;
    }

    Node* findNode(const T& value) const {
        Node* x = head;
        for (int i = static_cast<int>(level); i >= 0; --i) {
            while (x->forward[i] && comparator(x->forward[i]->value, value)) {
                x = x->forward[i];
            }
        }
        x = x->forward[0];
        if (x && !comparator(value, x->value) && !comparator(x->value, value)) return x;
        return nullptr;
    }
};

#endif // SKIP_LIST_H
