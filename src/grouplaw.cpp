#include "stdafx.h"
#include "grouplaw.h"

GroupLaw::GroupLaw() 
{
    Default();
}

GroupLaw::~GroupLaw()
{
}

void GroupLaw::Default()
{
    m_gain = 0.0f;
    m_gainRef = 0.0f;

    m_start = 0.0f;
    m_range = 75.0f;

    m_rectifier = RectifierMode::RM_WAVE;

    m_isVideoFilter = false;

    m_freq = FreqBand::FB_NONE;

    m_sumgain = BestSumgain();

    m_thickFactor = 0.0f;

    m_probe = ProbeChannel::pa;

    m_gateHeight[Gate::GATE_A] = 5;
    m_gateLogic[Gate::GATE_A] = LogicMode::LM_WAVE_PEAK;
    m_gateHeight[Gate::GATE_B] = 5;
    m_gateLogic[Gate::GATE_B] = LogicMode::LM_WAVE_PEAK;
    m_gateHeight[Gate::GATE_I] = 5;
    m_gateLogic[Gate::GATE_I] = LogicMode::LM_WAVE_PEAK;

    m_Average = AverageMode::AM_1;

    m_ttl = TTLSource::TS_Av;

    m_hicknessMax = 99999;

    m_pulseWidth = 100;

}

//序列化
SERIALIZE_BEGIN(GroupLaw)
    SERIALIZE_VAR(m_gain)
    SERIALIZE_VAR(m_gainRef)
    SERIALIZE_VAR(m_start)
    SERIALIZE_VAR(m_range)
    SERIALIZE_VAR(m_rectifier)
    SERIALIZE_VAR(m_isVideoFilter)
    SERIALIZE_VAR(m_freq)
    SERIALIZE_VAR(m_sumgain)
    SERIALIZE_VAR(m_thickFactor)
    SERIALIZE_VAR(m_gateHeight)
    SERIALIZE_VAR(m_gateLogic)
    SERIALIZE_VAR(m_Average)
    SERIALIZE_VAR(m_ttl)
    SERIALIZE_VAR(m_hicknessMax)
    SERIALIZE_VAR(m_pulseWidth)
    SERIALIZE_VAR(m_probe)
SERIALIZE_END

//反序列化
DE_SERIALIZE_BEGIN(GroupLaw)
    DE_SERIALIZE_VAR(m_gain)
    DE_SERIALIZE_VAR(m_gainRef)
    DE_SERIALIZE_VAR(m_start)
    DE_SERIALIZE_VAR(m_range)
    DE_SERIALIZE_VAR(m_rectifier)
    DE_SERIALIZE_VAR(m_isVideoFilter)
    DE_SERIALIZE_VAR(m_freq)
    DE_SERIALIZE_VAR(m_sumgain)
    DE_SERIALIZE_VAR(m_thickFactor)
    DE_SERIALIZE_VAR(m_gateHeight)
    DE_SERIALIZE_VAR(m_gateLogic)
    DE_SERIALIZE_VAR(m_Average)
    DE_SERIALIZE_VAR(m_ttl)
    DE_SERIALIZE_VAR(m_hicknessMax)
    DE_SERIALIZE_VAR(m_pulseWidth)
    DE_SERIALIZE_VAR(m_probe)
DE_SERIALIZE_END
