#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

struct Activity { int start; int end; };

// Keep only the comparator using const refs; comp_by_value is unused.

// Comparator that uses const refs (preferred)
bool comp_const_ref(const Activity& a, const Activity& b) { return a.end < b.end; }

// Only keep the fastest implementation: move-selected activities out of the input.

// Fast variant: move selected Activities out of the input, leaving the input
// in a valid but unspecified state (fastest when caller relinquishes input).
vector<Activity> selectFastMove(vector<Activity>& activities) {
    if (activities.empty()) return {};
    sort(activities.begin(), activities.end(), comp_const_ref);
    vector<Activity> selected;
    selected.reserve(activities.size());
    selected.push_back(std::move(activities[0]));
    int lastEnd = selected.front().end;
    for (size_t i = 1; i < activities.size(); ++i) {
        if (activities[i].start >= lastEnd) {
            selected.push_back(std::move(activities[i]));
            lastEnd = selected.back().end;
        }
    }
    return selected;
}

// Helper to generate random activities
vector<Activity> gen_random(int n, int max_time = 1000000) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, max_time);
    vector<Activity> v;
    v.reserve(n);
    for (int i = 0; i < n; ++i) {
        int a = dist(gen);
        int b = dist(gen);
        if (a <= b) v.push_back({a, b});
        else v.push_back({b, a});
    }
    return v;
}

// Run a single test for function f (by reference) using a copy of data
using SelectorRef = vector<Activity>(*)(vector<Activity>&);

// Measure in microseconds to avoid 0ms artifacts on small inputs
long long bench_by_ref(SelectorRef f, vector<Activity> data, int iterations = 10) {
    // run in-place variant: must use fresh copy each iteration to avoid sorted input
    long long total_ms = 0;
    for (int i = 0; i < iterations; ++i) {
        vector<Activity> copy = data;
        auto start = chrono::high_resolution_clock::now();
        auto res = f(copy);
        auto stop = chrono::high_resolution_clock::now();
        total_ms += chrono::duration_cast<chrono::microseconds>(stop - start).count();
        (void)res;
    }
    return total_ms / iterations; // returns average microseconds
}

// Removed additional bench variants; measuring only the fastest (move) variant.

int main() {
    vector<int> sizes = {1000, 10000, 50000, 100000, 500000, 1000000};
    cout << "Benchmarking Activity Selection Variants\n";

    for (int s : sizes) {
        cout << "N = " << s << '\n';
        auto data = gen_random(s);

        long long tFast = bench_by_ref(selectFastMove, data);
        cout << "  Fastest Move variant: " << (tFast/1000.0) << " ms\n";

        cout << "\n";
    }

    return 0;
}
