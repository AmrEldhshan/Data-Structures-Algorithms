#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Merge overlapping intervals
//
// Sort by start. If the next interval starts before or at the current end, the
// two overlap; extend the current end to the maximum of the two. Otherwise
// flush the current interval and start a new one.
//
// Time:  O(n log n)
// Space: O(n)
// ---------------------------------------------------------------------------
struct Interval {
    int start;
    int end;
};

vector<Interval> mergeIntervals(vector<Interval> intervals) {
    if (intervals.empty()) return {};

    sort(intervals.begin(), intervals.end(),
         [](const Interval& a, const Interval& b) {
             return a.start < b.start;
         });

    vector<Interval> merged;
    merged.push_back(intervals[0]);

    for (size_t i = 1; i < intervals.size(); ++i) {
        if (intervals[i].start <= merged.back().end) {
            merged.back().end = max(merged.back().end, intervals[i].end);
        } else {
            merged.push_back(intervals[i]);
        }
    }

    return merged;
}

int main() {
    vector<Interval> intervals = {
        {1, 3}, {2, 6}, {8, 10}, {15, 18}, {17, 20}, {9, 12}
    };

    cout << "input:  ";
    for (const Interval& interval : intervals) {
        cout << '[' << interval.start << ',' << interval.end << "] ";
    }
    cout << '\n';

    vector<Interval> merged = mergeIntervals(intervals);
    cout << "merged: ";
    for (const Interval& interval : merged) {
        cout << '[' << interval.start << ',' << interval.end << "] ";
    }
    cout << '\n';

    return 0;
}
