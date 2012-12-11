#ifndef WEDGE_H
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

    //����ΪĬ��ֵ
    void Default(WedgeType type = WedgeType::WT_PA);

    //���غͱ��ֺ�Olympus���ݵ�Ш���ļ���ʽ
    bool LoadFromOlympus(const QString& path, WedgeType type);
    bool SaveToOlympus(const QString& path);

    //Ш������ PA or UT
    WedgeType Type() const { return m_wedgeType; }
    //void Type(WedgeType val) { m_wedgeType = val; }

    //Ш������
    QString Model() const { return m_model; }
    void Model(QString val) { m_model = val; }

    //Ш����������
    QString Serial() const { return m_serial; }
    void Serial(QString val) { m_serial = val; }

    //Ш��Ƕ� (�Ƕ�)
    float Angle() const { return m_angle; }
    void Angle(float val) { m_angle = val; }

    //�ο��� (mm)
    float RefPoint() const { return m_refPoint; }
    void RefPoint(float val) { m_refPoint = val; }
    
    //���� (m/s)
    float Velocity() const { return m_velocity; }
    void Velocity(float val) { m_velocity = val; }

    //UT��Ш���ӳ� (us)
    float Ut_wedgeDelay() const { return m_ut_wedgeDelay; }
    void Ut_wedgeDelay(float val) { m_ut_wedgeDelay = val; }

    //UTШ��ʱ����������,�Შ or �ݲ�
    WedgeWaveType Ut_waveType() const { return m_ut_waveType; }
    void Ut_waveType(WedgeWaveType val) { m_ut_waveType = val; }

    //PAШ��ķ���, ���� or ����
    WedgeOrient Pa_orient() const { return m_pa_orient; }
    void Pa_orient(WedgeOrient val) { m_pa_orient = val; }

    //��һ��Ԫ�߶� (mm)
    float Pa_height() const { return m_pa_height; }
    void Pa_height(float val) { m_pa_height = val; }

    //����ƫ�� (mm)
    float Pa_priOffset() const { return m_pa_priOffset; }
    void Pa_priOffset(float val) { m_pa_priOffset = val; }

    //����ƫ�� (mm)
    float Pa_secOffset() const { return m_pa_secOffset; }
    void Pa_secOffset(float val) { m_pa_secOffset = val; }

    //��Ԫλ��
    QPointF Pa_elmPos(int index, const Probe& probe, float offset = 0) const;

private:
    //Ш������
    WedgeType m_wedgeType;
    //����
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
