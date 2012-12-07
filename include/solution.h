#ifndef SOLUTION_H
#define SOLUTION_H

#include "gconfig.h"
#include "grouplaw.h"
#include "focalaw.h"
#include "beamlaw.h"
#include "probe.h"
#include "wedge.h"

class Solution : public QObject
{
public:
    explicit Solution(QObject* parent = NULL);
    virtual ~Solution();
    void Default();
    int Prf();
    void Prf(int prf);
    void PrfRange();

    float Velocity();
    void Velocity(float v);

public:
    //æ€Ωπ∑®‘Ú
    Gconfig m_config;
    QMap<ProbeChannel, Probe*> m_probe;
    QMap<ProbeChannel, Wedge*> m_wedge;
    float m_velocity;

    SERIALIZE_ENABLE_CLASS(Solution);
};

#endif // SOLUTION_H
