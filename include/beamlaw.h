#ifndef BEAMLAW_H
#define BEAMLAW_H

#include "qrange.h"

//3个探头通道
enum ProbeChannel
{
    pa = 0,
    ut1 = 1,
    ut2 = 2,
};
SERIALIZE_ENABLE_ENUM(ProbeChannel);

//闸门
enum Gate
{
    GATE_A,
    GATE_B,
    GATE_I,
};
SERIALIZE_ENABLE_ENUM(Gate)

//深度模式
enum DepthType
{
    DT_BEAM_PATH = 0,   //半声程
    DT_TRUE_DEPTH = 1,  //真实深度
};
SERIALIZE_ENABLE_ENUM(DepthType)

struct ElmDelay
{
    //单位(ns)
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

    //设置为默认值
    void Default();

    //激发阵元数
    int ActiveElems() const { return m_activeElems; }
    void ActiveElems(int val) { m_activeElems = val; m_delay.resize(m_activeElems); }
    //发射起始阵元
    int TxFirst() const { return m_txFirst; }
    void TxFirst(int val) { m_txFirst = val; }
    //接受起始阵元
    int RxFirst() const { return m_rxFirst; }
    void RxFirst(int val) { m_rxFirst = val; }
    //设置阵元延迟(单位 ns)
    void TxDelay(int index, ushort delay) {m_delay[index].TxDelay = delay; }
    void RxDelay(int index, ushort delay) {m_delay[index].RxDelay = delay; }
    ushort TxDelay(int index) { return m_delay[index].TxDelay; }
    ushort RxDelay(int index) { return m_delay[index].RxDelay; }
    //闸门测量范围
    QRangeF GateRange(Gate gate) { return m_gateRange[gate]; }
    QRangeF GateRange(Gate gate, QRangeF range) { m_gateRange[gate] = range; }

private:
    //激发阵元数(1-32)
    int m_activeElems;
    //发射起始阵元
    int m_txFirst;
    //接受起始阵元
    int m_rxFirst;
    //阵元收发延迟
    QVector<ElmDelay> m_delay;
    //闸门范围
    QMap< Gate, QRangeF > m_gateRange;
    //增益补偿(db,分辨率0.1db)
    float m_gainOffset;
    //波束延迟(us, 分辨率10ns)
    float m_beamDelay;
    
    SERIALIZE_ENABLE_CLASS(BeamLaw);
};

#endif // BEAMLAW_H
