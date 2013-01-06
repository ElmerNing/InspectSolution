#ifndef groupdata_h__
#define groupdata_h__

#include "stdafx.h"
#include "beamdata.h"

class GroupData
{
public:
    GroupData();
    ~GroupData();

    void Init(uchar* data, int beamQty, int beamPoint);

    inline BeamData& operator[](int index) { return m_beams[index]; }

private:
    QVector<BeamData> m_beams;
};

#endif // groupdata_h__