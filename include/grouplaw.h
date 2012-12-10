#ifndef GROUPLAW_H
#define GROUPLAW_H

#include "beamlaw.h"

enum RectifierMode
{
    RM_RF = 0,      //��Ƶ
    RM_HALFP = 1,   //���벨
    RM_HALFN = 2,   //���벨
    RM_WAVE = 3,    //ȫ��
};
SERIALIZE_ENABLE_ENUM(RectifierMode);

enum FreqBand
{
    FB_NONE,    //0.5 - 20
    FB_1_MHZ,   //0.5 - 2.5
    FB_2_MHZ,   //1 - 5
    FB_4_MHZ,   //2 - 10
    FB_7_MHZ,   //4 - 16
    FB_10_MHZ,  //5 - 20
};
SERIALIZE_ENABLE_ENUM(FreqBand);

enum LogicMode
{
    LM_WAVE_FRONT = 0,
    LM_WAVE_PEAK = 1,
};
SERIALIZE_ENABLE_ENUM(LogicMode);

enum AverageMode
{
    AM_1 = 0,
    AM_2 = 1,
    AM_4 = 2,
    AM_8 = 3,
    AM_16 = 4,
};
SERIALIZE_ENABLE_ENUM(AverageMode);

enum TTLSource
{
    TS_Av = 0,      // A^
    TS_Av_Iv = 1,   // A^ - I^
    TS_Av_Ix = 2,   // A^-I/
    TS_Bv = 3,      // B^
    TS_Bv_Iv = 4,   // B^ - I^  
    TS_Bv_Ix = 5,   // B^ - I/
    TS_Bv_Av = 6,   // B^ - A^
    TS_Iv = 7,      // I^
    TS_Ix = 8,      // I/
};
SERIALIZE_ENABLE_ENUM(TTLSource);


class GroupLaw
{
public:
    explicit GroupLaw();
    virtual ~GroupLaw();

    //����ΪĬ��ֵ
    void Default();

    //����,�ο�����(��λdb, ����0.1db). �������� = m_gain + m_gainref
    float Gain() const { return m_gain; }
    void Gain(float val) { m_gain = val; }
    float GainRef() const { return m_gainRef; }
    void GainRef(float val) { m_gainRef = val; }

    //ɨ�鷶Χ(��λmm), 
    float Range() const { return m_range; }
    void Range(float val) { m_range = val; }
    float Start() const { return m_start; }
    void Start(float val) { m_start = val; }

    //�첨ģʽ, ��Ƶʱ, �Զ��ر���Ƶ�˲�
    RectifierMode Rectifier() const { return m_rectifier; }
    void Rectifier(RectifierMode val) { 
        m_rectifier = val; 
        if (val == RectifierMode::RM_RF ) m_isVideoFilter = false;
    }
    
    //�Ƿ���Ƶ�˲�
    bool VideoFilter() const { return m_isVideoFilter; }
    void VideoFilter(bool val) { m_isVideoFilter = val; }

    //Ƶ��ѡ��
    FreqBand Freq() const { return m_freq; }
    void Freq(FreqBand val) { m_freq = val; }

    //������(��λdb, 20dB��48dB)
    //20*log( N==1 ? 4095 : 6400/N),����NΪ��Ԫ��
    //����,ÿ��beam������Ԫ�� �����ܲ�һ��
    float Sumgain() const { return m_sumgain; }
    void Sumgain(float val) { m_sumgain = val; }
    float BestSumgain() const;

    //��Ȳ�,(ò������)
    float ThickFactor() const { return m_thickFactor; }
    void ThickFactor(float val) { m_thickFactor = val; }

    //բ�Ÿ߶� 0% ~ 100%
    int GateHeight(Gate gate) const { return m_gateHeight[gate]; }
    void GateHeight(Gate gate, int height) { m_gateHeight[gate] = height; }

    //բ���߼�,��ǰ����
    LogicMode GateLogic(Gate gate) const { return m_gateLogic[gate]; }
    void GateLogic(Gate gate, LogicMode logic) { m_gateLogic[gate] = logic; }

    //ʹ��̽ͷ
    ProbeChannel Probe() const { return m_probe; }
    void Probe(ProbeChannel val) { m_probe = val; }

private:
    QVector<BeamLaw> m_beamLaws;
    //����,�ο�����(��λdb, ����0.1db). �������� = m_gain + m_gainref
    float m_gain; 
    float m_gainRef;
    
    //ɨ����ʼ�뷶Χ,������Ш���ӳ�(��λmm), 
    float m_start;
    float m_range;

    //�첨ģʽ
    RectifierMode m_rectifier;

    //�Ƿ���Ƶ�˲�
    bool m_isVideoFilter;

    //Ƶ��ѡ��
    FreqBand m_freq;

    //������(��λdb)
    float m_sumgain;

    //��Ȳ�,(ò������)
    float m_thickFactor;

    //̽ͷ����ͨ��ʹ�����
    //QByteArray m_probeEnable;

    //բ�Ÿ߶�բ�Ÿ߶� 0% ~ 100% �� բ���߼� ��ǰ����
    QMap<Gate, ushort> m_gateHeight;
    QMap<Gate, LogicMode> m_gateLogic;

    //ƽ��
    AverageMode m_Average;

    //TTLԴ
    TTLSource m_ttl;

    // ��������� (��λδ֪,�����!)
    uint m_hicknessMax;

    // ������ 30~500ns 2.5nsΪ����
    float m_pulseWidth;

    //ʹ��̽ͷ
    ProbeChannel m_probe;

    //���л�,�����л�,ʹ��
    SERIALIZE_ENABLE_CLASS(GroupLaw);
};


#endif // GROUPLAW_H
