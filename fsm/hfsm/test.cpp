#include <stdio.h>
#include <unistd.h>
#include "fsm.h"

class Agent
{
public:
    Agent()
    {
        _fsm = new FSM();
    }

    void init()
    {
        _fsm->init();
    }
    void loop(){}

private:
    FSM* _fsm = nullptr;
};

int main()
{
    Agent* ag = new Agent();
    if (!ag)
        return 0;

    ag->init();
    while (true)
    {
        printf("tick ...\n");
        usleep(1000000);
        ag->loop();
    }
}
