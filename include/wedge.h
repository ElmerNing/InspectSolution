﻿#ifndef WEDGE_H
#define WEDGE_H

class Probe;

enum WedgeWaveType
{
    WWT_L = 1,
    WWT_S = 2,
};
SERIALIZE_ENABLE_ENUM(WedgeWaveType);

enum WedgeOrient
{
    WO_REVERSAL = 0,
    WO_NORMAL = 1,
};
SERIALIZE_ENABLE_ENUM(WedgeOrient);

enum WedgeType
{
    WT_PA,
    WT_UT,
};
SERIALIZE_ENABLE_ENUM(WedgeType);

class Wedge
{
public:
    explicit Wedge(WedgeType type = WedgeType::WT_PA);
    virtual ~Wedge();

    //设置为默认值
    void Default(WedgeType type = WedgeType::WT_PA);

    //加载和保持和Olympus兼容的楔块文件格式
    bool LoadFromOlympus(const QString& path, WedgeType type);
    bool SaveToOlympus(const QString& path);

    //楔块类型 PA or UT
    WedgeType Type() const { return m_wedgeType; }
    //void Type(WedgeType val) { m_wedgeType = val; }

    //楔块名字
    QString Model() const { return m_model; }
    void Model(QString val) { m_model = val; }

    //楔块所属序列
    QString Serial() const { return m_serial; }
    void Serial(QString val) { m_serial = val; }

    //楔块角度 (角度)
    float Angle() const { return m_angle; }
    void Angle(float val) { m_angle = val; }

    //参考点 (mm)
    float RefPoint() const { return m_refPoint; }
    void RefPoint(float val) { m_refPoint = val; }
    
    //声速 (m/s)
    float Velocity() const { return m_velocity; }
    void Velocity(float val) { m_velocity = val; }

    //UT的楔块延迟 (us)
    float Ut_wedgeDelay() const { return m_ut_wedgeDelay; }
    void Ut_wedgeDelay(float val) { m_ut_wedgeDelay = val; }

    //UT楔块时的声波类型,横波 or 纵波
    WedgeWaveType Ut_waveType() const { return m_ut_waveType; }
    void Ut_waveType(WedgeWaveType val) { m_ut_waveType = val; }

    //PA楔块的方向, 正向 or 反向
    WedgeOrient Pa_orient() const { return m_pa_orient; }
    void Pa_orient(WedgeOrient val) { m_pa_orient = val; }

    //第一振元高度 (mm)
    float Pa_height() const { return m_pa_height; }
    void Pa_height(float val) { m_pa_height = val; }

    //主轴偏置 (mm)
    float Pa_priOffset() const { return m_pa_priOffset; }
    void Pa_priOffset(float val) { m_pa_priOffset = val; }

    //次轴偏置 (mm)
    float Pa_secOffset() const { return m_pa_secOffset; }
    void Pa_secOffset(float val) { m_pa_secOffset = val; }

    //阵元位置
    QPointF Pa_elmPos(int index, const Probe& probe, float offset = 0) const;

private:
    //楔块类型
    WedgeType m_wedgeType;
    //共用
    QString m_model;
    QString m_serial;
    float m_angle;
    float m_refPoint;
    float m_velocity;
    //UT
    float m_ut_wedgeDelay;
    WedgeWaveType m_ut_waveType;
    //PA
    WedgeOrient m_pa_orient;
    float m_pa_height;
    float m_pa_priOffset;
    float m_pa_secOffset;

    SERIALIZE_ENABLE_CLASS(Wedge);
};

#endif // WEDGE_H
