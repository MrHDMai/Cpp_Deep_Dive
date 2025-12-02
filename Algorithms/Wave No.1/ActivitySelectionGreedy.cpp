#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Activity struct: holds the start and end times for an activity.
struct Activity {
    int start;
    int end;

    Activity(int s, int e) : start(s), end(e) {}
};

// Compare by end time; prefer const references to avoid copies.
// Returns true when 'a' ends earlier than 'b'.
bool compareByEnd(const Activity& a, const Activity& b) {
    return a.end < b.end;
}

// Greedy selection algorithm:
// - Sort activities by end time (O(n log n)).
// - Iterate through sorted list, selecting each activity whose start is
//   >= end time of the last selected activity (O(n)).
// Complexity: O(n log n) time, O(n) extra space for the result.
// "Non-mutating" variant: takes vector by value and returns selected activities.
// This is useful when the caller needs the original vector unchanged.
// Fastest implementation: move selected activities out of the input and
// return them. This avoids copies for large Activity objects and minimizes
// allocations for the result (inputs will be in a valid but unspecified
// state after the call).
vector<Activity> selectActivities(vector<Activity>& activities) {
    if (activities.empty()) return {};
    sort(activities.begin(), activities.end(), compareByEnd);
    vector<Activity> selected;
    selected.reserve(activities.size());
    selected.push_back(std::move(activities[0]));
    int lastEnd = selected.front().end;
    const size_t n = activities.size();
    for (size_t i = 1; i < n; ++i) {
        if (activities[i].start >= lastEnd) {
            selected.push_back(std::move(activities[i]));
            lastEnd = selected.back().end;
        }
    }
    return selected;
}



// Only the fastest move-select variant is kept: `selectActivities`.
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cout << "Enter number of activities: ";
    cin >> n;

    vector<Activity> activities;
    cout << "Enter start and end times of each activity:\n";

    for (int i = 0; i < n; ++i) {
        int s, e;
        cin >> s >> e;
        activities.emplace_back(s, e);
    }

    // Use the fastest implementation that moves selected activities out
    // of the input vector. This keeps allocation and copying minimal.
    auto selected = selectActivities(activities);
    cout << "\nMaximum set of non-overlapping activities:\n";
    for (const auto& act : selected) cout << "[" << act.start << ", " << act.end << "]\n";
    cout << "\nTotal activities selected: " << selected.size() << "\n";
    
    return 0;
}
