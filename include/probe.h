#ifndef PROBE_H
#define PROBE_H

#include "stdafx.h"

class Wedge;

enum PaProbeType
{
    PPT_CUSTOM = 1,
    PPT_ANGLEBEAM = 3,
    PPT_CONTACT = 5,
    PPT_IMMERSION = 6,
};
SERIALIZE_ENABLE_ENUM(PaProbeType);

enum ProbeType
{
    PT_PA,
    PT_UT,
};
SERIALIZE_ENABLE_ENUM(ProbeType);

class Probe
{
public:
    explicit Probe(ProbeType type = ProbeType::PT_PA);
    virtual ~Probe();

    //设置为默认值
    void Default(ProbeType type = ProbeType::PT_PA);
    
    //加载和保持和Olympus兼容的楔块文件格式
    bool LoadFromOlympus(const QString& path, ProbeType type);
    bool SaveToOlympus(const QString& path);

    //探头类型
    ProbeType Type() const { return m_probeType; }
    //void Type(ProbeType val) { m_probeType = val; }

    //探头型号
    QString Model() const { return m_model; }
    void Model(const QString& val) { m_model = val; }
    
    //探头系列
    QString Serial() const { return m_serial; }
    void Serial(const QString& val) { m_serial = val; }
    
    //探头频率 (MHZ)
    float Freq() const { return m_freq; }
    void Freq(float val) { m_freq = val; }

    //Ut探头阵元大小(mm)
    float Ut_elmSize() const { return m_ut_elmSize; }
    void Ut_elmSize(float val) { m_ut_elmSize = val; }

    //Pa探头阵元间距(mm)
    float Pa_pitch() const { return m_pa_pitch; }
    void Pa_pitch(float val) { m_pa_pitch = val; }

    //Pa探头阵元数量
    int Pa_elmQty() const { return m_pa_elmQty; }
    void Pa_elmQty(int val) { m_pa_elmQty = val; }

    //Pa探头类型
    PaProbeType Pa_probeType() const { return m_pa_probeType; }
    void Pa_probeType(PaProbeType val) { m_pa_probeType = val; }

    //Pa探头参考点(mm)
    float Pa_refPoint() const { return m_pa_refPoint; }
    void Pa_refPoint(float val) { m_pa_refPoint = val; }

    //pa探头阵元位置
    QPointF Pa_elmPos(int index, const Wedge& wedge, float offset = 0) const;

private:
    ProbeType m_probeType;
    //共用
    QString m_model;
    QString m_serial;
    float m_freq;
    //UT
    float m_ut_elmSize;
    //PA
    float m_pa_pitch;
    int m_pa_elmQty;
    PaProbeType m_pa_probeType;
    float m_pa_refPoint;

    SERIALIZE_ENABLE_CLASS(Probe);
};

#endif // PROBE_H
