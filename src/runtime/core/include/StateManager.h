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

std::mutex exec_mutex; // FIXME: DO BETTER W/ MUTEX

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

    // std::cout << idIn << "<>" << idOut << std::endl;
    // std::cout << (State.find(idIn) != State.end()) << " " << (LookupOther.find(idIn) != LookupOther.end()) << " " << (State.find(idOut) != State.end()) << " " << (LookupOther.find(idOut) != LookupOther.end()) << std::endl;

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

void WriteHelper(unsigned int aId, Message m) { //uint8_t * (*func)(unsigned int)) {
exec_mutex.lock();
    auto i_oAId = LookupOther.find(aId);

    if (i_oAId == LookupOther.end())
    {
        std::cout << "E53 " << aId << std::endl;
        return; // FIXME: DO BETTER
    }

    unsigned int oAId = i_oAId->second;

    auto i_buffer = State.find(oAId);
    exec_mutex.unlock();

    if (i_buffer == State.end())
    {
        std::cout << "E65 " << aId << "->" << oAId << std::endl;

        for (auto e : State)
        {
            std::cout << e.first << std::endl;
        }

        return; // FIXME: DO BETTER
    }

    // Value v;
    // v.v = value;

    // std::cout << "Write " << (*(int *) value) << "@" << i_buffer->first << std::endl;
    i_buffer->second->enqueue(m);
}

extern "C" void WriteChannel(unsigned int aId, uint8_t *value)
{
    Value v; 
    v.v = value; 
    WriteHelper(aId, v);
}

extern "C" void WriteProjection(unsigned int aId, unsigned int selVal) //FIXME: methodize with WriteChannel
{
    SEL s; 
    s.i = selVal; 
    WriteHelper(aId, s);
}

extern "C" uint8_t *ReadChannel(unsigned int aId)
{
    exec_mutex.lock();
    auto i_buffer = State.find(aId);
    exec_mutex.unlock();

    if (i_buffer == State.end())
    {
        std::cout << "E79 " << aId << std::endl;
        for (auto e : State)
        {
            std::cout << e.first << std::endl;
        }
        return nullptr; // FIXME: DO BETTER
    }
    // return nullptr; // FIXME: DO BETTER
    uint8_t *v = std::get<Value>(i_buffer->second->dequeue()).v;
    // std::cout << "Read " << (*(int *) v) << "@" << i_buffer->first << std::endl;
    return v; // FIXME: RENAME TO BE MESSAGE VALUE OR SOMETHING
}

extern "C" unsigned int ReadProjection(unsigned int aId) //FIXME: SHOULD METHODIZE ALL THESE
{
    exec_mutex.lock();
    auto i_buffer = State.find(aId);
    exec_mutex.unlock();

    if (i_buffer == State.end())
    {
        std::cout << "79 " << aId << std::endl;
        return false; // FIXME: DO BETTER
    }

    Message m = i_buffer->second->dequeue();

    if (std::holds_alternative<SEL>(m))
    {
        unsigned int i = std::get<SEL>(m).i;
        return i; 
    }

    std::cout << "E168" << std::endl; // FIXME: DO BETTER
    
    return 0; 
}

extern "C" bool ShouldLoop(unsigned int aId)
{
    exec_mutex.lock();
    auto i_buffer = State.find(aId);
    exec_mutex.unlock();

    if (i_buffer == State.end())
    {
        std::cout << "79 " << aId << std::endl;
        return false; // FIXME: DO BETTER
    }

    Message m = i_buffer->second->dequeue();

    if (std::holds_alternative<START_LOOP>(m))
        return true;
    if (std::holds_alternative<END_LOOP>(m))
        return false;

    std::cout << "E126" << std::endl; // FIXME: DO BETTER
    std::cout << "SL: " << std::holds_alternative<START_LOOP>(m) << " EL: " << std::holds_alternative<END_LOOP>(m) << " VAL: " << std::holds_alternative<Value>(m) << " SEL: " << std::holds_alternative<SEL>(m) << std::endl;

    return false;
}

extern "C" void ContractChannel(unsigned int aId)
{
    exec_mutex.lock();
    auto i_oAId = LookupOther.find(aId);
    exec_mutex.unlock();

    if (i_oAId == LookupOther.end())
    {
        std::cout << "E138 " << aId << std::endl;
        return; // FIXME: DO BETTER
    }

    unsigned int oAId = i_oAId->second;

    exec_mutex.lock();
    auto i_buffer = State.find(oAId);
    exec_mutex.unlock();

    if (i_buffer == State.end())
    {
        std::cout << "E148 " << aId << "->" << oAId << std::endl;
        return; // FIXME: DO BETTER
    }

    START_LOOP v;
    // v.v = value;

    // std::cout << "Write " << (*(int *) value) << "@" << i_buffer->first << std::endl;
    i_buffer->second->enqueue(v);
}

extern "C" void WeakenChannel(unsigned int aId)
{
    exec_mutex.lock();
    auto i_oAId = LookupOther.find(aId);

    if (i_oAId == LookupOther.end())
    {
        std::cout << "E165 " << aId << std::endl;
        return; // FIXME: DO BETTER
    }

    unsigned int oAId = i_oAId->second;

    auto i_buffer = State.find(oAId);

    exec_mutex.unlock();

    if (i_buffer == State.end())
    {
        std::cout << "E175 " << aId << "->" << oAId << std::endl;
        return; // FIXME: DO BETTER
    }

    END_LOOP v;
    // v.v = value;

    // std::cout << "Write " << (*(int *) value) << "@" << i_buffer->first << std::endl;
    i_buffer->second->enqueue(v);
}