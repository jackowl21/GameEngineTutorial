#include "gravityAffector.h"

GravityAffector::GravityAffector()
{
}

GravityAffector::GravityAffector(float gravityScale, int gravityDirection_y)
{
	m_gravity_scale = gravityScale;
	m_gravity_dirction_y = gravityDirection_y;
	m_gravity_mode = G_OVERLIFE;
}

GravityAffector::GravityAffector(float gravityScale, Vector3 gravityPoint, GravityOrbitType gravityOrbitType)
{
	m_gravity_scale = gravityScale;
	m_gravity_position = gravityPoint;
	m_gravity_mode = G_ORBIT;
	m_gravity_orbit_type = gravityOrbitType;
}

GravityAffector::~GravityAffector()
{
}

void GravityAffector::affectParticle(ParticleObject * particle)
{
	if (m_gravity_mode == G_OVERLIFE)
	{
		particle->p_acceleration = gravityOverLife(particle->lifespan, particle->baseLifespan, m_gravity_dirction_y);
	}
	else if (m_gravity_mode == G_ORBIT)
	{
		if (m_gravity_orbit_type == G_TYPE_1)
			particle->p_acceleration = gravityAttractor(particle);
		else if (m_gravity_orbit_type == G_TYPE_2)
			particle->p_acceleration = gravityOrbit(particle);
	}
	
	particle->SetParticleMotion();
}

Vector3 GravityAffector::gravityOverLife(float curLifespan, float baseLifespan, int gDir)
{
	float gForce = gDir * m_gravity_scale * (1 - curLifespan / baseLifespan);
	return Vector3(0, gForce, 0);
}

Vector3 GravityAffector::gravityOrbit(ParticleObject * particle)
{
	float x = m_gravity_scale;
	float y = m_gravity_scale;

	if (particle->GetParticlePos().m_x > m_gravity_position.m_x)
	{
		x = m_gravity_scale * -1;
	}
	else
	{
		x = m_gravity_scale;
	}

	if (particle->GetParticlePos().m_y > m_gravity_position.m_y)
	{
		y = m_gravity_scale * -1;
	}
	else
	{
		y = m_gravity_scale;
	}

	return Vector3(x, y, 0);
}

Vector3 GravityAffector::gravityAttractor(ParticleObject * particle)
{
	float tempX = m_gravity_position.m_x - particle->GetParticlePos().m_x;
	float tempY = m_gravity_position.m_y - particle->GetParticlePos().m_y;

	return Vector3(tempX * m_gravity_scale, tempY * m_gravity_scale, 0);
}


