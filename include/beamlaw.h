#ifndef BEAMLAW_H
#define BEAMLAW_H

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
SERIALIZE_ENABLE_ENUM(Gate)

//���ģʽ
enum DepthType
{
    DT_BEAM_PATH = 0,   //������
    DT_TRUE_DEPTH = 1,  //��ʵ���
};
SERIALIZE_ENABLE_ENUM(DepthType)

struct ElmDelay
{
    //��λ(ns)
    ElmDelay(){TxDelay = 0; RxDelay = 0;}
    ushort TxDelay;
    ushort RxDelay;
    SERIALIZE_ENABLE_CLASS(ElmDelay)
};

class BeamLaw
{
public:
    explicit BeamLaw();
    virtual ~BeamLaw();

    //����ΪĬ��ֵ
    void Default();

    //������Ԫ��
    int ActiveElems() const { return m_activeElems; }
    void ActiveElems(int val) { m_activeElems = val; m_delay.resize(m_activeElems); }
    //������ʼ��Ԫ
    int TxFirst() const { return m_txFirst; }
    void TxFirst(int val) { m_txFirst = val; }
    //������ʼ��Ԫ
    int RxFirst() const { return m_rxFirst; }
    void RxFirst(int val) { m_rxFirst = val; }
    //������Ԫ�ӳ�(��λ ns)
    void TxDelay(int index, ushort delay) {m_delay[index].TxDelay = delay; }
    void RxDelay(int index, ushort delay) {m_delay[index].RxDelay = delay; }
    ushort TxDelay(int index) { return m_delay[index].TxDelay; }
    ushort RxDelay(int index) { return m_delay[index].RxDelay; }
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
    //��Ԫ�շ��ӳ�
    QVector<ElmDelay> m_delay;
    //բ�ŷ�Χ
    QMap< Gate, QRangeF > m_gateRange;
    //���油��(db,�ֱ���0.1db)
    float m_gainOffset;
    //�����ӳ�(us, �ֱ���10ns)
    float m_beamDelay;
    
    SERIALIZE_ENABLE_CLASS(BeamLaw);
};

#endif // BEAMLAW_H
