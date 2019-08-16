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
        _all_timers.push_back(entry);
    }

    void removeTimer(uint32_t timer_id)
    {
        _all_timers.remove_if([&](TimerEntry& t){ 
                              return t.timerid == timer_id;
                              });
    }

    void tick(const uint32_t& cur_secs)
    {
        auto it = _all_timers.begin();
        for (; it != _all_timers.end();)
        {
            if (it->duetime <= cur_secs)
            {
                _due_timers.push_back(*it);
                it = _all_timers.erase(it);
            }
            else
            {
                ++it;
            }
        }

        if (!_due_timers.empty())
        {
            for (const auto& it : _due_timers)
            {
                it.callback();
            }
            _due_timers.clear();
        }
    }

private:

    std::list<TimerEntry> _all_timers;

    std::list<TimerEntry> _due_timers;
};
