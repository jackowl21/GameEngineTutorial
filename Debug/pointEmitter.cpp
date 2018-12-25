#include "pointEmitter.h"

PointEmitter::PointEmitter()
{

}

PointEmitter::PointEmitter(float v_min_x, float v_max_x, float v_min_y, float v_max_y, float a_min_x, float a_max_x, float a_min_y, float a_max_y)
{
	SetVelocity(v_min_x, v_max_x, v_min_y, v_max_y);
	SetAcceleration(a_min_x, a_max_x, a_min_y, a_max_y);
}

PointEmitter::~PointEmitter()
{

}

void PointEmitter::emitParticle(std::list<ParticleObject*> &particleList, Sprite* sprite, float lifespan, float particleScale_min, float particleScale_max,
	Vector3 position, float emissionLevel)
{
	SetStartMotion();

	Vector3 velocity = Vector3(m_velocity_start.m_x * emissionLevel, m_velocity_start.m_y * emissionLevel, 0.0f);
	particleList.push_back(new ParticleObject(sprite, lifespan, SetStartScale(particleScale_min, particleScale_max), position, velocity, m_acceleration_start));
}

/*void PointEmitter::emitParticle2(std::list<ParticleObject*>& particleList, Sprite * sprite, float lifespan, float particleScale, Vector3 position, Vector3 velocity, Vector3 acceleration)
{
	particleList.push_back(new ParticleObject(sprite, lifespan, particleScale, position, velocity, acceleration));
}*/
