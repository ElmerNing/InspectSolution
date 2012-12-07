#include "stdafx.h"
#include "solution.h"

Solution::Solution(QObject* parent)
    :QObject(parent)
    ,m_config(this)
{
}

Solution::~Solution()
{
}

void Solution::Default()
{
    m_probe[ProbeChannel::pa] = new Probe(this);
    m_probe[ProbeChannel::ut1] = new Probe(this);
    m_probe[ProbeChannel::ut2] = new Probe(this);

    m_wedge[ProbeChannel::pa] = new Wedge(this);
    m_wedge[ProbeChannel::ut1] = new Wedge(this);
    m_wedge[ProbeChannel::ut2] = new Wedge(this);
}

SERIALIZE_BEGIN(Solution)
    SERIALIZE_VAR(m_config)
    SERIALIZE_VAR(m_velocity)
    SERIALIZE_VAR(m_wedge)
    SERIALIZE_VAR(m_probe)
SERIALIZE_END

DE_SERIALIZE_BEGIN(Solution)
    DE_SERIALIZE_VAR(m_config)
    DE_SERIALIZE_VAR(m_velocity)
    DE_SERIALIZE_VAR(m_wedge)
    DE_SERIALIZE_VAR(m_probe)
DE_SERIALIZE_END

