#include "circleEmitter.h"

CircleEmitter::CircleEmitter()
{

}


CircleEmitter::CircleEmitter(float radius, float v_min_x, float v_max_x, float v_min_y, float v_max_y, float a_min_x, float a_max_x, float a_min_y, float a_max_y)
{
	m_radius = radius;
	SetVelocity(v_min_x, v_max_x, v_min_y, v_max_y);
	SetAcceleration(a_min_x, a_max_x, a_min_y, a_max_y);
}

CircleEmitter::~CircleEmitter()
{
}

void CircleEmitter::emitParticle(std::list<ParticleObject*> &particleList, Sprite * sprite,
	float lifespan, float particleScale_min, float particleScale_max, Vector3 position, float emissionLevel)
{
	float randRadius = Random::randf(-m_radius, m_radius);
	float randDegree = Random::randf(1, 361);

	float circleRandX = randRadius * cos(randDegree);
	float circleRandY = randRadius * sin(randDegree);

	Vector3 finalPosition = position + Vector3(circleRandX, circleRandY, 0);

	SetStartMotion();
	particleList.push_back(new ParticleObject(sprite, lifespan, SetStartScale(particleScale_min, particleScale_max), finalPosition,
		m_velocity_start, m_acceleration_start));
}


