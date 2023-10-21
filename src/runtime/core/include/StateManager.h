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

std::mutex running_mutex; // NOTE: A PATTERN LIKE THIS MIGHT BE CHALLENGING IN MY LANG! (SEE THIS AND WAITFORALLTOFINISH)
std::condition_variable running_cond;
std::atomic<int> running;
std::atomic<unsigned int> num_exec; // Temporary debugging var used to give each channel a unique id

bool DEBUG = false;

extern "C" void waitForAllToFinish();

// Actual state stuff
std::mutex exec_mutex;

extern "C" unsigned int Execute(void (*func)(unsigned int));

std::string Message2String(Message m);

void debug();

IPCBuffer<Message> *getReadQueue(unsigned int aId);
IPCBuffer<Message> *getWriteQueue(unsigned int aId);

// TODO: do better error handling for WriteMessageTo instead of just logging and returns!
void WriteMessageTo(unsigned int aId, Message m);

Message ReadLinearMessageFrom(unsigned int aId);
Message ReadLossyMessageFrom(unsigned int aId);

// TODO: move definition to separate file!
extern "C" struct _Channel {
    const unsigned int id; 
    IPCBuffer<Message> read; 
    IPCBuffer<Message> write; 

    _Channel(unsigned int i) : id(i) {}
};

extern "C" void WriteChannel(unsigned int aId, uint8_t *value);
extern "C" uint8_t *ReadChannel(unsigned int aId);
extern "C" uint8_t * _ReadLossyChannel(unsigned int aId); // FIXME: START USING


extern "C" void WriteProjection(unsigned int aId, unsigned int selVal);
extern "C" unsigned int ReadProjection(unsigned int aId);
extern "C" unsigned int _ReadLossyProjection(unsigned int aId); // FIXME: START USING



extern "C" bool ShouldLoop(unsigned int aId);
extern "C" bool _ShouldLossyLoop(unsigned int aId); // FIXME: START USING!

extern "C" bool _OC_isPresent(unsigned int aId);
extern "C" bool _OC_isPresentLossy(unsigned int aId); // FIXME: START USING!

extern "C" bool ShouldAcceptWhileLoop(unsigned int aId);
extern "C" bool ShouldLossyAcceptWhileLoop(unsigned int aId); // FIXME: START USING!

extern "C" void ContractChannel(unsigned int aId);

extern "C" void WeakenChannel(unsigned int aId);

extern "C" unsigned int _ArrayToChannel(uint8_t * array[], unsigned int len);



void _ClearChannel(std::deque<Message> &q);//(IPCBuffer<Message> * readQueue);// unsigned int aId);
extern "C" void _PreemptChannel(unsigned int aId, unsigned int skipTo);
