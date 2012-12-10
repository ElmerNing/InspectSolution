#ifndef PROBE_H
#define PROBE_H

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

    //����ΪĬ��ֵ
    void Default(ProbeType type = ProbeType::PT_PA);
    
    //���غͱ��ֺ�Olympus���ݵ�Ш���ļ���ʽ
    bool LoadFromOlympus(const QString& path, ProbeType type);
    bool SaveToOlympus(const QString& path);

    //̽ͷ����
    ProbeType Type() const { return m_probeType; }
    void Type(ProbeType val) { m_probeType = val; }\

    //̽ͷ�ͺ�
    QString Model() const { return m_model; }
    void Model(const QString& val) { m_model = val; }
    
    //̽ͷϵ��
    QString Serial() const { return m_serial; }
    void Serial(const QString& val) { m_serial = val; }
    
    //̽ͷƵ�� (MHZ)
    float Freq() const { return m_freq; }
    void Freq(float val) { m_freq = val; }

    //Ut̽ͷ��Ԫ��С(mm)
    float Ut_elmSize() const { return m_ut_elmSize; }
    void Ut_elmSize(float val) { m_ut_elmSize = val; }

    //Pa̽ͷ��Ԫ���(mm)
    float Pa_pitch() const { return m_pa_pitch; }
    void Pa_pitch(float val) { m_pa_pitch = val; }

    //Pa̽ͷ��Ԫ����
    int Pa_elmQty() const { return m_pa_elmQty; }
    void Pa_elmQty(int val) { m_pa_elmQty = val; }

    //Pa̽ͷ����
    PaProbeType Pa_probeType() const { return m_pa_probeType; }
    void Pa_probeType(PaProbeType val) { m_pa_probeType = val; }

    //Pa̽ͷ�ο���(mm)
    float Pa_refPoint() const { return m_pa_refPoint; }
    void Pa_refPoint(float val) { m_pa_refPoint = val; }

private:
    ProbeType m_probeType;
    //����
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
