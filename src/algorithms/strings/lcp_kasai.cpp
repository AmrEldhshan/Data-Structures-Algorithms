#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Suffix array + Kasai's LCP algorithm
//
// A suffix array lists the starting positions of all suffixes in sorted order.
// The LCP array stores the longest common prefix of neighbouring suffixes:
//
//   lcp[i] = LCP(suffix[sa[i]], suffix[sa[i + 1]])
//
// Kasai's trick: when moving from suffix i to suffix i + 1, the LCP can drop by
// at most one, so the total work is O(n) after the suffix array is built.
//
// The suffix array below uses doubling: O(n log² n).
// ---------------------------------------------------------------------------
vector<int> buildSuffixArray(const string& text) {
    int n = static_cast<int>(text.size());
    vector<int> suffixArray(n);
    vector<int> rank(n);
    vector<int> nextRank(n);

    for (int i = 0; i < n; ++i) {
        suffixArray[i] = i;
        rank[i] = static_cast<unsigned char>(text[i]);
    }

    for (int length = 1; length < n; length *= 2) {
        auto compare = [&](int a, int b) {
            if (rank[a] != rank[b]) return rank[a] < rank[b];
            int rankA = (a + length < n) ? rank[a + length] : -1;
            int rankB = (b + length < n) ? rank[b + length] : -1;
            return rankA < rankB;
        };

        sort(suffixArray.begin(), suffixArray.end(), compare);

        nextRank[suffixArray[0]] = 0;
        for (int i = 1; i < n; ++i) {
            nextRank[suffixArray[i]] =
                nextRank[suffixArray[i - 1]] +
                (compare(suffixArray[i - 1], suffixArray[i]) ? 1 : 0);
        }

        rank.swap(nextRank);
    }

    return suffixArray;
}

vector<int> buildLcp(const string& text, const vector<int>& suffixArray) {
    int n = static_cast<int>(text.size());
    vector<int> rank(n);
    for (int i = 0; i < n; ++i) rank[suffixArray[i]] = i;

    vector<int> lcp(max(0, n - 1), 0);
    int common = 0;

    for (int i = 0; i < n; ++i) {
        int position = rank[i];
        if (position == n - 1) {
            common = 0;
            continue;
        }

        int nextSuffix = suffixArray[position + 1];
        while (i + common < n && nextSuffix + common < n &&
               text[i + common] == text[nextSuffix + common]) {
            ++common;
        }

        lcp[position] = common;
        if (common > 0) --common;
    }

    return lcp;
}

int main() {
    string text = "banana";
    vector<int> suffixArray = buildSuffixArray(text);
    vector<int> lcp = buildLcp(text, suffixArray);

    cout << "text: " << text << "\n\n";
    cout << "suffix array: ";
    for (int index : suffixArray) cout << index << ' ';
    cout << "\n\n";
    cout << "sorted suffixes and LCP with the next suffix:\n";
    for (int i = 0; i < static_cast<int>(suffixArray.size()); ++i) {
        cout << "  " << text.substr(suffixArray[i]);
        if (i < static_cast<int>(lcp.size())) {
            cout << "   lcp=" << lcp[i];
        }
        cout << '\n';
    }

    return 0;
}
