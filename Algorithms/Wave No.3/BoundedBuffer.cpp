#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

class BoundedQueue {
    std::queue<int> q;
    const size_t capacity;
    std::mutex m;
    std::condition_variable cv_not_full;
    std::condition_variable cv_not_empty;

public:
    explicit BoundedQueue(size_t cap) : capacity(cap) {}

    void push(int x) {
        std::unique_lock<std::mutex> lock(m);
        cv_not_full.wait(lock, [&] {
            return q.size() < capacity;
        });
        q.push(x);
        cv_not_empty.notify_one();
    }

    int pop() {
        std::unique_lock<std::mutex> lock(m);
        cv_not_empty.wait(lock, [&] {
            return !q.empty();
        });
        int x = q.front();
        q.pop();
        cv_not_full.notify_one();
        return x;
    }
};

int main() {
    BoundedQueue bq(5);

    std::thread producer([&] {
        for (int i = 1; i <= 20; i++) {
            bq.push(i);
            std::cout << "Produced " << i << "\n";
        }
    });

    std::thread consumer([&] {
        for (int i = 1; i <= 20; i++) {
            int x = bq.pop();
            std::cout << "Consumed " << x << "\n";
        }
    });

    producer.join();
    consumer.join();
}
