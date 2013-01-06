#ifndef GROUPLAW_SC_H__
#define GROUPLAW_SC_H__
#include "stdafx.h"
#include "grouplaw.h"
#include "beamlaw_sc.h"
#include "material.h"

class Wedge;
class Probe;

class GroupLaw_sc : public GroupLaw
{
public:
    GroupLaw_sc();
    GroupLaw_sc(WeldFill fill) {m_fill = fill;}
    ~GroupLaw_sc();

    virtual void Default();

    //当前group对应的区域
    const WeldFill& Fill() const { return m_fill; }
    WeldFill& Fill() { return m_fill; }
    void Fill(WeldFill val) { m_fill = val; }

    //设置孔径
    int Aperture() const { return m_aperture; }
    void Aperture(int aperture) { m_aperture = aperture; m_lawReady = false; }
    
    //聚焦角度
    float Angle() const { return m_angle; }
    void Angle(float val) { m_angle = qAbs(val); m_lawReady = false;}

    //聚焦深度
    float Depth() const { return m_depth; }
    void Depth(float val) { m_depth = val; m_lawReady = false; }

    //计算聚焦法则
    void GenerateLaw(float offset, const Probe& probe, const Wedge& wedge, const Material& material);

    //GenerateLaw是否计算完成 
    bool LawReady() const { return m_lawReady; }

    //以下Law前缀的函数, 需要GenerateLaw后才能正确调用

    //Tx的中心阵元坐标
    QPointF Law_MidElmPos() const { Q_ASSERT(m_lawReady); return m_midElmPos; }
    
    //Tx的入射点坐标
    float Law_ProbIndex() const { Q_ASSERT(m_lawReady); return m_probIndex; }
    
    //Tx的实际发射角度
    float Law_ActualAngle() const { Q_ASSERT(m_lawReady); return m_actualAngle; }

public:
    virtual float BestSumgain() const;

private:
    //执行GenerateLaw前,需要设置的一些值
    WeldFill m_fill;
    int m_aperture;
    float m_angle;
    float m_depth;

    //是否已经GenerateLaw
    bool m_lawReady;

    //执行GenerateLaw后,得到的计算结果
    BeamLaw_sc m_beamLaw;
    QPointF m_midElmPos;
    float m_probIndex;
    float m_actualAngle;

    SERIALIZE_ENABLE_CLASS(GroupLaw_sc);
};

#endif // grouplaw_sc_h__
