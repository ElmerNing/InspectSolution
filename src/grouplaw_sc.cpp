#include "stdafx.h"
#include "grouplaw_sc.h"

SCgroupLaw::SCgroupLaw()
{

}

SCgroupLaw::~SCgroupLaw()
{

}

SERIALIZE_BEGIN(SCgroupLaw)
    SERIALIZE_BASE(GroupLaw)
SERIALIZE_END

DE_SERIALIZE_BEGIN(SCgroupLaw)
    DE_SERIALIZE_BASE(GroupLaw)
DE_SERIALIZE_END