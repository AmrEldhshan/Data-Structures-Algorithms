#ifndef DSA_BIG_INTEGER_H
#define DSA_BIG_INTEGER_H

#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

// ---------------------------------------------------------------------------
// BigInteger
//
// Arbitrary-precision signed integer stored as base-10^9 limbs, least
// significant limb first. Implements comparison, addition, subtraction, and
// schoolbook multiplication.
//
// Addition/subtraction: O(n)
// Multiplication:       O(n * m)
// ---------------------------------------------------------------------------
class BigInteger {
public:
    BigInteger() : negative_(false), digits_{0} {}

    explicit BigInteger(long long value) : negative_(value < 0) {
        unsigned long long magnitude =
            value < 0 ? static_cast<unsigned long long>(-(value + 1)) + 1
                      : static_cast<unsigned long long>(value);

        do {
            digits_.push_back(static_cast<int>(magnitude % BASE));
            magnitude /= BASE;
        } while (magnitude != 0);

        normalize();
    }

    explicit BigInteger(const std::string& text) {
        *this = fromString(text);
    }

    bool isNegative() const { return negative_; }
    bool isZero() const { return digits_.size() == 1 && digits_[0] == 0; }

    std::string toString() const {
        if (isZero()) return "0";

        std::string result = negative_ ? "-" : "";
        result += std::to_string(digits_.back());

        for (std::size_t i = digits_.size() - 1; i-- > 0;) {
            std::string limb = std::to_string(digits_[i]);
            result.append(WIDTH - limb.size(), '0');
            result += limb;
        }

        return result;
    }

    BigInteger operator-() const {
        BigInteger result = *this;
        if (!result.isZero()) result.negative_ = !result.negative_;
        return result;
    }

    BigInteger operator+(const BigInteger& other) const {
        if (negative_ == other.negative_) {
            BigInteger result;
            result.digits_ = addMagnitudes(digits_, other.digits_);
            result.negative_ = negative_;
            result.normalize();
            return result;
        }

        int comparison = compareMagnitudes(digits_, other.digits_);
        if (comparison == 0) return BigInteger(0);

        BigInteger result;
        if (comparison > 0) {
            result.digits_ = subtractMagnitudes(digits_, other.digits_);
            result.negative_ = negative_;
        } else {
            result.digits_ = subtractMagnitudes(other.digits_, digits_);
            result.negative_ = other.negative_;
        }
        result.normalize();
        return result;
    }

    BigInteger operator-(const BigInteger& other) const {
        return *this + (-other);
    }

    BigInteger operator*(const BigInteger& other) const {
        BigInteger result;
        result.digits_.assign(digits_.size() + other.digits_.size(), 0);
        result.negative_ = negative_ != other.negative_;

        for (std::size_t i = 0; i < digits_.size(); ++i) {
            long long carry = 0;

            for (std::size_t j = 0; j < other.digits_.size() || carry != 0; ++j) {
                long long current = result.digits_[i + j] + carry;

                if (j < other.digits_.size()) {
                    current += static_cast<long long>(digits_[i]) * other.digits_[j];
                }

                result.digits_[i + j] = static_cast<int>(current % BASE);
                carry = current / BASE;
            }
        }

        result.normalize();

        bool isZeroResult = result.isZero();
        result.negative_ = isZeroResult ? false : result.negative_;
        return result;
    }

    bool operator==(const BigInteger& other) const {
        return negative_ == other.negative_ && digits_ == other.digits_;
    }

    bool operator!=(const BigInteger& other) const { return !(*this == other); }

    bool operator<(const BigInteger& other) const {
        if (negative_ != other.negative_) return negative_;
        int comparison = compareMagnitudes(digits_, other.digits_);
        return negative_ ? comparison > 0 : comparison < 0;
    }

    bool operator>(const BigInteger& other) const { return other < *this; }
    bool operator<=(const BigInteger& other) const { return !(other < *this); }
    bool operator>=(const BigInteger& other) const { return !(*this < other); }

private:
    static constexpr int BASE = 1'000'000'000;
    static constexpr std::size_t WIDTH = 9;

    bool negative_;
    std::vector<int> digits_;

    static BigInteger fromString(const std::string& text) {
        BigInteger result;
        result.digits_.clear();

        std::size_t start = 0;
        if (!text.empty() && (text[0] == '+' || text[0] == '-')) {
            result.negative_ = text[0] == '-';
            start = 1;
        }

        if (start == text.size()) {
            throw std::invalid_argument("BigInteger: empty digit string");
        }

        for (std::size_t end = text.size(); end > start;) {
            std::size_t begin = end >= start + WIDTH ? end - WIDTH : start;
            int limb = 0;

            for (std::size_t i = begin; i < end; ++i) {
                if (text[i] < '0' || text[i] > '9') {
                    throw std::invalid_argument("BigInteger: invalid digit");
                }
                limb = limb * 10 + (text[i] - '0');
            }

            result.digits_.push_back(limb);
            end = begin;
        }

        result.normalize();
        return result;
    }

    void normalize() {
        while (digits_.size() > 1 && digits_.back() == 0) digits_.pop_back();
        if (isZero()) negative_ = false;
    }

    static int compareMagnitudes(const std::vector<int>& a,
                                 const std::vector<int>& b) {
        if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;

        for (std::size_t i = a.size(); i-- > 0;) {
            if (a[i] != b[i]) return a[i] < b[i] ? -1 : 1;
        }

        return 0;
    }

    static std::vector<int> addMagnitudes(const std::vector<int>& a,
                                          const std::vector<int>& b) {
        std::vector<int> result;
        int carry = 0;

        for (std::size_t i = 0; i < std::max(a.size(), b.size()) || carry != 0; ++i) {
            long long sum = carry;
            if (i < a.size()) sum += a[i];
            if (i < b.size()) sum += b[i];

            result.push_back(static_cast<int>(sum % BASE));
            carry = static_cast<int>(sum / BASE);
        }

        return result;
    }

    static std::vector<int> subtractMagnitudes(const std::vector<int>& a,
                                               const std::vector<int>& b) {
        std::vector<int> result;
        int borrow = 0;

        for (std::size_t i = 0; i < a.size(); ++i) {
            long long difference = a[i] - borrow - (i < b.size() ? b[i] : 0);

            if (difference < 0) {
                difference += BASE;
                borrow = 1;
            } else {
                borrow = 0;
            }

            result.push_back(static_cast<int>(difference));
        }

        while (result.size() > 1 && result.back() == 0) result.pop_back();
        return result;
    }
};

#endif
