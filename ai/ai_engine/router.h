#pragma once

class Router
{
public:
    void sendMsg(uint32_t msgid, uint64_t sender, uint64_t receiver);

    void sendDelayMsg(uint32_t msgid, uint32_t delay, uint64_t sender, uint64_t receiver);

    void routeMsg(AIMsg* msg);

    void pushDelayMsg(AIMsg* msg);

    bool routeMsgHelper(GameObj* go, uint32_t stateid, AIMsg* msg);

    uint64 getCurTime()
    {
    }

public:
    void loop();

    // 循环中消耗延迟消息
    void checkSendDelayedMsg();

private:
    std::list<AIMsg> _delay_msgs;
};
