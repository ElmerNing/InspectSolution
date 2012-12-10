#include "stdafx.h"
#include "solution_sc.h"
#include <math.h>

Solution_sc::Solution_sc()
{
    m_probes[ProbeChannel::pa] = Probe(ProbeType::PT_PA);
    m_probes[ProbeChannel::ut1] = Probe(ProbeType::PT_UT);
    m_probes[ProbeChannel::ut2] = Probe(ProbeType::PT_UT);

    m_wedges[ProbeChannel::pa] = Wedge(WedgeType::WT_PA);
    m_wedges[ProbeChannel::ut1] = Wedge(WedgeType::WT_UT);
    m_wedges[ProbeChannel::ut2] = Wedge(WedgeType::WT_UT);
}

Solution_sc::~Solution_sc()
{

}

bool Solution_sc::Generate()
{
    //���
    m_groupLaws.clear();

    //PA

    //
    return true;
}

void Solution_sc::PaProbeOffset()
{
    for (auto weldArea=m_weldArea.begin(); weldArea!=m_weldArea.end(); weldArea++)
    {
        WeldArea* area = &(*weldArea);
        QRangeF range = PAProbeOffset_help(area);
    }
}

QRangeF Solution_sc::ProbeOffset_help( const WeldArea& area )
{
    //�۽��㷶Χ
    QPointF focusStart(0,0), focusEnd(0,0);
    if (area.Angle() >= area)
    {
        focusStart.ry() = area.Depth();
        focusEnd.ry() = focusStart.ry() + area.Thickness();
    }
    else
    {
        focusEnd.ry() = 2*m_material.Thickness() - area.Depth();
        focusStart.ry() =  focusEnd.ry() - area.Thickness();
    }

    //������
    float rate = m_wedges[ProbeChannel::pa].Velocity() / m_material.Velocity();
    //����Ƕ�,����Ƕ�,��λ ����
    float rAngle, iAngle;
    rAngle = qAbs(area.Angle() * M_PI_180);
    iAngle = qAsin(qSin(rAngle) * rate);

    //����̽ͷ�����С��Ԫ�����꣬
    //�˴����㣬��Ш��Ķ���Ϊԭ��
    int eStart = GetAperture() / 2 ;
    int eEnd = m_probes[ProbeChannel::pa].Pa_elmQty() - 1 - eStart;

    PointF
    
    /*
    QPointF elmPosStart = GetElementPos(probe, wedge, 0, elmStart);
    QPointF elmPosEnd = GetElementPos(probe, wedge, 0, elmEnd);

    float x1 = elmPosStart.x() - qAbs(elmPosStart.y()) * qTan(incidenceAngle);
    float x2 = elmPosEnd.x() - qAbs(elmPosEnd.y()) * qTan(incidenceAngle);

    float probeIndex_elmStart = qMin( x1, x2 );
    float probeIndex_elmEnd = qMax(x1, x2);

    //����㷶Χ
    //�˴�����ԭ���ں���������
    float probeIndexStart = focusStart.y() * qTan(refractAngle);
    float probeIndexEnd = focusEnd.y() * qTan(refractAngle);

    //̽ͷ�����Сƫ��
    float maxOffset = probeIndexStart - probeIndex_elmStart;
    float minOffset = probeIndexEnd - probeIndex_elmEnd;

    return QRangeF(minOffset, maxOffset);*/

}

SERIALIZE_BEGIN(Solution_sc)
    
SERIALIZE_END

DE_SERIALIZE_BEGIN(Solution_sc)
   
DE_SERIALIZE_END