#pragma once
#include "entity_state.h"

class Entity;

class FSM
{
public:
    void changeState(State* s)
    {
        if (_curState) {
            _curState->exit(nullptr); //TODO
            delete _curState;
        }
        _curState = s;
        _curState->enter(nullptr);
    }

    void update(Entity* e)
    {
        if (_curState)
            _curState->execute(e);
    }

private:
    State* _curState = nullptr;
};
