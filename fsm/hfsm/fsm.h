#ifndef _FSM_H
#define _FSM_H

struct FSMTransition
{
    uint32_t transition = 0;
    uint32_t out = 0;
};
using TransitionGroup = std::vector<FSMTransition>;

class FSM
{
public:
    FSM(){}

    void init();

    // 添加转换事件
    void addTransition(uint32_t start, uint32_t tran, uint32_t out);

    // 切换到状态
    void changeNextState(uint32_t state);

    // 实际切换状态
    void doChangeState();

    // 主循环
    void loop();

private:

    // 当前状态
    uint32 _cur_state = 0;

    // 下一个要切换到的状态
    uint32 _next_state = 0;

    // 转换事件列表
    std::map<uint32_t, TransitionGroup> _transitions;
};
#endif // _FSM_H
