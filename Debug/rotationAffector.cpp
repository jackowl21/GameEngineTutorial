#include "rotationAffector.h"

RotationAffector::RotationAffector()
{

}

RotationAffector::RotationAffector(float rotationIndex)
{
	m_rotation = rotationIndex;
	m_rotation_mode = R_NORMAL;
}

RotationAffector::RotationAffector(float rotation_min, float rotation_max)
{
	m_rotation_min = rotation_min;
	m_rotation_max = rotation_max;
	m_rotation_mode = R_RANDOM;
}

RotationAffector::~RotationAffector()
{

}

void RotationAffector::affectParticle(ParticleObject * particle)
{
	if (m_rotation_mode == R_NORMAL)
		particle->p_rotation = rotationOverLife(particle->lifespan, particle->baseLifespan);
	else if(m_rotation_mode == R_RANDOM)
		particle->p_rotation = randomizeRotation();

	particle->SetParticleRotation(particle->GetParticleRotation() + particle->p_rotation);
}

float RotationAffector::randomizeRotation()
{
	float rotation = Random::randf(m_rotation_min, m_rotation_max);
	return rotation;
}

float RotationAffector::rotationOverLife(float curLifespan, float baseLifespan)
{
	return m_rotation * (1 - curLifespan / baseLifespan);
}
