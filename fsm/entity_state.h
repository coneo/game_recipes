#include <stdio.h>
#include "state.h"
#include "entity.h"

class RunState : public State
{
public:
    virtual void enter(Entity* e) override{
        printf("enter run \n");
    }

    virtual void exit(Entity* e) override{
        printf("exit run \n");
    }

    virtual void execute(Entity* e) override{
    }
};

class AttackState : public State
{
public:
    virtual void enter(Entity* e) override{
        printf("enter attack \n");
    }

    virtual void exit(Entity* e) override{
        printf("exit attack \n");
    }

    virtual void execute(Entity* e) override{
    }
};
