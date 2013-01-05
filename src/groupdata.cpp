#include "groupdata.h"
GroupData::GroupData()
{

}

GroupData::~GroupData()
{

}

void GroupData::Init( uchar* data, int beamQty, int pointQty )
{
    m_beams.resize(beamQty);
    uchar* beamData = data;
    for (int beamId = 0; beamId < m_beams.size(); beamId++)
    {
        m_beams[beamId].Init(data, pointQty);
        beamData += (pointQty + BeamData::BEAM_PONIT_DELT);
    }
}

