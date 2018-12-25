#include "particleObject.h"

ParticleObject::ParticleObject()
{
	SetSprite(new Sprite("../media/SimpleRadial.png"));
	
	SetScale(0.02f);
	SetColor(m_color.blue);
	SetBlendingMode(BLEND_ADDITIVE);
	SetPos(Vector3(300, 300, 0));
	SetVelocity(Vector3(0, -10, 0));

}

ParticleObject::ParticleObject(Sprite * sprite, float life, float scale,
	Vector3 pos, Vector3 velocity, Vector3 acceleration) : GameObject(sprite)
{
	lifespan = life;
	baseLifespan = lifespan;
	p_acceleration = acceleration;
	SetPos(pos);
	SetScale(scale);
	SetColor(Color(0.0f, 0.8f, 1.0f, 1.0f));
	SetBlendingMode(BLEND_ADDITIVE);
	SetVelocity(velocity + acceleration);
}

ParticleObject::~ParticleObject()
{

}

void ParticleObject::update(float deltaTime)
{
	SetVelocity(GetParticleVelocity() + p_acceleration);

	move();
	draw();
	lifespan -= deltaTime;
}

void ParticleObject::SetParticleColor(const Color & color)
{
	SetColor(color);
}

void ParticleObject::SetParticleSize(float size)
{
	SetScale(size);
}

void ParticleObject::SetParticleMotion()
{
	Vector3 tempVelocity = GetVelocity();
	SetVelocity(tempVelocity + p_acceleration);
}

void ParticleObject::SetParticleVelocity(Vector3 velocity)
{
	SetVelocity(velocity);
}

void ParticleObject::SetParticleRotation(float rotation)
{
	SetRotation(rotation);
}

Vector3 ParticleObject::GetParticlePos()
{
	return GetPos();
}

Vector3 ParticleObject::GetParticleVelocity()
{
	return GetVelocity();
}

float ParticleObject::GetParticleRotation()
{
	return GetRotation();
}
