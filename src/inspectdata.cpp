#include "inspectdata.h"
InspectData::InspectData()
{

}


InspectData::~InspectData()
{

}

void InspectData::OnReceiveBlock( uchar* data, int index )
{
    if (index >= m_blocks.size())
    {
        for (int i=m_blocks.size(); i<=index; i++)
        {
            m_blocks.append(BlockData());
        }
    }
    m_blocks[index].Init(data, m_blockInfo);
}

QDataStream& operator<<(QDataStream& stream, const InspectData & data)
{
    stream << data.m_blocks.size();
    stream << data.m_blockInfo;
    QFile* file = (QFile*)stream.device();
    qint64 pos = file->pos();
    for (int i=0; i<data.m_blocks.size(); i++)
    {
        char* temp = (char*)data.m_blocks[i].Data();
        stream.writeRawData( temp, data.m_blockInfo.GetBlockSize() );
    }
    return stream;
}

QDataStream& operator>>(QDataStream& stream, InspectData & data)
{
    int blockQty;
    stream >> blockQty;
    stream >> data.m_blockInfo;
    int blockSize = data.m_blockInfo.GetBlockSize();

    QFile* file = (QFile*)stream.device();
    qint64 pos = file->pos();

    uchar* blocksdata = file->map(pos, blockSize*blockQty);
    file->seek(pos + blockSize*blockQty);

    for (int i=0; i<blockQty; i++)
    {
        data.OnReceiveBlock(blocksdata, i);
        blocksdata += blockSize;
    }

    return stream;
}
