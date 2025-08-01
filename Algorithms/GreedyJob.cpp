#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Job {
    int id;       // Job ID
    int deadline; // Deadline to finish the job
    int profit;   // Profit if job is completed
};

// Sort jobs by decreasing profit
bool compare(Job a, Job b) {
    return a.profit > b.profit;
}

pair<int, int> jobScheduling(vector<Job>& jobs) {
    // Step 1: Sort jobs in descending order of profit
    sort(jobs.begin(), jobs.end(), compare);

    // Step 2: Find max deadline
    int maxDeadline = 0;
    for (auto& job : jobs)
        maxDeadline = max(maxDeadline, job.deadline);

    // Step 3: Initialize time slots as free (index 1 to maxDeadline)
    vector<int> timeSlot(maxDeadline + 1, -1);  // -1 = free
    int totalJobs = 0;
    int totalProfit = 0;

    // Step 4: Try placing each job in latest free slot ≤ deadline
    for (auto& job : jobs) {
        for (int t = job.deadline; t > 0; --t) {
            if (timeSlot[t] == -1) {
                timeSlot[t] = job.id;
                totalJobs++;
                totalProfit += job.profit;
                break;
            }
        }
    }

    return {totalJobs, totalProfit};
}
