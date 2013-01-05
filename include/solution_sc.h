#ifndef SCSOLUTION_H
#define SCSOLUTION_H
#include "gconfig.h"
#include "grouplaw_sc.h"
#include "material.h"
#include "wedge.h"
#include "probe.h"

class Data_sc
{
public:
    Data_sc();
    ~Data_sc();


};

//StripChart��solution
class Solution_sc
{
public:
    Solution_sc();
    ~Solution_sc();

    //����m_weld,���ɽ������
    bool AutoGenerate();
    GroupLaw_sc* GetGroupLaw(const WeldFill& fill );
    GroupLaw_sc* GetGroupLaw(int index);

private:
    void PaProbeOffset();
    QRangeF PaProbeOffset_helper(const WeldArea& area);

public:
    Gconfig m_config;
    Material m_material;
    QMap<ProbeChannel, Probe> m_probes;
    QMap<ProbeChannel, Wedge> m_wedges;
    QMap<ProbeChannel, float> m_offset;
    QMap<WeldAreaType, WeldArea> m_weldArea;
    QVector<GroupLaw_sc> m_groupLaws;

private:
    SERIALIZE_ENABLE_CLASS(Solution_sc);
};


#endif // SCSOLUTION_H
