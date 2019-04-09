#include <unistd.h>
#include "entity.h"

int main()
{
    Entity e;
    while (true) {
        ++ e._testid; // 测试条件变化
        usleep(100000);
        e.loop();
    }
}
