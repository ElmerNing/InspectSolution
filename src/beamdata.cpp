#include "beamdata.h"
BeamData::BeamData()
{

}

BeamData::~BeamData()
{

}

void BeamData::Init( uchar* data, int pointQty )
{
    m_data = data;
    m_len = pointQty;
}


