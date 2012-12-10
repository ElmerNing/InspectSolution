#ifndef SCGROUPLAW_H
#define SCGROUPLAW_H

#include "grouplaw.h"

class GroupLaw_sc : public GroupLaw
{
public:
    GroupLaw_sc();
    ~GroupLaw_sc();

private:
    SERIALIZE_ENABLE_CLASS(GroupLaw_sc);
};
#endif // SCGROUPLAW_H
