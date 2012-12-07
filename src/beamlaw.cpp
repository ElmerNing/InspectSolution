#include "stdafx.h"
#include "beamlaw.h"

BeamLaw::BeamLaw() 
{
    Default();
}

BeamLaw::~BeamLaw()
{
}

void BeamLaw::Default()
{
    m_activeElems = 1;
    m_rxFirst = 1;
    m_txFirst = 1;
    m_angle = 0;
    m_screwAngle = 0;
    m_gainOffset = 0;
    m_focusDepthType = DepthType::DT_BEAM_PATH;
    m_focusDepth = 30;
    m_gateRange[Gate::GATE_A] = QRangeF(0, 30);
    m_gateRange[Gate::GATE_B] = QRangeF(0, 30);
    m_gateRange[Gate::GATE_I] = QRangeF(0, 30);
}

//序列化
SERIALIZE_BEGIN(BeamLaw)
    SERIALIZE_VAR(m_activeElems)
    SERIALIZE_VAR(m_txFirst)
    SERIALIZE_VAR(m_rxFirst)
    SERIALIZE_VAR(m_angle)
    SERIALIZE_VAR(m_screwAngle)
    SERIALIZE_VAR(m_focusDepthType)
    SERIALIZE_VAR(m_focusDepth)
    SERIALIZE_VAR(m_gateRange)
    SERIALIZE_VAR(m_gainOffset)
    SERIALIZE_VAR(m_beamDelay)
SERIALIZE_END

//反序列化
DE_SERIALIZE_BEGIN(BeamLaw)
    DE_SERIALIZE_VAR(m_activeElems)
    DE_SERIALIZE_VAR(m_txFirst)
    DE_SERIALIZE_VAR(m_rxFirst)
    DE_SERIALIZE_VAR(m_angle)
    DE_SERIALIZE_VAR(m_screwAngle)
    DE_SERIALIZE_VAR(m_focusDepthType)
    DE_SERIALIZE_VAR(m_focusDepth)
    DE_SERIALIZE_VAR(m_gateRange)
    DE_SERIALIZE_VAR(m_gainOffset)
    DE_SERIALIZE_VAR(m_beamDelay)
DE_SERIALIZE_END

