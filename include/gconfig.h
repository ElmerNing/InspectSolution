#ifndef GCONFIG_H
#define GCONFIG_H

#include "solutionmodule.h"

//Pa��ѹ
enum PaVoltage
{
    PV_50,
    PV_100,
    PV_200,
    PV_400,
};
SERIALIZE_ENABLE_ENUM(PaVoltage);

//Ut��ѹֵ
enum UtVoltage
{
    UV_Low = 0,
    UV_50 = 1,
    UV_100 = 2,
    UV_200 = 3,
};
SERIALIZE_ENABLE_ENUM(UtVoltage);

//�װ��������
enum BoardVoltage
{
    //pa�����ѹ
    BV_PaTx = 0,
    //12Vת5.4V
    BV_to54 = 1,
    //12Vת5V
    BV_to5 = 2,
    //FPGA��Դ
    BV_FPGA = 3,
    //Ut�����ѹ
    BV_UtRx = 4,
};
SERIALIZE_ENABLE_ENUM(BoardVoltage);

//����1 ����
enum UtDamp
{
    UD_50R = 0,
    UD_100R = 1,
    UD_200R = 2,
    UD_500R = 3,
};
SERIALIZE_ENABLE_ENUM(UtDamp);

//Ut�շ�ģʽ
enum UtRxTx
{
    URT_PC = 0,
    URT_PE = 0,
};
SERIALIZE_ENABLE_ENUM(UtRxTx);

//����������
enum EncoderType
{
    ET_BOTH = 3,
    ET_INC = 2,
    ET_DEC = 1,
};
SERIALIZE_ENABLE_ENUM(EncoderType);

//������״̬
enum EncoderStatus
{
    ES_NORMAL = 0,
    ES_DISABLE = 1,
    ES_PAUSE = 2,
};
SERIALIZE_ENABLE_ENUM(EncoderStatus);

//����������
enum EncoderPolar
{
    EP_FORWARD = 0,
    EP_REVERSE = 1,
};
SERIALIZE_ENABLE_ENUM(EncoderPolar);

//����ͨ��
enum RxChannel
{
    RX_CHANNEL_0 =0,    RX_CHANNEL_1 =1,      RX_CHANNEL_2 =2,     RX_CHANNEL_3=3,
    RX_CHANNEL_4 =4,    RX_CHANNEL_5 =5,      RX_CHANNEL_6 =6,     RX_CHANNEL_7=7,
    RX_CHANNEL_8 =8,    RX_CHANNEL_9 =9,      RX_CHANNEL_10=10,    RX_CHANNEL_11=11,
    RX_CHANNEL_12=12,    RX_CHANNEL_13=13,    RX_CHANNEL_14=14,    RX_CHANNEL_15=15,
    RX_CHANNEL_16=16,    RX_CHANNEL_17=17,    RX_CHANNEL_18=18,    RX_CHANNEL_19=19,
    RX_CHANNEL_20=20,    RX_CHANNEL_21=21,    RX_CHANNEL_22=22,    RX_CHANNEL_23=23,
    RX_CHANNEL_24=24,    RX_CHANNEL_25=25,    RX_CHANNEL_26=26,    RX_CHANNEL_27=27,
    RX_CHANNEL_28=28,    RX_CHANNEL_29=29,    RX_CHANNEL_30=30,    RX_CHANNEL_31=31,
};
SERIALIZE_ENABLE_ENUM(RxChannel);


class Gconfig : public SolutionModule
{
public:
    explicit Gconfig(QObject *parent = 0);
    virtual ~Gconfig();

    //����ΪĬ��ֵ
    void Default();

    //������ѹ
    PaVoltage PaV() const { return m_paV; }
    void PaV(PaVoltage val) { m_paV = val; }

    //Ut��ѹ
    UtVoltage UtV() const { return m_utV; }
    void UtV(UtVoltage val) { m_utV = val; }

    //�װ��ѹ��������ʹ��
    bool BoardV(BoardVoltage bv) const { return m_boardEnable[(int)bv]; }
    void BoardV(BoardVoltage bv, bool enable) { m_boardEnable[(int)bv] = enable; }

    //Ut����
    UtDamp DampUt1() const { return m_dampUt1; }
    void DampUt1(UtDamp val) { m_dampUt1 = val; }
    UtDamp DampUt2() const { return m_dampUt2; }
    void DampUt2(UtDamp val) { m_dampUt2 = val; }

    //Ut �շ�ģʽ
    UtRxTx PeUt1() const { return m_bPeUt1; }
    void PeUt1(UtRxTx val) { m_bPeUt1 = val; }
    UtRxTx PeUt2() const { return m_bPeUt2; }
    void PeUt2(UtRxTx val) { m_bPeUt2 = val; }

    //������X����
    EncoderType EncoderTypeX() const { return m_encoderTypeX; }
    void EncoderTypeX(EncoderType val) { m_encoderTypeX = val; }
    
    //������X״̬,����, ֹͣ, ��ͣ
    EncoderStatus EncoderStatusX() const { return m_encoderStatusX; }
    void EncoderStatusX(EncoderStatus val) { m_encoderStatusX = val; }
    
    //����������,����,����
    EncoderPolar EncoderPolarX() const { return m_encoderPolarX; }
    void EncoderPolarX(EncoderPolar val) { m_encoderPolarX = val; }

    //������X����
    EncoderType EncoderTypeY() const { return m_encoderTypeY; }
    void EncoderTypeY(EncoderType val) { m_encoderTypeY = val; }
    
    //������X״̬,����, ֹͣ, ��ͣ
    EncoderStatus EncoderStatusY() const { return m_encoderStatusY; }
    void EncoderStatusY(EncoderStatus val) { m_encoderStatusY = val; }
    
    //����������,����,����
    EncoderPolar EncoderPolarY() const { return m_encoderPolarY; }
    void EncoderPolarY(EncoderPolar val) { m_encoderPolarY = val; }

    //32ͨ��ʹ��
    bool ChanelEnable(RxChannel chn) const { return m_rxChanelEnable[chn]; }
    void ChanelEnable(RxChannel chn, bool enable) { m_rxChanelEnable[chn] = enable; }

private:
    //pa��ѹ
    PaVoltage m_paV;

    //ut��ѹ
    UtVoltage m_utV;

    //�װ��ѹʹ�����
    QBitArray m_boardEnable;

    //Ut����
    UtDamp m_dampUt1;
    UtDamp m_dampUt2;

    //Ut �շ�ģʽ
    UtRxTx m_bPeUt1;
    UtRxTx m_bPeUt2;

    //����������(X����,Y����): ����,ʹ��,����
    EncoderType m_encoderTypeX;
    EncoderStatus m_encoderStatusX;
    EncoderPolar m_encoderPolarX;
    
    EncoderType m_encoderTypeY;
    EncoderStatus m_encoderStatusY;
    EncoderPolar m_encoderPolarY;

    //32������ͨ��ʹ��
    QBitArray m_rxChanelEnable;

    //FPGAʹ��/����, Ŀǰò����Ч,��Ҫͨ��GPIO������fpgaʹ��/����
    bool m_fpgaEnable;


    SERIALIZE_ENABLE_CLASS(Gconfig);
};

#endif // GCONFIG_H
