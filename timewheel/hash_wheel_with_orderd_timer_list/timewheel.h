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

template <int BUCKET_SIZE>
class TimeWheel
{
public:
    TimeWheel(uint32_t interval) : _interval(interval)
    {
    }

    void addTimer(uint32_t timerid, uint32_t delay, std::function<void()> cb)
    {
        uint32_t bucket = (_cur_pos + delay / _interval + 1) % BUCKET_SIZE; //FIXME

        uint32_t cur_secs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() / 1000;

        TimerEntry entry;
        entry.timerid = timerid;
        entry.duetime = delay + cur_secs;
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
        for (int i = 0; i < BUCKET_SIZE; ++i)
        {
            _all_timers[i].remove_if([&](TimerEntry& t){ 
                                  return t.timerid == timer_id;
                                  });
        }
    }

    void tick(const uint32_t& cur_secs)
    {
        if (_last_step_time + _interval > cur_secs)
            return ;

        _cur_pos = (_cur_pos + 1) % BUCKET_SIZE;
        auto& timers = _all_timers[_cur_pos];
        while (!timers.empty() && timers.front().duetime <= cur_secs)
        {
            TimerEntry t = timers.front();
            timers.pop_front();
            t.callback();
        }
        _last_step_time = cur_secs;
    }

private:

    // 时间轮多久转动一次
    uint32_t _interval = 0;

    // 当前的刻度
    uint32_t _cur_pos = 0;

    // 上次刻度跳转时间
    uint64_t _last_step_time = 0;

    // timer数据
    std::list<TimerEntry> _all_timers[BUCKET_SIZE];
};
