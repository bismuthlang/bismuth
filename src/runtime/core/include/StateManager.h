#pragma once

#include "IPCBuffer.h"
#include "Messages.h"

#include <map>
#include <thread>
#include <iostream>
#include <iterator>

#include <atomic> // Is this really needed? also how does this library work?
// For tracking running threads


// #include "gc_cpp.h"


// extern "C" void * My_malloc(size_t t) { return GC_MALLOC(t); }

std::mutex running_mutex; // NOTE: A PATTERN LIKE THIS MIGHT BE CHALLENGING IN MY LANG! (SEE THIS AND WAITFORALLTOFINISH)
std::condition_variable running_cond;
std::atomic<int> running;

extern "C" void waitForAllToFinish()
{
    // int **p = (int **) GC_malloc(sizeof(int *));
    std::unique_lock<std::mutex> lock{running_mutex};
    running_cond.wait(lock, [&]
                      { return running == 0; });
}

// Actual state stuff

std::map<unsigned int, IPCBuffer<Message> *> State;

std::map<unsigned int, unsigned int> LookupOther; // FIXME: NAME BETTER

std::mutex exec_mutex;

extern "C" unsigned int Execute(void (*func)(unsigned int))
{
    exec_mutex.lock();

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

    try
    {
        std::thread t([func, idIn]()
                      {
        func(idIn);

        std::unique_lock<std::mutex> lock(running_mutex);
        while(!running) //TODO: VERIFY
        {
            running_cond.wait(lock); 
        }
        running--; 
        running_cond.notify_one(); });
        t.detach();
    }
    catch (...)
    {
        std::cout << "E70" << std::endl;
    }

    exec_mutex.unlock();
    return idOut;
}

// TODO: do better error handling for WriteHelper instead of just logging and returns!
void WriteHelper(unsigned int aId, Message m) { //uint8_t * (*func)(unsigned int)) {
    exec_mutex.lock();
    auto i_oAId = LookupOther.find(aId);

    if (i_oAId == LookupOther.end())
    {
        throw "Preservation Error: WriteHelper could not locate channel to write to!";
    }

    unsigned int oAId = i_oAId->second;

    auto i_buffer = State.find(oAId);
    exec_mutex.unlock();

    if (i_buffer == State.end())
    {
        // std::cout << "E65 " << aId << "->" << oAId << std::endl;

        // for (auto e : State)
        // {
        //     std::cout << e.first << std::endl;
        // }

        throw "Preservation Error: WriteHelper could not locate buffer to write to!";
    }

    i_buffer->second->enqueue(m);
}

Message ReadHelper(unsigned int aId)
{
    exec_mutex.lock();
    auto i_buffer = State.find(aId);
    exec_mutex.unlock();

    if (i_buffer == State.end())
    {
        throw "Preservation error: failed to reac channel!";
    }

    return i_buffer->second->dequeue();
}

extern "C" void WriteChannel(unsigned int aId, uint8_t *value)
{
    Value v; 
    v.v = value; 
    WriteHelper(aId, v);
}

extern "C" void WriteProjection(unsigned int aId, unsigned int selVal)
{
    SEL s; 
    s.i = selVal; 
    WriteHelper(aId, s);
}

extern "C" uint8_t *ReadChannel(unsigned int aId)
{
    Message m = ReadHelper(aId); 

    if (std::holds_alternative<Value>(m))
    {
        uint8_t *v = std::get<Value>(m).v;
        return v; 
    }

    throw "Preservation Error: ReadChannel got non-VALUE!";
}

extern "C" unsigned int ReadProjection(unsigned int aId)
{
    Message m = ReadHelper(aId); 

    if (std::holds_alternative<SEL>(m))
    {
        unsigned int i = std::get<SEL>(m).i;
        return i; 
    }

    throw "Preservation Error: ReadProjection got non-SEL!";
}

extern "C" bool ShouldLoop(unsigned int aId)
{
    Message m = ReadHelper(aId); 

    if (std::holds_alternative<START_LOOP>(m))
        return true;
    if (std::holds_alternative<END_LOOP>(m))
        return false;

    throw "Preservation Error: ShouldLoop got something besides START_LOOP or END_LOOP!";
}

extern "C" void ContractChannel(unsigned int aId)
{
    START_LOOP v;
    WriteHelper(aId, v);
}

extern "C" void WeakenChannel(unsigned int aId)
{
    END_LOOP v;
    WriteHelper(aId, v);
}