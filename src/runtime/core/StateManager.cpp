#include "StateManager.h"

#include <exception>

extern "C" void waitForAllToFinish()
{
    std::unique_lock<std::mutex> lock{running_mutex};
    running_cond.wait(lock, [&]
                      { return running == 0; });
}

extern "C" _Channel Execute(void (*func)(_Channel))
{
    exec_mutex.lock();

    _Channel a = _Channel(); 
    _Channel b = _Channel(a.write, a.read); // Flip direction of buffers

    // unsigned int idOut = State.size();
    // State.insert({idOut, aOut});

    std::lock_guard<std::mutex> lock(running_mutex);
    running++;
    running_cond.notify_one();

    try
    {
        std::thread t([func, a]()
                      {
        func(a);

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
    return b;
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

// void debug(std::string logWhere)
// {
//     exec_mutex.lock();
//     std::cout << logWhere << std::endl;
//     for (auto itr : State)
//     {
//         std::cout << itr.first << " -> " << LookupOther.find(itr.first)->second << std::endl;
//         std::cout << "\t";

//         std::deque<Message> copy_queue = itr.second->copy();

//         while (!copy_queue.empty())
//         {
//             Message m = copy_queue.front();
//             std::cout << Message2String(m);
//             copy_queue.pop_front();
//         }
//         std::cout << std::endl;
//     }
//     std::cout << "--------------------------------" << std::endl;

//     exec_mutex.unlock();
// }


Message ReadLinearMessageFrom(_Channel c)
{
    Message m = c.read->dequeue();
    // if (DEBUG)
    // {
    //     std::ostringstream p;
    //     p << "DEQUEUE " << aId << " " << Message2String(m) << std::endl;
    //     std::cerr << p.str();
    // }
    return m;
}

Message ReadLossyMessageFrom(_Channel c)
{
    IPCBuffer<Message> *readQueue = c.read;

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

void WriteMessageTo(_Channel c, Message m)
{
    IPCBuffer<Message> *writeQueue = c.write;

    // if (DEBUG)
    // {
    //     std::ostringstream p;
    //     p << "ENQUEUE " << aId << " -> " << oAId << " " << Message2String(m) << std::endl;
    //     std::cerr << p.str();
    // }

    writeQueue->enqueue(m);
}





extern "C" void WriteChannel(_Channel c, uint8_t *value)
{
    Value v(value);
    WriteMessageTo(c, v);
}

extern "C" uint8_t *ReadChannel(_Channel c)
{
    Message m = ReadLinearMessageFrom(c);

    if (std::holds_alternative<Value>(m))
    {
        uint8_t *v = std::get<Value>(m).v;
        return v;
    }

    throw std::runtime_error("Preservation Error: _ReadLinearChannel got non-VALUE: " + Message2String(m));
}

extern "C" uint8_t *_ReadLossyChannel(_Channel c)
{
    Message m = ReadLossyMessageFrom(c);

    if (std::holds_alternative<Value>(m))
    {
        uint8_t *v = std::get<Value>(m).v;
        return v;
    }
    else if(std::holds_alternative<CLOSE>(m))
    {
        return nullptr;  // TODO: VERIFY GOOD ENOUGH!
    }

    // FIXME: instead, write closeable for reading lossy then return nullptr!
    throw std::runtime_error("Preservation Error: _ReadLossyChannel got non-VALUE: " + Message2String(m));
}






extern "C" void WriteProjection(_Channel c, unsigned int selVal)
{
    SEL s(selVal);
    WriteMessageTo(c, s);
}

extern "C" unsigned int ReadProjection(_Channel c)
{
    Message m = ReadLinearMessageFrom(c);

    if (std::holds_alternative<SEL>(m))
    {
        unsigned int i = std::get<SEL>(m).i;
        return i;
    }

    throw std::runtime_error("Preservation Error: ReadProjection got non-SEL!");
}

extern "C" unsigned int _ReadLossyProjection(_Channel c)
{
    Message m = ReadLossyMessageFrom(c);

    if (std::holds_alternative<SEL>(m))
    {
        unsigned int i = std::get<SEL>(m).i;
        return i;
    }
    else if(std::holds_alternative<CLOSE>(m))
    {
        return 0; 
    }

    throw std::runtime_error("Preservation Error: _ReadLossyProjection got non-SEL!");
}





extern "C" bool ShouldLoop(_Channel c)
{
    Message m = ReadLinearMessageFrom(c);

    if (std::holds_alternative<START_LOOP>(m))
        return true;
    if (std::holds_alternative<END_LOOP>(m))
        return false;

    throw std::runtime_error("Preservation Error: ShouldLoop got something besides START_LOOP or END_LOOP!");
}

extern "C" bool _ShouldLossyLoop(_Channel c)
{
    Message m = ReadLossyMessageFrom(c);

    if (std::holds_alternative<START_LOOP>(m))
        return true;
    if (std::holds_alternative<END_LOOP>(m))
        return false;
    if(std::holds_alternative<CLOSE>(m))
        return false; 

    throw std::runtime_error("Preservation Error: _ShouldLossyLoop got something besides START_LOOP or END_LOOP!");
}




extern "C" bool _OC_isPresent(_Channel c)
{
    std::optional<Message> mOpt = c.read->peakNow();

    if (!mOpt)
        return false;

    Message m = mOpt.value();

    if (std::holds_alternative<START_LOOP>(m))
        return true;
    else if (std::holds_alternative<END_LOOP>(m))
        return false;

    throw std::runtime_error("Preservation Error: _OC_isPresent got something besides START_LOOP or END_LOOP!");
}

extern "C" bool _OC_isPresentLossy(_Channel c)
{
    std::optional<Message> mOpt = c.read->peakNow();

    if (!mOpt)
        return false;

    Message m = mOpt.value();

    if (std::holds_alternative<START_LOOP>(m))
        return true;
    else if (std::holds_alternative<END_LOOP>(m))
        return false;
    else if(std::holds_alternative<CLOSE>(m))
        return false;

    throw std::runtime_error("Preservation Error: _OC_isPresentLossy got something besides START_LOOP or END_LOOP!");
}




extern "C" bool ShouldAcceptWhileLoop(_Channel c)
{
    IPCBuffer<Message> *readQueue = c.read;
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

    throw std::runtime_error("Preservation Error: ShouldLoop got something besides START_LOOP or END_LOOP!");
}

extern "C" bool ShouldLossyAcceptWhileLoop(_Channel c)
{
    IPCBuffer<Message> *readQueue = c.read;
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

    if(std::holds_alternative<CLOSE>(m))
    {
        return false; 
    }

    throw std::runtime_error("Preservation Error: ShouldLossyAcceptWhileLoop got something besides START_LOOP or END_LOOP!");
}






extern "C" void ContractChannel(_Channel c)
{
    START_LOOP v;
    WriteMessageTo(c, v);
}

extern "C" void WeakenChannel(_Channel c)
{
    END_LOOP v;
    WriteMessageTo(c, v);
}

extern "C" _Channel _ArrayToChannel(uint8_t *array[], unsigned int len)
{
    exec_mutex.lock();
    IPCBuffer<Message> *aRead = new IPCBuffer<Message>();
    _Channel c = _Channel(aRead, nullptr); // TODO: note nullptr!

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

    return c;
}

void _ClearChannel(std::deque<Message> &q)//(IPCBuffer<Message> *readQueue) // _Channel c)
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

extern "C" void _PreemptChannel(_Channel c, unsigned int skipTo)
{
    c.read->operateOn([skipTo](std::deque<Message> &q)
                         { q.push_front(SKIP(skipTo));
                           _ClearChannel(q); });

    c.write->operateOn([skipTo](std::deque<Message> &q)
                          { q.push_back(CLOSE(skipTo));
                            _ClearChannel(q); });

    // _ClearChannel(c.read);
    // _ClearChannel(c.write);
}
