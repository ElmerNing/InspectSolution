#include "grouplaw_sc.h"
#include "wedge.h"
#include "probe.h"

//计算入射点位置
float ComputeProbeIndex_helper(
    const QPointF& elemPos, const QPointF& focusPos , 
    const float& rate, const float& epl, 
    float& start, float& end)
{
    float x1 = elemPos.x();
    float y1 = elemPos.y();
    float x2 = focusPos.x();
    float y2 = focusPos.y();
    float x0 = (start + end)/2.0f;
    float y0 = 0;

    float sin1 = qAbs(x1-x0) / qSqrt( (x1-x0)*(x1-x0) + (y1-y0)*(y1-y0) );
    float sin2 = qAbs(x2-x0) / qSqrt( (x2-x0)*(x2-x0) + (y2-y0)*(y2-y0) );

    float newrate = sin1/sin2;

    if (qAbs(newrate - rate) < epl)
        return x0;
    else if (newrate > rate)
        start = x0;
    else
        end = x0;
    
    return ComputeProbeIndex_helper(elemPos, focusPos, 
        rate, epl, 
        start, end);
}

static QPointF ComputeProbeIndex(QPointF elmPos, QPointF focusPos, float rate)
{
    float xstart = 0;
    float xend = elmPos.x();
    float x = ComputeProbeIndex_helper(elmPos, focusPos, rate, 0.001f, xstart, xend );
    float y = 0;
    return QPointF(x, y);
}

GroupLaw_sc::GroupLaw_sc()
{

}

GroupLaw_sc::~GroupLaw_sc()
{

}

void GroupLaw_sc::Default()
{
    GroupLaw::Default();
    m_aperture = 16;
    m_angle = 30.0f;
    m_depth = 20.0f;
}

void GroupLaw_sc::GenerateLaw(float offset, const Probe& probe, const Wedge& wedge, const Material& material)
{
    //折射率,聚焦点,阵元坐标,折射率,入射点位置    
    float rate;
    rate = wedge.Velocity() / material.Velocity();

    QPointF focusPos(0, m_depth);
    if (m_angle < 0)  //有一次反射的时候, 做镜面映射
        focusPos.ry() = 2 * material.Thickness() - focusPos.y();

    QVector<QPointF> elemPos(probe.Pa_elmQty());
    for (int i=0; i<elemPos.size(); i++)
        elemPos[i] = probe.Pa_elmPos(i, wedge, offset);

    QVector<QPointF> probeIndexPos(probe.Pa_elmQty());
    for (int i=0; i<probeIndexPos.size(); i++)
        probeIndexPos[i] = ComputeProbeIndex(elemPos[i], focusPos, rate);
    
    //最佳孔径位置startElm
    int startElm = 0;
    float bestSin = qSin(qAbs(m_angle * M_PI_180));
    float actualSin = bestSin + 1;    //发射角度
    for (int start = 0; 
        start < probe.Pa_elmQty() - m_aperture - 1; 
        start++)
    {
        int center = start + (m_aperture>>1);
        float sin = 0.0f, probeIndex = 0.0;
        QPointF midElm(0,0);
        int aver = (m_aperture&1) == 0 ? 2 : 1;
        for (int i=0; i<aver; i++)
        {
            float x = probeIndexPos[center-i].x() - focusPos.x();
            float y = probeIndexPos[center-i].y() - focusPos.y();
            sin += qAbs(x) / qSqrt(x*x + y*y);
            probeIndex += probeIndexPos[center-i].x();
            midElm += elemPos[center-i];
        }
        sin = sin / aver;
        probeIndex = probeIndex / aver;
        midElm /= (float)aver;
        if (qAbs(sin-bestSin) < qAbs(actualSin - bestSin))
        {
            actualSin = sin;
            m_probIndex = probeIndex;
            startElm = start;
        }
    }
    m_actualAngle = qAsin(actualSin) * M_180_PI;

    //计算每个阵元的声程
    QVector<float> flyTime(elemPos.size());  //单位 ms
    float maxFlyTime = 0;
    for (int i=startElm; i<startElm+m_aperture; i++)
    {
        float x1 = elemPos[i].x() - probeIndexPos[i].x();
        float y1 = elemPos[i].y() - probeIndexPos[i].y();
        float x2 = focusPos.x() - probeIndexPos[i].x();
        float y2 = focusPos.y() - probeIndexPos[i].y();
        float weldDist = qSqrt(x2*x2 + y2*y2);
        float wedgeDist = qSqrt(x1*x1 + y1*y1);
        flyTime[i] = weldDist/material.Velocity() + wedgeDist/wedge.Velocity();
        if (flyTime[i] > maxFlyTime)
            maxFlyTime = flyTime[i];
    }

    //设置BeamLaw
    m_beamLaw.ActiveElems(m_aperture);
    m_beamLaw.RxFirst(startElm);
    m_beamLaw.TxFirst(startElm);
    for (int i=startElm; i<startElm+m_aperture; i++)
    {
        ushort delay = ushort(qAbs(flyTime[i] - maxFlyTime)*1000000);
        if (delay > 25560)
            delay = 25560;
        m_beamLaw.TxDelay(i-startElm, delay);
        m_beamLaw.RxDelay(i-startElm, delay);
    }

    //法则计算完毕
    m_lawReady = true;
}

float GroupLaw_sc::BestSumgain() const
{
    /*
    int averElm = 0;
    for (int i=0; i<m_beamLaws.size(); i++)
    {
        averElm += m_beamLaws[i].ActiveElems();
    }

    if (m_beamLaws.size() != 0)
        averElm = averElm / m_beamLaws.size();
    else
        averElm = 1;*/
    int sumgain = m_aperture<2 ? 4095 : (6400/m_aperture);
    return 20 * log10(sumgain / 16.0f);
}

SERIALIZE_BEGIN(GroupLaw_sc)
    SERIALIZE_BASE(GroupLaw)
    SERIALIZE_VAR(m_fill)
    SERIALIZE_VAR(m_aperture)
    SERIALIZE_VAR(m_angle)
    SERIALIZE_VAR(m_depth)
    SERIALIZE_VAR(m_lawReady)
    SERIALIZE_VAR(m_beamLaw)
    SERIALIZE_VAR(m_midElmPos)
    SERIALIZE_VAR(m_probIndex)
    SERIALIZE_VAR(m_actualAngle)
SERIALIZE_END

DE_SERIALIZE_BEGIN(GroupLaw_sc)
    DE_SERIALIZE_BASE(GroupLaw)
    DE_SERIALIZE_VAR(m_fill)
    DE_SERIALIZE_VAR(m_aperture)
    DE_SERIALIZE_VAR(m_angle)
    DE_SERIALIZE_VAR(m_depth)
    DE_SERIALIZE_VAR(m_lawReady)
    DE_SERIALIZE_VAR(m_beamLaw)
    DE_SERIALIZE_VAR(m_midElmPos)
    DE_SERIALIZE_VAR(m_probIndex)
    DE_SERIALIZE_VAR(m_actualAngle)
DE_SERIALIZE_END