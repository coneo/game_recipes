#include "fsm.h"

void FSM::init()
{
}

void FSM::addTransition(uint32_t start, uint32_t tran, uint32_t out)
{
    FSMTransition t;
    t.transition = tran;
    t.out = out;
    _transitions[start].push_back(t);
}

void FSM::changeNextState(uint32_t state)
{
    _next_state = state;
}

void FSM::doChangeState()
{
    if (_next_state && _next_state != _cur_state)
    {
        printf("状态切换:%u -> %u\n",_cur_state, _next_state);
        _cur_state = _next_state;
        _next_state = 0;
    }
}

void FSM::loop()
{
    doChangeState();

    if (!_cur_state)
        return ;

    auto it = _transitions.find(_cur_state);
    if (it != _transitions.end())
    {
        for (auto& t : it->second)
        {
            if (call_tran_func(t.transition))
            {
                changeNextState(t.out);
                break;
            }
        }
    }
}
