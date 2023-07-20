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

bool DEBUG = false;

extern "C" void waitForAllToFinish();

// Actual state stuff

std::map<unsigned int, IPCBuffer<Message> *> State;

std::map<unsigned int, unsigned int> LookupOther; // Name this something better?

std::mutex exec_mutex;

extern "C" unsigned int Execute(void (*func)(unsigned int));

std::string Message2String(Message m);

void debug();

// TODO: do better error handling for WriteHelper instead of just logging and returns!
void WriteHelper(unsigned int aId, Message m);

Message ReadHelper(unsigned int aId);

// Message PeakHelper(unsigned int aId)
// {
//     exec_mutex.lock();
//     auto i_buffer = State.find(aId);
//     exec_mutex.unlock();

//     if (i_buffer == State.end())
//     {
//         throw  "Preservation error: failed to find read channel!";
//     }

//     return i_buffer->second->peak();
// }

IPCBuffer<Message> *getReadQueue(unsigned int aId);

extern "C" void WriteChannel(unsigned int aId, uint8_t *value);

extern "C" void WriteProjection(unsigned int aId, unsigned int selVal);

extern "C" uint8_t *ReadChannel(unsigned int aId);

extern "C" unsigned int ReadProjection(unsigned int aId);

extern "C" bool ShouldLoop(unsigned int aId);

extern "C" bool _OC_isPresent(unsigned int aId);

extern "C" bool ShouldAcceptWhileLoop(unsigned int aId);

extern "C" void PopEndLoop(unsigned int aId);

extern "C" void ContractChannel(unsigned int aId);

extern "C" void WeakenChannel(unsigned int aId);

extern "C" unsigned int _ArrayToChannel(uint8_t * array[], unsigned int len);