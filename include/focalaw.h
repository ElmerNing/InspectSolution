#ifndef FOCALAW_H
#define FOCALAW_H

#include "solutionmodule.h"
#include "qobjvector.h"

class GroupLaw;

class Focalaw : public SolutionModule
{
public:
    explicit Focalaw(QObject *parent = 0);
    virtual ~Focalaw();

    //设置为默认值,单个group
    void Default();

private:
    QObjectVector<GroupLaw> m_groupLaws;

    SERIALIZE_ENABLE_CLASS(Focalaw);
};

#endif // FOCALAW_H
