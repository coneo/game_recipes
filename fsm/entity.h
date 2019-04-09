#pragma once

#include "fsm.h"

class Entity
{
public:
    void loop() {
        _fsm.update(this);

        if (_testid == 100) {
            _fsm.changeState(new RunState());
        } else if (_testid == 200) {
            _fsm.changeState(new AttackState());
        }
    }

    uint32_t _testid = 0;

private:
    FSM _fsm;

};
