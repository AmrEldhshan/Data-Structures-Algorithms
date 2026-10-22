/*
============================================================
 Tests for the header-only data structures
============================================================

Each block builds a tiny structure, performs one or two
operations, and checks the result. The checks use `require`
instead of `assert` so they also run in Release builds.
*/

#include "data_structures/big_integer/big_integer.h"
#include "data_structures/bitset/bitset.h"
#include "data_structures/dynamic_array/dynamic_array.h"
#include "data_structures/cache/lru_cache.h"
#include "data_structures/disjoint_set/union_find.h"
#include "data_structures/heaps/binomial_heap.h"
#include "data_structures/heaps/min_heap.h"
#include "data_structures/heaps/min_max_heap.h"
#include "data_structures/heaps/pairing_heap.h"
#include "data_structures/heaps/fibonacci_heap.h"
#include "data_structures/matrix/matrix.h"
#include "data_structures/ordered/ordered_map.h"
#include "data_structures/ordered/ordered_set.h"
#include "data_structures/hashing/hash_map.h"
#include "data_structures/hashing/separate_chaining.h"
#include "data_structures/heaps/heap.h"
#include "data_structures/heaps/max_heap.h"
#include "data_structures/linked_lists/single_linked_list.h"
#include "data_structures/linked_lists/skip_list.h"
#include "data_structures/probabilistic/count_min_sketch.h"
#include "data_structures/probabilistic/cuckoo_filter.h"
#include "data_structures/probabilistic/hyperloglog.h"
#include "data_structures/queues/deque.h"
#include "data_structures/queues/priority_queue.h"
#include "data_structures/queues/queue.h"
#include "data_structures/stacks/stack.h"
#include "data_structures/trees/avl.h"
#include "data_structures/trees/bst.h"
#include "data_structures/trees/fenwick_tree.h"
#include "data_structures/trees/sparse_table.h"
#include "data_structures/trees/splay_tree.h"
#include "data_structures/trees/lazy_segment_tree.h"
#include "data_structures/trees/merge_sort_tree.h"
#include "data_structures/trees/persistent_segment_tree.h"
#include "data_structures/trees/wavelet_tree.h"
#include "data_structures/trees/disjoint_sparse_table.h"
#include "data_structures/trees/radix_tree.h"
#include "data_structures/trees/suffix_tree.h"
#include "data_structures/trees/b_tree.h"
#include "data_structures/trees/b_plus_tree.h"
#include "data_structures/strings/rope.h"
#include "data_structures/sets/van_emde_boas.h"
#include "data_structures/sqrt_decomposition/sqrt_decomposition.h"
#include "data_structures/strings/suffix_automaton.h"
#include "data_structures/trees/trie.h"

#include <iostream>
#include <string>

using namespace std;

namespace {

int failures = 0;

void require(bool condition, const string& message) {
    if (!condition) {
        cerr << "FAILED: " << message << '\n';
        ++failures;
    }
}

void testSingleLinkedList() {
    SingleLinkedList<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    require(list.size() == 3, "linked list size should be 3");
    require(list.contains(2), "linked list should contain 2");

    list.pop_front();
    require(list.size() == 2, "linked list size should be 2 after pop_front");
    require(!list.contains(1), "linked list should not contain 1 after pop_front");
}

void testStack() {
    Stack<int> stack;
    stack.push(10);
    stack.push(20);

    require(stack.top() == 20, "stack top should be 20");
    require(stack.pop() == 20, "stack pop should return 20");
    require(stack.pop() == 10, "stack pop should return 10");
    require(stack.isEmpty(), "stack should be empty");
}

void testQueue() {
    Queue<int> queue;
    queue.enqueue(10);
    queue.enqueue(20);

    require(queue.getSize() == 2, "queue size should be 2");
    require(queue.first() == 10, "queue front should be 10");
    require(queue.back() == 20, "queue back should be 20");
    require(queue.dequeue() == 10, "queue dequeue should return 10");
}

void testPriorityQueue() {
    // In this implementation a smaller priority number means higher priority.
    PriorityQueue<string> queue;
    queue.enqueue("high", 1);
    queue.enqueue("medium", 5);
    queue.enqueue("low", 10);

    require(queue.front() == "high", "highest priority should be first");
    require(queue.dequeue() == "high", "dequeue should return highest priority");
}

void testBST() {
    BST<int> tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);

    require(tree.search(30) != nullptr, "BST should contain 30");
    require(tree.search(100) == nullptr, "BST should not contain 100");
}

void testAVL() {
    AVL<int> tree;
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);

    require(tree.search(20), "AVL should contain 20");
    tree.deleteNode(20);
    require(!tree.search(20), "AVL should not contain 20 after deletion");
}

void testMaxHeap() {
    MaxHeap<int> heap;
    heap.insert(3);
    heap.insert(1);
    heap.insert(2);

    require(heap.extractMax() == 3, "max-heap should extract 3 first");
}

void testHeap() {
    Heap heap;
    heap.insert(10);
    heap.insert(30);
    heap.insert(20);

    require(heap.extractMax() == 30, "heap should extract 30 first");
    require(heap.extractMin() == 10, "heap should extract 10 as the minimum");
}

void testSkipList() {
    SkipList<int> list;
    list.insert(5);
    list.insert(3);

    require(list.contains(5), "skip list should contain 5");
    require(list.size() == 2, "skip list size should be 2");
    require(list.erase(5), "skip list erase should succeed");
    require(!list.contains(5), "skip list should not contain 5 after erase");
}

void testSeparateChaining() {
    SeparateChaining table(7);
    table.insert(10);
    table.insert(17); // same bucket as 10 (10 % 7 == 17 % 7 == 3)

    require(table.search(10), "hash table should contain 10");
    require(table.search(17), "hash table should contain 17");
    require(!table.search(5), "hash table should not contain 5");
}

void testTrie() {
    Trie trie;
    trie.insert("cat");
    trie.insert("car");

    require(trie.countWords() == 2, "trie should contain two words");
    require(trie.contains("cat"), "trie should contain cat");
    require(!trie.contains("ca"), "trie should not treat a prefix as a word");
    require(trie.startsWith("ca"), "trie should have prefix ca");
    require(trie.wordsWithPrefix("ca").size() == 2,
            "trie should return two words for prefix ca");
}

void testFenwickTree() {
    FenwickTree tree(vector<long long>{1, 3, 5});

    require(tree.prefixSum(2) == 9, "Fenwick prefix sum should be 9");
    require(tree.rangeSum(1, 2) == 8, "Fenwick range sum should be 8");

    tree.add(1, 2);
    require(tree.rangeSum(0, 1) == 6, "Fenwick sum after update should be 6");
}

void testSparseTable() {
    SparseTable table(vector<int>{4, 1, 7, 2, 9});

    require(table.rangeMin(0, 4) == 1, "sparse table min over all should be 1");
    require(table.rangeMin(2, 4) == 2, "sparse table min[2..4] should be 2");
    require(table.rangeMin(1, 3) == 1, "sparse table min[1..3] should be 1");
}

void testDeque() {
    Deque<int> deque;
    deque.pushBack(2);
    deque.pushBack(3);
    deque.pushFront(1);

    require(deque.size() == 3, "deque size should be 3");
    require(deque.front() == 1, "deque front should be 1");
    require(deque.back() == 3, "deque back should be 3");

    deque.popFront();
    require(deque.front() == 2, "deque front after popFront should be 2");

    deque.popBack();
    require(deque.back() == 2, "deque back after popBack should be 2");
    require(deque.size() == 1, "deque size after pops should be 1");
}

void testLruCache() {
    LruCache<string, int> cache(2);
    cache.put("a", 1);
    cache.put("b", 2);

    require(cache.get("a").value_or(-1) == 1, "LRU should return a");
    cache.put("c", 3);

    require(!cache.contains("b"), "LRU should evict the least recent key");
    require(cache.contains("a"), "LRU should keep the recently used key");
    require(cache.contains("c"), "LRU should keep the newest key");
}

void testHashMap() {
    HashMap<string, int> map;
    require(map.insert("apple", 2), "hash map should insert a new key");
    map.insert("banana", 3);
    require(!map.insert("apple", 5), "hash map should update an existing key");

    require(map.size() == 2, "hash map size should be 2");
    require(map.contains("apple"), "hash map should contain apple");
    require(*map.find("apple") == 5, "hash map should store the updated value");

    map["cherry"] += 1;
    require(*map.find("cherry") == 1, "hash map operator[] should insert zero then increment");
    require(map.erase("banana"), "hash map erase should succeed");
    require(!map.contains("banana"), "hash map should not contain erased key");
}

void testMatrix() {
    Matrix<int> a(2, 2, 0);
    a(0, 0) = 1; a(0, 1) = 2;
    a(1, 0) = 3; a(1, 1) = 4;

    Matrix<int> product = a * Matrix<int>::identity(2);
    require(product == a, "multiplying by the identity should not change a matrix");

    Matrix<int> b(2, 1, 0);
    b(0, 0) = 5; b(1, 0) = 6;
    Matrix<int> result = a * b;
    require(result(0, 0) == 17 && result(1, 0) == 39,
            "matrix multiplication result is wrong");
    require(a.transpose()(0, 1) == 3, "matrix transpose is wrong");
}

void testBitset() {
    Bitset<10> bits;
    bits.set(0);
    bits.set(3);
    bits.set(9);

    require(bits.count() == 3, "bitset count should be 3");
    require(bits.test(3), "bitset bit 3 should be set");
    require(!bits.test(2), "bitset bit 2 should be clear");
    require(bits.to_string() == "1000001001", "bitset string is wrong");

    Bitset<10> other;
    other.set(0);
    require((bits & other).count() == 1, "bitset AND is wrong");
    require((bits | other).count() == 3, "bitset OR is wrong");
    require((bits ^ other).count() == 2, "bitset XOR is wrong");
}

void testMinHeap() {
    MinHeap<int> heap;
    heap.push(3);
    heap.push(1);
    heap.push(2);

    require(heap.top() == 1, "min-heap top should be 1");
    heap.pop();
    require(heap.top() == 2, "min-heap top after pop should be 2");
    require(heap.size() == 2, "min-heap size should be 2");
}

void testUnionFind() {
    UnionFind sets(5);
    require(sets.components() == 5, "union-find should start with 5 components");

    require(sets.unite(0, 1), "union-find should merge 0 and 1");
    require(sets.unite(1, 2), "union-find should merge 1 and 2");
    require(!sets.unite(0, 2), "union-find should detect an existing component");
    require(sets.connected(0, 2), "0 and 2 should be connected");
    require(sets.componentSize(0) == 3, "component size should be 3");
    require(sets.components() == 3, "union-find should have 3 components");
}

void testDynamicArray() {
    DynamicArray<int> values;
    values.push_back(10);
    values.push_back(20);
    values.push_back(30);

    require(values.size() == 3, "dynamic array size should be 3");
    values.insert(1, 15);
    require(values[1] == 15 && values[3] == 30,
            "dynamic array insert is wrong");
    values.erase(2);
    require(values[2] == 30, "dynamic array erase is wrong");

    DynamicArray<int> copy = values;
    copy.pop_back();
    require(copy.size() == 2 && values.size() == 3,
            "dynamic array copy should be independent");
}

void testBigInteger() {
    BigInteger a("123456789012345678901234567890");
    BigInteger b("987654321098765432109876543210");

    require(a + b == BigInteger("1111111110111111111011111111100"),
            "big integer addition is wrong");
    require(b - a == BigInteger("864197532086419753208641975320"),
            "big integer subtraction is wrong");
    require(a * b ==
                BigInteger("121932631137021795226185032733622923332237463801111263526900"),
            "big integer multiplication is wrong");
    require(BigInteger(-5) * BigInteger(3) == BigInteger(-15),
            "big integer negative multiplication is wrong");
    require(BigInteger("000123") == BigInteger(123),
            "big integer parsing should ignore leading zeros");
}

void testOrderedSet() {
    OrderedSet<int> set;
    for (int value : {5, 1, 9, 3, 7, 3}) set.insert(value);

    require(set.size() == 5, "ordered set should contain 5 unique values");
    require(set.contains(7), "ordered set should contain 7");
    require(set.minimum() == 1 && set.maximum() == 9,
            "ordered set min/max are wrong");
    require(set.kth(2) == 5, "ordered set kth(2) should be 5");
    require(set.rank(7) == 3, "ordered set rank(7) should be 3");
    require(set.lowerBound(6) == 7, "ordered set lowerBound is wrong");
    require(set.upperBound(7) == 9, "ordered set upperBound is wrong");
    require(set.erase(7) && !set.contains(7), "ordered set erase failed");
}

void testOrderedMap() {
    OrderedMap<std::string, int> ages;
    ages["alice"] = 30;
    ages["bob"] = 25;
    ages["carol"] = 35;

    require(ages.size() == 3, "ordered map size should be 3");
    require(ages.at("bob") == 25, "ordered map at(bob) is wrong");
    require(ages.kthKey(0) == "alice", "ordered map kthKey(0) is wrong");
    require(ages.rank("carol") == 2, "ordered map rank(carol) should be 2");
    require(ages.erase("bob") && !ages.contains("bob"),
            "ordered map erase failed");
}

void testSplayTree() {
    SplayTree<int> tree;
    for (int value : {50, 30, 70, 20, 40, 60, 80}) tree.insert(value);

    require(tree.size() == 7, "splay tree size should be 7");
    require(tree.contains(40), "splay tree should contain 40");
    require(tree.kth(3) == 50, "splay tree kth(3) should be 50");
    require(tree.rank(50) == 3, "splay tree rank(50) should be 3");
    require(tree.minimum() == 20 && tree.maximum() == 80,
            "splay tree min/max are wrong");
    require(tree.erase(70) && !tree.contains(70), "splay tree erase failed");
    require(tree.size() == 6, "splay tree size should be 6 after erase");
}

void testMinMaxHeap() {
    MinMaxHeap<int> heap;
    for (int value : {5, 1, 9, 3, 7, 2, 8, 4, 6}) heap.insert(value);

    require(heap.minimum() == 1, "min-max heap minimum should be 1");
    require(heap.maximum() == 9, "min-max heap maximum should be 9");

    for (int expected = 1; expected <= 9; ++expected) {
        require(heap.extractMin() == expected,
                "min-max heap extractMin order is wrong");
    }
    require(heap.empty(), "min-max heap should be empty");
}

void testBinomialHeap() {
    BinomialHeap<int> heap;
    for (int value : {7, 2, 9, 1, 5, 3, 8, 4, 6}) heap.insert(value);

    require(heap.size() == 9, "binomial heap size should be 9");
    require(heap.minimum() == 1, "binomial heap minimum should be 1");
    require(heap.values() == std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9}),
            "binomial heap values should be sorted");

    for (int expected = 1; expected <= 9; ++expected) {
        require(heap.extractMin() == expected,
                "binomial heap extractMin order is wrong");
    }
}

void testLazySegmentTree() {
    std::vector<long long> values = {1, 2, 3, 4, 5, 6, 7, 8};
    LazySegmentTree tree(values);

    require(tree.sum(0, 8) == 36, "lazy segment tree initial sum is wrong");
    tree.add(1, 6, 10);
    require(tree.sum(0, 8) == 86, "lazy segment tree range add is wrong");
    require(tree.sum(2, 5) == 42, "lazy segment tree range sum is wrong");
    tree.add(0, 8, -1);
    require(tree.sum(0, 8) == 78, "lazy segment tree full add is wrong");
}

void testSqrtDecomposition() {
    std::vector<long long> values = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    SqrtDecomposition<long long> blocks(values);

    require(blocks.sum(0, 10) == 55, "sqrt decomposition initial sum is wrong");
    blocks.add(2, 8, 5);
    require(blocks.sum(0, 10) == 85, "sqrt decomposition range add is wrong");
    require(blocks.sum(3, 7) == 42, "sqrt decomposition range sum is wrong");
}

void testCountMinSketch() {
    CountMinSketch<std::string> sketch(64, 4);
    for (int i = 0; i < 5; ++i) sketch.add("apple");
    sketch.add("banana");
    sketch.add("banana");

    require(sketch.estimate("apple") >= 5,
            "count-min sketch should not underestimate apple");
    require(sketch.estimate("banana") >= 2,
            "count-min sketch should not underestimate banana");
    require(sketch.estimate("missing") == 0,
            "count-min sketch should report zero for unseen values");
}

void testHyperLogLog() {
    HyperLogLog<int> sketch(12);
    for (int i = 0; i < 5000; ++i) sketch.add(i);

    double estimate = sketch.estimate();
    require(estimate > 4000 && estimate < 6000,
            "HyperLogLog estimate should be within 20%");
}

void testCuckooFilter() {
    CuckooFilter<std::string> filter(64, 4);
    require(filter.insert("apple"), "cuckoo filter insert should succeed");
    require(filter.insert("banana"), "cuckoo filter insert should succeed");
    require(filter.contains("apple"), "cuckoo filter should contain apple");
    require(filter.erase("apple"), "cuckoo filter erase should succeed");
    require(!filter.contains("apple"), "cuckoo filter should forget apple");
}

void testSuffixAutomaton() {
    SuffixAutomaton automaton("banana");
    require(automaton.contains("ana"), "suffix automaton should contain ana");
    require(!automaton.contains("bananana"),
            "suffix automaton should reject a missing pattern");
    require(automaton.distinctSubstrings() == 15,
            "banana should have 15 distinct substrings");
    require(automaton.occurrences("ana") == 2,
            "ana should occur twice in banana");
}

void testMergeSortTree() {
    std::vector<int> values = {5, 2, 8, 1, 9, 3};
    MergeSortTree<int> tree(values);

    require(tree.countLessOrEqual(0, 6, 5) == 4,
            "merge-sort tree count should be 4");
    require(tree.countLessOrEqual(1, 4, 4) == 2,
            "merge-sort tree partial count is wrong");
    require(tree.kthSmallest(0, 6, 1) == 1,
            "merge-sort tree kth(1) should be 1");
    require(tree.kthSmallest(0, 6, 6) == 9,
            "merge-sort tree kth(6) should be 9");
}

void testPersistentSegmentTree() {
    std::vector<long long> values = {1, 2, 3, 4};
    PersistentSegmentTree tree(values);

    int version1 = tree.update(0, 1, 10);
    int version2 = tree.update(version1, 3, 40);

    require(tree.sum(0, 0, 4) == 10, "persistent tree version 0 is wrong");
    require(tree.sum(version1, 0, 4) == 18, "persistent tree version 1 is wrong");
    require(tree.sum(version2, 0, 4) == 54, "persistent tree version 2 is wrong");
    require(tree.sum(0, 1, 2) == 2,
            "persistent tree old version should be unchanged");
}

void testWaveletTree() {
    std::vector<int> values = {5, 2, 8, 1, 9, 3};
    WaveletTree tree(values);

    require(tree.countLess(0, 6, 5) == 3, "wavelet tree countLess is wrong");
    require(tree.countLessOrEqual(1, 4, 8) == 3,
            "wavelet tree partial count is wrong");
    require(tree.kthSmallest(0, 6, 1) == 1, "wavelet tree kth(1) is wrong");
    require(tree.kthSmallest(0, 6, 6) == 9, "wavelet tree kth(6) is wrong");
}

void testDisjointSparseTable() {
    std::vector<int> values = {4, 1, 7, 2, 9, 3, 8, 5};
    DisjointSparseTable<int> table(values);

    require(table.query(0, 7) == 1, "disjoint sparse table full min is wrong");
    require(table.query(2, 5) == 2, "disjoint sparse table partial min is wrong");
    require(table.query(3, 3) == 2, "disjoint sparse table point min is wrong");
}

void testPairingHeap() {
    PairingHeap<int> heap;
    for (int value : {7, 2, 9, 1, 5, 3}) heap.insert(value);

    require(heap.size() == 6, "pairing heap size should be 6");
    require(heap.minimum() == 1, "pairing heap minimum should be 1");
    for (int expected = 1; expected <= 9; ++expected) {
        if (expected == 4 || expected == 6 || expected == 8) continue;
        require(heap.extractMin() == expected,
                "pairing heap extractMin order is wrong");
    }
    require(heap.empty(), "pairing heap should be empty");
}

void testRadixTree() {
    RadixTree tree;
    for (const char* word : {"car", "cart", "carbon", "dog", "do", "dot"}) {
        tree.insert(word);
    }

    require(tree.size() == 6, "radix tree size should be 6");
    require(tree.contains("car"), "radix tree should contain car");
    require(tree.contains("carbon"), "radix tree should contain carbon");
    require(!tree.contains("ca"), "radix tree should reject ca");
    require(tree.containsPrefix("car"), "radix tree prefix car should exist");
    require(tree.countPrefix("car") == 3, "car prefix count should be 3");
    require(tree.countPrefix("do") == 3, "do prefix count should be 3");
}

void testSuffixTree() {
    SuffixTree tree("banana");
    require(tree.contains("ana"), "suffix tree should contain ana");
    require(!tree.contains("bananana"), "suffix tree should reject missing pattern");
    require(tree.occurrences("ana") == 2, "ana should occur twice");
    require(tree.occurrences("ban") == 1, "ban should occur once");
}

void testVanEmdeBoas() {
    VanEmdeBoas set;
    for (int value : {3, 5, 8, 13, 21, 34}) set.insert(value);

    require(set.size() == 6, "vEB size should be 6");
    require(set.minimum() == 3 && set.maximum() == 34,
            "vEB min/max are wrong");
    require(set.contains(13), "vEB should contain 13");
    require(set.successor(4) == 5, "vEB successor(4) should be 5");
    require(set.successor(8) == 13, "vEB successor(8) should be 13");
    require(set.predecessor(13) == 8, "vEB predecessor(13) should be 8");
    require(set.predecessor(3) == -1, "vEB predecessor(min) should be -1");

    set.remove(13);
    require(!set.contains(13), "vEB should forget 13");
    require(set.successor(8) == 21, "vEB successor after remove is wrong");
}

void testBTree() {
    BTree<int> tree(2);
    for (int value : {10, 20, 5, 6, 12, 30, 7, 17, 3, 25, 18, 40, 1}) {
        tree.insert(value);
    }

    std::vector<int> expected = {1, 3, 5, 6, 7, 10, 12, 17, 18, 20, 25, 30, 40};
    require(tree.size() == expected.size(), "B-tree size should match");
    require(tree.inOrder() == expected, "B-tree in-order should be sorted");
    require(tree.contains(17), "B-tree should contain 17");
    require(!tree.contains(41), "B-tree should reject 41");
}

void testBPlusTree() {
    BPlusTree<int> tree(4);
    for (int value : {10, 20, 5, 6, 12, 30, 7, 17, 3, 25}) tree.insert(value);

    std::vector<int> expected = {3, 5, 6, 7, 10, 12, 17, 20, 25, 30};
    require(tree.size() == expected.size(), "B+ tree size should match");
    require(tree.values() == expected, "B+ tree leaves should be sorted");
    require(tree.contains(17), "B+ tree should contain 17");
    require(!tree.contains(99), "B+ tree should reject 99");
}

void testFibonacciHeap() {
    FibonacciHeap<int> heap;
    for (int value : {7, 2, 9, 1, 5, 3, 8, 4, 6}) heap.insert(value);

    require(heap.size() == 9, "Fibonacci heap size should be 9");
    require(heap.minimum() == 1, "Fibonacci heap minimum should be 1");
    for (int expected = 1; expected <= 9; ++expected) {
        require(heap.extractMin() == expected,
                "Fibonacci heap extractMin order is wrong");
    }
    require(heap.empty(), "Fibonacci heap should be empty");
}

void testRope() {
    Rope rope("Hello world");
    require(rope.size() == 11, "rope size should be 11");
    require(rope.at(6) == 'w', "rope random access is wrong");

    rope.insert(5, ",");
    rope.append("!");
    require(rope.toString() == "Hello, world!", "rope insert/append failed");
    require(rope.substring(7, 5) == "world", "rope substring failed");

    rope.erase(0, 7);
    require(rope.toString() == "world!", "rope erase failed");
}

} // namespace

int main() {
    testSingleLinkedList();
    testStack();
    testQueue();
    testPriorityQueue();
    testBST();
    testAVL();
    testMaxHeap();
    testHeap();
    testSkipList();
    testSeparateChaining();
    testTrie();
    testFenwickTree();
    testSparseTable();
    testDeque();
    testLruCache();
    testHashMap();
    testMatrix();
    testBitset();
    testMinHeap();
    testUnionFind();
    testDynamicArray();
    testBigInteger();
    testOrderedSet();
    testOrderedMap();
    testSplayTree();
    testMinMaxHeap();
    testBinomialHeap();
    testLazySegmentTree();
    testSqrtDecomposition();
    testCountMinSketch();
    testHyperLogLog();
    testCuckooFilter();
    testSuffixAutomaton();
    testMergeSortTree();
    testPersistentSegmentTree();
    testWaveletTree();
    testDisjointSparseTable();
    testPairingHeap();
    testRadixTree();
    testSuffixTree();
    testVanEmdeBoas();
    testBTree();
    testBPlusTree();
    testFibonacciHeap();
    testRope();

    if (failures == 0) {
        cout << "All data structure tests passed.\n";
        return 0;
    }

    cerr << failures << " test(s) failed.\n";
    return 1;
}
