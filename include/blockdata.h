#ifndef blockdata_h__
#define blockdata_h__

#include "stdafx.h"
#include "groupdata.h"

class BlockInfo;

//数据块
class BlockData
{
public:
    BlockData();
    ~BlockData();

    //初始化block
    void Init(uchar* data, const BlockInfo& info);

    //返回数据的起始地址
    const uchar* Data() const { return m_data; }
    uchar* Data() { return m_data; }
    
    inline GroupData& operator[](int index) { return m_groups[index]; }
private:
    QVector<GroupData> m_groups;
    uchar* m_data;

    SERIALIZE_ENABLE_CLASS(BlockInfo)
};

//每个数据块的相关信息
class BlockInfo
{
public:
    //grpNum,block包含的组数
    BlockInfo(int grpQty = 0)
    {
        m_beamQty.resize(grpQty);
        m_beamPointQty.resize(grpQty);
    }

    void SetGrpQty(int grpQty)
    {
        m_beamQty.resize(grpQty);
        m_beamPointQty.resize(grpQty);
    }

    //组的个数
    int GetGrpQty() const { return m_beamQty.size(); }

    //设置grpId的组的相关参数; beamnum:grp包含的beam数量; samplePtNum:每个beam的采样点数
    void SetGrp(int grpId, int beamNum, int beamPoints)
    {
        Q_ASSERT(grpId>=0 && grpId < m_beamQty.size());
        m_beamQty[grpId] = beamNum;
        m_beamPointQty[grpId] = beamPoints;
    }

    //grp的beam数量
    int GetBeamQty(int grpId) const
    {
        Q_ASSERT(grpId>=0 && grpId < m_beamQty.size());
        return m_beamQty[grpId];
    }

    //每个beam的采样点数
    int GetBeamPointQty(int grpId) const
    {
        Q_ASSERT(grpId>=0 && grpId < m_beamQty.size());
        return m_beamPointQty[grpId];
    }

    //每个组的数据所占空间大小
    int GetGrpDataSize(int grpId) const
    {
        Q_ASSERT(grpId>=0 && grpId < m_beamQty.size());
        return (m_beamPointQty[grpId] + BeamData::BEAM_PONIT_DELT) * m_beamQty[grpId];
    }

    int GetBlockSize() const
    {
        int blockSize = 0;
        for(int i=0; i<GetGrpQty(); i++)
        {
            blockSize += GetGrpDataSize(i);
        }
        return blockSize;
    }

private:
    QVector<int> m_beamQty;
    QVector<int> m_beamPointQty;

    SERIALIZE_ENABLE_CLASS(BlockInfo)
};

#endif // blockdata_h__
