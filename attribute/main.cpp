#include "attrinfo.h"
#include <iostream>

int main()
{
    AttrInfo info;
    info.set_maxhp(33);
    info.set_attack(44);

    std::cout << info.get_maxhp() << " " << info.get_attack() << std::endl;
}
