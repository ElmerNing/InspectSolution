#include "blockdata.h"

SERIALIZE_BEGIN(BlockInfo)
    SERIALIZE_VAR(m_beamQty)
    SERIALIZE_VAR(m_beamPointQty)
SERIALIZE_END

DE_SERIALIZE_BEGIN(BlockInfo)
    DE_SERIALIZE_VAR(m_beamQty)
    DE_SERIALIZE_VAR(m_beamPointQty)
DE_SERIALIZE_END


BlockData::BlockData(void)
{
}


BlockData::~BlockData(void)
{
}

void BlockData::Init( uchar* data, const BlockInfo& info )
{
    m_data = data;
    m_groups.resize( info.GetGrpQty() );
    uchar* groupdata = data; 
    for (int grpId=0; grpId<m_groups.size(); grpId++)
    {
        m_groups[grpId].Init( groupdata, info.GetBeamQty(grpId), info.GetBeamPointQty(grpId) );
        groupdata += info.GetGrpDataSize(grpId);
    }
}
