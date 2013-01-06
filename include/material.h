#ifndef MATERIAL_H__
#define MATERIAL_H__

#include "stdafx.h"

enum WeldAreaType
{
    WA_ROOT,
    WA_FILL,
    WA_CAP,
};
SERIALIZE_ENABLE_ENUM(WeldAreaType);

struct WeldFill
{
    WeldFill(WeldAreaType _type = WeldAreaType::WA_ROOT, int _index = 0) 
    {
        type = _type; index = _index;
    }
    friend inline bool operator==(const WeldFill & w1, const WeldFill & w2)
    {
        return (w1.type == w2.type && w1.index == w2.index);
    }
    WeldAreaType type;
    int index;
    SERIALIZE_ENABLE_CLASS(WeldFill);
};

class WeldArea
{
public:
    WeldArea();
    ~WeldArea();
    void Default();
    float Depth() const { return m_depth; }
    void Depth(float val) { m_depth = val; }
    float Thickness() const { return m_thickness; }
    void Thickness(float val) { m_thickness = val; }
    int Division() const { return m_division; }
    void Division(int val) { m_division = val; }
    float Angle() const { return m_angle; }
    void Angle(float val) { m_angle = val; }
    
private:
    float m_depth;
    float m_thickness;
    int m_division;
    float m_angle;
    SERIALIZE_ENABLE_CLASS(WeldArea);
};

class Material
{
public:
    Material(void);
    ~Material(void);
    void Default();
    //声速
    float Velocity() const {return m_velocity;}
    void Velocity(float velocity)  {m_velocity = velocity;}
    //厚度
    float Thickness() const { return m_thickness; }
    void Thickness(float val) { m_thickness = val; }

private:
    
    //声速
    float m_velocity;
    float m_thickness;
    
    SERIALIZE_ENABLE_CLASS(Material);
};

#endif // material_h__
