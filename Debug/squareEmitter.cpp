#include "squareEmitter.h"

SquareEmitter::SquareEmitter()
{

}

SquareEmitter::SquareEmitter(float width, float height, float v_min_x, float v_max_x, float v_min_y, float v_max_y, float a_min_x, float a_max_x, float a_min_y, float a_max_y)
{
	m_width = width;
	m_height = height;
	SetVelocity(v_min_x, v_max_x, v_min_y, v_max_y);
	SetAcceleration(a_min_x, a_max_x, a_min_y, a_max_y);
}

SquareEmitter::~SquareEmitter()
{
}

void SquareEmitter::emitParticle(std::list<ParticleObject*>& particleList, Sprite * sprite, 
	float lifespan, float particleScale_min, float particleScale_max, Vector3 position, float emissionLevel)
{
	SetStartMotion();

	float width = Random::randf(-m_width/2, m_width/2);
	float height = Random::randf(-m_height/2, m_height/2);

	Vector3 finalPosition = position + Vector3(width, height, 0);

	particleList.push_back(new ParticleObject(sprite, lifespan, SetStartScale(particleScale_min, particleScale_max), finalPosition,
		m_velocity_start, m_acceleration_start));
}

