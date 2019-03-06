#ifndef _ATTR_INFO_H
#define _ATTR_INFO_H

#include <stdint.h>

class AttrInfo
{
public:
    AttrInfo(){}

#define CTRL_ATTR(attr, type, name)\
    uint32_t get_##attr() { return _##attr; }
#include "attrdef.h"
#undef CTRL_ATTR

#define CTRL_ATTR(attr, type, name)\
    void set_##attr(uint32_t v) { _##attr = v; }
#include "attrdef.h"
#undef CTRL_ATTR

private:

#define CTRL_ATTR(attr, type, name)\
    uint32_t _##attr;
#include "attrdef.h"
#undef CTRL_ATTR
};

#endif // _ATTR_INFO_H
