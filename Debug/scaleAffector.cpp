#include "scaleAffector.h"

ScaleAffector::ScaleAffector()
{

}

ScaleAffector::ScaleAffector(ScaleMode scaleType, float startSize, float endSize)
{
	m_size_start = startSize;
	m_size_end = endSize;
	m_scale_mode = scaleType;
}

ScaleAffector::~ScaleAffector()
{
}

void ScaleAffector::affectParticle(ParticleObject * particle)
{
	if (m_scale_mode == S_INTERPOLATE)
	{
		particle->SetParticleSize(interpolateScaleOverLife(m_size_start, m_size_end, particle->lifespan, particle->baseLifespan));
	}
	else if (m_scale_mode == S_PULSATE)
	{
		particle->SetParticleSize(pulsateScale(particle));
	}
		
}

float ScaleAffector::interpolateScaleOverLife(float startSize, float endSize, float curLifespan, float baseLifespan)
{

	if (startSize < endSize)
	{
		return (startSize - endSize * curLifespan / baseLifespan) + endSize;
	}
	else
	{
		return (endSize - startSize * curLifespan / baseLifespan) + endSize;
	}
		
}

float ScaleAffector::pulsateScale(ParticleObject * particle)
{
	float size = m_size_end * sin(particle->baseLifespan - particle->lifespan * 10.0f) + m_size_start;
	return size;
}
