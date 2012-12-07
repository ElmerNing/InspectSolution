#ifndef BEAMLAW_H
#define BEAMLAW_H

#include "solutionmodule.h"
#include "qrange.h"

//3��̽ͷͨ��
enum ProbeChannel
{
    pa = 0,
    ut1 = 1,
    ut2 = 2,
};
SERIALIZE_ENABLE_ENUM(ProbeChannel);

//բ��
enum Gate
{
    GATE_A,
    GATE_B,
    GATE_I,
};
SERIALIZE_ENABLE_ENUM(Gate);

//���ģʽ
enum DepthType
{
    DT_BEAM_PATH = 0,   //������
    DT_TRUE_DEPTH = 1,  //��ʵ���
};
SERIALIZE_ENABLE_ENUM(DepthType);

class BeamLaw
{
public:

    explicit BeamLaw();
    virtual ~BeamLaw();

    //����ΪĬ��ֵ
    void Default();

    //������Ԫ��, �ı��ͬʱ�ı�group��sumgain,����ʵ��
    int ActiveElems() const { return m_activeElems; }
    void ActiveElems(int val) { m_activeElems = val; }
    //������ʼ��Ԫ
    int TxFirst() const { return m_txFirst; }
    void TxFirst(int val) { m_txFirst = val; }
    //������ʼ��Ԫ
    int RxFirst() const { return m_rxFirst; }
    void RxFirst(int val) { m_rxFirst = val; }
    //�۽��Ƕ�
    float Angle() const { return m_angle; }
    void Angle(float val) { m_angle = val; }
    //�۽�ת���
    float ScrewAngle() const { return m_screwAngle; }
    void ScrewAngle(float val) { m_screwAngle = val; }
    //�۽��������
    DepthType FocusDepthType() const { return m_focusDepthType; }
    void FocusDepthType(DepthType val) { m_focusDepthType = val; }
    //�۽����,FocusDepthType��ͬ,�в�ͬ��������
    float FocusDepth() const { return m_focusDepth; }
    void FocusDepth(float val) { m_focusDepth = val; }
    //բ�Ų�����Χ
    QRangeF GateRange(Gate gate) { return m_gateRange[gate]; }
    QRangeF GateRange(Gate gate, QRangeF range) { m_gateRange[gate] = range; }

private:
    //������Ԫ��(1-32)
    int m_activeElems;
    //������ʼ��Ԫ
    int m_txFirst;
    //������ʼ��Ԫ
    int m_rxFirst;
    //�۽��Ƕ�
    float m_angle;
    //�۽�ת���
    float m_screwAngle;
    //�۽��������
    DepthType m_focusDepthType;
    //�۽����
    float m_focusDepth;
    //բ�ŷ�Χ
    QMap< Gate, QRangeF > m_gateRange;
    //���油��(db,�ֱ���0.1db)
    float m_gainOffset;
    //�����ӳ�(us, �ֱ���10ns)
    float m_beamDelay;
    
    SERIALIZE_ENABLE_CLASS(BeamLaw);
};

#endif // BEAMLAW_H
