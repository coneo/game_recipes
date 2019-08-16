#include <thread>
#include "timewheel.h"

int main()
{
    TimeWheel tw;

    tw.addTimer(1, 2, [](){printf("test11\n");});
    tw.addTimer(2, 5, [](){printf("test22\n");});
    tw.addTimer(3, 7, [](){printf("test33\n");});

    tw.removeTimer(2);

    while (true)
    {
        printf("tick \n");
        uint32_t cur_secs = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() / 1000;

        tw.tick(cur_secs);

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    return 0;
}
