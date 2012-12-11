#include "stdafx.h"
#include "solution_sc.h"
#include <math.h>

static inline int GetAperture()
{
    return 16;
}

Solution_sc::Solution_sc()
{
    m_probes[ProbeChannel::pa] = Probe(ProbeType::PT_PA);
    m_probes[ProbeChannel::ut1] = Probe(ProbeType::PT_UT);
    m_probes[ProbeChannel::ut2] = Probe(ProbeType::PT_UT);

    m_wedges[ProbeChannel::pa] = Wedge(WedgeType::WT_PA);
    m_wedges[ProbeChannel::ut1] = Wedge(WedgeType::WT_UT);
    m_wedges[ProbeChannel::ut2] = Wedge(WedgeType::WT_UT);

    m_offset[ProbeChannel::pa] = 0;
    m_offset[ProbeChannel::ut1] = 0;
    m_offset[ProbeChannel::ut2] = 0;
}

Solution_sc::~Solution_sc()
{

}

bool Solution_sc::AutoGenerate()
{
    //���
    m_groupLaws.clear();

    //PA
    PaProbeOffset();
    for (auto weldArea=m_weldArea.begin(); weldArea!=m_weldArea.end(); weldArea++)
    {
        for (int i=0; i<weldArea->Division(); i++)
        {
            WeldFill fill (weldArea.key(), i);
            int index = m_groupLaws.size();

            //���һ��������fill��ͨ��
            m_groupLaws.append(GroupLaw_sc(fill));
            
            //����ͨ���׾�
            m_groupLaws[index].Aperture( GetAperture() );
            
            //���þ۽������۽�����Ƕ�
            float depth = weldArea->Depth() + 
                (index + 0.5f) * weldArea->Thickness() / weldArea->Division();
            m_groupLaws[index].Depth(depth);
            m_groupLaws[index].Angle(weldArea->Angle());

            //������ΪPa
            m_groupLaws[index].ChannelOfProbe(ProbeChannel::pa);

            //����
            m_groupLaws[index].GenerateLaw(
                m_offset[ProbeChannel::pa],
                m_probes[ProbeChannel::pa],
                m_wedges[ProbeChannel::pa],
                m_material
            );
        }
    }

    //TOFD
    //////
    return true;
}

void Solution_sc::PaProbeOffset()
{
    QVector<QRangeF> ranges;
    for (auto weldArea=m_weldArea.begin(); weldArea!=m_weldArea.end(); weldArea++)
    {
        //������ĳ����������weldArea,̽ͷƫ����Ҫ����ķ�Χ
        QRangeF range = PaProbeOffset_helper(*weldArea);
        ranges.append(range);
    }
    //��ȡ����range�Ľ���
    QRangeF r( 0, std::numeric_limits<float>::max());
    foreach (QRangeF range, ranges)
    {
        float start = qMax(range.Start(), r.Start());
        float end = qMin(range.End(), r.End());
        r.Start(start);
        r.End(end);
    }

    int start = qCeil( r.Start() );
    int end = qFloor( r.End() );

    //����PA̽ͷ��ƫ��!!!
    m_offset[ProbeChannel::pa] = qRound( 0.5f * (start+end) );
}

QRangeF Solution_sc::PaProbeOffset_helper( const WeldArea& area )
{
    Wedge* wedge = &m_wedges[ProbeChannel::pa];
    Probe* probe = &m_probes[ProbeChannel::pa];

    //û��ʹ��
    if (area.Division() == 0)
        return QRangeF(0, std::numeric_limits<float>::max());

    //�۽��㷶Χ
    QPointF focusStart(0,0), focusEnd(0,0);
    if (area.Angle() >= 0)
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
    float rate = wedge->Velocity() / m_material.Velocity();
    //����Ƕ�,����Ƕ�,��λ ����
    float rAngle, iAngle;
    rAngle = qAbs(area.Angle() * M_PI_180);
    iAngle = qAsin(qSin(rAngle) * rate);

    //̽ͷ�����С��Ԫ�����꣬
    int eStart = GetAperture() / 2;
    int eEnd = probe->Pa_elmQty() - 1 - eStart;
    QPointF eStartPos = probe->Pa_elmPos(eStart, *wedge);
    QPointF eEndPos = probe->Pa_elmPos(eEnd, *wedge);

    //̽ͷ���ܸ��ǵ�����㷶Χ
    float x1 = eStartPos.x() - qAbs(eStartPos.y()) * qTan(iAngle);
    float x2 = eEndPos.x() - qAbs(eEndPos.y()) * qTan(iAngle);
    float probeIndexMin = qMin( x1, x2 );
    float probeIndexMax = qMax( x1, x2 );

    //ɨ�麸���������踲�ǵ�����㷶Χ
    float probeIndexStart = focusStart.y() * qTan(rAngle);
    float probeIndexEnd = focusEnd.y() * qTan(rAngle);

    //̽ͷƫ��
    float maxOffset = probeIndexStart - probeIndexMin;
    float minOffset = probeIndexEnd - probeIndexMax;
    return QRangeF(minOffset, maxOffset);
}

SERIALIZE_BEGIN(Solution_sc)
    SERIALIZE_VAR(m_config)
    SERIALIZE_VAR(m_material)
    SERIALIZE_VAR(m_probes)
    SERIALIZE_VAR(m_wedges)
    SERIALIZE_VAR(m_offset)
    SERIALIZE_VAR(m_weldArea)
    SERIALIZE_VAR(m_groupLaws)
SERIALIZE_END

DE_SERIALIZE_BEGIN(Solution_sc)
    DE_SERIALIZE_VAR(m_config)
    DE_SERIALIZE_VAR(m_material)
    DE_SERIALIZE_VAR(m_probes)
    DE_SERIALIZE_VAR(m_wedges)
    DE_SERIALIZE_VAR(m_offset)
    DE_SERIALIZE_VAR(m_weldArea)
    DE_SERIALIZE_VAR(m_groupLaws)
DE_SERIALIZE_END