#pragma once

#include "IPCBuffer.h"
#include "Messages.h"

#include <map>
#include <thread>
#include <iostream>
#include <iterator>

#include <atomic> // Is this really needed? also how does this library work?
// For tracking running threads

std::mutex running_mutex; // FIXME: A PATTERN LIKE THIS MIGHT BE CHALLENGING IN MY LANG! (SEE THIS AND WAITFORALLTOFINISH)
std::condition_variable running_cond;
std::atomic<int> running;

extern "C" void waitForAllToFinish()
{
    std::unique_lock<std::mutex> lock{running_mutex};
    running_cond.wait(lock, [&]
              { return running == 0; });
}

// Actual state stuff

std::map<unsigned int, IPCBuffer<Message> *> State;

std::map<unsigned int, unsigned int> LookupOther; // FIXME: NAME BETTER

// extern "C" void helper(void (*func)(unsigned int), unsigned int i)
// {
//     func(i);
// }

extern "C" unsigned int Execute(void (*func)(unsigned int))
{
    IPCBuffer<Message> *aIn = new IPCBuffer<Message>();
    IPCBuffer<Message> *aOut = new IPCBuffer<Message>();

    unsigned int idIn = State.size();
    State.insert({idIn, aIn});

    unsigned int idOut = State.size();
    State.insert({idOut, aOut});

    LookupOther.insert({idOut, idIn});
    LookupOther.insert({idIn, idOut});

    std::lock_guard<std::mutex> lock(running_mutex);
    running++; 
    running_cond.notify_one();

    std::thread t ([func, idIn](){
        func(idIn);

        std::unique_lock<std::mutex> lock(running_mutex);
        while(!running) //TODO: VERIFY
        {
            running_cond.wait(lock); 
        }
        running--; 
        running_cond.notify_one();
    });
    t.detach();
    return idOut;
}

extern "C" void WriteChannel(unsigned int aId, uint8_t *value)
{
    auto i_oAId = LookupOther.find(aId);

    if (i_oAId == LookupOther.end())
    {
        std::cout << "E53" << std::endl;
        return; // FIXME: DO BETTER
    }

    unsigned int oAId = i_oAId->second;

    auto i_buffer = State.find(oAId);

    if (i_buffer == State.end())
    {
        std::cout << "E65" << std::endl;
        return; // FIXME: DO BETTER
    }

    Value v;
    v.v = value;

    // std::cout << "Write " << (*(int *) value) << "@" << i_buffer->first << std::endl;
    i_buffer->second->enqueue(v);
}

extern "C" uint8_t *ReadChannel(unsigned int aId)
{
    auto i_buffer = State.find(aId);

    if (i_buffer == State.end())
    {
        std::cout << "79" << std::endl;
        return nullptr; // FIXME: DO BETTER
    }
    // return nullptr; // FIXME: DO BETTER
    uint8_t *v = std::get<Value>(i_buffer->second->dequeue()).v;
    // std::cout << "Read " << (*(int *) v) << "@" << i_buffer->first << std::endl;
    return v; // FIXME: RENAME TO BE MESSAGE VALUE OR SOMETHING
}