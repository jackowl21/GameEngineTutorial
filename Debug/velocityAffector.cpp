#include "velocityAffector.h"

VelocityAffector::VelocityAffector()
{

}

VelocityAffector::VelocityAffector(Vector3 start, Vector3 end)
{
	m_velocity_start = start;
	m_velocity_end = end;

	m_velocity_mode = V_OVER_LIFE;
}

VelocityAffector::VelocityAffector(float spiralIntensity, float velocity_x, float velocity_y)
{
	m_spiral_value = spiralIntensity;
	m_velocity_scale_x = velocity_x;
	m_velocity_scale_y = velocity_y;
	m_velocity_mode = V_SPIRAL_MOTION;
}

VelocityAffector::VelocityAffector(float maxX, float minX, float maxY, float minY)
{
	m_velocity_x_max = maxX;
	m_velocity_x_min = minX;

	m_velocity_y_max = maxY;
	m_velocity_y_min = minY;

	m_velocity_mode = V_RANDOM;
}

VelocityAffector::~VelocityAffector()
{
}

void VelocityAffector::affectParticle(ParticleObject * particle)
{
	if (m_velocity_mode == V_OVER_LIFE)
	{
		//particle->p_velocity = velocityOverLife(particle->lifespan, particle->baseLifespan);
		particle->SetParticleVelocity(velocityOverLife(particle->lifespan, particle->baseLifespan));
	}	
	else if (m_velocity_mode == V_RANDOM)
	{
		//particle->p_velocity = randomizeVelocity();
		//particle->GetParticleVelocity() = randomizeVelocityOverLife(particle->lifespan, particle->baseLifespan);
		particle->SetParticleVelocity(randomizeVelocityOverLife(particle->lifespan, particle->baseLifespan));
	}
	else if (m_velocity_mode == V_SPIRAL_MOTION)
	{
		//particle->p_velocity = spiralMotion(particle->lifespan, particle->baseLifespan);
		particle->SetParticleVelocity(spiralMotion(particle->lifespan, particle->baseLifespan));
	}
	
	
	particle->SetParticleMotion();
}

Vector3 VelocityAffector::velocityOverLife(float curLifespan, float baseLifespan)
{
	float ratio = 1 - curLifespan / baseLifespan;

	if (ratio <= 0)
	{
		ratio = 0;
	}

	return ((m_velocity_end - m_velocity_start) * ratio) + m_velocity_start;
}

Vector3 VelocityAffector::randomizeVelocity()
{
	float v_X = Random::randf(m_velocity_x_min, m_velocity_x_max);
	float v_Y = Random::randf(m_velocity_y_min, m_velocity_y_max);

	return Vector3(v_X, v_Y, 0);
}

Vector3 VelocityAffector::randomizeVelocityOverLife(float curLifespan, float baseLifespan)
{
	float v_X = Random::randf(m_velocity_x_min, m_velocity_x_max);
	float v_Y = Random::randf(m_velocity_y_min, m_velocity_y_max);

	v_X *= (1 - curLifespan / baseLifespan);
	v_Y *= (1 - curLifespan / baseLifespan);

	return Vector3(v_X, v_Y, 0.0f);
}

Vector3 VelocityAffector::spiralMotion(float curLifespan, float baseLifespan)
{
	float ratio = 1 - (curLifespan / baseLifespan);
	float v_x = ratio * sin((baseLifespan + (curLifespan)) * m_spiral_value)  * m_velocity_scale_x;
	float v_y = ratio * cos((baseLifespan + (curLifespan)) * m_spiral_value)  * m_velocity_scale_y;
	return Vector3(v_x, v_y, 0);
}


