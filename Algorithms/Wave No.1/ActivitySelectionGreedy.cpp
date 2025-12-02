#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Activity struct
struct Activity {
    int start;
    int end;

    Activity(int s, int e) : start(s), end(e) {}
};

// Sort by end time
bool compare(Activity a, Activity b) {
    return a.end < b.end;
}

// Core greedy function
vector<Activity> selectActivities(vector<Activity>& activities) {
    // Step 1: Sort activities by end time
    sort(activities.begin(), activities.end(), compare);

    vector<Activity> selected;
    int lastEnd = -1;

    // Step 2: Select activities
    for (auto& activity : activities) {
        if (activity.start >= lastEnd) {
            selected.push_back(activity);
            lastEnd = activity.end;
        }
    }

    return selected;
}
int main() {
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

    vector<Activity> selected = selectActivities(activities);

    cout << "\nMaximum set of non-overlapping activities:\n";
    for (auto& act : selected) {
        cout << "[" << act.start << ", " << act.end << "]\n";
    }

    cout << "\nTotal activities selected: " << selected.size() << "\n";
    return 0;
}
