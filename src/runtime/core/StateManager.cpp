#include "StateManager.h"

#include <exception>

extern "C" void waitForAllToFinish()
{
    std::unique_lock<std::mutex> lock{running_mutex};
    running_cond.wait(lock, [&]
                      { return running == 0; });
}

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
        while(!running)
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

std::string Message2String(Message m)
{
    return std::visit(overload{[](START_LOOP &)
                               { return std::string("START-LOOP "); },
                               [](END_LOOP &)
                               { return std::string("END-LOOP "); },
                               [](Value &)
                               { return std::string("Val "); },
                               [](SEL &s)
                               { return "SEL[" + std::to_string(s.i) + "] "; },
                               [](SKIP &s)
                               { return "SKIP[" + std::to_string(s.i) + "] "; },
                               [](CLOSE &s)
                               { return "CLOSE[" + std::to_string(s.i) + "] "; }},
                      m);
}

void debug(std::string logWhere)
{
    exec_mutex.lock();
    std::cout << logWhere << std::endl;
    for (auto itr : State)
    {
        std::cout << itr.first << " -> " << LookupOther.find(itr.first)->second << std::endl;
        std::cout << "\t";

        std::deque<Message> copy_queue = itr.second->copy();

        while (!copy_queue.empty())
        {
            Message m = copy_queue.front();
            std::cout << Message2String(m);
            copy_queue.pop_front();
        }
        std::cout << std::endl;
    }
    std::cout << "--------------------------------" << std::endl;

    exec_mutex.unlock();
}

IPCBuffer<Message> *getWriteQueue(unsigned int aId)
{
    exec_mutex.lock();
    auto i_oAId = LookupOther.find(aId);

    if (i_oAId == LookupOther.end())
    {
        throw std::runtime_error("Preservation Error: could not locate channel to write to!");
    }

    unsigned int oAId = i_oAId->second;

    auto i_buffer = State.find(oAId);
    exec_mutex.unlock();

    if (i_buffer == State.end())
    {
        throw std::runtime_error("Preservation Error: could not locate buffer to write to!");
    }

    return i_buffer->second;
}

IPCBuffer<Message> *getReadQueue(unsigned int aId)
{
    exec_mutex.lock();
    auto i_buffer = State.find(aId);
    exec_mutex.unlock();

    if (i_buffer == State.end())
    {
        throw std::runtime_error("Preservation error: failed to find read channel!");
    }

    return i_buffer->second;
}

Message ReadMessageFrom(unsigned int aId)
{
    IPCBuffer<Message> *readQueue = getReadQueue(aId);

    // TODO: ONLY DO EXTRA CHECK ON ERROR QUEUE!
    Message m = readQueue->peak(); 

    while(std::holds_alternative<SKIP>(m)) // Happens if we haven't had a chance to clean up yet. //TODO: DO BETTER
    {
        m = readQueue->peak(); 
    }

    // May want to move some of the close related logic to encapsulations around the queue itself 
    if(!(std::holds_alternative<CLOSE>(m)))
    {
        readQueue->dequeue();
    }

    return m;
}

void WriteMessageTo(unsigned int aId, Message m)
{
    IPCBuffer<Message> *writeQueue = getWriteQueue(aId);

    // if (DEBUG)
    // {
    //     std::ostringstream p;
    //     p << "ENQUEUE " << aId << " -> " << oAId << " " << Message2String(m) << std::endl;
    //     std::cerr << p.str();
    // }

    writeQueue->enqueue(m);
}

extern "C" void WriteChannel(unsigned int aId, uint8_t *value)
{
    Value v(value);
    WriteMessageTo(aId, v);
}

extern "C" void WriteProjection(unsigned int aId, unsigned int selVal)
{
    SEL s(selVal);
    WriteMessageTo(aId, s);
}

extern "C" uint8_t *ReadChannel(unsigned int aId)
{
    Message m = ReadMessageFrom(aId);

    if (std::holds_alternative<Value>(m))
    {
        uint8_t *v = std::get<Value>(m).v;
        return v;
    }
    else if(std::holds_alternative<CLOSE>(m))
    {
        return nullptr;  // TODO: VERIFY GOOD ENOUGH!
    }

    throw std::runtime_error("Preservation Error: ReadChannel got non-VALUE: " + Message2String(m));
}

extern "C" unsigned int ReadProjection(unsigned int aId)
{
    Message m = ReadMessageFrom(aId);

    if (std::holds_alternative<SEL>(m))
    {
        unsigned int i = std::get<SEL>(m).i;
        return i;
    }

    throw std::runtime_error("Preservation Error: ReadProjection got non-SEL!");
}

extern "C" bool ShouldLoop(unsigned int aId)
{
    Message m = ReadMessageFrom(aId);

    if (std::holds_alternative<START_LOOP>(m))
        return true;
    if (std::holds_alternative<END_LOOP>(m))
        return false;

    throw std::runtime_error("Preservation Error: ShouldLoop got something besides START_LOOP or END_LOOP!");
}

extern "C" bool _OC_isPresent(unsigned int aId)
{
    IPCBuffer<Message> *readQueue = getReadQueue(aId);
    std::optional<Message> mOpt = readQueue->peakNow();

    if (!mOpt)
        return false;

    Message m = mOpt.value();

    if (std::holds_alternative<START_LOOP>(m))
        return true;
    else if (std::holds_alternative<END_LOOP>(m))
        return false;

    throw std::runtime_error("Preservation Error: _OC_isPresent got something besides START_LOOP or END_LOOP!");
}

extern "C" bool ShouldAcceptWhileLoop(unsigned int aId)
{
    IPCBuffer<Message> *readQueue = getReadQueue(aId);
    Message m = readQueue->peak();

    if (std::holds_alternative<START_LOOP>(m))
    {
        readQueue->pop();
        return true;
    }

    if (std::holds_alternative<END_LOOP>(m))
    {
        return false;
    }

    // Message m = PeakHelper(aId);

    // if (std::holds_alternative<START_LOOP>(m))
    //     return true;
    // if (std::holds_alternative<END_LOOP>(m))
    //     return false;

    throw std::runtime_error("Preservation Error: ShouldLoop got something besides START_LOOP or END_LOOP!");
}

extern "C" void PopEndLoop(unsigned int aId)
{
    IPCBuffer<Message> *readQueue = getReadQueue(aId);
    Message m = readQueue->peak();
    readQueue->pop();

    if (!std::holds_alternative<END_LOOP>(m))
    {
        // return false;
        throw std::runtime_error("Preservation Error: PopEndLoop got something besides END_LOOP!");
    }

    // Message m = PeakHelper(aId);

    // if (std::holds_alternative<START_LOOP>(m))
    //     return true;
    // if (std::holds_alternative<END_LOOP>(m))
    //     return false;
}

extern "C" void ContractChannel(unsigned int aId)
{
    START_LOOP v;
    WriteMessageTo(aId, v);
}

extern "C" void WeakenChannel(unsigned int aId)
{
    END_LOOP v;
    WriteMessageTo(aId, v);
}

extern "C" unsigned int _ArrayToChannel(uint8_t *array[], unsigned int len)
{
    exec_mutex.lock();
    IPCBuffer<Message> *aRead = new IPCBuffer<Message>();
    unsigned int id = State.size();

    State.insert({id, aRead});

    for (unsigned int i = 0; i < len; i++)
    {
        START_LOOP s;
        Value v(array[i]);

        aRead->enqueue(s);
        aRead->enqueue(v);
    }

    END_LOOP end;
    aRead->enqueue(end);

    exec_mutex.unlock();

    return id;
}

void _ClearChannel(std::deque<Message> &q)//(IPCBuffer<Message> *readQueue) // unsigned int aId)
{
    // readQueue->operateOn([](std::deque<Message> &q)
        // {
            if (q.empty())
                return;

            if (!std::holds_alternative<SKIP>(q.front()))
                return;

            unsigned int skipAmt = 0; // skipTo;

            while (!q.empty())
            {
                Message frontMsg = q.front();

                if (std::holds_alternative<SKIP>(frontMsg))
                {
                    // If first-ish message is skip, then
                    // update amount skipped to the max, and continue
                    q.pop_front();
                    SKIP skipMsg = std::get<SKIP>(frontMsg);
                    skipAmt = std::max(skipAmt, skipMsg.i);
                }
                else if (std::holds_alternative<CLOSE>(frontMsg))
                {
                    CLOSE closeMsg = std::get<CLOSE>(frontMsg);

                    if (skipAmt == closeMsg.i)
                    {
                        // If close # = skip #, then we are done (both programs hit same sync point)
                        // and we can clear out the close.
                        q.pop_front();
                        return;
                    }

                    if (skipAmt > closeMsg.i)
                    {
                        // If we skip past the close, then ignore the close
                        q.pop_front();
                    }
                    else // skipAmt < closeMessage.i
                    {
                        // If the close is for more than we skip, then preserve the close
                        // and return before we re-add the skip message to the front
                        // of the queue
                        return;
                    }
                }
                else
                {
                    q.pop_front(); // FIXME: MAY HAVE TO FREE IF VALUE & DEAL WITH HIGHER-ORDER STUFF!
                }
            }

            SKIP s(skipAmt);
            q.push_front(s);
        // });
}

extern "C" void _PreemptChannel(unsigned int aId, unsigned int skipTo)
{
    IPCBuffer<Message> *readQueue = getReadQueue(aId);

    readQueue->operateOn([skipTo](std::deque<Message> &q)
                         { q.push_front(SKIP(skipTo));
                           _ClearChannel(q); });

    IPCBuffer<Message> *writeQueue = getWriteQueue(aId);
    writeQueue->operateOn([skipTo](std::deque<Message> &q)
                          { q.push_back(CLOSE(skipTo));
                            _ClearChannel(q); });

    // _ClearChannel(readQueue);
    // _ClearChannel(writeQueue);
}
