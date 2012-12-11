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
    //清除
    m_groupLaws.clear();

    //PA
    PaProbeOffset();
    for (auto weldArea=m_weldArea.begin(); weldArea!=m_weldArea.end(); weldArea++)
    {
        for (int i=0; i<weldArea->Division(); i++)
        {
            WeldFill fill (weldArea.key(), i);
            int index = m_groupLaws.size();

            //添加一个关联至fill的通道
            m_groupLaws.append(GroupLaw_sc(fill));
            
            //设置通道孔径
            m_groupLaws[index].Aperture( GetAperture() );
            
            //设置聚焦深度与聚焦发射角度
            float depth = weldArea->Depth() + 
                (index + 0.5f) * weldArea->Thickness() / weldArea->Division();
            m_groupLaws[index].Depth(depth);
            m_groupLaws[index].Angle(weldArea->Angle());

            //设置组为Pa
            m_groupLaws[index].ChannelOfProbe(ProbeChannel::pa);

            //计算
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
        //计算检测某个焊缝区域weldArea,探头偏置需要满足的范围
        QRangeF range = PaProbeOffset_helper(*weldArea);
        ranges.append(range);
    }
    //求取所有range的交集
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

    //设置PA探头的偏置!!!
    m_offset[ProbeChannel::pa] = qRound( 0.5f * (start+end) );
}

QRangeF Solution_sc::PaProbeOffset_helper( const WeldArea& area )
{
    Wedge* wedge = &m_wedges[ProbeChannel::pa];
    Probe* probe = &m_probes[ProbeChannel::pa];

    //没有使用
    if (area.Division() == 0)
        return QRangeF(0, std::numeric_limits<float>::max());

    //聚焦点范围
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

    //折射率
    float rate = wedge->Velocity() / m_material.Velocity();
    //折射角度,入射角度,单位 弧度
    float rAngle, iAngle;
    rAngle = qAbs(area.Angle() * M_PI_180);
    iAngle = qAsin(qSin(rAngle) * rate);

    //探头最大，最小阵元的坐标，
    int eStart = GetAperture() / 2;
    int eEnd = probe->Pa_elmQty() - 1 - eStart;
    QPointF eStartPos = probe->Pa_elmPos(eStart, *wedge);
    QPointF eEndPos = probe->Pa_elmPos(eEnd, *wedge);

    //探头所能覆盖的入射点范围
    float x1 = eStartPos.x() - qAbs(eStartPos.y()) * qTan(iAngle);
    float x2 = eEndPos.x() - qAbs(eEndPos.y()) * qTan(iAngle);
    float probeIndexMin = qMin( x1, x2 );
    float probeIndexMax = qMax( x1, x2 );

    //扫查焊缝区域所需覆盖的入射点范围
    float probeIndexStart = focusStart.y() * qTan(rAngle);
    float probeIndexEnd = focusEnd.y() * qTan(rAngle);

    //探头偏移
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