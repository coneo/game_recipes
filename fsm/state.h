#pragma once

class Entity;

class State
{
public:
    virtual ~State() {}

    // 状态进入回调
    virtual void enter(Entity* e) = 0;

    // 状态退出回调
    virtual void exit(Entity* e) = 0;

    // 状态更新回调
    virtual void execute(Entity* e) = 0;

private:
    // 状态唯一编号
    uint32_t _id = 0;
};
