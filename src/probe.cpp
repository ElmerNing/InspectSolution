#include "stdafx.h"
#include "probe.h"

#pragma pack(push) //�������״̬
#pragma pack(4)
typedef struct 
{
    //PA ʱ���ȶ���4���ֽ�
    char	A1[2];
    unsigned char	PaProbeType;	// ̽ͷ���� 1 ��Custom 3 ��angle beam 5 �� Contact 6��Immersion
    char	A10;
    unsigned char	UtProbeType;	// ̽ͷ���� 1 n/a 0 converntional
    char	A11;
    char	cModel[20];				// ̽ͷ����
    char	cSerial[20];				// ̽ͷ����
    unsigned char	ucElemQty;		//��Ԫ��
    unsigned char	ucFreq2;			// UT ʱ�� Ƶ���� (freq2 << 8) + elem_qty
    unsigned int	iPitch;                      // ��Ԫ���ļ�� 0.001mm Ϊ��λ ��Χ��0.01~65.00mm UT ��Elemet_size
    unsigned int	A3;
    unsigned short A4;
    unsigned short wFrequency;		// Ƶ��
    unsigned int	 A5[75];
    unsigned short A6;
    unsigned short A7;
    unsigned short A8;
    unsigned short wRefPoint; //
    unsigned int	 A9[36];
} __RW_PROBE;
#pragma pack(pop) //�������״̬

Probe::Probe(ProbeType type)
{
    Default(type);
}

Probe::~Probe()
{
}


void Probe::Default(ProbeType type)
{
    if (type == ProbeType::PT_UT)
    {
        this->m_probeType = ProbeType::PT_UT;
        m_model = "";
        m_serial = "";
        this->m_freq = 1.0f;
        this->m_ut_elmSize = 25.4f;
    }
    else
    {
        this->m_probeType = ProbeType::PT_PA;
        m_model = "";
        m_serial = "";
        this->m_freq = 1.0f;
        this->m_pa_pitch = 0.5f;
        this->m_pa_elmQty = 0.5;
        this->m_pa_probeType = PaProbeType::PPT_CUSTOM;
        this->m_pa_refPoint = 0;
    }
}

bool Probe::LoadFromOlympus( const QString& path, ProbeType type )
{
    __RW_PROBE probe_rw;
    char* readpos = (char*)&probe_rw;

    //���ļ�
    QFile file(path);
    QDataStream in(&file);
    if (!file.open(QFile::ReadOnly) )
        return false;
    
    //PA�Ļ� ,�ӵ��ĸ��ֽڿ�ʼ��ȡ
    int offset = type == ProbeType::PT_PA ? 4 : 0;
    file.seek(offset);

    if ( in.readRawData(readpos, sizeof(__RW_PROBE) - offset ) != sizeof(__RW_PROBE) - offset ) 
        return false;

    //��ʽת��
    this->m_probeType = type;
    this->m_model = QString(probe_rw.cModel);
    this->m_serial = QString(probe_rw.cSerial);
    if (type == ProbeType::PT_PA)
        this->m_freq = float(probe_rw.wFrequency / 1000.0f);
    else
        this->m_freq = float((probe_rw.ucFreq2 * 256 + probe_rw.ucElemQty) / 1000.0f);

    //UT
    this->m_ut_elmSize = float(probe_rw.iPitch / 1000.0f);

    //PA
    this->m_pa_pitch = float(probe_rw.iPitch / 1000.0f);
    this->m_pa_elmQty = probe_rw.ucElemQty;
    this->m_pa_probeType = PaProbeType(probe_rw.PaProbeType);
    this->m_pa_refPoint = (-1.0f) * float(probe_rw.wRefPoint / 1000.0f);

    return true;
}

bool Probe::SaveToOlympus( const QString& path )
{
    __RW_PROBE probe_rw;
    memset(&probe_rw, 0, sizeof(__RW_PROBE));

    //��ʽת�� 
    QByteArray temp = m_model.toAscii();
    if (temp.count() > 19)
        return false;
    strcpy(probe_rw.cModel, temp.data());
    
    temp = m_serial.toAscii();
    if (temp.count() > 19)
        return false;
    strcpy(probe_rw.cSerial, temp.data());

    if (m_probeType == ProbeType::PT_PA)
    {
        probe_rw.ucElemQty = this->m_pa_elmQty;
        probe_rw.wFrequency = qRound(this->m_freq * 1000.0f);
        probe_rw.iPitch = qRound(this->m_pa_pitch * 1000.0f);
    }
    else
    {
        int iFreq = qRound(this->m_freq * 1000.0f);
        probe_rw.ucFreq2 = iFreq/256;
        probe_rw.ucElemQty = iFreq%256;
        probe_rw.iPitch = qRound(this->m_ut_elmSize * 1000.0);
    }

    probe_rw.wRefPoint = qRound(this->m_pa_refPoint * (-1000.0f));
    probe_rw.PaProbeType = uchar(this->m_pa_probeType);

    //���ļ�
    QFile file(path);
    QDataStream out(&file);
    if ( !file.open(QFile::WriteOnly))
        return false;

    //PA�Ļ� ,�ӵ��ĸ��ֽڿ�ʼд��
    char* writepos = (char*)&probe_rw;
    int offset = m_probeType == ProbeType::PT_PA ? 4 : 0;
    out.writeRawData(writepos, offset);

    out.writeRawData(writepos, sizeof(__RW_PROBE));
    return true;
}

//���л�
SERIALIZE_BEGIN(Probe)
    SERIALIZE_VAR(m_model)
    SERIALIZE_VAR(m_serial)
    SERIALIZE_VAR(m_freq)
    SERIALIZE_VAR(m_ut_elmSize)
    SERIALIZE_VAR(m_pa_pitch)
    SERIALIZE_VAR(m_pa_elmQty)
    SERIALIZE_VAR(m_pa_probeType)
    SERIALIZE_VAR(m_pa_refPoint)
SERIALIZE_END

//�����л�
DE_SERIALIZE_BEGIN(Probe)
    DE_SERIALIZE_VAR(m_model)
    DE_SERIALIZE_VAR(m_serial)
    DE_SERIALIZE_VAR(m_freq)
    DE_SERIALIZE_VAR(m_ut_elmSize)
    DE_SERIALIZE_VAR(m_pa_pitch)
    DE_SERIALIZE_VAR(m_pa_elmQty)
    DE_SERIALIZE_VAR(m_pa_probeType)
    DE_SERIALIZE_VAR(m_pa_refPoint)
DE_SERIALIZE_END
