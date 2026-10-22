#ifndef DSA_BIT_MANIPULATION_H
#define DSA_BIT_MANIPULATION_H

#include <cstddef>

// ---------------------------------------------------------------------------
// Bit manipulation helpers
//
// Bit tricks are everywhere in competitive programming and systems code. The
// key operations below are all O(number of bits) or O(1).
// ---------------------------------------------------------------------------
namespace bits {

// Count set bits with Brian Kernighan's trick: x & (x - 1) removes the lowest
// set bit, so the loop runs once per set bit (not once per bit position).
inline int countSetBits(unsigned long long value) {
    int count = 0;
    while (value != 0) {
        value &= value - 1;
        ++count;
    }
    return count;
}

inline bool isPowerOfTwo(unsigned long long value) {
    return value != 0 && (value & (value - 1)) == 0;
}

// Index of the lowest set bit (0-based). Returns -1 for zero.
inline int lowestSetBitIndex(unsigned long long value) {
    if (value == 0) return -1;

    int index = 0;
    while ((value & 1ULL) == 0) {
        value >>= 1;
        ++index;
    }
    return index;
}

inline bool isSet(unsigned long long value, int index) {
    return (value >> index) & 1ULL;
}

inline unsigned long long setBit(unsigned long long value, int index) {
    return value | (1ULL << index);
}

inline unsigned long long clearBit(unsigned long long value, int index) {
    return value & ~(1ULL << index);
}

inline unsigned long long toggleBit(unsigned long long value, int index) {
    return value ^ (1ULL << index);
}

// Number of bits needed to represent value (0 needs 0 bits).
inline int bitLength(unsigned long long value) {
    int length = 0;
    while (value != 0) {
        value >>= 1;
        ++length;
    }
    return length;
}

} // namespace bits

#endif // DSA_BIT_MANIPULATION_H
