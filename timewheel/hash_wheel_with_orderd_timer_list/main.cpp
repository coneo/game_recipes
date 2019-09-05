#include <thread>
#include "timewheel.h"

int main()
{
    TimeWheel<20> tw(1);

    tw.addTimer(1, 2, [](){printf("test11\n");});
    tw.addTimer(2, 5, [](){printf("test22\n");});
    tw.addTimer(3, 7, [](){printf("test33\n");});

    tw.removeTimer(2);

    while (true)
    {
        uint32_t cur_secs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() / 1000;

        printf("tick %u\n", cur_secs);

        tw.tick(cur_secs);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return 0;
}
