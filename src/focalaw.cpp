#include "stdafx.h"
#include "focalaw.h"
#include "grouplaw.h"


Focalaw::Focalaw(QObject *parent) :
    SolutionModule(parent),
    m_groupLaws(this)
{
    Default();
}

Focalaw::~Focalaw()
{

}

void Focalaw::Default()
{
}

//序列化
SERIALIZE_BEGIN(Focalaw)
    SERIALIZE_VAR(m_groupLaws);
SERIALIZE_END

//反序列化
DE_SERIALIZE_BEGIN(Focalaw)
    DE_SERIALIZE_VAR(m_groupLaws);
DE_SERIALIZE_END