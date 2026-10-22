#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Digit DP: count numbers in [0, N] whose digits sum to a target
//
// The state is (position, current digit sum, tight). `tight` means the prefix
// chosen so far equals N's prefix, so the next digit may not exceed N's digit.
// Once tight is false, the remaining suffix can be memoised.
//
// Time:  O(digits * target * 10)
// Space: O(digits * target)
// ---------------------------------------------------------------------------
class DigitCounter {
public:
    DigitCounter(const string& limit, int target)
        : digits_(limit), target_(target),
          memo_(limit.size(), vector<vector<long long>>(
                                   target + 1, vector<long long>(2, -1))) {}

    long long count() { return countFrom(0, 0, true); }

private:
    long long countFrom(int position, int sum, bool tight) {
        if (sum > target_) return 0;
        if (position == static_cast<int>(digits_.size())) {
            return sum == target_ ? 1 : 0;
        }

        long long& cached = memo_[position][sum][tight ? 1 : 0];
        if (cached != -1 && !tight) return cached;

        int limit = tight ? digits_[position] - '0' : 9;
        long long total = 0;

        for (int digit = 0; digit <= limit; ++digit) {
            total += countFrom(position + 1, sum + digit,
                               tight && digit == limit);
        }

        if (!tight) cached = total;
        return total;
    }

    string digits_;
    int target_;
    vector<vector<vector<long long>>> memo_;
};

int main() {
    long long upper = 1000;
    int target = 9;
    string text = to_string(upper);

    DigitCounter counter(text, target);
    cout << "numbers in [0, " << upper << "] with digit sum " << target
         << ": " << counter.count() << '\n';

    // Small sanity checks.
    for (long long limit : {9LL, 99LL, 999LL}) {
        DigitCounter small(to_string(limit), target);
        cout << "  [0, " << limit << "] -> " << small.count() << '\n';
    }

    return 0;
}
