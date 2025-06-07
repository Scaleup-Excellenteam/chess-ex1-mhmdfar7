#pragma once
#include <queue>
#include <mutex>
#include <functional>

template <typename T, typename Compare = std::less<T>>
class SafePriorityQueue {
public:
    void push(const T& item) {
        std::lock_guard<std::mutex> lock(mtx);
        pq.push(item);
    }

    bool tryPop(T& result) {
        std::lock_guard<std::mutex> lock(mtx);
        if (pq.empty()) return false;
        result = pq.top();
        pq.pop();
        return true;
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(mtx);
        return pq.empty();
    }

private:
    mutable std::mutex mtx;
    std::priority_queue<T, std::vector<T>, Compare> pq;
};
