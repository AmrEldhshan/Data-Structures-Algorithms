#ifndef DSA_BITSET_H
#define DSA_BITSET_H

#include <array>
#include <bit>
#include <cstddef>
#include <stdexcept>
#include <string>

// ---------------------------------------------------------------------------
// Fixed-size bitset
//
// Stores N bits in an array of 64-bit words. Index 0 is the least significant
// bit. Operations touch only the words that are needed.
//
// Space: O(N / 64) words.
// ---------------------------------------------------------------------------
template <std::size_t N>
class Bitset {
public:
    static constexpr std::size_t wordCount = (N + 63) / 64;

    Bitset() = default;

    constexpr std::size_t size() const { return N; }

    void set(std::size_t index) {
        check(index);
        words_[index / 64] |= (1ULL << (index % 64));
    }

    void reset(std::size_t index) {
        check(index);
        words_[index / 64] &= ~(1ULL << (index % 64));
    }

    void flip(std::size_t index) {
        check(index);
        words_[index / 64] ^= (1ULL << (index % 64));
    }

    bool test(std::size_t index) const {
        check(index);
        return (words_[index / 64] >> (index % 64)) & 1ULL;
    }

    void setAll() {
        for (auto& word : words_) word = ~0ULL;
        clearUnusedBits();
    }

    void resetAll() {
        for (auto& word : words_) word = 0;
    }

    void flipAll() {
        for (auto& word : words_) word = ~word;
        clearUnusedBits();
    }

    std::size_t count() const {
        std::size_t total = 0;
        for (auto word : words_) total += std::popcount(word);
        return total;
    }

    bool any() const {
        for (auto word : words_) {
            if (word != 0) return true;
        }
        return false;
    }

    bool none() const { return !any(); }

    bool all() const { return count() == N; }

    Bitset operator&(const Bitset& other) const {
        Bitset result;
        for (std::size_t i = 0; i < wordCount; ++i) {
            result.words_[i] = words_[i] & other.words_[i];
        }
        return result;
    }

    Bitset operator|(const Bitset& other) const {
        Bitset result;
        for (std::size_t i = 0; i < wordCount; ++i) {
            result.words_[i] = words_[i] | other.words_[i];
        }
        return result;
    }

    Bitset operator^(const Bitset& other) const {
        Bitset result;
        for (std::size_t i = 0; i < wordCount; ++i) {
            result.words_[i] = words_[i] ^ other.words_[i];
        }
        return result;
    }

    Bitset operator~() const {
        Bitset result;
        for (std::size_t i = 0; i < wordCount; ++i) {
            result.words_[i] = ~words_[i];
        }
        result.clearUnusedBits();
        return result;
    }

    // Most significant bit first, so the string reads like a binary number.
    std::string to_string() const {
        std::string text;
        text.reserve(N);
        for (std::size_t i = N; i-- > 0;) {
            text.push_back(test(i) ? '1' : '0');
        }
        return text;
    }

private:
    void check(std::size_t index) const {
        if (index >= N) {
            throw std::out_of_range("Bitset: index out of range");
        }
    }

    void clearUnusedBits() {
        constexpr std::size_t used = N % 64;
        if (used != 0) {
            words_[wordCount - 1] &= (1ULL << used) - 1;
        }
    }

    std::array<unsigned long long, wordCount> words_{};
};

#endif // DSA_BITSET_H
