#pragma once

#include "IPCBuffer.h"
#include "Messages.h"

#include <map>
#include <thread>
#include <iostream>
#include <iterator>


std::map<unsigned int, IPCBuffer<Message> *> State;

std::map<unsigned int, unsigned int> LookupOther; // FIXME: NAME BETTER

extern "C" void helper(void (*func)(unsigned int), unsigned int i)
{
    func(i);
}

extern "C" unsigned int Execute(void (*func)(unsigned int))
{
    IPCBuffer<Message> *aIn = new IPCBuffer<Message>();
    IPCBuffer<Message> *aOut = new IPCBuffer<Message>();
    std::cout << "EXEC 20" << std::endl;

    unsigned int idIn = State.size();
    State.insert({idIn, aIn});

    unsigned int idOut = State.size();
    State.insert({idOut, aOut});

    LookupOther.insert({idOut, idIn});
    LookupOther.insert({idIn, idOut});
    // func(idIn);
    // std::thread t (helper, func, idIn);
    std::thread t(func, idIn);
    // std::thread t ([func](){
    //     std::cout << "THREADED" << std::endl;
    // });
    // t.detach();
    t.join();
    std::cout << "EXEC 34" << std::endl;
    return idOut;
    // func(idIn); //FIXME: RUN IN THREAD!
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

    std::cout << "Write " << (*(int *) value) << "@" << i_buffer->first << std::endl; 
    i_buffer->second->enqueue(v);
}

extern "C" uint8_t* ReadChannel(unsigned int aId)
{
    auto i_buffer = State.find(aId);

    if (i_buffer == State.end())
    {
        std::cout << "79" << std::endl;
        return nullptr; // FIXME: DO BETTER
    }
        // return nullptr; // FIXME: DO BETTER
    uint8_t * v  = std::get<Value>(i_buffer->second->dequeue()).v;
    std::cout << "Read " << (*(int *) v) << "@" << i_buffer->first << std::endl; 
    return  v;// FIXME: RENAME TO BE MESSAGE VALUE OR SOMETHING
}