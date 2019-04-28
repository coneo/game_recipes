#pragma once

struct AIMsg
{
    uint32_t msgid = 0;             // 消息ID
    uint32_t senderid = 0;          // 发送者ID
    uint32_t receiverid = 0;        // 接收者ID
    uint64_t deliverytime = 0;      // 投递时间

    // 额外数据
};
