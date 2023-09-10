#pragma once

#include <deque> // Could be regular queue except for operateOn needs for clearing stuffs
#include <mutex>
#include <condition_variable>
#include <optional> 
#include <functional> // std::function
#include <algorithm> // std::max


// A threadsafe-queue from https://stackoverflow.com/questions/15278343/c11-thread-safe-queue
template <class T>
class IPCBuffer
{
public:
    IPCBuffer(void)
        : q(), m(), c()
    {
    }

    ~IPCBuffer(void)
    {
    }

    // Add an element to the queue.
    void enqueue(T t)
    {
        std::lock_guard<std::mutex> lock(m);

        q.push_back(t);
        c.notify_one();
    }

    // Get the "front"-element.
    // If the queue is empty, wait till a element is available.
    T dequeue(void)
    {
        std::unique_lock<std::mutex> lock(m);
        while (q.empty())
        {
            // release lock as long as the wait and reacquire it afterwards.
            c.wait(lock);
        }
        T val = q.front();
        q.pop_front();

        return val;
    }

    T peak(void)
    {
        std::unique_lock<std::mutex> lock(m);
        while (q.empty())
        {
            // release lock as long as the wait and reacquire it afterwards.
            c.wait(lock);
        }
        return q.front();
    }

    std::optional<T> peakNow(void)
    {
        std::unique_lock<std::mutex> lock(m);
        if (q.empty())
        {
            return std::nullopt; 
        }
        return q.front();
    }

    void pop(void)
    {
        std::unique_lock<std::mutex> lock(m);
        while (q.empty())
        {
            // release lock as long as the wait and reacquire it afterwards.
            c.wait(lock);
        }
        q.pop_front();

        return;
    }

    bool empty()
    {
        return q.empty();
    }

    std::deque<T> copy()
    {
        return q;
    }

    void operateOn(std::function<void(std::deque<T>&)> const& func)//(void (func)(std::queue<T>& m))
    {
        std::unique_lock<std::mutex> lock(m);
        func(q);
        c.notify_one(); // Just in case people mess with the queue, notify listeners
    }

private:
    std::deque<T> q;
    mutable std::mutex m;
    std::condition_variable c;
};