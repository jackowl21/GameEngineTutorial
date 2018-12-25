#include "particleEmitter.h"

ParticleEmitter::ParticleEmitter()
{

}

ParticleEmitter::~ParticleEmitter()
{

}

void ParticleEmitter::SetVelocity(float v_min_x, float v_max_x, float v_min_y, float v_max_y)
{
	m_velocity_min_x = v_min_x;
	m_velocity_max_x = v_max_x;

	m_velocity_min_y = v_min_y;
	m_velocity_max_y = v_max_y;
}

void ParticleEmitter::SetAcceleration(float a_min_x, float a_max_x, float a_min_y, float a_max_y)
{
	m_acceleration_min_x = a_min_x;
	m_acceleration_max_x = a_max_x;

	m_acceleration_min_y = a_min_y;
	m_acceleration_max_y = a_max_y;
}

void ParticleEmitter::SetStartMotion()
{
	float v_X = Random::randf(m_velocity_min_x, m_velocity_max_x);
	float v_Y = Random::randf(m_velocity_min_y, m_velocity_max_y);

	float a_X = Random::randf(m_acceleration_min_x, m_acceleration_max_x);
	float a_Y = Random::randf(m_acceleration_min_y, m_acceleration_max_y);

	m_velocity_start = Vector3(v_X, v_Y, 0);
	m_acceleration_start = Vector3(a_X, a_Y, 0);
}

float ParticleEmitter::SetStartScale(float scale_min, float scale_max)
{
	return Random::randf(scale_min, scale_max);
}
