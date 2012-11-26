#ifndef SCGROUPLAW_H
#define SCGROUPLAW_H

#include "grouplaw.h"
#include "qobjvector.h"

class SCgroupLaw : public GroupLaw
{
public:
    SCgroupLaw(QObject *parent = NULL);
    ~SCgroupLaw();

private:

    SERIALIZE_ENABLE_CLASS(SCgroupLaw);
};

typedef QObjectVector<SCgroupLaw> SCgroupLawVector;

#endif // SCGROUPLAW_H