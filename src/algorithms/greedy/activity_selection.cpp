#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// ---------------------------------------------------------------------------
// Activity selection (interval scheduling)
//
// Choose the largest set of activities that do not overlap. The greedy choice
// is to always take the activity that finishes earliest among the remaining
// ones: it leaves the most room for later activities.
//
// Time:  O(n log n) for the sort
// Space: O(n)
// ---------------------------------------------------------------------------
struct Activity {
    string name;
    int start;
    int finish;
};

vector<Activity> selectActivities(vector<Activity> activities) {
    sort(activities.begin(), activities.end(),
         [](const Activity& a, const Activity& b) {
             return a.finish < b.finish;
         });

    vector<Activity> chosen;
    int lastFinish = -1;

    for (const Activity& activity : activities) {
        if (activity.start >= lastFinish) {
            chosen.push_back(activity);
            lastFinish = activity.finish;
        }
    }

    return chosen;
}

int main() {
    vector<Activity> activities = {
        {"A", 1, 4}, {"B", 3, 5}, {"C", 0, 6}, {"D", 5, 7},
        {"E", 3, 9}, {"F", 5, 9}, {"G", 6, 10}, {"H", 8, 11}
    };

    vector<Activity> chosen = selectActivities(activities);
    cout << "selected activities: ";
    for (const Activity& activity : chosen) cout << activity.name << ' ';
    cout << "\ncount = " << chosen.size() << '\n';

    return 0;
}
