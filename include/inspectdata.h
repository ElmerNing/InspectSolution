#ifndef inspectdata_h__
#define inspectdata_h__

#include "stdafx.h"
#include <QObject>
#include "blockdata.h"

class InspectData : QObject
{
    Q_OBJECT
public:
    InspectData();
    ~InspectData();

    //设置每块数据的相关信息, 使用其他
    void Init(const BlockInfo& info) { m_blockInfo = info; } 

    inline BlockData& operator[](int index) { return m_blocks[index]; }

public slots:
    void OnReceiveBlock(uchar* data, int index);

private:
    BlockInfo m_blockInfo;
    QVector<BlockData> m_blocks;

    SERIALIZE_ENABLE_CLASS(InspectData)
};

#endif // inspectdata_h__
