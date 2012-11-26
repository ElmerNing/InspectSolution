#include "stdafx.h"
#include "wedge.h"

#pragma pack(push) //�������״̬
#pragma pack(4)
typedef struct 
{
    unsigned char	A1[2];			//0x03000300 PA 0x01000100 UT
    char	cWaveType;		// 1 ��L 2 �� S
    char	A11;
    char	szModel[20];		// ���� Ш������
    char	szSerial[20];		// ���� Ш������
    unsigned short wAngle;			// ���� �Ƕȵ�λ0.1��
    unsigned short	A7;
    unsigned short wProbeDelay; 	// UT nsΪ��λ
    char	A2;
    char	A10;			  // UT 1 SW 0 LW//
    int	iRefPoint;		// UT ʹ��
    //����ط� �� ���һ���ֽ�
    unsigned int	iHeight;			// ��λ΢��
    unsigned int	iVelocityUt;
    unsigned int	A8;
    unsigned int	iVelocityPa;	// �ٶ� mm/s
    char	cOrientation;	// 1 Normal 0 reversal
    char	A4[3];
    int	iPrimaryOffset;	// ΢��
    int	iSecondaryOffset;	// ΢��
    int	A6[107];
} __WR_WEDGE;
#pragma pack(pop) //�������״̬

Wedge::Wedge(QObject *parent) :
    SolutionModule(parent)
{
    Default();
}

Wedge::~Wedge()
{

}

void Wedge::Default()
{
    m_wedgeType = WedgeType::WT_UT;
    m_angle = 0;
    m_ut_wedgeDelay = 0;
    m_ut_waveType = WedgeWaveType::WWT_S;
    m_refPoint = 0;
    m_velocity = 5200;
}


bool Wedge::LoadFromOlympus( const QString& path, WedgeType type )
{
    __WR_WEDGE wedge_rw;
    char* readpos = (char*)&wedge_rw;

    //�ض�λ��
    int cupoff = (int)(&(((__WR_WEDGE*)NULL)->iRefPoint));

    //���ļ�
    QFile file(path);
    QDataStream in(&file);
    if (!file.open(QFile::ReadOnly) )
        return false;

    //�ض�ǰ
    if (in.readRawData(readpos, cupoff) != cupoff)
        return false;
    
    //�ض�λ��,����һ���ֽ�
    file.seek(cupoff + 1);

    //�ضϺ�
    readpos += cupoff;
    int size = sizeof(__WR_WEDGE) - cupoff;
    if (in.readRawData(readpos, size) != size)
        return false;

    //��ʽת�� 
    this->m_wedgeType = type;
    this->m_model = QString(wedge_rw.szModel);
    this->m_serial = QString(wedge_rw.szSerial);
    this->m_angle = float(wedge_rw.wAngle / 10.0f);
    this->m_refPoint = (-1.0) * float(wedge_rw.iRefPoint / 1000.0f);
    if (type == WedgeType::WT_PA)
        this->m_velocity = float(wedge_rw.iVelocityPa / 1000.0f);
    else
        this->m_velocity = float(wedge_rw.iVelocityUt / 1000.0f);

    //UT
    this->m_ut_wedgeDelay = float(wedge_rw.wProbeDelay / 1000.0f);
    this->m_ut_waveType = WedgeWaveType(wedge_rw.cWaveType);

    //PA
    this->m_pa_orient = WedgeOrient(wedge_rw.cOrientation);
    this->m_height = float(wedge_rw.iHeight / 1000.0f);
    this->m_priOffset = float(wedge_rw.iPrimaryOffset / 1000.0f);
    this->m_secOffset = float(wedge_rw.iSecondaryOffset / 1000.0f);
    
    return true;
}

bool Wedge::SaveToOlympus( const QString& path )
{
    __WR_WEDGE wedge_rw;
    memset(&wedge_rw, 0, sizeof(__WR_WEDGE));
    
    //��ʽת�� 
    QByteArray temp = m_model.toAscii();
    if (temp.count() > 19)
        return false;
    strcpy(wedge_rw.szModel, temp.data());

    temp = m_serial.toAscii();
    if (temp.count() > 19)
        return false;
    strcpy(wedge_rw.szSerial, temp.data());

    wedge_rw.wAngle = qRound(this->m_angle * 10.0f);
    wedge_rw.iRefPoint = qRound(this->m_refPoint * (-1000.0f));
    wedge_rw.iVelocityPa = qRound(this->m_velocity * 1000.0f);
    wedge_rw.iVelocityUt = qRound(this->m_velocity * 1000.0f);

    //UT
    wedge_rw.wProbeDelay = qRound(this->m_ut_wedgeDelay * 1000.0f);
    wedge_rw.cWaveType = char(this->m_ut_waveType);

    //PA
    wedge_rw.cOrientation = char(this->m_pa_orient);
    wedge_rw.iHeight = qRound(this->m_height * 1000.0f);
    wedge_rw.iPrimaryOffset = qRound(this->m_priOffset);
    wedge_rw.iSecondaryOffset = qRound(this->m_secOffset);

    //�ض�λ��
    int cupoff = (int)(&(((__WR_WEDGE*)NULL)->iRefPoint));

    //���ļ�
    QFile file(path);
    QDataStream out(&file);
    if (!file.open(QFile::WriteOnly) )
        return false;

    //�ض�λ��ǰ
    char* writepos = (char*)&wedge_rw;
    out.writeRawData(writepos, cupoff);
    writepos += cupoff;
    
    //�ض�λ�ö�дһ���ֽ�
    out.writeRawData(writepos, 1);

    //�ضϺ�
    out.writeRawData(writepos, sizeof(__WR_WEDGE) - cupoff);

    return true;
}

//���л�
SERIALIZE_BEGIN(Wedge)
    SERIALIZE_VAR(m_wedgeType)
    SERIALIZE_VAR(m_model)
    SERIALIZE_VAR(m_serial)
    SERIALIZE_VAR(m_angle)
    SERIALIZE_VAR(m_refPoint)
    SERIALIZE_VAR(m_velocity)
    SERIALIZE_VAR(m_ut_wedgeDelay)
    SERIALIZE_VAR(m_ut_waveType)
    SERIALIZE_VAR(m_pa_orient)
    SERIALIZE_VAR(m_height)
    SERIALIZE_VAR(m_priOffset)
    SERIALIZE_VAR(m_secOffset)
SERIALIZE_END

//�����л�
DE_SERIALIZE_BEGIN(Wedge)
    DE_SERIALIZE_VAR(m_wedgeType)
    DE_SERIALIZE_VAR(m_model)
    DE_SERIALIZE_VAR(m_serial)
    DE_SERIALIZE_VAR(m_angle)
    DE_SERIALIZE_VAR(m_refPoint)
    DE_SERIALIZE_VAR(m_velocity)
    DE_SERIALIZE_VAR(m_ut_wedgeDelay)
    DE_SERIALIZE_VAR(m_ut_waveType)
    DE_SERIALIZE_VAR(m_pa_orient)
    DE_SERIALIZE_VAR(m_height)
    DE_SERIALIZE_VAR(m_priOffset)
    DE_SERIALIZE_VAR(m_secOffset)
DE_SERIALIZE_END