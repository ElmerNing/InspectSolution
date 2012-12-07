#include "stdafx.h"
#include "Material.h"


SERIALIZE_BEGIN(WeldArea)
    SERIALIZE_VAR(m_thickness)
    SERIALIZE_VAR(m_fillNum)
SERIALIZE_END

DE_SERIALIZE_BEGIN(WeldArea)
    DE_SERIALIZE_VAR(m_thickness)
    DE_SERIALIZE_VAR(m_fillNum)
DE_SERIALIZE_END

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
