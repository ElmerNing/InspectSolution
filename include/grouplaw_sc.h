#ifndef SCGROUPLAW_H
#define SCGROUPLAW_H

#include "grouplaw.h"

class SCgroupLaw : public GroupLaw
{
public:
    SCgroupLaw();
    ~SCgroupLaw();

private:
    SERIALIZE_ENABLE_CLASS(SCgroupLaw);
};
#endif // SCGROUPLAW_H
