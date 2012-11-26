#include "stdafx.h"
#include "gconfig.h"

Gconfig::Gconfig(QObject *parent) :
    SolutionModule(parent) ,
    m_boardEnable(3, true) ,
    m_rxChanelEnable(32, true)
{
    Default();
}

Gconfig::~Gconfig()
{
}

void Gconfig::Default()
{
    //pa ut��ѹ����Ϊ��Сֵ
    m_paV = PaVoltage::PV_50;
    m_utV = UtVoltage::UV_Low;
    
    //�װ��ѹȫ��ʹ��
    m_boardEnable.fill(true);
    
    //UT ��ʼ��Ϊ ����20ŷ, PEģʽ
    m_dampUt1 = UtDamp::UD_50R;
    m_dampUt2 = UtDamp::UD_50R;
    m_bPeUt1 = UtRxTx::URT_PE;
    m_bPeUt2 = UtRxTx::URT_PE;
    
    //encoder ��ʼ��Ϊ ˫��, ʹ��, ������,
    m_encoderTypeX = EncoderType::ET_BOTH;
    m_encoderStatusX = EncoderStatus::ES_NORMAL;
    m_encoderPolarX = EncoderPolar::EP_FORWARD;
    m_encoderTypeY = EncoderType::ET_BOTH;
    m_encoderStatusY = EncoderStatus::ES_NORMAL;
    m_encoderPolarY = EncoderPolar::EP_FORWARD;

    //32����ͨ��ȫ��ʹ��
    m_rxChanelEnable.fill(true);
}


//���л�
SERIALIZE_BEGIN(Gconfig)
    SERIALIZE_VAR(m_paV)
    SERIALIZE_VAR(m_utV)
    SERIALIZE_VAR(m_boardEnable)
    SERIALIZE_VAR(m_dampUt1)
    SERIALIZE_VAR(m_dampUt2)
    SERIALIZE_VAR(m_bPeUt1)
    SERIALIZE_VAR(m_bPeUt2)
    SERIALIZE_VAR(m_encoderTypeX)
    SERIALIZE_VAR(m_encoderStatusX)
    SERIALIZE_VAR(m_encoderPolarX)
    SERIALIZE_VAR(m_encoderTypeY)
    SERIALIZE_VAR(m_encoderStatusY)
    SERIALIZE_VAR(m_encoderPolarY)
    SERIALIZE_VAR(m_rxChanelEnable)
    SERIALIZE_VAR(m_fpgaEnable)
SERIALIZE_END

//�����л�
DE_SERIALIZE_BEGIN(Gconfig)
    DE_SERIALIZE_VAR(m_paV)
    DE_SERIALIZE_VAR(m_utV)
    DE_SERIALIZE_VAR(m_boardEnable)
    DE_SERIALIZE_VAR(m_dampUt1)
    DE_SERIALIZE_VAR(m_dampUt2)
    DE_SERIALIZE_VAR(m_bPeUt1)
    DE_SERIALIZE_VAR(m_bPeUt2)
    DE_SERIALIZE_VAR(m_encoderTypeX)
    DE_SERIALIZE_VAR(m_encoderStatusX)
    DE_SERIALIZE_VAR(m_encoderPolarX)
    DE_SERIALIZE_VAR(m_encoderTypeY)
    DE_SERIALIZE_VAR(m_encoderStatusY)
    DE_SERIALIZE_VAR(m_encoderPolarY)
    DE_SERIALIZE_VAR(m_rxChanelEnable)
    DE_SERIALIZE_VAR(m_fpgaEnable)
DE_SERIALIZE_END
