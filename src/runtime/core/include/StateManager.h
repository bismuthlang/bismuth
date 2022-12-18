#pragma once

#include "IPCBuffer.h"
#include "Messages.h"

#include <map>
#include <thread>
#include <iostream>
#include <iterator>

std::map<unsigned int, IPCBuffer<Message> *> State;

std::map<unsigned int, unsigned int> LookupOther; // FIXME: NAME BETTER

extern "C" void Execute(void (*func)(unsigned int))
{
    IPCBuffer<Message> *aIn = new IPCBuffer<Message>();
    IPCBuffer<Message> *aOut = new IPCBuffer<Message>();

    unsigned int idIn = State.size();

    State.insert({idIn, aIn});

    unsigned int idOut = State.size();

    State.insert({idOut, aOut});

    LookupOther.insert({idOut, idIn});
    LookupOther.insert({idIn, idOut});

    std::thread t(func, idIn);
    // func(idIn); //FIXME: RUN IN THREAD!
}

extern "C" void WriteChannel(unsigned int aId, void *value)
{
    auto i_oAId = LookupOther.find(aId);

    if (i_oAId == LookupOther.end())
        return; // FIXME: DO BETTER

    unsigned int oAId = i_oAId->second;



    auto i_buffer = State.find(oAId);

    if (i_buffer == State.end())
        return; // FIXME: DO BETTER

    Value v; 
    v.v = value; 

    i_buffer->second->enqueue(v);
}


extern "C" void* ReadChannel(unsigned int aId)
{
    auto i_buffer = State.find(aId);

    if (i_buffer == State.end())
        return nullptr; // FIXME: DO BETTER

    return std::get<Value>(i_buffer->second->dequeue()).v; //FIXME: RENAME TO BE MESSAGE VALUE OR SOMETHING
}