#ifndef BEAMLAW_H
#define BEAMLAW_H

#include "solutionmodule.h"
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
SERIALIZE_ENABLE_ENUM(Gate);

//深度模式
enum DepthType
{
    DT_BEAM_PATH = 0,   //半声程
    DT_TRUE_DEPTH = 1,  //真实深度
};
SERIALIZE_ENABLE_ENUM(DepthType);

class BeamLaw
{
public:

    explicit BeamLaw();
    virtual ~BeamLaw();

    //设置为默认值
    void Default();

    //激发阵元数, 改变会同时改变group的sumgain,过会实现
    int ActiveElems() const { return m_activeElems; }
    void ActiveElems(int val) { m_activeElems = val; }
    //发射起始阵元
    int TxFirst() const { return m_txFirst; }
    void TxFirst(int val) { m_txFirst = val; }
    //接受起始阵元
    int RxFirst() const { return m_rxFirst; }
    void RxFirst(int val) { m_rxFirst = val; }
    //聚焦角度
    float Angle() const { return m_angle; }
    void Angle(float val) { m_angle = val; }
    //聚焦转向角
    float ScrewAngle() const { return m_screwAngle; }
    void ScrewAngle(float val) { m_screwAngle = val; }
    //聚焦深度类型
    DepthType FocusDepthType() const { return m_focusDepthType; }
    void FocusDepthType(DepthType val) { m_focusDepthType = val; }
    //聚焦深度,FocusDepthType不同,有不同物理意义
    float FocusDepth() const { return m_focusDepth; }
    void FocusDepth(float val) { m_focusDepth = val; }
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
    //聚焦角度
    float m_angle;
    //聚焦转向角
    float m_screwAngle;
    //聚焦深度类型
    DepthType m_focusDepthType;
    //聚焦深度
    float m_focusDepth;
    //闸门范围
    QMap< Gate, QRangeF > m_gateRange;
    //增益补偿(db,分辨率0.1db)
    float m_gainOffset;
    //波束延迟(us, 分辨率10ns)
    float m_beamDelay;
    
    SERIALIZE_ENABLE_CLASS(BeamLaw);
};

#endif // BEAMLAW_H
