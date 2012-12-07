#ifndef SCSOLUTION_H
#define SCSOLUTION_H
#include "gconfig.h"
#include "grouplaw_sc.h"
#include "material.h"

class SCsolution
{

public:
    SCsolution();
    ~SCsolution();

public:
    Gconfig m_config;
    Weld m_weld;
    //QMap<ProbeChannel, Probe> m_probe;
    //QMap<ProbeChannel, Wedge> m_wedge;

private:

    SERIALIZE_ENABLE_CLASS(SCsolution);
};

#endif // SCSOLUTION_H
