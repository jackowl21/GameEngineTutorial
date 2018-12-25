#include "ringEmitter.h"

RingEmitter::RingEmitter()
{
}

RingEmitter::RingEmitter(float radius)
{
	m_radius = radius;
}

RingEmitter::RingEmitter(float radius, float v_min_x, float v_max_x,
	float v_min_y, float v_max_y, float a_min_x, float a_max_x, float a_min_y, float a_max_y)
{
	m_radius = radius;
	SetVelocity(v_min_x, v_max_x, v_min_y, v_max_y);
	SetAcceleration(a_min_x, a_max_x, a_min_y, a_max_y);
}

RingEmitter::~RingEmitter()
{
}

void RingEmitter::emitParticle(std::list<ParticleObject*>& particleList, Sprite * sprite,
	float lifespan, float particleScale_min, float particleScale_max, Vector3 position, float emissionLevel)
{
	SetStartMotion();

	float randDegree2 = Random::randf(1, 361);

	float circleRandX = m_radius * cos(randDegree2);
	float circleRandY = m_radius * sin(randDegree2);

	Vector3 finalPos = position + Vector3(circleRandX, circleRandY, 0);

	particleList.push_back(new ParticleObject(sprite, lifespan, SetStartScale(particleScale_min, particleScale_max), finalPos,
		m_velocity_start, m_acceleration_start));
}


