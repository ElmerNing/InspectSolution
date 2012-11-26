#ifndef GCONFIG_H
#define GCONFIG_H

#include "solutionmodule.h"

//Pa电压
enum PaVoltage
{
    PV_50,
    PV_100,
    PV_200,
    PV_400,
};
SERIALIZE_ENABLE_ENUM(PaVoltage);

//Ut电压值
enum UtVoltage
{
    UV_Low = 0,
    UV_50 = 1,
    UV_100 = 2,
    UV_200 = 3,
};
SERIALIZE_ENABLE_ENUM(UtVoltage);

//底板各个部件
enum BoardVoltage
{
    //pa发射电压
    BV_PaTx = 0,
    //12V转5.4V
    BV_to54 = 1,
    //12V转5V
    BV_to5 = 2,
    //FPGA电源
    BV_FPGA = 3,
    //Ut发射电压
    BV_UtRx = 4,
};
SERIALIZE_ENABLE_ENUM(BoardVoltage);

//常规1 阻尼
enum UtDamp
{
    UD_50R = 0,
    UD_100R = 1,
    UD_200R = 2,
    UD_500R = 3,
};
SERIALIZE_ENABLE_ENUM(UtDamp);

//Ut收发模式
enum UtRxTx
{
    URT_PC = 0,
    URT_PE = 0,
};
SERIALIZE_ENABLE_ENUM(UtRxTx);

//编码器类型
enum EncoderType
{
    ET_BOTH = 3,
    ET_INC = 2,
    ET_DEC = 1,
};
SERIALIZE_ENABLE_ENUM(EncoderType);

//编码器状态
enum EncoderStatus
{
    ES_NORMAL = 0,
    ES_DISABLE = 1,
    ES_PAUSE = 2,
};
SERIALIZE_ENABLE_ENUM(EncoderStatus);

//编码器极性
enum EncoderPolar
{
    EP_FORWARD = 0,
    EP_REVERSE = 1,
};
SERIALIZE_ENABLE_ENUM(EncoderPolar);

//接收通道
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

    //设置为默认值
    void Default();

    //相控阵电压
    PaVoltage PaV() const { return m_paV; }
    void PaV(PaVoltage val) { m_paV = val; }

    //Ut电压
    UtVoltage UtV() const { return m_utV; }
    void UtV(UtVoltage val) { m_utV = val; }

    //底板电压各个部分使能
    bool BoardV(BoardVoltage bv) const { return m_boardEnable[(int)bv]; }
    void BoardV(BoardVoltage bv, bool enable) { m_boardEnable[(int)bv] = enable; }

    //Ut阻尼
    UtDamp DampUt1() const { return m_dampUt1; }
    void DampUt1(UtDamp val) { m_dampUt1 = val; }
    UtDamp DampUt2() const { return m_dampUt2; }
    void DampUt2(UtDamp val) { m_dampUt2 = val; }

    //Ut 收发模式
    UtRxTx PeUt1() const { return m_bPeUt1; }
    void PeUt1(UtRxTx val) { m_bPeUt1 = val; }
    UtRxTx PeUt2() const { return m_bPeUt2; }
    void PeUt2(UtRxTx val) { m_bPeUt2 = val; }

    //编码器X类型
    EncoderType EncoderTypeX() const { return m_encoderTypeX; }
    void EncoderTypeX(EncoderType val) { m_encoderTypeX = val; }
    
    //编码器X状态,正常, 停止, 暂停
    EncoderStatus EncoderStatusX() const { return m_encoderStatusX; }
    void EncoderStatusX(EncoderStatus val) { m_encoderStatusX = val; }
    
    //编码器极性,正向,反向
    EncoderPolar EncoderPolarX() const { return m_encoderPolarX; }
    void EncoderPolarX(EncoderPolar val) { m_encoderPolarX = val; }

    //编码器X类型
    EncoderType EncoderTypeY() const { return m_encoderTypeY; }
    void EncoderTypeY(EncoderType val) { m_encoderTypeY = val; }
    
    //编码器X状态,正常, 停止, 暂停
    EncoderStatus EncoderStatusY() const { return m_encoderStatusY; }
    void EncoderStatusY(EncoderStatus val) { m_encoderStatusY = val; }
    
    //编码器极性,正向,反向
    EncoderPolar EncoderPolarY() const { return m_encoderPolarY; }
    void EncoderPolarY(EncoderPolar val) { m_encoderPolarY = val; }

    //32通道使能
    bool ChanelEnable(RxChannel chn) const { return m_rxChanelEnable[chn]; }
    void ChanelEnable(RxChannel chn, bool enable) { m_rxChanelEnable[chn] = enable; }

private:
    //pa电压
    PaVoltage m_paV;

    //ut电压
    UtVoltage m_utV;

    //底板电压使能情况
    QBitArray m_boardEnable;

    //Ut阻尼
    UtDamp m_dampUt1;
    UtDamp m_dampUt2;

    //Ut 收发模式
    UtRxTx m_bPeUt1;
    UtRxTx m_bPeUt2;

    //编码器控制(X方向,Y方向): 类型,使能,极性
    EncoderType m_encoderTypeX;
    EncoderStatus m_encoderStatusX;
    EncoderPolar m_encoderPolarX;
    
    EncoderType m_encoderTypeY;
    EncoderStatus m_encoderStatusY;
    EncoderPolar m_encoderPolarY;

    //32个接受通道使能
    QBitArray m_rxChanelEnable;

    //FPGA使能/冻结, 目前貌似无效,需要通过GPIO来配置fpga使能/冻结
    bool m_fpgaEnable;


    SERIALIZE_ENABLE_CLASS(Gconfig);
};

#endif // GCONFIG_H
