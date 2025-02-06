#pragma once

#include "IPCBuffer.h"
#include "Messages.h"

#include <map>
#include <thread>
#include <iostream>
#include <iterator>
#include <sstream>

#include <atomic> // Is this really needed? also how does this library work?
// For tracking running threads

// #include "gc_cpp.h"

// extern "C" void * My_malloc(size_t t) { return GC_MALLOC(t); }

// TODO: REMOVE NEED FOR RUNNING MUTEX?
std::mutex running_mutex; // NOTE: A PATTERN LIKE THIS MIGHT BE CHALLENGING IN MY LANG! (SEE THIS AND waitForAllToFinish)
std::condition_variable running_cond;
std::atomic<int> running;

bool DEBUG = false;

extern "C" void waitForAllToFinish();

// Actual state stuff
std::mutex exec_mutex;



std::string Message2String(Message m);

// void debug();


// TODO: move definition to separate file!
extern "C" struct _Channel {
    IPCBuffer<Message> * read; 
    IPCBuffer<Message> * write; 

    _Channel() : read(new IPCBuffer<Message>()), write(new IPCBuffer<Message>()) {}
    _Channel(IPCBuffer<Message> * r, IPCBuffer<Message> * w) : read(r), write(w) {}
};

extern "C" _Channel * _Execute(void (*func)(_Channel *));

// TODO: do better error handling for WriteMessageTo instead of just logging and returns!
void WriteMessageTo(_Channel * c, Message m);

Message ReadLinearMessageFrom(_Channel * c);
Message ReadLossyMessageFrom(_Channel * c);

extern "C" void _WriteChannel(_Channel * c, uint8_t *value);
extern "C" uint8_t *_ReadLinearChannel(_Channel * c);
extern "C" uint8_t * _ReadLossyChannel(_Channel * c);


extern "C" void _WriteProjection(_Channel * c, unsigned int selVal);
extern "C" unsigned int _ReadLinearProjection(_Channel * c);
extern "C" unsigned int _ReadLossyProjection(_Channel * c);



extern "C" bool _ShouldLinearLoop(_Channel * c);
extern "C" bool _ShouldLossyLoop(_Channel * c);

extern "C" bool _OC_isPresent(_Channel * c);
extern "C" bool _OC_isPresentLossy(_Channel * c);

extern "C" bool _ShouldLinearAcceptWhileLoop(_Channel * c);
extern "C" bool _ShouldLossyAcceptWhileLoop(_Channel * c);

extern "C" void _ContractChannel(_Channel * c);

extern "C" void _WeakenChannel(_Channel * c);

extern "C" _Channel * _ArrayToChannel(uint8_t * array[], unsigned int len);



void _ClearChannel(std::deque<Message> &q);//(IPCBuffer<Message> * readQueue);// _Channel c);
extern "C" void _PreemptChannel(_Channel * c, unsigned int skipTo);
