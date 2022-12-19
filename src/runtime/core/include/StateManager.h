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
    // std::cout << "EXEC 20" << std::endl; 

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
    t.detach();
    // t.join();
// std::cout << "EXEC 34" << std::endl; 
    return idOut;
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