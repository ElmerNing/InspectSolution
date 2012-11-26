#ifndef SCSOLUTION_H
#define SCSOLUTION_H

#include "solution.h"
#include "scgrouplaw.h"
#include "qobjvector.h"

class SCsolution : public Solution
{
public:
    SCsolution(QObject *parent = NULL);
    ~SCsolution();

public:
    const SCgroupLawVector& GroupLaws() const {return m_groupLaws;}
    SCgroupLawVector& GroupLaws() {return m_groupLaws;}


private:
    SCgroupLawVector m_groupLaws;

    SERIALIZE_ENABLE_CLASS(SCsolution);
};

#endif // SCSOLUTION_H
