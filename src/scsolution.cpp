#include "stdafx.h"
#include "scsolution.h"

SCsolution::SCsolution(QObject *parent)
    : Solution(parent)
    , m_groupLaws(this)
{

}

SCsolution::~SCsolution()
{

}

SERIALIZE_BEGIN(SCsolution)
    SERIALIZE_BASE(Solution)
    SERIALIZE_VAR(m_groupLaws)
SERIALIZE_END

DE_SERIALIZE_BEGIN(SCsolution)
    DE_SERIALIZE_BASE(Solution)
    DE_SERIALIZE_VAR(m_groupLaws)
DE_SERIALIZE_END