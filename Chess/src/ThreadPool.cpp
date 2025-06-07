#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t numThreads)
    : running(true)
{
    for (size_t i = 0; i < numThreads; ++i) {
        workers.emplace_back([this] { this->workerLoop(); });
    }
}

ThreadPool::~ThreadPool() {
    shutdown();
}

void ThreadPool::enqueue(std::function<void()> task) {
    {
        std::lock_guard<std::mutex> lock(queueMutex);
        tasks.push(std::move(task));
    }
    condition.notify_one();
}

void ThreadPool::shutdown() {
    running = false;
    condition.notify_all();
    for (auto& thread : workers) {
        if (thread.joinable()) thread.join();
    }
}

void ThreadPool::workerLoop() {
    while (running) {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            condition.wait(lock, [this] { return !running || !tasks.empty(); });
            if (!running && tasks.empty()) return;
            job = std::move(tasks.front());
            tasks.pop();
        }
        job();
    }
}
