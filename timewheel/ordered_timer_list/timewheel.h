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

class TimeWheel
{
public:
    void addTimer(uint32_t timerid, uint32_t timestamp, std::function<void()> cb)
    {
        TimerEntry entry;
        entry.timerid = timerid;
        entry.duetime = timestamp;
        entry.callback = cb;

        auto it = _all_timers.begin();
        for (; it != _all_timers.end(); )
        {
            if (entry.duetime < it->duetime)
            {
                _all_timers.insert(it, entry);
                break;
            }
            else
            {
                ++it;
            }
        }

        if (it == _all_timers.end())
        {
            _all_timers.push_back(entry);
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

    std::list<TimerEntry> _all_timers;
};
