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

//���л�
SERIALIZE_BEGIN(Focalaw)
    SERIALIZE_VAR(m_groupLaws);
SERIALIZE_END

//�����л�
DE_SERIALIZE_BEGIN(Focalaw)
    DE_SERIALIZE_VAR(m_groupLaws);
DE_SERIALIZE_END