#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

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

        q.push(t);
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
        q.pop();

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
        T val = q.front();
        // q.pop();

        return val;
    }

    void pop(void)
    {
        std::unique_lock<std::mutex> lock(m);
        while (q.empty())
        {
            // release lock as long as the wait and reacquire it afterwards.
            c.wait(lock);
        }
        // T val = q.front();
        q.pop();

        return;
    }

    bool empty() {
        return q.empty(); 
    }

    std::queue<T> copy() {
        return q; 
    }

private:
    std::queue<T> q;
    mutable std::mutex m;
    std::condition_variable c;
};