#include "stdafx.h"
#include "Material.h"


Weld::Weld(void)
{
}

Weld::~Weld(void)
{
}


SERIALIZE_BEGIN(Weld)
    SERIALIZE_VAR(m_velocity)
SERIALIZE_END

DE_SERIALIZE_BEGIN(Weld)
    DE_SERIALIZE_VAR(m_velocity)
DE_SERIALIZE_END
