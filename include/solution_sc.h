#ifndef SCSOLUTION_H
#define SCSOLUTION_H
#include "gconfig.h"
#include "grouplaw_sc.h"
#include "material.h"
#include "wedge.h"
#include "probe.h"

class Solution_sc
{

public:
    Solution_sc();
    ~Solution_sc();

    //根据m_weld,生成解决方案
    bool Generate();

private:
    void PaProbeOffset();
    QRangeF PAProbeOffset_help(const WeldArea& area);

public:
    Gconfig m_config;
    Material m_material;
    QMap<ProbeChannel, Probe> m_probes;
    QMap<ProbeChannel, Wedge> m_wedges;
    QMap<WeldAreaType, WeldArea> m_weldArea;

    QVector<GroupLaw_sc> m_groupLaws;
private:
    SERIALIZE_ENABLE_CLASS(Solution_sc);
};

#endif // SCSOLUTION_H
