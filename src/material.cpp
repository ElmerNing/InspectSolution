#include "stdafx.h"
#include "Material.h"


WeldArea::WeldArea()
{
    Default();
}

WeldArea::~WeldArea()
{
    
}

void WeldArea::Default()
{
    m_depth = 0.0f;
    m_thickness = 0.0f;
    m_division = 0;
    m_angle = 30.0f;
};

SERIALIZE_BEGIN(WeldArea)
    SERIALIZE_VAR(m_depth)
    SERIALIZE_VAR(m_thickness)
    SERIALIZE_VAR(m_division)
    SERIALIZE_VAR(m_angle)
SERIALIZE_END

DE_SERIALIZE_BEGIN(WeldArea)
    DE_SERIALIZE_VAR(m_depth)
    DE_SERIALIZE_VAR(m_thickness)
    DE_SERIALIZE_VAR(m_division)
    DE_SERIALIZE_VAR(m_angle)
DE_SERIALIZE_END

Material::Material(void)
{
    Default();
}

Material::~Material(void)
{
}

void Material::Default()
{
    m_velocity = 5200;
    m_thickness = 20;
}

SERIALIZE_BEGIN(Material)
    SERIALIZE_VAR(m_velocity)
    SERIALIZE_VAR(m_thickness)
SERIALIZE_END

DE_SERIALIZE_BEGIN(Material)
    DE_SERIALIZE_VAR(m_velocity)
    DE_SERIALIZE_VAR(m_thickness)
DE_SERIALIZE_END
