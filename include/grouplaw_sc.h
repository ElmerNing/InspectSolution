#ifndef GROUPLAW_SC_H__
#define GROUPLAW_SC_H__

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

    //��ǰgroup��Ӧ������
    const WeldFill& Fill() const { return m_fill; }
    WeldFill& Fill() { return m_fill; }
    void Fill(WeldFill val) { m_fill = val; }

    //���ÿ׾�
    int Aperture() const { return m_aperture; }
    void Aperture(int aperture) { m_aperture = aperture; m_lawReady = false; }
    
    //�۽��Ƕ�
    float Angle() const { return m_angle; }
    void Angle(float val) { m_angle = qAbs(val); m_lawReady = false;}

    //�۽����
    float Depth() const { return m_depth; }
    void Depth(float val) { m_depth = val; m_lawReady = false; }

    //����۽�����
    void GenerateLaw(float offset, const Probe& probe, const Wedge& wedge, const Material& material);

    //GenerateLaw�Ƿ������� 
    bool LawReady() const { return m_lawReady; }

    //����Lawǰ׺�ĺ���, ��ҪGenerateLaw�������ȷ����

    //Tx��������Ԫ����
    QPointF Law_MidElmPos() const { Q_ASSERT(m_lawReady); return m_midElmPos; }
    
    //Tx�����������
    float Law_ProbIndex() const { Q_ASSERT(m_lawReady); return m_probIndex; }
    
    //Tx��ʵ�ʷ���Ƕ�
    float Law_ActualAngle() const { Q_ASSERT(m_lawReady); return m_actualAngle; }

public:
    virtual float BestSumgain() const;

private:
    //ִ��GenerateLawǰ,��Ҫ���õ�һЩֵ
    WeldFill m_fill;
    int m_aperture;
    float m_angle;
    float m_depth;

    //�Ƿ��Ѿ�GenerateLaw
    bool m_lawReady;

    //ִ��GenerateLaw��,�õ��ļ�����
    BeamLaw_sc m_beamLaw;
    QPointF m_midElmPos;
    float m_probIndex;
    float m_actualAngle;

    SERIALIZE_ENABLE_CLASS(GroupLaw_sc);
};

#endif // grouplaw_sc_h__
