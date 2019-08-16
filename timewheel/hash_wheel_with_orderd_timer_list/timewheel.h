#pragma once
#include <stdio.h>
#include <cstdint>
#include <string>
#include <list>
#include <chrono>
#include <functional>

struct TimerEntry
{
    uint32_t timerid = 0;
    uint32_t duetime = 0;
    std::function<void()> callback;
};

template <typename BUCKET_SIZE>
class TimeWheel
{
public:
    void addTimer(uint32_t timerid, uint32_t delay, std::function<void()> cb)
    {
        uint32_t bucket = (_cur_pos + delay / _interval) % BUCKET_SIZE;

        TimerEntry entry;
        entry.timerid = timerid;
        entry.duetime = delay;
        entry.callback = cb;

        auto& bucket_data = _all_timers[bucket];
        auto it = bucket_data.begin();
        for (; it != bucket_data.end(); )
        {
            if (entry.duetime < it->duetime)
            {
                bucket_data.insert(it, entry);
                break;
            }
            else
            {
                ++it;
            }
        }

        if (it == bucket_data.end())
        {
            bucket_data.push_back(entry);
        }
    }

    void removeTimer(uint32_t timer_id)
    {
        _all_timers.remove_if([&](TimerEntry& t){ 
                              return t.timerid == timer_id;
                              });
    }

    void tick(const uint32_t& cur_secs)
    {
        while (!_all_timers.empty() && _all_timers.front().duetime <= cur_secs)
        {
            TimerEntry t = _all_timers.front();
            _all_timers.pop_front();
            t.callback();
        }
    }

private:

    // 时间轮多久转动一次
    uint32_t _interval = 0;

    // 当前的刻度
    uint32_t _cur_pos = 0;

    // timer数据
    std::list<TimerEntry> _all_timers[BUCKET_SIZE];
};
