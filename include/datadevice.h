#ifndef datadevice_h__
#define datadevice_h__

#include <QFile>
#include "inspectdata.h"
//数据采集设备, 基类,
class DataDevice
{
public:
    //打开一个设备,并指定读或写
    virtual bool Open(QString) = 0;
    //将设备关联至带读写数据,并开始读写.
    virtual bool Connect(InspectData) = 0;
    //关闭设备
    virtual void Close() = 0;
signals:
    virtual void GetOneBlock(uchar*, int) = 0;
};

//通过文件打开
class DataFileDevice 
{

};

//数据采集, Net
class DataNetDevice
{

};

//数据采集DMA
class DataDmaDevice
{

};

#endif // datadevice_h__