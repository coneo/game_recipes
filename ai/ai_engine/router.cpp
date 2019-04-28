#include "router.h"

void Router::sendMsg(uint32_t msgid, uint64_t sender, uint64_t receiver)
{
    AIMsg msg;
    msg.msgid = msgid;
    msg.senderid = sender;
    msg.receiverid = receiver;
    msg.deliverytime = 0; // TODO now

    routeMsg(&msg);
}

void Router::sendDelayMsg(uint32_t msgid, uint32_t delay, uint64_t sender, uint64_t receiver)
{
    AIMsg msg;
    msg.msgid = msgid;
    msg.senderid = sender;
    msg.receiverid = receiver;
    msg.deliverytime = now + delay; // 毫秒

    routeMsg(&msg);
}

void Router::routeMsg(AIMsg* msg)
{
    GameObj* go = GameObjMgr::getme().getGameObj(msg->receiverid);
    if (!go)
        return ;

    if (msg->deliverytime > getCurTime()) {
        pushDelayMsg(msg);
        return ;
    }

    if (!routeMsgHelper(go, go->state, msg)) {
        routeMsgHelper(go, 0, msg);
    }
}

// 插入时按时间排序
void Router::pushDelayMsg(AIMsg* msg)
{
    for (auto it = _delay_msgs.begin(); it != _delay_msgs.end();)
    {
        if (it->deliverytime > msg->deliverytime)
            _delay_msgs.insert(it, *msg);
        else
            ++it;
    }
}

bool Router::routeMsgHelper(GameObj* go, uint32_t stateid, AIMsg* msg)
{
    // 这里可以找到合适的状态机，然后投递消息
    //switch (go->fsmid) 
    //{
    //   switch xxx:
    //      go->xxxfsm->processMsg(go, stateid, msg);
    //      break;
    //}
    return go->fsm->processMsg(go, stateid, msg);
}

void Router::loop()
{
    checkSendDelayedMsg();
}

void Router::checkSendDelayedMsg()
{
    for (it = _delay_msgs.begin(); it != _delay_msgs.end(); )
    {
        if (it.deliverytime <= getCurTime()) 
        {
            it.besend = true;
            this->routeMsg(&it);
        }
        else
        {
            // 消息队列按时间排序的，这里时间截断了
            break;
        }
    }
}
