#include "include/LightSource.hpp"

LightSource::LightSource() {}
LightSource::LightSource(const RT_Vec3& pos, const RT_Vec3& ka, \
	const RT_Vec3& kd, const RT_Vec3& ks):
  	m_Position(pos), m_Ka(ka), m_Kd(kd), m_Ks(ks) {}

void LightSource::setPosition(const RT_Vec3& pos)
{
	m_Position=pos;
}

void LightSource::setKa(const RT_Vec3& ka)
{
    m_Ka=ka;
}

void LightSource::setKd(const RT_Vec3& kd)
{
    m_Kd=kd;
}

void LightSource::setKs(const RT_Vec3& ks)
{
    m_Ks=ks;
}

RT_Vec3 LightSource::getPosition() const
{
    return m_Position;
}

RT_Vec3 LightSource::getKa() const
{
    return m_Ka;
}

RT_Vec3 LightSource::getKd() const
{
    return m_Kd;
}

RT_Vec3 LightSource::getKs() const
{
    return m_Ks;
}
