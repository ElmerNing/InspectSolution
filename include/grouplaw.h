#ifndef GROUPLAW_H
#define GROUPLAW_H

#include "beamlaw.h"

enum RectifierMode
{
    RM_RF = 0,      //射频
    RM_HALFP = 1,   //正半波
    RM_HALFN = 2,   //负半波
    RM_WAVE = 3,    //全波
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

    //设置为默认值
    virtual void Default();

    //增益,参考增益(单位db, 精度0.1db). 最终增益 = m_gain + m_gainref
    float Gain() const { return m_gain; }
    void Gain(float val) { m_gain = val; }
    float GainRef() const { return m_gainRef; }
    void GainRef(float val) { m_gainRef = val; }

    // 
    int Range() const { return m_range; }
    void Range(int val) { m_range = val; }
    int Start() const { return m_start; }
    void Start(int val) { m_start = val; }

    //检波模式, 射频时, 自动关闭视频滤波
    RectifierMode Rectifier() const { return m_rectifier; }
    void Rectifier(RectifierMode val) { 
        m_rectifier = val; 
        if (val == RectifierMode::RM_RF ) m_isVideoFilter = false;
    }
    
    //是否视频滤波
    bool VideoFilter() const { return m_isVideoFilter; }
    void VideoFilter(bool val) { m_isVideoFilter = val; }

    //频带选择
    FreqBand Freq() const { return m_freq; }
    void Freq(FreqBand val) { m_freq = val; }

    //总增益(单位db, 20dB－48dB)
    //20*log( N==1 ? 4095 : 6400/N),其中N为阵元数
    //疑问,每个beam所用阵元数 都可能不一样
    float Sumgain() const { return m_sumgain; }
    void Sumgain(float val) { m_sumgain = val; }
    virtual float BestSumgain() const = 0;

    //厚度差,(貌似无用)
    float ThickFactor() const { return m_thickFactor; }
    void ThickFactor(float val) { m_thickFactor = val; }

    //闸门高度 0% ~ 100%
    int GateHeight(Gate gate) const { return m_gateHeight[gate]; }
    void GateHeight(Gate gate, int height) { m_gateHeight[gate] = height; }

    //闸门逻辑,波前波峰
    LogicMode GateLogic(Gate gate) const { return m_gateLogic[gate]; }
    void GateLogic(Gate gate, LogicMode logic) { m_gateLogic[gate] = logic; }

    //使用探头
    ProbeChannel ChannelOfProbe() const { return m_probe; }
    void ChannelOfProbe(ProbeChannel val) { m_probe = val; }

private:
    //增益,参考增益(单位db, 精度0.1db). 最终增益 = m_gain + m_gainref
    float m_gain; 
    float m_gainRef;
    
    //扫查起始与范围,不包括楔块延迟(单位mm), 
    int m_start;
    int m_range;

    //检波模式
    RectifierMode m_rectifier;

    //是否视频滤波
    bool m_isVideoFilter;

    //频带选择
    FreqBand m_freq;

    //总增益(单位db)
    float m_sumgain;

    //厚度差,(貌似无用)
    float m_thickFactor;

    //探头各个通道使能情况
    //QByteArray m_probeEnable;

    //闸门高度闸门高度 0% ~ 100% 和 闸门逻辑 波前波峰
    QMap<Gate, ushort> m_gateHeight;
    QMap<Gate, LogicMode> m_gateLogic;

    //平均
    AverageMode m_Average;

    //TTL源
    TTLSource m_ttl;

    // 测量最大厚度 (单位未知,求解释!)
    uint m_hicknessMax;

    // 脉冲宽度 30~500ns 2.5ns为步进
    float m_pulseWidth;

    //使用探头
    ProbeChannel m_probe;

    //序列化,反序列化,使能
    SERIALIZE_ENABLE_CLASS(GroupLaw);
};


#endif // GROUPLAW_H
